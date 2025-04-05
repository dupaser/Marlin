/**
 * Marlin 3D Printer Firmware
<<<<<<< HEAD
<<<<<<<< HEAD:Marlin/src/gcode/lcd/M256.cpp
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
========
 * Copyright (c) 2024 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>>> origin/release-2.1.3-beta2:Marlin/tests/feature/test_runout.cpp
=======
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>> origin/release-2.1.3-beta2
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
<<<<<<< HEAD
<<<<<<<< HEAD:Marlin/src/gcode/lcd/M256.cpp
=======
>>>>>>> origin/release-2.1.3-beta2
#include "../../inc/MarlinConfig.h"

#if HAS_LCD_BRIGHTNESS

#include "../gcode.h"
#include "../../lcd/marlinui.h"

/**
 * M256: Set the LCD brightness
 */
void GcodeSuite::M256() {
  if (parser.seenval('B'))
    ui.set_brightness(parser.value_int());
  else
    M256_report();
}

void GcodeSuite::M256_report(const bool forReplay/*=true*/) {
<<<<<<< HEAD
=======
  TERN_(MARLIN_SMALL_BUILD, return);
>>>>>>> origin/release-2.1.3-beta2
  report_heading_etc(forReplay, F(STR_LCD_BRIGHTNESS));
  SERIAL_ECHOLNPGM("  M256 B", ui.brightness);
}

#endif // HAS_LCD_BRIGHTNESS
<<<<<<< HEAD
========

#include "../test/unit_tests.h"

#if ENABLED(FILAMENT_RUNOUT_SENSOR)

#include <src/feature/runout.h>

MARLIN_TEST(runout, poll_runout_states) {
  FilamentSensorBase sensor;
  // Expected default value is one bit set for each extruder
  uint8_t expected = static_cast<uint8_t>(~(~0u << NUM_RUNOUT_SENSORS));
  TEST_ASSERT_EQUAL(expected, sensor.poll_runout_states());
}

#endif
>>>>>>>> origin/release-2.1.3-beta2:Marlin/tests/feature/test_runout.cpp
=======
>>>>>>> origin/release-2.1.3-beta2
