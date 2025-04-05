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
 * lcd/extui/dgus/dgus_extui.cpp
 */

#include "../../../inc/MarlinConfigPre.h"

#if HAS_DGUS_LCD_CLASSIC

#include "../ui_api.h"
#include "DGUSDisplay.h"
#include "DGUSDisplayDef.h"
#include "DGUSScreenHandler.h"

<<<<<<< HEAD
#include "../../../module/settings.h" //свое для пида

#include "../../../module/temperature.h" //свое для выключения нагрева при килл

namespace ExtUI {

  void onStartup() {
    dgusdisplay.InitDisplay();
    ScreenHandler.UpdateScreenVPData();
  }

  void onIdle() { ScreenHandler.loop(); }

  void onPrinterKilled(FSTR_P const error, FSTR_P const) {
   Temperature::disable_all_heaters(); //свое
    DGUSScreenHandlerMKS::Error(GET_TEXT_F(MSG_PLEASE_RESET), 1); //свое

   // dgusdisplay.WriteVariable(VP_ERROR_STATUS, (uint16_t)1); //Свое 
    //ScreenHandler.sendinfoscreen(GET_TEXT_F(MSG_HALTED), error, FPSTR(NUL_STR), GET_TEXT_F(MSG_PLEASE_RESET), true, true, true, true);
    //ScreenHandler.GotoScreen(DGUSLCD_SCREEN_KILL);
   // while (!ScreenHandler.loop());  // Wait while anything is left to be sent
  }

  void onMediaInserted() { TERN_(SDSUPPORT, ScreenHandler.SDCardInserted()); }
  void onMediaError()    { TERN_(SDSUPPORT, ScreenHandler.SDCardError()); }
  void onMediaRemoved()  { TERN_(SDSUPPORT, ScreenHandler.SDCardRemoved()); }

  void onPlayTone(const uint16_t frequency, const uint16_t duration) {}
=======
namespace ExtUI {

  void onStartup() {
    dgus.initDisplay();
    screen.updateScreenVPData();
  }

  void onIdle() { screen.loop(); }

  void onPrinterKilled(FSTR_P const error, FSTR_P const) {
    screen.sendInfoScreen(GET_TEXT_F(MSG_HALTED), error, FPSTR(NUL_STR), GET_TEXT_F(MSG_PLEASE_RESET), true, true, true, true);
    screen.gotoScreen(DGUS_SCREEN_KILL);
    while (!screen.loop());  // Wait while anything is left to be sent
  }

  void onMediaMounted() { TERN_(HAS_MEDIA, screen.sdCardInserted()); }
  void onMediaError()   { TERN_(HAS_MEDIA, screen.sdCardError()); }
  void onMediaRemoved() { TERN_(HAS_MEDIA, screen.sdCardRemoved()); }

  void onHeatingError(const heater_id_t header_id) {}
  void onMinTempError(const heater_id_t header_id) {}
  void onMaxTempError(const heater_id_t header_id) {}

  void onPlayTone(const uint16_t frequency, const uint16_t duration/*=0*/) {}
>>>>>>> origin/release-2.1.3-beta2
  void onPrintTimerStarted() {}
  void onPrintTimerPaused() {}
  void onPrintTimerStopped() {}
  void onFilamentRunout(const extruder_t extruder) {}

  void onUserConfirmRequired(const char * const msg) {
    if (msg) {
<<<<<<< HEAD
      ScreenHandler.sendinfoscreen(F("Please confirm."), nullptr, msg, nullptr, true, true, false, true);
      ScreenHandler.SetupConfirmAction(setUserConfirmed);
      ScreenHandler.GotoScreen(DGUSLCD_SCREEN_POPUP);
    }
    else if (ScreenHandler.getCurrentScreen() == DGUSLCD_SCREEN_POPUP) {
      ScreenHandler.SetupConfirmAction(nullptr);
      ScreenHandler.PopToOldScreen();
    }
  }

  void onStatusChanged(const char * const msg) { ScreenHandler.setstatusmessage(msg); }

  void onHomingStart() {}
  void onHomingDone() {}
=======
      screen.sendInfoScreen(F("Please confirm."), nullptr, msg, nullptr, true, true, false, true);
      screen.setupConfirmAction(setUserConfirmed);
      screen.gotoScreen(DGUS_SCREEN_POPUP);
    }
    else if (screen.getCurrentScreen() == DGUS_SCREEN_POPUP) {
      screen.setupConfirmAction(nullptr);
      screen.popToOldScreen();
    }
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

  void onStatusChanged(const char * const msg) { screen.setStatusMessage(msg); }

  void onHomingStart() {}
  void onHomingDone() {}

>>>>>>> origin/release-2.1.3-beta2
  void onPrintDone() {}

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
    }

    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const probe_state_t state) {
      // Called to indicate a special condition
    }
  #endif

