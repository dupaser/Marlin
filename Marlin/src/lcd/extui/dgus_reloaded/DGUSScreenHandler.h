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
#pragma once

#include "config/DGUS_Addr.h"
#include "config/DGUS_Data.h"
<<<<<<< HEAD
#include "config/DGUS_Screen.h"
=======
#include "config/DGUS_ScreenID.h"
>>>>>>> origin/release-2.1.3-beta2
#include "config/DGUS_Constants.h"

#include "../ui_api.h"
#include "../../../inc/MarlinConfigPre.h"

class DGUSScreenHandler {
public:
  DGUSScreenHandler() = default;

<<<<<<< HEAD
  static void Init();
  static void Ready();
  static void Loop();

  static void PrinterKilled(FSTR_P const error, FSTR_P const component);
  static void UserConfirmRequired(const char * const msg);
  static void SettingsReset();
  static void StoreSettings(char *buff);
  static void LoadSettings(const char *buff);
  static void ConfigurationStoreWritten(bool success);
  static void ConfigurationStoreRead(bool success);

  static void PlayTone(const uint16_t frequency, const uint16_t duration);
  static void MeshUpdate(const int8_t xpos, const int8_t ypos);
  static void PrintTimerStarted();
  static void PrintTimerPaused();
  static void PrintTimerStopped();
  static void FilamentRunout(const ExtUI::extruder_t extruder);

  #if ENABLED(SDSUPPORT)
    /// Marlin informed us that a new SD has been inserted.
    static void SDCardInserted();
    /// Marlin informed us that the SD Card has been removed().
    static void SDCardRemoved();
    /// Marlin informed us about a bad SD Card.
    static void SDCardError();
  #endif

  #if ENABLED(POWER_LOSS_RECOVERY)
    static void PowerLossResume();
  #endif

  #if HAS_PID_HEATING
    static void PidTuning(const ExtUI::result_t rst);
  #endif

  static void SetMessageLine(const char* msg, uint8_t line);
  static void SetMessageLinePGM(PGM_P msg, uint8_t line);

  static void SetStatusMessage(const char* msg, const millis_t duration = DGUS_STATUS_EXPIRATION_MS);
  static void SetStatusMessage(FSTR_P const msg, const millis_t duration = DGUS_STATUS_EXPIRATION_MS);

  static void ShowWaitScreen(DGUS_Screen return_screen, bool has_continue = false);

  static DGUS_Screen GetCurrentScreen();
  static void TriggerScreenChange(DGUS_Screen screen);
  static void TriggerFullUpdate();

  static void TriggerEEPROMSave();

  static bool IsPrinterIdle();

  static uint8_t debug_count;

  #if ENABLED(SDSUPPORT)
=======
  static void init();
  static void ready();
  static void loop();

  static void printerKilled(FSTR_P const error, FSTR_P const component);
  static void userConfirmRequired(const char * const msg);
  static void settingsReset();
  static void storeSettings(char *buff);
  static void loadSettings(const char *buff);
  static void configurationStoreWritten(bool success);
  static void configurationStoreRead(bool success);

  static void playTone(const uint16_t frequency, const uint16_t duration=0);
  static void meshUpdate(const int8_t xpos, const int8_t ypos);
  static void printTimerStarted();
  static void printTimerPaused();
  static void printTimerStopped();
  static void filamentRunout(const ExtUI::extruder_t extruder);

  #if HAS_MEDIA
    // Marlin informed us that a new SD has been inserted.
    static void sdCardInserted();
    // Marlin informed us that the SD Card has been removed().
    static void sdCardRemoved();
    // Marlin informed us about a bad SD Card.
    static void sdCardError();
  #endif

  #if ENABLED(POWER_LOSS_RECOVERY)
    static void powerLossResume();
  #endif

  #if HAS_PID_HEATING
    static void pidTuning(const ExtUI::pidresult_t rst);
  #endif

