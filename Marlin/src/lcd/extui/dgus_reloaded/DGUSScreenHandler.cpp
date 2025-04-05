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

#include "../../../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if ENABLED(DGUS_LCD_UI_RELOADED)
=======
#if DGUS_LCD_UI_RELOADED
>>>>>>> origin/release-2.1.3-beta2

#include "DGUSScreenHandler.h"

#include "DGUSDisplay.h"
#include "definition/DGUS_ScreenAddrList.h"
#include "definition/DGUS_ScreenSetup.h"

#include "../../../gcode/queue.h"

uint8_t DGUSScreenHandler::debug_count = 0;

<<<<<<< HEAD
#if ENABLED(SDSUPPORT)
=======
#if HAS_MEDIA
>>>>>>> origin/release-2.1.3-beta2
  ExtUI::FileList DGUSScreenHandler::filelist;
  uint16_t DGUSScreenHandler::filelist_offset = 0;
  int16_t DGUSScreenHandler::filelist_selected = -1;
#endif

DGUS_Data::StepSize DGUSScreenHandler::offset_steps = DGUS_Data::StepSize::MMP1;
DGUS_Data::StepSize DGUSScreenHandler::move_steps = DGUS_Data::StepSize::MM10;

uint16_t DGUSScreenHandler::probing_icons[] = { 0, 0 };

DGUS_Data::Extruder DGUSScreenHandler::filament_extruder = DGUS_Data::Extruder::CURRENT;
uint16_t DGUSScreenHandler::filament_length = DGUS_DEFAULT_FILAMENT_LEN;

char DGUSScreenHandler::gcode[] = "";

DGUS_Data::Heater DGUSScreenHandler::pid_heater = DGUS_Data::Heater::H0;
<<<<<<< HEAD
uint16_t DGUSScreenHandler::pid_temp = DGUS_PLA_TEMP_HOTEND;
=======
celsius_t DGUSScreenHandler::pid_temp = DGUS_PLA_TEMP_HOTEND;
>>>>>>> origin/release-2.1.3-beta2
uint8_t DGUSScreenHandler::pid_cycles = 5;

bool DGUSScreenHandler::settings_ready = false;
bool DGUSScreenHandler::booted = false;

<<<<<<< HEAD
DGUS_Screen DGUSScreenHandler::current_screen = DGUS_Screen::BOOT;
DGUS_Screen DGUSScreenHandler::new_screen = DGUS_Screen::BOOT;
bool DGUSScreenHandler::full_update = false;

DGUS_Screen DGUSScreenHandler::wait_return_screen = DGUS_Screen::HOME;
=======
DGUS_ScreenID DGUSScreenHandler::current_screenID = DGUS_ScreenID::BOOT;
DGUS_ScreenID DGUSScreenHandler::new_screenID = DGUS_ScreenID::BOOT;
bool DGUSScreenHandler::full_update = false;

DGUS_ScreenID DGUSScreenHandler::wait_return_screenID = DGUS_ScreenID::HOME;
>>>>>>> origin/release-2.1.3-beta2
bool DGUSScreenHandler::wait_continue = false;

bool DGUSScreenHandler::leveling_active = false;

millis_t DGUSScreenHandler::status_expire = 0;
millis_t DGUSScreenHandler::eeprom_save = 0;

<<<<<<< HEAD
const char DGUS_MSG_HOMING_REQUIRED[] PROGMEM = "Homing required",
           DGUS_MSG_BUSY[] PROGMEM = "Busy",
           DGUS_MSG_UNDEF[] PROGMEM = "-",
           DGUS_MSG_HOMING[] PROGMEM = "Homing...",
           DGUS_MSG_FW_OUTDATED[] PROGMEM = "DWIN GUI/OS update required",
           DGUS_MSG_ABL_REQUIRED[] PROGMEM = "Auto bed leveling required";

const char DGUS_CMD_HOME[] PROGMEM = "G28",
           DGUS_CMD_EEPROM_SAVE[] PROGMEM = "M500";

void DGUSScreenHandler::Init() {
  dgus_display.Init();

  MoveToScreen(DGUS_Screen::BOOT, true);
}

void DGUSScreenHandler::Ready() {
  dgus_display.PlaySound(1);
}