<<<<<<< HEAD
  #if ENABLED(POWER_LOSS_RECOVERY)
    void onPowerLossResume() {
      // Called on resume from power-loss
      IF_DISABLED(DGUS_LCD_UI_MKS, ScreenHandler.GotoScreen(DGUSLCD_SCREEN_POWER_LOSS));
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
    void onPowerLossResume() {
      // Called on resume from power-loss
      IF_DISABLED(DGUS_LCD_UI_MKS, screen.gotoScreen(DGUS_SCREEN_POWER_LOSS));
>>>>>>> origin/release-2.1.3-beta2
    }
  #endif

  #if HAS_PID_HEATING
<<<<<<< HEAD
    void onPidTuning(const result_t rst, int heater_type, int cycles , int ncycles ) {
      // Called for temperature PID tuning result
      const char* statusMessage = nullptr;
      char buf[20];  
      bool screen = 0;
      switch (rst) {
        case PID_TUNING_CYCLE: 
          sprintf_P(buf, PSTR("%s %d / %d"), GET_TEXT(MSG_PID_CYCLE), cycles, ncycles);
          dgusdisplay.WriteString(VP_PID_AUTOTUNE_CYCLES, buf, 20);
          screen = 1;
          break;

        case PID_STARTED:
           if (heater_type == 0 || heater_type == 1)
            statusMessage = GET_TEXT(MSG_PID_AUTOTUNE_E);
            else if (heater_type == -1 )
            statusMessage = GET_TEXT(MSG_PID_AUTOTUNE_BED);
            else 
            statusMessage = GET_TEXT(MSG_PID_AUTOTUNE);
            screen = 1;
            break;
        case PID_BAD_EXTRUDER_NUM:
            statusMessage = GET_TEXT(MSG_PID_BAD_EXTRUDER_NUM);
            break;
        case PID_TEMP_TOO_HIGH:
            statusMessage = GET_TEXT(MSG_PID_TEMP_TOO_HIGH);
            break;
        case PID_TUNING_TIMEOUT:
            statusMessage = GET_TEXT(MSG_PID_TIMEOUT);
            break;
        case PID_DONE:
            statusMessage = GET_TEXT(MSG_PID_AUTOTUNE_DONE);
            settings.save();
            break;
        case PID_TUNING_ABORT:
            statusMessage = GET_TEXT(MSG_PID_AUTOTUNE_ABORTED);
            break;
      }
      if (statusMessage) 
        dgusdisplay.WriteString(VP_PID_AUTOTUNE_STATUS, statusMessage, VP_SD_FileName_LEN);
      if (screen)
        ScreenHandler.GotoScreen(MKSLCD_PID_PROCESS);
      else
        ScreenHandler.GotoScreen(MKSLCD_PID_COMPLETE);
   
    
    

    }    
  #endif
    
  void onSteppersDisabled() {}
  void onSteppersEnabled()  {}
=======
    void onPIDTuning(const pidresult_t rst) {
      // Called for temperature PID tuning result
      switch (rst) {
        case PID_STARTED:
        case PID_BED_STARTED:
        case PID_CHAMBER_STARTED:
          screen.setStatusMessage(GET_TEXT_F(MSG_PID_AUTOTUNE));
          break;
        case PID_BAD_HEATER_ID:
          screen.setStatusMessage(GET_TEXT_F(MSG_PID_BAD_HEATER_ID));
          break;
        case PID_TEMP_TOO_HIGH:
          screen.setStatusMessage(GET_TEXT_F(MSG_PID_TEMP_TOO_HIGH));
          break;
        case PID_TUNING_TIMEOUT:
          screen.setStatusMessage(GET_TEXT_F(MSG_PID_TIMEOUT));
          break;
        case PID_DONE:
          screen.setStatusMessage(GET_TEXT_F(MSG_PID_AUTOTUNE_DONE));
          break;
      }
      screen.gotoScreen(DGUS_SCREEN_MAIN);
    }
    void onStartM303(const int count, const heater_id_t hid, const celsius_t temp) {
      // Called by M303 to update the UI
    }
  #endif

  #if ENABLED(MPC_AUTOTUNE)
    void onMPCTuning(const mpcresult_t rst) {
      // Called for temperature MPC tuning result
      switch (rst) {
        case MPC_STARTED:
          screen.setStatusMessage(GET_TEXT_F(MSG_MPC_AUTOTUNE));
          break;
        case MPC_TEMP_ERROR:
          //screen.setStatusMessage(GET_TEXT_F(MSG_MPC_TEMP_ERROR));
          break;
        case MPC_INTERRUPTED:
          //screen.setStatusMessage(GET_TEXT_F(MSG_MPC_INTERRUPTED));
          break;
        case MPC_DONE:
          //screen.setStatusMessage(GET_TEXT_F(MSG_MPC_AUTOTUNE_DONE));
          break;
      }
      screen.gotoScreen(DGUS_SCREEN_MAIN);
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

#endif // HAS_DGUS_LCD_CLASSIC
