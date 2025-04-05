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

#include "DGUSSetupHandler.h"

#include "DGUSDisplay.h"
#include "DGUSScreenHandler.h"

#include "../../../gcode/queue.h"

<<<<<<< HEAD
#if ENABLED(SDSUPPORT)
  bool DGUSSetupHandler::Print() {
    dgus_screen_handler.filelist.refresh();

    while (!dgus_screen_handler.filelist.isAtRootDir()) {
      dgus_screen_handler.filelist.upDir();
    }

    dgus_screen_handler.filelist_offset = 0;
    dgus_screen_handler.filelist_selected = -1;
=======
#if HAS_MEDIA
  bool DGUSSetupHandler::print() {
    screen.filelist.refresh();

    while (!screen.filelist.isAtRootDir()) {
      screen.filelist.upDir();
    }

    screen.filelist_offset = 0;
    screen.filelist_selected = -1;
>>>>>>> origin/release-2.1.3-beta2

    return true;
  }
#endif

<<<<<<< HEAD
bool DGUSSetupHandler::PrintStatus() {
=======
bool DGUSSetupHandler::printStatus() {
>>>>>>> origin/release-2.1.3-beta2
  if (ExtUI::isPrinting() || ExtUI::isPrintingPaused()) {
    return true;
  }

<<<<<<< HEAD
  dgus_screen_handler.TriggerScreenChange(DGUS_Screen::PRINT_FINISHED);
  return false;
}

bool DGUSSetupHandler::PrintAdjust() {
=======
  screen.triggerScreenChange(DGUS_ScreenID::PRINT_FINISHED);
  return false;
}

bool DGUSSetupHandler::printAdjust() {
>>>>>>> origin/release-2.1.3-beta2
  if (ExtUI::isPrinting() || ExtUI::isPrintingPaused()) {
    return true;
  }

<<<<<<< HEAD
  dgus_screen_handler.TriggerScreenChange(DGUS_Screen::PRINT_FINISHED);
  return false;
}

bool DGUSSetupHandler::LevelingMenu() {
  ExtUI::setLevelingActive(dgus_screen_handler.leveling_active);

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
  screen.triggerScreenChange(DGUS_ScreenID::PRINT_FINISHED);
  return false;
}

bool DGUSSetupHandler::levelingMenu() {
  ExtUI::setLevelingActive(screen.leveling_active);

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return false;
  }

  if (ExtUI::isPositionKnown()) {
    if (ExtUI::getAxisPosition_mm(ExtUI::Z) < 10.0f) {
      queue.enqueue_now(F("G0Z10"));
    }

    return true;
  }

<<<<<<< HEAD
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 1);
  dgus_screen_handler.SetMessageLinePGM(DGUS_MSG_HOMING, 2);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 3);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 4);
  dgus_screen_handler.ShowWaitScreen(DGUS_Screen::LEVELING_MENU);

  queue.enqueue_now_P(DGUS_CMD_HOME);
=======
  screen.showWaitScreen(GET_TEXT_F(DGUS_MSG_HOMING), DGUS_ScreenID::LEVELING_MENU);

  queue.enqueue_now(F("G28"));
>>>>>>> origin/release-2.1.3-beta2

  return false;
}

<<<<<<< HEAD
bool DGUSSetupHandler::LevelingManual() {
=======
bool DGUSSetupHandler::levelingManual() {
>>>>>>> origin/release-2.1.3-beta2
  ExtUI::setLevelingActive(false);

  if (ExtUI::isPositionKnown()) {
    return true;
  }

<<<<<<< HEAD
  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
    return false;
  }

  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 1);
  dgus_screen_handler.SetMessageLinePGM(DGUS_MSG_HOMING, 2);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 3);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 4);
  dgus_screen_handler.ShowWaitScreen(DGUS_Screen::LEVELING_MANUAL);

  queue.enqueue_now_P(DGUS_CMD_HOME);
=======
  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
    return false;
  }

  screen.showWaitScreen(GET_TEXT_F(DGUS_MSG_HOMING), DGUS_ScreenID::LEVELING_MANUAL);

  queue.enqueue_now(F("G28"));
>>>>>>> origin/release-2.1.3-beta2

  return false;
}