void DGUSScreenHandler::Loop() {
  if (!settings_ready || current_screen == DGUS_Screen::KILL) {
    return;
  }
=======
void DGUSScreenHandler::init() {
  dgus.init();

  moveToScreen(DGUS_ScreenID::BOOT, true);
}

void DGUSScreenHandler::ready() {
  dgus.playSound(1);
}

void DGUSScreenHandler::loop() {
  if (!settings_ready || current_screenID == DGUS_ScreenID::KILL)
    return;
>>>>>>> origin/release-2.1.3-beta2

  const millis_t ms = ExtUI::safe_millis();
  static millis_t next_event_ms = 0;

<<<<<<< HEAD
  if (new_screen != DGUS_Screen::BOOT) {
    const DGUS_Screen screen = new_screen;
    new_screen = DGUS_Screen::BOOT;
    if (current_screen == screen)
      TriggerFullUpdate();
    else
      MoveToScreen(screen);
=======
  if (new_screenID != DGUS_ScreenID::BOOT) {
    const DGUS_ScreenID screenID = new_screenID;
    new_screenID = DGUS_ScreenID::BOOT;
    if (current_screenID == screenID)
      triggerFullUpdate();
    else
      moveToScreen(screenID);
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  if (!booted && ELAPSED(ms, 3000)) {
    booted = true;

<<<<<<< HEAD
    dgus_display.ReadVersions();

    if (current_screen == DGUS_Screen::BOOT)
      MoveToScreen(DGUS_Screen::HOME);
=======
    dgus.readVersions();

    if (current_screenID == DGUS_ScreenID::BOOT)
      moveToScreen(DGUS_ScreenID::HOME);
>>>>>>> origin/release-2.1.3-beta2

    return;
  }

  if (ELAPSED(ms, next_event_ms) || full_update) {
    next_event_ms = ms + DGUS_UPDATE_INTERVAL_MS;

<<<<<<< HEAD
    if (!SendScreenVPData(current_screen, full_update))
      DEBUG_ECHOLNPGM("SendScreenVPData failed");
=======
    if (!sendScreenVPData(current_screenID, full_update))
      DEBUG_ECHOLNPGM("sendScreenVPData failed");
>>>>>>> origin/release-2.1.3-beta2

    return;
  }

<<<<<<< HEAD
  if (current_screen == DGUS_Screen::WAIT
      && ((wait_continue && !wait_for_user)
          || (!wait_continue && IsPrinterIdle()))
  ) {
    MoveToScreen(wait_return_screen, true);
    return;
  }

  if (current_screen == DGUS_Screen::LEVELING_PROBING && IsPrinterIdle()) {
    dgus_display.PlaySound(3);

    SetStatusMessage(ExtUI::getMeshValid() ? F("Probing successful") : F("Probing failed"));

    MoveToScreen(DGUS_Screen::LEVELING_AUTOMATIC);
=======
  if (current_screenID == DGUS_ScreenID::WAIT
      && ((wait_continue && !wait_for_user) || (!wait_continue && isPrinterIdle()))
  ) {
    moveToScreen(wait_return_screenID, true);
    return;
  }

  if (current_screenID == DGUS_ScreenID::LEVELING_PROBING && isPrinterIdle()) {
    dgus.playSound(3);

    setStatusMessage(ExtUI::getLevelingIsValid() ? GET_TEXT_F(DGUS_MSG_PROBING_SUCCESS) : GET_TEXT_F(DGUS_MSG_PROBING_FAILED));

    moveToScreen(DGUS_ScreenID::LEVELING_AUTOMATIC);
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  if (status_expire > 0 && ELAPSED(ms, status_expire)) {
<<<<<<< HEAD
    SetStatusMessage(FPSTR(NUL_STR), 0);
    return;
  }

  if (eeprom_save > 0 && ELAPSED(ms, eeprom_save) && IsPrinterIdle()) {
    eeprom_save = 0;
    queue.enqueue_now_P(DGUS_CMD_EEPROM_SAVE);
    return;
  }

  dgus_display.Loop();
}

void DGUSScreenHandler::PrinterKilled(FSTR_P const error, FSTR_P const component) {
  SetMessageLinePGM(FTOP(error), 1);
  SetMessageLinePGM(FTOP(component), 2);
  SetMessageLinePGM(NUL_STR, 3);
  SetMessageLinePGM(GET_TEXT(MSG_PLEASE_RESET), 4);

  dgus_display.PlaySound(3, 1, 200);

  MoveToScreen(DGUS_Screen::KILL, true);
}

void DGUSScreenHandler::UserConfirmRequired(const char * const msg) {
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 1);
  dgus_screen_handler.SetMessageLine(msg, 2);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 3);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 4);

  dgus_display.PlaySound(3);

  dgus_screen_handler.ShowWaitScreen(current_screen, true);
}

void DGUSScreenHandler::SettingsReset() {
  dgus_display.SetVolume(DGUS_DEFAULT_VOLUME);
  dgus_display.SetBrightness(DGUS_DEFAULT_BRIGHTNESS);

  if (!settings_ready) {
    settings_ready = true;
    Ready();
  }

  SetStatusMessage(F("EEPROM reset"));
}

void DGUSScreenHandler::StoreSettings(char *buff) {
=======
    setStatusMessage(FPSTR(NUL_STR), 0);
    return;
  }

  if (eeprom_save > 0 && ELAPSED(ms, eeprom_save) && isPrinterIdle()) {
    eeprom_save = 0;
    queue.enqueue_now(F("M500"));
    return;
  }

  dgus.loop();
}

void DGUSScreenHandler::printerKilled(FSTR_P const error, FSTR_P const component) {
  setMessageLine(error, 1);
  setMessageLine(component, 2);
  setMessageLine_P(NUL_STR, 3);
  setMessageLine(GET_TEXT_F(MSG_PLEASE_RESET), 4);

  dgus.playSound(3, 1, 200);

  moveToScreen(DGUS_ScreenID::KILL, true);
}

void DGUSScreenHandler::userConfirmRequired(const char * const msg) {
  setMessageLine_P(NUL_STR, 1);
  setMessageLine(msg, 2);
  setMessageLine_P(NUL_STR, 3);
  setMessageLine_P(NUL_STR, 4);

  dgus.playSound(3);

  showWaitScreen(current_screenID, true);
}

void DGUSScreenHandler::settingsReset() {
  dgus.setVolume(DGUS_DEFAULT_VOLUME);
  dgus.setBrightness(DGUS_DEFAULT_BRIGHTNESS);

  if (!settings_ready) {
    settings_ready = true;
    ready();
  }

  setStatusMessage(GET_TEXT_F(DGUS_MSG_RESET_EEPROM));
}

void DGUSScreenHandler::storeSettings(char *buff) {
>>>>>>> origin/release-2.1.3-beta2
  eeprom_data_t data;

  static_assert(sizeof(data) <= ExtUI::eeprom_data_size, "sizeof(eeprom_data_t) > eeprom_data_size.");

  data.initialized = true;
<<<<<<< HEAD
  data.volume = dgus_display.GetVolume();
  data.brightness = dgus_display.GetBrightness();
  data.abl_okay = (ExtUI::getLevelingActive() && ExtUI::getMeshValid());
=======
  data.volume = dgus.getVolume();
  data.brightness = dgus.getBrightness();
  data.abl_okay = (ExtUI::getLevelingActive() && ExtUI::getLevelingIsValid());
>>>>>>> origin/release-2.1.3-beta2

  memcpy(buff, &data, sizeof(data));
}

<<<<<<< HEAD
void DGUSScreenHandler::LoadSettings(const char *buff) {
=======
void DGUSScreenHandler::loadSettings(const char *buff) {
>>>>>>> origin/release-2.1.3-beta2
  eeprom_data_t data;

  static_assert(sizeof(data) <= ExtUI::eeprom_data_size, "sizeof(eeprom_data_t) > eeprom_data_size.");

  memcpy(&data, buff, sizeof(data));

<<<<<<< HEAD
  dgus_display.SetVolume(data.initialized ? data.volume : DGUS_DEFAULT_VOLUME);
  dgus_display.SetBrightness(data.initialized ? data.brightness : DGUS_DEFAULT_BRIGHTNESS);

  if (data.initialized) {
    leveling_active = (data.abl_okay && ExtUI::getMeshValid());
=======
  dgus.setVolume(data.initialized ? data.volume : DGUS_DEFAULT_VOLUME);
  dgus.setBrightness(data.initialized ? data.brightness : DGUS_DEFAULT_BRIGHTNESS);

  if (data.initialized) {
    leveling_active = (data.abl_okay && ExtUI::getLevelingIsValid());
>>>>>>> origin/release-2.1.3-beta2
    ExtUI::setLevelingActive(leveling_active);
  }
}

<<<<<<< HEAD
void DGUSScreenHandler::ConfigurationStoreWritten(bool success) {
  if (!success)
    SetStatusMessage(F("EEPROM write failed"));
}

void DGUSScreenHandler::ConfigurationStoreRead(bool success) {
  if (!success) {
    SetStatusMessage(F("EEPROM read failed"));
  }
  else if (!settings_ready) {
    settings_ready = true;
    Ready();
  }
}

void DGUSScreenHandler::PlayTone(const uint16_t frequency, const uint16_t duration) {
  UNUSED(duration);

  if (frequency >= 1 && frequency <= 255) {
    if (duration >= 1 && duration <= 255)
      dgus_display.PlaySound((uint8_t)frequency, (uint8_t)duration);
    else
      dgus_display.PlaySound((uint8_t)frequency);
  }
}

void DGUSScreenHandler::MeshUpdate(const int8_t xpos, const int8_t ypos) {
  if (current_screen != DGUS_Screen::LEVELING_PROBING) {
    if (current_screen == DGUS_Screen::LEVELING_AUTOMATIC)
      TriggerFullUpdate();
=======
void DGUSScreenHandler::configurationStoreWritten(bool success) {
  if (!success)
    setStatusMessage(GET_TEXT_F(DGUS_MSG_WRITE_EEPROM_FAILED));
}

void DGUSScreenHandler::configurationStoreRead(bool success) {
  if (!success) {
    setStatusMessage(GET_TEXT_F(DGUS_MSG_READ_EEPROM_FAILED));
  }
  else if (!settings_ready) {
    settings_ready = true;
    ready();
  }
}

void DGUSScreenHandler::playTone(const uint16_t frequency, const uint16_t duration/*=0*/) {
  if (WITHIN(frequency, 1, 255)) {
    if (WITHIN(duration, 1, 255))
      dgus.playSound((uint8_t)frequency, (uint8_t)duration);
    else
      dgus.playSound((uint8_t)frequency);
  }
}

void DGUSScreenHandler::meshUpdate(const int8_t xpos, const int8_t ypos) {
  if (current_screenID != DGUS_ScreenID::LEVELING_PROBING) {
    if (current_screenID == DGUS_ScreenID::LEVELING_AUTOMATIC)
      triggerFullUpdate();
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  uint8_t point = ypos * GRID_MAX_POINTS_X + xpos;
  probing_icons[point < 16 ? 0 : 1] |= (1U << (point % 16));

<<<<<<< HEAD
  if (xpos >= GRID_MAX_POINTS_X - 1 && ypos >= GRID_MAX_POINTS_Y - 1 && !ExtUI::getMeshValid())
    probing_icons[0] = probing_icons[1] = 0;

  TriggerFullUpdate();
}

void DGUSScreenHandler::PrintTimerStarted() {
  TriggerScreenChange(DGUS_Screen::PRINT_STATUS);
}

void DGUSScreenHandler::PrintTimerPaused() {
  dgus_display.PlaySound(3);
  TriggerFullUpdate();
}

void DGUSScreenHandler::PrintTimerStopped() {
  if (current_screen != DGUS_Screen::PRINT_STATUS && current_screen != DGUS_Screen::PRINT_ADJUST)
    return;

  dgus_display.PlaySound(3);

  TriggerScreenChange(DGUS_Screen::PRINT_FINISHED);
}

void DGUSScreenHandler::FilamentRunout(const ExtUI::extruder_t extruder) {
  char buffer[21];
  snprintf_P(buffer, sizeof(buffer), PSTR("Filament runout E%d"), extruder);

  SetStatusMessage(buffer);

  dgus_display.PlaySound(3);
}

#if ENABLED(SDSUPPORT)

  void DGUSScreenHandler::SDCardInserted() {
    if (current_screen == DGUS_Screen::HOME)
      TriggerScreenChange(DGUS_Screen::PRINT);
  }

  void DGUSScreenHandler::SDCardRemoved() {
    if (current_screen == DGUS_Screen::PRINT)
      TriggerScreenChange(DGUS_Screen::HOME);
  }

  void DGUSScreenHandler::SDCardError() {
    SetStatusMessage(GET_TEXT_F(MSG_MEDIA_READ_ERROR));
    if (current_screen == DGUS_Screen::PRINT)
      TriggerScreenChange(DGUS_Screen::HOME);
  }

#endif // SDSUPPORT

#if ENABLED(POWER_LOSS_RECOVERY)

  void DGUSScreenHandler::PowerLossResume() {
    MoveToScreen(DGUS_Screen::POWERLOSS, true);
  }

#endif // POWER_LOSS_RECOVERY

#if HAS_PID_HEATING

  void DGUSScreenHandler::PidTuning(const ExtUI::result_t rst) {
    switch (rst) {
      case ExtUI::PID_STARTED:
        SetStatusMessage(GET_TEXT_F(MSG_PID_AUTOTUNE));
        break;
      case ExtUI::PID_BAD_EXTRUDER_NUM:
        SetStatusMessage(GET_TEXT_F(MSG_PID_BAD_EXTRUDER_NUM));
        break;
      case ExtUI::PID_TEMP_TOO_HIGH:
        SetStatusMessage(GET_TEXT_F(MSG_PID_TEMP_TOO_HIGH));
        break;
      case ExtUI::PID_TUNING_TIMEOUT:
        SetStatusMessage(GET_TEXT_F(MSG_PID_TIMEOUT));
        break;
      case ExtUI::PID_DONE:
        SetStatusMessage(GET_TEXT_F(MSG_PID_AUTOTUNE_DONE));
=======
  if (xpos >= GRID_MAX_POINTS_X - 1 && ypos >= GRID_MAX_POINTS_Y - 1 && !ExtUI::getLevelingIsValid())
    probing_icons[0] = probing_icons[1] = 0;

  triggerFullUpdate();
}

void DGUSScreenHandler::printTimerStarted() {
  triggerScreenChange(DGUS_ScreenID::PRINT_STATUS);
}

void DGUSScreenHandler::printTimerPaused() {
  dgus.playSound(3);
  triggerFullUpdate();
}

void DGUSScreenHandler::printTimerStopped() {
  if (current_screenID != DGUS_ScreenID::PRINT_STATUS && current_screenID != DGUS_ScreenID::PRINT_ADJUST)
    return;

  dgus.playSound(3);

  triggerScreenChange(DGUS_ScreenID::PRINT_FINISHED);
}

void DGUSScreenHandler::filamentRunout(const ExtUI::extruder_t extruder) {
  char buffer[21];

  snprintf_P(buffer, sizeof(buffer), GET_TEXT(DGUS_MSG_FILAMENT_RUNOUT), extruder);

  setStatusMessage(buffer);

  dgus.playSound(3);
}

#if HAS_MEDIA

  void DGUSScreenHandler::sdCardInserted() {
    if (current_screenID == DGUS_ScreenID::HOME)
      triggerScreenChange(DGUS_ScreenID::PRINT);
  }

  void DGUSScreenHandler::sdCardRemoved() {
    if (current_screenID == DGUS_ScreenID::PRINT)
      triggerScreenChange(DGUS_ScreenID::HOME);
  }

  void DGUSScreenHandler::sdCardError() {
    setStatusMessage(GET_TEXT_F(MSG_MEDIA_READ_ERROR));
    if (current_screenID == DGUS_ScreenID::PRINT)
      triggerScreenChange(DGUS_ScreenID::HOME);
  }

#endif // HAS_MEDIA

#if ENABLED(POWER_LOSS_RECOVERY)
  void DGUSScreenHandler::powerLossResume() {
    moveToScreen(DGUS_ScreenID::POWERLOSS, true);
  }
#endif

#if HAS_PID_HEATING

  void DGUSScreenHandler::pidTuning(const ExtUI::pidresult_t rst) {
    switch (rst) {
      case ExtUI::PID_STARTED:
      case ExtUI::PID_BED_STARTED:
      case ExtUI::PID_CHAMBER_STARTED:
        setStatusMessage(GET_TEXT_F(MSG_PID_AUTOTUNE));
        break;
      case ExtUI::PID_BAD_HEATER_ID:
        setStatusMessage(GET_TEXT_F(MSG_PID_BAD_HEATER_ID));
        break;
      case ExtUI::PID_TEMP_TOO_HIGH:
        setStatusMessage(GET_TEXT_F(MSG_PID_TEMP_TOO_HIGH));
        break;
      case ExtUI::PID_TUNING_TIMEOUT:
        setStatusMessage(GET_TEXT_F(MSG_PID_TIMEOUT));
        break;
      case ExtUI::PID_DONE:
        setStatusMessage(GET_TEXT_F(MSG_PID_AUTOTUNE_DONE));
>>>>>>> origin/release-2.1.3-beta2
        break;
      default:
        return;
    }

<<<<<<< HEAD
    dgus_display.PlaySound(3);
=======
    dgus.playSound(3);
>>>>>>> origin/release-2.1.3-beta2
  }

#endif // HAS_PID_HEATING

<<<<<<< HEAD
void DGUSScreenHandler::SetMessageLine(const char* msg, uint8_t line) {
  switch (line) {
    default: return;
    case 1:
      dgus_display.WriteString((uint16_t)DGUS_Addr::MESSAGE_Line1, msg, DGUS_LINE_LEN, true, true);
      break;
    case 2:
      dgus_display.WriteString((uint16_t)DGUS_Addr::MESSAGE_Line2, msg, DGUS_LINE_LEN, true, true);
      break;
    case 3:
      dgus_display.WriteString((uint16_t)DGUS_Addr::MESSAGE_Line3, msg, DGUS_LINE_LEN, true, true);
      break;
    case 4:
      dgus_display.WriteString((uint16_t)DGUS_Addr::MESSAGE_Line4, msg, DGUS_LINE_LEN, true, true);
=======
void DGUSScreenHandler::setMessageLine(const char * const msg, const uint8_t line) {
  switch (line) {
    default: return;
    case 1:
      dgus.writeString((uint16_t)DGUS_Addr::MESSAGE_Line1, msg, DGUS_LINE_LEN, true, true);
      break;
    case 2:
      dgus.writeString((uint16_t)DGUS_Addr::MESSAGE_Line2, msg, DGUS_LINE_LEN, true, true);
      break;
    case 3:
      dgus.writeString((uint16_t)DGUS_Addr::MESSAGE_Line3, msg, DGUS_LINE_LEN, true, true);
      break;
    case 4:
      dgus.writeString((uint16_t)DGUS_Addr::MESSAGE_Line4, msg, DGUS_LINE_LEN, true, true);
>>>>>>> origin/release-2.1.3-beta2
      break;
  }
}

<<<<<<< HEAD
void DGUSScreenHandler::SetMessageLinePGM(PGM_P msg, uint8_t line) {
  switch (line) {
    default: return;
    case 1:
      dgus_display.WriteStringPGM((uint16_t)DGUS_Addr::MESSAGE_Line1, msg, DGUS_LINE_LEN, true, true);
      break;
    case 2:
      dgus_display.WriteStringPGM((uint16_t)DGUS_Addr::MESSAGE_Line2, msg, DGUS_LINE_LEN, true, true);
      break;
    case 3:
      dgus_display.WriteStringPGM((uint16_t)DGUS_Addr::MESSAGE_Line3, msg, DGUS_LINE_LEN, true, true);
      break;
    case 4:
      dgus_display.WriteStringPGM((uint16_t)DGUS_Addr::MESSAGE_Line4, msg, DGUS_LINE_LEN, true, true);
=======
void DGUSScreenHandler::setMessageLine_P(PGM_P const msg, const uint8_t line) {
  switch (line) {
    default: return;
    case 1:
      dgus.writeStringPGM((uint16_t)DGUS_Addr::MESSAGE_Line1, msg, DGUS_LINE_LEN, true, true);
      break;
    case 2:
      dgus.writeStringPGM((uint16_t)DGUS_Addr::MESSAGE_Line2, msg, DGUS_LINE_LEN, true, true);
      break;
    case 3:
      dgus.writeStringPGM((uint16_t)DGUS_Addr::MESSAGE_Line3, msg, DGUS_LINE_LEN, true, true);
      break;
    case 4:
      dgus.writeStringPGM((uint16_t)DGUS_Addr::MESSAGE_Line4, msg, DGUS_LINE_LEN, true, true);
>>>>>>> origin/release-2.1.3-beta2
      break;
  }
}

<<<<<<< HEAD
void DGUSScreenHandler::SetStatusMessage(const char* msg, const millis_t duration) {
  dgus_display.WriteString((uint16_t)DGUS_Addr::MESSAGE_Status, msg, DGUS_STATUS_LEN, false, true);

  status_expire = (duration > 0 ? ExtUI::safe_millis() + duration : 0);
}

void DGUSScreenHandler::SetStatusMessage(FSTR_P const fmsg, const millis_t duration) {
  dgus_display.WriteStringPGM((uint16_t)DGUS_Addr::MESSAGE_Status, FTOP(fmsg), DGUS_STATUS_LEN, false, true);

  status_expire = (duration > 0 ? ExtUI::safe_millis() + duration : 0);
}

void DGUSScreenHandler::ShowWaitScreen(DGUS_Screen return_screen, bool has_continue) {
  if (return_screen != DGUS_Screen::WAIT) {
    wait_return_screen = return_screen;
  }
  wait_continue = has_continue;

  TriggerScreenChange(DGUS_Screen::WAIT);
}

DGUS_Screen DGUSScreenHandler::GetCurrentScreen() {
  return current_screen;
}

void DGUSScreenHandler::TriggerScreenChange(DGUS_Screen screen) {
  new_screen = screen;
}

void DGUSScreenHandler::TriggerFullUpdate() {
  full_update = true;
}

void DGUSScreenHandler::TriggerEEPROMSave() {
  eeprom_save = ExtUI::safe_millis() + 500;
}

bool DGUSScreenHandler::IsPrinterIdle() {
  return (!ExtUI::commandsInQueue()
          && !ExtUI::isMoving());
}

const DGUS_Addr* DGUSScreenHandler::FindScreenAddrList(DGUS_Screen screen) {
=======
void DGUSScreenHandler::setStatusMessage(const char* msg, const millis_t duration) {
  dgus.writeString((uint16_t)DGUS_Addr::MESSAGE_Status, msg, DGUS_STATUS_LEN, false, true);
  status_expire = (duration > 0 ? ExtUI::safe_millis() + duration : 0);
}

void DGUSScreenHandler::setStatusMessage(FSTR_P const fmsg, const millis_t duration) {
  dgus.writeString((uint16_t)DGUS_Addr::MESSAGE_Status, fmsg, DGUS_STATUS_LEN, false, true);
  status_expire = (duration > 0 ? ExtUI::safe_millis() + duration : 0);
}

void DGUSScreenHandler::showWaitScreen(const DGUS_ScreenID return_screenID, const bool has_continue/*=false*/) {
  if (return_screenID != DGUS_ScreenID::WAIT)
    wait_return_screenID = return_screenID;

  wait_continue = has_continue;

  triggerScreenChange(DGUS_ScreenID::WAIT);
}

void DGUSScreenHandler::showWaitScreen(FSTR_P const msg, const DGUS_ScreenID return_screenID, const bool has_continue/*=false*/) {
  setMessageLine_P(NUL_STR, 1);
  setMessageLine(msg, 2);
  setMessageLine_P(NUL_STR, 3);
  setMessageLine_P(NUL_STR, 4);
  showWaitScreen(return_screenID, has_continue);
}

DGUS_ScreenID DGUSScreenHandler::getCurrentScreen() {
  return current_screenID;
}

void DGUSScreenHandler::triggerScreenChange(const DGUS_ScreenID screenID) {
  new_screenID = screenID;
}

void DGUSScreenHandler::triggerFullUpdate() {
  full_update = true;
}

void DGUSScreenHandler::triggerEEPROMSave() {
  eeprom_save = ExtUI::safe_millis() + 500;
}

bool DGUSScreenHandler::isPrinterIdle() {
  return (!ExtUI::commandsInQueue() && !ExtUI::isMoving());
}

const DGUS_Addr* DGUSScreenHandler::findScreenAddrList(const DGUS_ScreenID screenID) {
>>>>>>> origin/release-2.1.3-beta2
  DGUS_ScreenAddrList list;
  const DGUS_ScreenAddrList *map = screen_addr_list_map;

  do {
    memcpy_P(&list, map, sizeof(*map));
    if (!list.addr_list) break;
<<<<<<< HEAD
    if (list.screen == screen) {
      return list.addr_list;
    }
=======
    if (list.screenID == screenID) return list.addr_list;
>>>>>>> origin/release-2.1.3-beta2
  } while (++map);

  return nullptr;
}

<<<<<<< HEAD
bool DGUSScreenHandler::CallScreenSetup(DGUS_Screen screen) {
=======
bool DGUSScreenHandler::callScreenSetup(const DGUS_ScreenID screenID) {
>>>>>>> origin/release-2.1.3-beta2
  DGUS_ScreenSetup setup;
  const DGUS_ScreenSetup *list = screen_setup_list;

  do {
    memcpy_P(&setup, list, sizeof(*list));
    if (!setup.setup_fn) break;
<<<<<<< HEAD
    if (setup.screen == screen) {
=======
    if (setup.screenID == screenID) {
>>>>>>> origin/release-2.1.3-beta2
      return setup.setup_fn();
    }
  } while (++list);

  return true;
}

<<<<<<< HEAD
void DGUSScreenHandler::MoveToScreen(DGUS_Screen screen, bool abort_wait) {
  if (current_screen == DGUS_Screen::KILL) {
    return;
  }

  if (current_screen == DGUS_Screen::WAIT) {
    if (screen != DGUS_Screen::WAIT) {
      wait_return_screen = screen;
    }

    if (!abort_wait) return;

    if (wait_continue && wait_for_user) {
      ExtUI::setUserConfirmed();
    }
  }

  if (!CallScreenSetup(screen)) return;

  if (!SendScreenVPData(screen, true)) {
    DEBUG_ECHOLNPGM("SendScreenVPData failed");
    return;
  }

  current_screen = screen;
  dgus_display.SwitchScreen(current_screen);
}

bool DGUSScreenHandler::SendScreenVPData(DGUS_Screen screen, bool complete_update) {
  if (complete_update) {
    full_update = false;
  }

  const DGUS_Addr *list = FindScreenAddrList(screen);
=======
void DGUSScreenHandler::moveToScreen(const DGUS_ScreenID screenID, bool abort_wait) {
  if (current_screenID == DGUS_ScreenID::KILL) return;

  if (current_screenID == DGUS_ScreenID::WAIT) {
    if (screenID != DGUS_ScreenID::WAIT)
      wait_return_screenID = screenID;

    if (!abort_wait) return;

    if (wait_continue && wait_for_user)
      ExtUI::setUserConfirmed();
  }

  if (!callScreenSetup(screenID)) return;

  if (!sendScreenVPData(screenID, true)) return;

  current_screenID = screenID;
  dgus.switchScreen(current_screenID);
}

bool DGUSScreenHandler::sendScreenVPData(const DGUS_ScreenID screenID, bool complete_update) {
  if (complete_update) full_update = false;

  const DGUS_Addr *list = findScreenAddrList(screenID);
>>>>>>> origin/release-2.1.3-beta2

  while (true) {
    if (!list) return true; // Nothing left to send

    const uint16_t addr = pgm_read_word(list++);
    if (!addr) return true; // Nothing left to send

    DGUS_VP vp;
<<<<<<< HEAD
    if (!DGUS_PopulateVP((DGUS_Addr)addr, &vp)) continue; // Invalid VP
=======
    if (!populateVP((DGUS_Addr)addr, &vp)) continue; // Invalid VP
>>>>>>> origin/release-2.1.3-beta2
    if (!vp.tx_handler) continue; // Nothing to send
    if (!complete_update && !(vp.flags & VPFLAG_AUTOUPLOAD)) continue; // Unnecessary VP

    uint8_t expected_tx = 6 + vp.size; // 6 bytes header + payload.
    const millis_t try_until = ExtUI::safe_millis() + 1000;

<<<<<<< HEAD
    while (expected_tx > dgus_display.GetFreeTxBuffer()) {
      if (ELAPSED(ExtUI::safe_millis(), try_until)) return false; // Stop trying after 1 second

      dgus_display.FlushTx(); // Flush the TX buffer
=======
    while (expected_tx > dgus.getFreeTxBuffer()) {
      if (ELAPSED(ExtUI::safe_millis(), try_until)) return false; // Stop trying after 1 second

      dgus.flushTx(); // Flush the TX buffer
>>>>>>> origin/release-2.1.3-beta2
      delay(50);
    }

    vp.tx_handler(vp);
  }
}

#endif // DGUS_LCD_UI_RELOADED
