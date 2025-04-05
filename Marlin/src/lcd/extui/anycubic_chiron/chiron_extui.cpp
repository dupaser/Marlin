/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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

/**
 * lcd/extui/anycubic_chiron/chiron_extui.cpp
 *
 * Anycubic Chiron TFT support for Marlin
 */

#include "../../../inc/MarlinConfigPre.h"

#if ENABLED(ANYCUBIC_LCD_CHIRON)

#include "../ui_api.h"
#include "chiron_tft.h"

using namespace Anycubic;

namespace ExtUI {

<<<<<<< HEAD
  void onStartup() { Chiron.Startup(); }

  void onIdle() { Chiron.IdleLoop(); }

  void onPrinterKilled(FSTR_P const error, FSTR_P const component) {
    Chiron.PrinterKilled(error, component);
  }

  void onMediaInserted() { Chiron.MediaEvent(AC_media_inserted); }
  void onMediaError()    { Chiron.MediaEvent(AC_media_error);    }
  void onMediaRemoved()  { Chiron.MediaEvent(AC_media_removed);  }

  void onPlayTone(const uint16_t frequency, const uint16_t duration) {
=======
  void onStartup() { chiron.startup(); }

  void onIdle() { chiron.idleLoop(); }

  void onPrinterKilled(FSTR_P const error, FSTR_P const component) {
    chiron.printerKilled(error, component);
  }

  void onMediaMounted() { chiron.mediaEvent(AC_media_inserted); }
  void onMediaError()   { chiron.mediaEvent(AC_media_error);    }
  void onMediaRemoved() { chiron.mediaEvent(AC_media_removed);  }

  void onHeatingError(const heater_id_t header_id) {}
  void onMinTempError(const heater_id_t header_id) {}
  void onMaxTempError(const heater_id_t header_id) {}

  void onPlayTone(const uint16_t frequency, const uint16_t duration/*=0*/) {
>>>>>>> origin/release-2.1.3-beta2
    #if ENABLED(SPEAKER)
      ::tone(BEEPER_PIN, frequency, duration);
    #endif
  }

<<<<<<< HEAD
  void onPrintTimerStarted() { Chiron.TimerEvent(AC_timer_started); }
  void onPrintTimerPaused()  { Chiron.TimerEvent(AC_timer_paused);  }
  void onPrintTimerStopped() { Chiron.TimerEvent(AC_timer_stopped); }
  void onPrintDone() {}

  void onFilamentRunout(const extruder_t)            { Chiron.FilamentRunout();             }

  void onUserConfirmRequired(const char * const msg) { Chiron.ConfirmationRequest(msg);     }
  void onStatusChanged(const char * const msg)       { Chiron.StatusChange(msg);            }
=======
  void onPrintTimerStarted() { chiron.timerEvent(AC_timer_started); }
  void onPrintTimerPaused()  { chiron.timerEvent(AC_timer_paused);  }
  void onPrintTimerStopped() { chiron.timerEvent(AC_timer_stopped); }

  void onPrintDone() {}

  void onFilamentRunout(const extruder_t)            { chiron.filamentRunout(); }

  void onUserConfirmRequired(const char * const msg) { chiron.confirmationRequest(msg); }

  // For fancy LCDs include an icon ID, message, and translated button title
  void onUserConfirmRequired(const int icon, const char * const cstr, FSTR_P const fBtn) {
    onUserConfirmRequired(cstr);
    UNUSED(icon); UNUSED(fBtn);
  }
  void onUserConfirmRequired(const int icon, FSTR_P const fstr, FSTR_P const fBtn) {
    onUserConfirmRequired(fstr);
    UNUSED(icon); UNUSED(fBtn);
  }

  #if ENABLED(ADVANCED_PAUSE_FEATURE)
    void onPauseMode(
      const PauseMessage message,
      const PauseMode mode/*=PAUSE_MODE_SAME*/,
      const uint8_t extruder/*=active_extruder*/
    ) {
      stdOnPauseMode(message, mode, extruder);
    }
  #endif

  void onStatusChanged(const char * const msg)       { chiron.statusChange(msg); }
>>>>>>> origin/release-2.1.3-beta2

  void onHomingStart() {}
  void onHomingDone() {}

  void onFactoryReset() {}

  void onStoreSettings(char *buff) {
    // Called when saving to EEPROM (i.e. M500). If the ExtUI needs
    // permanent data to be stored, it can write up to eeprom_data_size bytes
    // into buff.

    // Example:
    //  static_assert(sizeof(myDataStruct) <= eeprom_data_size);
    //  memcpy(buff, &myDataStruct, sizeof(myDataStruct));
  }

  void onLoadSettings(const char *buff) {
    // Called while loading settings from EEPROM. If the ExtUI
    // needs to retrieve data, it should copy up to eeprom_data_size bytes
    // from buff

    // Example:
    //  static_assert(sizeof(myDataStruct) <= eeprom_data_size);
    //  memcpy(&myDataStruct, buff, sizeof(myDataStruct));
  }

  void onPostprocessSettings() {
    // Called after loading or resetting stored settings
  }

<<<<<<< HEAD
  void onSettingsStored(bool success) {
=======
  void onSettingsStored(const bool success) {
>>>>>>> origin/release-2.1.3-beta2
    // Called after the entire EEPROM has been written,
    // whether successful or not.
  }

<<<<<<< HEAD
  void onSettingsLoaded(bool success) {
=======
  void onSettingsLoaded(const bool success) {
>>>>>>> origin/release-2.1.3-beta2
    // Called after the entire EEPROM has been read,
    // whether successful or not.
  }

<<<<<<< HEAD
  #if HAS_MESH
    void onLevelingStart() {}
    void onLevelingDone() {}

=======
  #if HAS_LEVELING
    void onLevelingStart() {}
    void onLevelingDone() {}
    #if ENABLED(PREHEAT_BEFORE_LEVELING)
      celsius_t getLevelingBedTemp() { return LEVELING_BED_TEMP; }
    #endif
  #endif

  #if HAS_MESH
>>>>>>> origin/release-2.1.3-beta2
    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const_float_t zval) {
      // Called when any mesh points are updated
      //SERIAL_ECHOLNPGM("onMeshUpdate() x:", xpos, " y:", ypos, " z:", zval);
    }

    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const probe_state_t state) {
      // Called to indicate a special condition
      //SERIAL_ECHOLNPGM("onMeshUpdate() x:", xpos, " y:", ypos, " state:", state);
    }
  #endif

<<<<<<< HEAD
  #if ENABLED(POWER_LOSS_RECOVERY)
    // Called on resume from power-loss
    void onPowerLossResume() { Chiron.PowerLossRecovery(); }
  #endif

  #if HAS_PID_HEATING
    void onPidTuning(const result_t rst) {
      // Called for temperature PID tuning result
    }
  #endif

  void onSteppersDisabled() {}
  void onSteppersEnabled()  {}
=======
  #if ENABLED(PREVENT_COLD_EXTRUSION)
    void onSetMinExtrusionTemp(const celsius_t) {}
  #endif

  #if ENABLED(POWER_LOSS_RECOVERY)
    void onSetPowerLoss(const bool onoff) {
      // Called when power-loss is enabled/disabled
    }
    void onPowerLoss() {
      // Called when power-loss state is detected
    }
    // Called on resume from power-loss
    void onPowerLossResume() { chiron.powerLossRecovery(); }
  #endif

  #if HAS_PID_HEATING
    void onPIDTuning(const pidresult_t rst) {
      // Called for temperature PID tuning result
    }
    void onStartM303(const int count, const heater_id_t hid, const celsius_t temp) {
      // Called by M303 to update the UI
    }
  #endif

  #if ENABLED(MPC_AUTOTUNE)
    void onMPCTuning(const mpcresult_t rst) {
      // Called for temperature MPC tuning result
    }
  #endif

  #if ENABLED(PLATFORM_M997_SUPPORT)
    void onFirmwareFlash() {}
  #endif

  void onSteppersDisabled() {}
  void onSteppersEnabled() {}
  void onAxisDisabled(const axis_t) {}
  void onAxisEnabled(const axis_t) {}
>>>>>>> origin/release-2.1.3-beta2
}

#endif // ANYCUBIC_LCD_CHIRON