<<<<<<< HEAD
bool DGUSSetupHandler::LevelingOffset() {
  dgus_screen_handler.offset_steps = DGUS_Data::StepSize::MMP1;

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
bool DGUSSetupHandler::levelingOffset() {
  screen.offset_steps = DGUS_Data::StepSize::MMP1;

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return false;
  }

  if (ExtUI::isPositionKnown()) {
    if (ExtUI::getAxisPosition_mm(ExtUI::Z) < 4.0f) {
      queue.enqueue_now(F("G0Z4"));
    }

    char buffer[20];
    snprintf_P(buffer, sizeof(buffer), PSTR("G0X%dY%d"), DGUS_LEVEL_CENTER_X, DGUS_LEVEL_CENTER_Y);

    queue.enqueue_one_now(buffer);
    queue.enqueue_now(F("G0Z0"));

    return true;
  }

<<<<<<< HEAD
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 1);
  dgus_screen_handler.SetMessageLinePGM(DGUS_MSG_HOMING, 2);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 3);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 4);
  dgus_screen_handler.ShowWaitScreen(DGUS_Screen::LEVELING_OFFSET);

  queue.enqueue_now_P(DGUS_CMD_HOME);
=======
  screen.showWaitScreen(GET_TEXT_F(DGUS_MSG_HOMING), DGUS_ScreenID::LEVELING_OFFSET);

  queue.enqueue_now(F("G28"));
>>>>>>> origin/release-2.1.3-beta2

  return false;
}

<<<<<<< HEAD
bool DGUSSetupHandler::LevelingAutomatic() {
  if (ExtUI::getMeshValid()) {
    dgus_screen_handler.leveling_active = true;
=======
bool DGUSSetupHandler::levelingAutomatic() {
  if (ExtUI::getLevelingIsValid()) {
    screen.leveling_active = true;
>>>>>>> origin/release-2.1.3-beta2

    ExtUI::setLevelingActive(true);
  }

  return true;
}

<<<<<<< HEAD
bool DGUSSetupHandler::LevelingProbing() {
  dgus_screen_handler.probing_icons[0] = 0;
  dgus_screen_handler.probing_icons[1] = 0;
=======
bool DGUSSetupHandler::levelingProbing() {
  screen.probing_icons[0] = 0;
  screen.probing_icons[1] = 0;
>>>>>>> origin/release-2.1.3-beta2

  return true;
}

<<<<<<< HEAD
bool DGUSSetupHandler::Filament() {
  dgus_screen_handler.filament_extruder = DGUS_Data::Extruder::CURRENT;
  dgus_screen_handler.filament_length = DGUS_DEFAULT_FILAMENT_LEN;
=======
bool DGUSSetupHandler::filament() {
  screen.filament_extruder = DGUS_Data::Extruder::CURRENT;
  screen.filament_length = DGUS_DEFAULT_FILAMENT_LEN;
>>>>>>> origin/release-2.1.3-beta2

  return true;
}

<<<<<<< HEAD
bool DGUSSetupHandler::Move() {
  dgus_screen_handler.move_steps = DGUS_Data::StepSize::MM10;

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
bool DGUSSetupHandler::move() {
  screen.move_steps = DGUS_Data::StepSize::MM10;

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return false;
  }

  return true;
}

<<<<<<< HEAD
bool DGUSSetupHandler::Gcode() {
  ZERO(dgus_screen_handler.gcode);

  if (dgus_display.gui_version < 0x30 || dgus_display.os_version < 0x21) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_FW_OUTDATED));
=======
bool DGUSSetupHandler::gcode() {
  ZERO(screen.gcode);

  if (dgus.gui_version < 0x30 || dgus.os_version < 0x21) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_FW_OUTDATED));
>>>>>>> origin/release-2.1.3-beta2
    return false;
  }

  return true;
}

<<<<<<< HEAD
bool DGUSSetupHandler::PID() {
  dgus_screen_handler.pid_heater = DGUS_Data::Heater::H0;
  dgus_screen_handler.pid_temp = DGUS_PLA_TEMP_HOTEND;
=======
bool DGUSSetupHandler::pid() {
  screen.pid_heater = DGUS_Data::Heater::H0;
  screen.pid_temp = DGUS_PLA_TEMP_HOTEND;
>>>>>>> origin/release-2.1.3-beta2

  return true;
}

<<<<<<< HEAD
bool DGUSSetupHandler::Infos() {
  dgus_screen_handler.debug_count = 0;
=======
bool DGUSSetupHandler::infos() {
  screen.debug_count = 0;
>>>>>>> origin/release-2.1.3-beta2

  return true;
}

#endif // DGUS_LCD_UI_RELOADED
