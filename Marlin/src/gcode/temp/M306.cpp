/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2022 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfig.h"

#if ENABLED(MPCTEMP)

#include "../gcode.h"
<<<<<<< HEAD
=======
#include "../../lcd/marlinui.h"
>>>>>>> origin/release-2.1.3-beta2
#include "../../module/temperature.h"

/**
 * M306: MPC settings and autotune
 *
<<<<<<< HEAD
 *  T                         Autotune the active extruder.
 *
 *  A<watts/kelvin>           Ambient heat transfer coefficient (no fan).
 *  C<joules/kelvin>          Block heat capacity.
 *  E<extruder>               Extruder number to set. (Default: E0)
=======
 *  E<extruder>               Extruder index. (Default: Active Extruder)
 *
 * Set MPC values manually for the specified or active extruder:
 *  A<watts/kelvin>           Ambient heat transfer coefficient (no fan).
 *  C<joules/kelvin>          Block heat capacity.
>>>>>>> origin/release-2.1.3-beta2
 *  F<watts/kelvin>           Ambient heat transfer coefficient (fan on full).
 *  H<joules/kelvin/mm>       Filament heat capacity per mm.
 *  P<watts>                  Heater power.
 *  R<kelvin/second/kelvin>   Sensor responsiveness (= transfer coefficient / heat capcity).
<<<<<<< HEAD
 */

void GcodeSuite::M306() {
  if (parser.seen_test('T')) { thermalManager.MPC_autotune(); return; }

  if (parser.seen("ACFPRH")) {
    const heater_id_t hid = (heater_id_t)parser.intval('E', 0);
    MPC_t &constants = thermalManager.temp_hotend[hid].constants;
    if (parser.seenval('P')) constants.heater_power = parser.value_float();
    if (parser.seenval('C')) constants.block_heat_capacity = parser.value_float();
    if (parser.seenval('R')) constants.sensor_responsiveness = parser.value_float();
    if (parser.seenval('A')) constants.ambient_xfer_coeff_fan0 = parser.value_float();
    #if ENABLED(MPC_INCLUDE_FAN)
      if (parser.seenval('F')) constants.fan255_adjustment = parser.value_float() - constants.ambient_xfer_coeff_fan0;
    #endif
    if (parser.seenval('H')) constants.filament_heat_capacity_permm = parser.value_float();
=======
 *
 *  With MPC_AUTOTUNE:
 *  T                         Autotune the extruder specified with 'E' or the active extruder.
 *                            S0 : Autotuning method AUTO (default)
 *                            S1 : Autotuning method DIFFERENTIAL
 *                            S2 : Autotuning method ASYMPTOTIC
 */

void GcodeSuite::M306() {
  const uint8_t e = TERN0(HAS_MULTI_EXTRUDER, parser.intval('E', active_extruder));
  if (e >= (EXTRUDERS)) {
    SERIAL_ECHOLNPGM("?(E)xtruder index out of range (0-", (EXTRUDERS) - 1, ").");
    return;
  }

  #if ENABLED(MPC_AUTOTUNE)
    if (parser.seen_test('T')) {
      Temperature::MPCTuningType tuning_type;
      const uint8_t type = parser.byteval('S', 0);
      switch (type) {
        case 1: tuning_type = Temperature::MPCTuningType::FORCE_DIFFERENTIAL; break;
        case 2: tuning_type = Temperature::MPCTuningType::FORCE_ASYMPTOTIC; break;
        default: tuning_type = Temperature::MPCTuningType::AUTO; break;
      }
      LCD_MESSAGE(MSG_MPC_AUTOTUNE);
      thermalManager.MPC_autotune(e, tuning_type);
      ui.reset_status();
      return;
    }
  #endif

  if (parser.seen("ACFPRH")) {
    MPC_t &mpc = thermalManager.temp_hotend[e].mpc;
    if (parser.seenval('P')) mpc.heater_power = parser.value_float();
    if (parser.seenval('C')) mpc.block_heat_capacity = parser.value_float();
    if (parser.seenval('R')) mpc.sensor_responsiveness = parser.value_float();
    if (parser.seenval('A')) mpc.ambient_xfer_coeff_fan0 = parser.value_float();
    #if ENABLED(MPC_INCLUDE_FAN)
      if (parser.seenval('F')) mpc.applyFanAdjustment(parser.value_float());
    #endif
    if (parser.seenval('H')) mpc.filament_heat_capacity_permm = parser.value_float();
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  M306_report(true);
}

void GcodeSuite::M306_report(const bool forReplay/*=true*/) {
<<<<<<< HEAD
  report_heading(forReplay, F("Model predictive control"));
  HOTEND_LOOP() {
    report_echo_start(forReplay);
    MPC_t& constants = thermalManager.temp_hotend[e].constants;
    SERIAL_ECHOPGM("  M306 E", e);
    SERIAL_ECHOPAIR_F(" P", constants.heater_power, 2);
    SERIAL_ECHOPAIR_F(" C", constants.block_heat_capacity, 2);
    SERIAL_ECHOPAIR_F(" R", constants.sensor_responsiveness, 4);
    SERIAL_ECHOPAIR_F(" A", constants.ambient_xfer_coeff_fan0, 4);
    #if ENABLED(MPC_INCLUDE_FAN)
      SERIAL_ECHOPAIR_F(" F", constants.ambient_xfer_coeff_fan0 + constants.fan255_adjustment, 4);
    #endif
    SERIAL_ECHOPAIR_F(" H", constants.filament_heat_capacity_permm, 4);
    SERIAL_EOL();
=======
  TERN_(MARLIN_SMALL_BUILD, return);

  report_heading(forReplay, F("Model predictive control"));
  HOTEND_LOOP() {
    report_echo_start(forReplay);
    MPC_t &mpc = thermalManager.temp_hotend[e].mpc;
    SERIAL_ECHOPGM("  M306 E", e,
                         " P", p_float_t(mpc.heater_power, 2),
                         " C", p_float_t(mpc.block_heat_capacity, 2),
                         " R", p_float_t(mpc.sensor_responsiveness, 4),
                         " A", p_float_t(mpc.ambient_xfer_coeff_fan0, 4)
    );
    #if ENABLED(MPC_INCLUDE_FAN)
      SERIAL_ECHOPGM(" F", p_float_t(mpc.fanCoefficient(), 4));
    #endif
    SERIAL_ECHOLNPGM(" H", p_float_t(mpc.filament_heat_capacity_permm, 4));
>>>>>>> origin/release-2.1.3-beta2
  }
}

#endif // MPCTEMP
