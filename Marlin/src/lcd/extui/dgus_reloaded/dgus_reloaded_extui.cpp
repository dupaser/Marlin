/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * lcd/extui/dgus_reloaded/dgus_reloaded_extui.cpp
 */

#include "../../../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if ENABLED(DGUS_LCD_UI_RELOADED)
=======
#if DGUS_LCD_UI_RELOADED
>>>>>>> origin/release-2.1.3-beta2

#include "../ui_api.h"
#include "DGUSScreenHandler.h"

namespace ExtUI {

<<<<<<< HEAD
  void onStartup() { dgus_screen_handler.Init(); }
=======
  void onStartup() { screen.init(); }
>>>>>>> origin/release-2.1.3-beta2

  void onIdle() {
    static bool processing = false;

    // Prevent recursion
    if (!processing) {
      processing = true;
<<<<<<< HEAD
      dgus_screen_handler.Loop();
=======
      screen.loop();
>>>>>>> origin/release-2.1.3-beta2
      processing = false;
    }
  }

  void onPrinterKilled(FSTR_P const error, FSTR_P const component) {
<<<<<<< HEAD
    dgus_screen_handler.PrinterKilled(error, component);
  }

  void onMediaInserted() { TERN_(SDSUPPORT, dgus_screen_handler.SDCardInserted()); }
  void onMediaError()    { TERN_(SDSUPPORT, dgus_screen_handler.SDCardError()); }
  void onMediaRemoved()  { TERN_(SDSUPPORT, dgus_screen_handler.SDCardRemoved()); }

  void onPlayTone(const uint16_t frequency, const uint16_t duration) {
    dgus_screen_handler.PlayTone(frequency, duration);
  }

  void onPrintTimerStarted() {
    dgus_screen_handler.PrintTimerStarted();
  }

  void onPrintTimerPaused() {
    dgus_screen_handler.PrintTimerPaused();
  }

  void onPrintTimerStopped() {
    dgus_screen_handler.PrintTimerStopped();
  }

  void onFilamentRunout(const extruder_t extruder) {
    dgus_screen_handler.FilamentRunout(extruder);
  }

  void onUserConfirmRequired(const char * const msg) {
    dgus_screen_handler.UserConfirmRequired(msg);
  }

  void onStatusChanged(const char * const msg) {
    dgus_screen_handler.SetStatusMessage(msg);
=======
    screen.printerKilled(error, component);
  }

  void onMediaMounted()  { TERN_(HAS_MEDIA, screen.sdCardInserted()); }
  void onMediaError()    { TERN_(HAS_MEDIA, screen.sdCardError()); }
  void onMediaRemoved()  { TERN_(HAS_MEDIA, screen.sdCardRemoved()); }

  void onHeatingError(const heater_id_t header_id) {}
  void onMinTempError(const heater_id_t header_id) {}
  void onMaxTempError(const heater_id_t header_id) {}

  void onPlayTone(const uint16_t frequency, const uint16_t duration/*=0*/) {
    screen.playTone(frequency, duration);
  }

  void onPrintTimerStarted() {
    screen.printTimerStarted();
  }

  void onPrintTimerPaused() {
    screen.printTimerPaused();
  }

  void onPrintTimerStopped() {
    screen.printTimerStopped();
  }

  void onFilamentRunout(const extruder_t extruder) {
    screen.filamentRunout(extruder);
  }

  void onUserConfirmRequired(const char * const msg) {
    screen.userConfirmRequired(msg);
  }

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

  void onStatusChanged(const char * const msg) {
    screen.setStatusMessage(msg);
>>>>>>> origin/release-2.1.3-beta2
  }

  void onHomingStart() {}
  void onHomingDone() {}
<<<<<<< HEAD
  void onPrintDone() {}

  void onFactoryReset() {
    dgus_screen_handler.SettingsReset();
  }

  void onStoreSettings(char *buff) {
    dgus_screen_handler.StoreSettings(buff);
  }

  void onLoadSettings(const char *buff) {
    dgus_screen_handler.LoadSettings(buff);
=======

  void onPrintDone() {}

  void onFactoryReset() {
    screen.settingsReset();
  }

  void onStoreSettings(char *buff) {
    screen.storeSettings(buff);
  }

  void onLoadSettings(const char *buff) {
    screen.loadSettings(buff);
>>>>>>> origin/release-2.1.3-beta2
  }

  void onPostprocessSettings() {}

<<<<<<< HEAD
  void onSettingsStored(bool success) {
    dgus_screen_handler.ConfigurationStoreWritten(success);
  }

  void onSettingsLoaded(bool success) {
    dgus_screen_handler.ConfigurationStoreRead(success);
  }

  #if HAS_MESH
    void onLevelingStart() {}
    void onLevelingDone() {}

    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const_float_t zval) {
      dgus_screen_handler.MeshUpdate(xpos, ypos);
=======
  void onSettingsStored(const bool success) {
    screen.configurationStoreWritten(success);
  }

  void onSettingsLoaded(const bool success) {
    screen.configurationStoreRead(success);
  }

  #if HAS_LEVELING
    void onLevelingStart() {}
    void onLevelingDone() {}
    #if ENABLED(PREHEAT_BEFORE_LEVELING)
      celsius_t getLevelingBedTemp() { return LEVELING_BED_TEMP; }
    #endif
  #endif

  #if HAS_MESH
    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const_float_t zval) {
      screen.meshUpdate(xpos, ypos);
>>>>>>> origin/release-2.1.3-beta2
    }

    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const probe_state_t state) {
      if (state == G29_POINT_FINISH)
<<<<<<< HEAD
        dgus_screen_handler.MeshUpdate(xpos, ypos);
    }
  #endif

  #if ENABLED(POWER_LOSS_RECOVERY)
    void onPowerLossResume() {
      // Called on resume from power-loss
      dgus_screen_handler.PowerLossResume();
=======
        screen.meshUpdate(xpos, ypos);
    }
  #endif

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
    void onPowerLossResume() {
      // Called on resume from power-loss
      screen.powerLossResume();
>>>>>>> origin/release-2.1.3-beta2
    }
  #endif

  #if HAS_PID_HEATING
<<<<<<< HEAD
    void onPidTuning(const result_t rst) {
      // Called for temperature PID tuning result
      dgus_screen_handler.PidTuning(rst);
    }
  #endif

  void onSteppersDisabled() {}
  void onSteppersEnabled()  {}
=======
    void onPIDTuning(const pidresult_t rst) {
      // Called for temperature PID tuning result
      screen.pidTuning(rst);
    }
    void onStartM303(const int count, const heater_id_t hid, const celsius_t temp) {
      // Called by M303 to update the UI
    }
  #endif

  #if ENABLED(MPC_AUTOTUNE)
    void onMPCTuning(const mpcresult_t rst) {
      // Called for temperature PID tuning result
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

#endif // DGUS_LCD_UI_RELOADED