  static void setMessageLine(const char * const msg, const uint8_t line);
  static void setMessageLine_P(PGM_P const msg, const uint8_t line);
  static void setMessageLine(FSTR_P const msg, const uint8_t line) { setMessageLine_P(FTOP(msg), line); }

  static void setStatusMessage(const char* msg, const millis_t duration=DGUS_STATUS_EXPIRATION_MS);
  static void setStatusMessage(FSTR_P const msg, const millis_t duration=DGUS_STATUS_EXPIRATION_MS);

  static void showWaitScreen(const DGUS_ScreenID return_screenID, const bool has_continue=false);
  static void showWaitScreen(FSTR_P const msg, const DGUS_ScreenID return_screenID, const bool has_continue=false);

  static DGUS_ScreenID getCurrentScreen();
  static void triggerScreenChange(const DGUS_ScreenID screenID);
  static void triggerFullUpdate();

  static void triggerEEPROMSave();

  static bool isPrinterIdle();

  static uint8_t debug_count;

  #if HAS_MEDIA
>>>>>>> origin/release-2.1.3-beta2
    static ExtUI::FileList filelist;
    static uint16_t filelist_offset;
    static int16_t filelist_selected;
  #endif

  static DGUS_Data::StepSize offset_steps;
  static DGUS_Data::StepSize move_steps;

  static uint16_t probing_icons[2];

  static DGUS_Data::Extruder filament_extruder;
  static uint16_t filament_length;

  static char gcode[DGUS_GCODE_LEN + 1];

  static DGUS_Data::Heater pid_heater;
<<<<<<< HEAD
  static uint16_t pid_temp;
=======
  static celsius_t pid_temp;
>>>>>>> origin/release-2.1.3-beta2
  static uint8_t pid_cycles;

  static bool wait_continue;

  static bool leveling_active;

private:
<<<<<<< HEAD
  static const DGUS_Addr* FindScreenAddrList(DGUS_Screen screen);
  static bool CallScreenSetup(DGUS_Screen screen);

  static void MoveToScreen(DGUS_Screen screen, bool abort_wait = false);
  static bool SendScreenVPData(DGUS_Screen screen, bool complete_update);
=======
  static const DGUS_Addr* findScreenAddrList(const DGUS_ScreenID screenID);
  static bool callScreenSetup(const DGUS_ScreenID screenID);

  static void moveToScreen(const DGUS_ScreenID screenID, bool abort_wait=false);
  static bool sendScreenVPData(const DGUS_ScreenID screenID, bool complete_update);
>>>>>>> origin/release-2.1.3-beta2

  static bool settings_ready;
  static bool booted;

<<<<<<< HEAD
  static DGUS_Screen current_screen;
  static DGUS_Screen new_screen;
  static bool full_update;

  static DGUS_Screen wait_return_screen;
=======
  static DGUS_ScreenID current_screenID;
  static DGUS_ScreenID new_screenID;
  static bool full_update;

  static DGUS_ScreenID wait_return_screenID;
>>>>>>> origin/release-2.1.3-beta2

  static millis_t status_expire;
  static millis_t eeprom_save;

  typedef struct {
    bool initialized;
    uint8_t volume;
    uint8_t brightness;
    bool abl_okay;
  } eeprom_data_t;
};

<<<<<<< HEAD
extern DGUSScreenHandler dgus_screen_handler;

extern const char DGUS_MSG_HOMING_REQUIRED[],
                  DGUS_MSG_BUSY[],
                  DGUS_MSG_UNDEF[],
                  DGUS_MSG_HOMING[],
                  DGUS_MSG_FW_OUTDATED[],
                  DGUS_MSG_ABL_REQUIRED[];

extern const char DGUS_CMD_HOME[],
                  DGUS_CMD_EEPROM_SAVE[];
=======
extern DGUSScreenHandler screen;
>>>>>>> origin/release-2.1.3-beta2
