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

#include "DGUSTxHandler.h"

#include "DGUSScreenHandler.h"
#include "config/DGUS_Data.h"

#include "../ui_api.h"
#include "../../../module/stepper.h"
<<<<<<< HEAD
#include "../../../module/printcounter.h"
=======
#include "../../../module/temperature.h"
#include "../../../module/printcounter.h"

>>>>>>> origin/release-2.1.3-beta2
#if ENABLED(ADVANCED_PAUSE_FEATURE)
  #include "../../../feature/pause.h"
#endif

<<<<<<< HEAD
#if ENABLED(SDSUPPORT)
  void DGUSTxHandler::SetFileControlState(int file, bool state) {
=======
#if HAS_MEDIA
  void DGUSTxHandler::setFileControlState(int16_t file, bool state) {
>>>>>>> origin/release-2.1.3-beta2
    DGUS_Control control;

    switch (file) {
      default: return;
      case 0:
        control = DGUS_Control::FILE0;
        break;
      case 1:
        control = DGUS_Control::FILE1;
        break;
      case 2:
        control = DGUS_Control::FILE2;
        break;
      case 3:
        control = DGUS_Control::FILE3;
        break;
      case 4:
        control = DGUS_Control::FILE4;
        break;
    }

    if (state) {
<<<<<<< HEAD
      dgus_display.EnableControl(DGUS_Screen::PRINT,
=======
      dgus.enableControl(DGUS_ScreenID::PRINT,
>>>>>>> origin/release-2.1.3-beta2
                                 DGUSDisplay::RETURN_KEY_CODE,
                                 control);
    }
    else {
<<<<<<< HEAD
      dgus_display.DisableControl(DGUS_Screen::PRINT,
=======
      dgus.disableControl(DGUS_ScreenID::PRINT,
>>>>>>> origin/release-2.1.3-beta2
                                  DGUSDisplay::RETURN_KEY_CODE,
                                  control);
    }
  }

<<<<<<< HEAD
  void DGUSTxHandler::FileType(DGUS_VP &vp) {
    // Batch send
    uint16_t data[DGUS_FILE_COUNT];

    for (int i = 0; i < DGUS_FILE_COUNT; i++) {
      if (!dgus_screen_handler.filelist.seek(dgus_screen_handler.filelist_offset + i)) {
        data[i] = Swap16((uint16_t)DGUS_Data::SDType::NONE);

        SetFileControlState(i, false);
        continue;
      }

      data[i] = dgus_screen_handler.filelist.isDir() ?
                  Swap16((uint16_t)DGUS_Data::SDType::DIRECTORY)
                : Swap16((uint16_t)DGUS_Data::SDType::FILE);

      SetFileControlState(i, true);
    }

    dgus_display.Write((uint16_t)vp.addr, data, sizeof(*data) * DGUS_FILE_COUNT);
  }

  void DGUSTxHandler::FileName(DGUS_VP &vp) {
=======
  void DGUSTxHandler::fileType(DGUS_VP &vp) {
    // Batch send
    uint16_t data[DGUS_FILE_COUNT];

    for (int16_t i = 0; i < DGUS_FILE_COUNT; i++) {
      if (!screen.filelist.seek(screen.filelist_offset + i)) {
        data[i] = Swap16(DGUS_Data::SDType::NONE);

        setFileControlState(i, false);
        continue;
      }

      data[i] = screen.filelist.isDir() ?
                  Swap16(DGUS_Data::SDType::DIRECTORY)
                : Swap16(DGUS_Data::SDType::FILE);

      setFileControlState(i, true);
    }

    dgus.write((uint16_t)vp.addr, data, sizeof(*data) * DGUS_FILE_COUNT);
  }

  void DGUSTxHandler::fileName(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
    uint8_t offset;

    switch (vp.addr) {
      default: return;
      case DGUS_Addr::SD_FileName0:
        offset = 0;
        break;
      case DGUS_Addr::SD_FileName1:
        offset = 1;
        break;
      case DGUS_Addr::SD_FileName2:
        offset = 2;
        break;
      case DGUS_Addr::SD_FileName3:
        offset = 3;
        break;
      case DGUS_Addr::SD_FileName4:
        offset = 4;
        break;
    }

<<<<<<< HEAD
    if (dgus_screen_handler.filelist.seek(dgus_screen_handler.filelist_offset + offset)) {
      dgus_display.WriteString((uint16_t)vp.addr, dgus_screen_handler.filelist.filename(), vp.size);
    }
    else {
      dgus_display.WriteStringPGM((uint16_t)vp.addr, NUL_STR, vp.size);
    }
  }

  void DGUSTxHandler::ScrollIcons(DGUS_VP &vp) {
    uint16_t icons = 0;

    if (!dgus_screen_handler.filelist.isAtRootDir()) {
      icons |= (uint16_t)DGUS_Data::ScrollIcon::GO_BACK;

      dgus_display.EnableControl(DGUS_Screen::PRINT,
=======
    if (screen.filelist.seek(screen.filelist_offset + offset)) {
      dgus.writeString((uint16_t)vp.addr, screen.filelist.filename(), vp.size);
    }
    else {
      dgus.writeStringPGM((uint16_t)vp.addr, NUL_STR, vp.size);
    }
  }

  void DGUSTxHandler::scrollIcons(DGUS_VP &vp) {
    uint16_t icons = 0;

    if (!screen.filelist.isAtRootDir()) {
      icons |= (uint16_t)DGUS_Data::ScrollIcon::GO_BACK;

      dgus.enableControl(DGUS_ScreenID::PRINT,
>>>>>>> origin/release-2.1.3-beta2
                                 DGUSDisplay::RETURN_KEY_CODE,
                                 DGUS_Control::GO_BACK);
    }
    else {
<<<<<<< HEAD
      dgus_display.DisableControl(DGUS_Screen::PRINT,
=======
      dgus.disableControl(DGUS_ScreenID::PRINT,
>>>>>>> origin/release-2.1.3-beta2
                                  DGUSDisplay::RETURN_KEY_CODE,
                                  DGUS_Control::GO_BACK);
    }

<<<<<<< HEAD
    if (dgus_screen_handler.filelist_offset > 0) {
      icons |= (uint16_t)DGUS_Data::ScrollIcon::UP;

      dgus_display.EnableControl(DGUS_Screen::PRINT,
=======
    if (screen.filelist_offset > 0) {
      icons |= (uint16_t)DGUS_Data::ScrollIcon::UP;

      dgus.enableControl(DGUS_ScreenID::PRINT,
>>>>>>> origin/release-2.1.3-beta2
                                 DGUSDisplay::RETURN_KEY_CODE,
                                 DGUS_Control::SCROLL_UP);
    }
    else {
<<<<<<< HEAD
      dgus_display.DisableControl(DGUS_Screen::PRINT,
=======
      dgus.disableControl(DGUS_ScreenID::PRINT,
>>>>>>> origin/release-2.1.3-beta2
                                  DGUSDisplay::RETURN_KEY_CODE,
                                  DGUS_Control::SCROLL_UP);
    }

<<<<<<< HEAD
    if (dgus_screen_handler.filelist_offset + DGUS_FILE_COUNT < dgus_screen_handler.filelist.count()) {
      icons |= (uint16_t)DGUS_Data::ScrollIcon::DOWN;

      dgus_display.EnableControl(DGUS_Screen::PRINT,
=======
    if (screen.filelist_offset + DGUS_FILE_COUNT < screen.filelist.count()) {
      icons |= (uint16_t)DGUS_Data::ScrollIcon::DOWN;

      dgus.enableControl(DGUS_ScreenID::PRINT,
>>>>>>> origin/release-2.1.3-beta2
                                 DGUSDisplay::RETURN_KEY_CODE,
                                 DGUS_Control::SCROLL_DOWN);
    }
    else {
<<<<<<< HEAD
      dgus_display.DisableControl(DGUS_Screen::PRINT,
=======
      dgus.disableControl(DGUS_ScreenID::PRINT,
>>>>>>> origin/release-2.1.3-beta2
                                  DGUSDisplay::RETURN_KEY_CODE,
                                  DGUS_Control::SCROLL_DOWN);
    }

<<<<<<< HEAD
    dgus_display.Write((uint16_t)vp.addr, Swap16(icons));
  }

  void DGUSTxHandler::SelectedFileName(DGUS_VP &vp) {
    if (dgus_screen_handler.filelist_selected < 0
        || !dgus_screen_handler.filelist.seek(dgus_screen_handler.filelist_selected)) {
      dgus_display.WriteStringPGM((uint16_t)vp.addr, NUL_STR, vp.size);
      return;
    }

    dgus_display.WriteString((uint16_t)vp.addr, dgus_screen_handler.filelist.filename(), vp.size);
  }
#endif // SDSUPPORT

void DGUSTxHandler::PositionZ(DGUS_VP &vp) {
  float position = ExtUI::isAxisPositionKnown(ExtUI::Z) ?
                     planner.get_axis_position_mm(Z_AXIS)
                   : 0;

  const int16_t data = dgus_display.ToFixedPoint<float, int16_t, 1>(position);
  dgus_display.Write((uint16_t)vp.addr, Swap16(data));
}

void DGUSTxHandler::Ellapsed(DGUS_VP &vp) {
  char buffer[21];
  duration_t(print_job_timer.duration()).toString(buffer);

  dgus_display.WriteString((uint16_t)vp.addr, buffer, vp.size);
}

void DGUSTxHandler::Percent(DGUS_VP &vp) {
=======
    dgus.write((uint16_t)vp.addr, Swap16(icons));
  }

  void DGUSTxHandler::selectedFileName(DGUS_VP &vp) {
    if (screen.filelist_selected < 0
        || !screen.filelist.seek(screen.filelist_selected)) {
      dgus.writeStringPGM((uint16_t)vp.addr, NUL_STR, vp.size);
      return;
    }

    dgus.writeString((uint16_t)vp.addr, screen.filelist.filename(), vp.size);
  }
#endif // HAS_MEDIA

void DGUSTxHandler::zPosition(DGUS_VP &vp) {
  const float position = ExtUI::isAxisPositionKnown(ExtUI::Z) ? planner.get_axis_position_mm(Z_AXIS) : 0;
  const int32_t data = dgus.toFixedPoint<float, int32_t, 2>(int32_t(position * 50.0f) / 50.0f); // Round to 0.02
  dgus.write((uint16_t)vp.addr, dgus.swapBytes(data));
}

void DGUSTxHandler::elapsed(DGUS_VP &vp) {
  char buffer[21];
  duration_t(print_job_timer.duration()).toString(buffer);

  dgus.writeString((uint16_t)vp.addr, buffer, vp.size);
}

void DGUSTxHandler::percent(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  uint16_t progress;

  switch (vp.addr) {
    default: return;
    case DGUS_Addr::STATUS_Percent:
      progress = constrain(ExtUI::getProgress_percent(), 0, 100);
      break;
    case DGUS_Addr::STATUS_Percent_Complete:
      progress = 100;
      break;
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)DGUS_Addr::STATUS_Percent, Swap16(progress));
}

void DGUSTxHandler::StatusIcons(DGUS_VP &vp) {
=======
  dgus.write((uint16_t)DGUS_Addr::STATUS_Percent, Swap16(progress));
}

void DGUSTxHandler::statusIcons(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  uint16_t icons = 0;

  if (ExtUI::isPrinting()) {
    icons |= (uint16_t)DGUS_Data::StatusIcon::PAUSE;

<<<<<<< HEAD
    dgus_display.EnableControl(DGUS_Screen::PRINT_STATUS,
=======
    dgus.enableControl(DGUS_ScreenID::PRINT_STATUS,
>>>>>>> origin/release-2.1.3-beta2
                               DGUSDisplay::POPUP_WINDOW,
                               DGUS_Control::PAUSE);
  }
  else {
<<<<<<< HEAD
    dgus_display.DisableControl(DGUS_Screen::PRINT_STATUS,
=======
    dgus.disableControl(DGUS_ScreenID::PRINT_STATUS,
>>>>>>> origin/release-2.1.3-beta2
                                DGUSDisplay::POPUP_WINDOW,
                                DGUS_Control::PAUSE);
  }

  if (ExtUI::isPrintingPaused()) {
    icons |= (uint16_t)DGUS_Data::StatusIcon::RESUME;

<<<<<<< HEAD
    dgus_display.EnableControl(DGUS_Screen::PRINT_STATUS,
=======
    dgus.enableControl(DGUS_ScreenID::PRINT_STATUS,
>>>>>>> origin/release-2.1.3-beta2
                               DGUSDisplay::POPUP_WINDOW,
                               DGUS_Control::RESUME);
  }
  else {
<<<<<<< HEAD
    dgus_display.DisableControl(DGUS_Screen::PRINT_STATUS,
=======
    dgus.disableControl(DGUS_ScreenID::PRINT_STATUS,
>>>>>>> origin/release-2.1.3-beta2
                                DGUSDisplay::POPUP_WINDOW,
                                DGUS_Control::RESUME);
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::Flowrate(DGUS_VP &vp) {
=======
  dgus.write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::flowrate(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  int16_t flowrate;

  switch (vp.addr) {
    default: return;
    case DGUS_Addr::ADJUST_Flowrate_CUR:
      flowrate = ExtUI::getFlow_percent(TERN(HAS_MULTI_EXTRUDER, ExtUI::getActiveTool(), ExtUI::E0));
      break;
    #if HAS_MULTI_EXTRUDER
      case DGUS_Addr::ADJUST_Flowrate_E0:
        flowrate = ExtUI::getFlow_percent(ExtUI::E0);
        break;
      case DGUS_Addr::ADJUST_Flowrate_E1:
        flowrate = ExtUI::getFlow_percent(ExtUI::E1);
        break;
    #endif
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(flowrate));
}

void DGUSTxHandler::TempMax(DGUS_VP &vp) {
=======
  dgus.write((uint16_t)vp.addr, Swap16(flowrate));
}

void DGUSTxHandler::tempMax(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  uint16_t temp;

  switch (vp.addr) {
    default: return;
<<<<<<< HEAD
    case DGUS_Addr::TEMP_Max_Bed:
      temp = BED_MAX_TARGET;
      break;
    case DGUS_Addr::TEMP_Max_H0:
      temp = HEATER_0_MAXTEMP - HOTEND_OVERSHOOT;
      break;
    #if HAS_MULTI_HOTEND
      case DGUS_Addr::TEMP_Max_H1:
        temp = HEATER_1_MAXTEMP - HOTEND_OVERSHOOT;
=======
    #if HAS_HEATED_BED
      case DGUS_Addr::TEMP_Max_Bed:
        temp = BED_MAX_TARGET;
        break;
    #endif
    #if HAS_HOTEND
      case DGUS_Addr::TEMP_Max_H0:
        temp = thermalManager.hotend_max_target(0);
        break;
    #endif
    #if HAS_MULTI_HOTEND
      case DGUS_Addr::TEMP_Max_H1:
        temp = thermalManager.hotend_max_target(1);
>>>>>>> origin/release-2.1.3-beta2
        break;
    #endif
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(temp));
}

void DGUSTxHandler::StepperStatus(DGUS_VP &vp) {
  const bool motor_on = stepper.axis_enabled.bits & (_BV(NUM_AXES) - 1);
  dgus_display.Write((uint16_t)vp.addr, Swap16(uint16_t(motor_on ? DGUS_Data::Status::ENABLED : DGUS_Data::Status::DISABLED)));
}

void DGUSTxHandler::StepIcons(DGUS_VP &vp) {
=======
  dgus.write((uint16_t)vp.addr, Swap16(temp));
}

void DGUSTxHandler::stepperStatus(DGUS_VP &vp) {
  const bool motor_on = stepper.axis_enabled.bits & (_BV(NUM_AXES) - 1);
  dgus.write((uint16_t)vp.addr, Swap16(motor_on ? DGUS_Data::Status::ENABLED : DGUS_Data::Status::DISABLED));
}

void DGUSTxHandler::stepIcons(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  if (!vp.extra) return;
  uint16_t icons = 0;
  DGUS_Data::StepSize size = *(DGUS_Data::StepSize*)vp.extra;

  switch (size) {
    case DGUS_Data::StepSize::MM10:
      icons |= (uint16_t)DGUS_Data::StepIcon::MM10;
      break;
    case DGUS_Data::StepSize::MM1:
      icons |= (uint16_t)DGUS_Data::StepIcon::MM1;
      break;
    case DGUS_Data::StepSize::MMP1:
      icons |= (uint16_t)DGUS_Data::StepIcon::MMP1;
      break;
    case DGUS_Data::StepSize::MMP01:
      icons |= (uint16_t)DGUS_Data::StepIcon::MMP01;
      break;
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::ABLDisableIcon(DGUS_VP &vp) {
=======
  dgus.write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::ablDisableIcon(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  uint16_t data;

  if (ExtUI::getLevelingActive()) {
    data = (uint16_t)DGUS_Data::Status::ENABLED;

<<<<<<< HEAD
    dgus_display.EnableControl(DGUS_Screen::LEVELING_AUTOMATIC,
=======
    dgus.enableControl(DGUS_ScreenID::LEVELING_AUTOMATIC,
>>>>>>> origin/release-2.1.3-beta2
                               DGUSDisplay::RETURN_KEY_CODE,
                               DGUS_Control::DISABLE);
  }
  else {
    data = (uint16_t)DGUS_Data::Status::DISABLED;

<<<<<<< HEAD
    dgus_display.DisableControl(DGUS_Screen::LEVELING_AUTOMATIC,
=======
    dgus.disableControl(DGUS_ScreenID::LEVELING_AUTOMATIC,
>>>>>>> origin/release-2.1.3-beta2
                                DGUSDisplay::RETURN_KEY_CODE,
                                DGUS_Control::DISABLE);
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(data));
}

void DGUSTxHandler::ABLGrid(DGUS_VP &vp) {
=======
  dgus.write((uint16_t)vp.addr, Swap16(data));
}

void DGUSTxHandler::ablGrid(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  // Batch send
  int16_t data[DGUS_LEVEL_GRID_SIZE];
  xy_uint8_t point;
  int16_t fixed;

<<<<<<< HEAD
  for (int i = 0; i < DGUS_LEVEL_GRID_SIZE; i++) {
    point.x = i % (GRID_MAX_POINTS_X);
    point.y = i / (GRID_MAX_POINTS_X);
    fixed = dgus_display.ToFixedPoint<float, int16_t, 3>(ExtUI::getMeshPoint(point));
    data[i] = Swap16(fixed);
  }

  dgus_display.Write((uint16_t)vp.addr, data, sizeof(*data) * DGUS_LEVEL_GRID_SIZE);
}

void DGUSTxHandler::FilamentIcons(DGUS_VP &vp) {
  uint16_t icons = 0;

  switch (dgus_screen_handler.filament_extruder) {
=======
  for (int16_t i = 0; i < DGUS_LEVEL_GRID_SIZE; i++) {
    point.x = i % (GRID_MAX_POINTS_X);
    point.y = i / (GRID_MAX_POINTS_X);
    fixed = dgus.toFixedPoint<float, int16_t, 3>(ExtUI::getMeshPoint(point));
    data[i] = Swap16(fixed);
  }

  dgus.write((uint16_t)vp.addr, data, sizeof(*data) * DGUS_LEVEL_GRID_SIZE);
}

void DGUSTxHandler::filamentIcons(DGUS_VP &vp) {
  uint16_t icons = 0;

  switch (screen.filament_extruder) {
>>>>>>> origin/release-2.1.3-beta2
    default: return;
    case DGUS_Data::Extruder::CURRENT:
      #if HAS_MULTI_EXTRUDER
        switch (ExtUI::getActiveTool()) {
          default: break;
          case ExtUI::E0:
            icons |= (uint16_t)DGUS_Data::ExtruderIcon::E0;
            break;
          case ExtUI::E1:
            icons |= (uint16_t)DGUS_Data::ExtruderIcon::E1;
            break;
        }
        break;
      #endif
    case DGUS_Data::Extruder::E0:
      icons |= (uint16_t)DGUS_Data::ExtruderIcon::E0;
      break;
    case DGUS_Data::Extruder::E1:
      icons |= (uint16_t)DGUS_Data::ExtruderIcon::E1;
      break;
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::BLTouch(DGUS_VP &vp) {
  #if ENABLED(BLTOUCH)
    dgus_display.EnableControl(DGUS_Screen::SETTINGS_MENU2,
                               DGUSDisplay::RETURN_KEY_CODE,
                               DGUS_Control::EXTRA2);

    dgus_display.Write((uint16_t)vp.addr, Swap16((uint16_t)DGUS_Data::Status::ENABLED));
  #else
    dgus_display.DisableControl(DGUS_Screen::SETTINGS_MENU2,
                                DGUSDisplay::RETURN_KEY_CODE,
                                DGUS_Control::EXTRA2);

    dgus_display.Write((uint16_t)vp.addr, Swap16((uint16_t)DGUS_Data::Status::DISABLED));
  #endif
}

void DGUSTxHandler::PIDIcons(DGUS_VP &vp) {
  uint16_t icons = 0;

  switch (dgus_screen_handler.pid_heater) {
=======
  dgus.write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::blTouch(DGUS_VP &vp) {
  #if ENABLED(BLTOUCH)
    dgus.enableControl(DGUS_ScreenID::SETTINGS_MENU2,
                               DGUSDisplay::RETURN_KEY_CODE,
                               DGUS_Control::EXTRA2);

    dgus.write((uint16_t)vp.addr, Swap16(DGUS_Data::Status::ENABLED));
  #else
    dgus.disableControl(DGUS_ScreenID::SETTINGS_MENU2,
                                DGUSDisplay::RETURN_KEY_CODE,
                                DGUS_Control::EXTRA2);

    dgus.write((uint16_t)vp.addr, Swap16(DGUS_Data::Status::DISABLED));
  #endif
}

void DGUSTxHandler::pidIcons(DGUS_VP &vp) {
  uint16_t icons = 0;

  switch (screen.pid_heater) {
>>>>>>> origin/release-2.1.3-beta2
    default: return;
    case DGUS_Data::Heater::BED:
      icons |= (uint16_t)DGUS_Data::HeaterIcon::BED;
      break;
    case DGUS_Data::Heater::H0:
      icons |= (uint16_t)DGUS_Data::HeaterIcon::H0;
      break;
    case DGUS_Data::Heater::H1:
      icons |= (uint16_t)DGUS_Data::HeaterIcon::H1;
      break;
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::PIDKp(DGUS_VP &vp) {
  float value;

  switch (dgus_screen_handler.pid_heater) {
    default: return;
    #if ENABLED(PIDTEMPBED)
      case DGUS_Data::Heater::BED:
        value = ExtUI::getBedPIDValues_Kp();
=======
  dgus.write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::pidKp(DGUS_VP &vp) {
  float value;

  switch (screen.pid_heater) {
    default: return;
    #if ENABLED(PIDTEMPBED)
      case DGUS_Data::Heater::BED:
        value = ExtUI::getBedPID_Kp();
>>>>>>> origin/release-2.1.3-beta2
        break;
    #endif
    #if ENABLED(PIDTEMP)
      case DGUS_Data::Heater::H0:
<<<<<<< HEAD
        value = ExtUI::getPIDValues_Kp(ExtUI::E0);
        break;
      #if HAS_MULTI_HOTEND
        case DGUS_Data::Heater::H1:
          value = ExtUI::getPIDValues_Kp(ExtUI::E1);
=======
        value = ExtUI::getPID_Kp(ExtUI::E0);
        break;
      #if HAS_MULTI_HOTEND
        case DGUS_Data::Heater::H1:
          value = ExtUI::getPID_Kp(ExtUI::E1);
>>>>>>> origin/release-2.1.3-beta2
          break;
      #endif
    #endif
  }

<<<<<<< HEAD
  const int32_t data = dgus_display.ToFixedPoint<float, int32_t, 2>(value);
  dgus_display.Write((uint16_t)vp.addr, dgus_display.SwapBytes(data));
}

void DGUSTxHandler::PIDKi(DGUS_VP &vp) {
  float value;

  switch (dgus_screen_handler.pid_heater) {
    default: return;
    #if ENABLED(PIDTEMPBED)
      case DGUS_Data::Heater::BED:
        value = ExtUI::getBedPIDValues_Ki();
=======
  const int32_t data = dgus.toFixedPoint<float, int32_t, 2>(value);
  dgus.write((uint16_t)vp.addr, dgus.swapBytes(data));
}

void DGUSTxHandler::pidKi(DGUS_VP &vp) {
  float value;

  switch (screen.pid_heater) {
    default: return;
    #if ENABLED(PIDTEMPBED)
      case DGUS_Data::Heater::BED:
        value = ExtUI::getBedPID_Ki();
>>>>>>> origin/release-2.1.3-beta2
        break;
    #endif
    #if ENABLED(PIDTEMP)
      case DGUS_Data::Heater::H0:
<<<<<<< HEAD
        value = ExtUI::getPIDValues_Ki(ExtUI::E0);
        break;
      #if HAS_MULTI_HOTEND
        case DGUS_Data::Heater::H1:
          value = ExtUI::getPIDValues_Ki(ExtUI::E1);
=======
        value = ExtUI::getPID_Ki(ExtUI::E0);
        break;
      #if HAS_MULTI_HOTEND
        case DGUS_Data::Heater::H1:
          value = ExtUI::getPID_Ki(ExtUI::E1);
>>>>>>> origin/release-2.1.3-beta2
          break;
      #endif
    #endif
  }

<<<<<<< HEAD
  const int32_t data = dgus_display.ToFixedPoint<float, int32_t, 2>(value);
  dgus_display.Write((uint16_t)vp.addr, dgus_display.SwapBytes(data));
}

void DGUSTxHandler::PIDKd(DGUS_VP &vp) {
  float value;

  switch (dgus_screen_handler.pid_heater) {
    default: return;
    #if ENABLED(PIDTEMPBED)
      case DGUS_Data::Heater::BED:
        value = ExtUI::getBedPIDValues_Kd();
=======
  const int32_t data = dgus.toFixedPoint<float, int32_t, 2>(value);
  dgus.write((uint16_t)vp.addr, dgus.swapBytes(data));
}

void DGUSTxHandler::pidKd(DGUS_VP &vp) {
  float value;

  switch (screen.pid_heater) {
    default: return;
    #if ENABLED(PIDTEMPBED)
      case DGUS_Data::Heater::BED:
        value = ExtUI::getBedPID_Kd();
>>>>>>> origin/release-2.1.3-beta2
        break;
    #endif
    #if ENABLED(PIDTEMP)
      case DGUS_Data::Heater::H0:
<<<<<<< HEAD
        value = ExtUI::getPIDValues_Kd(ExtUI::E0);
        break;
      #if HAS_MULTI_HOTEND
        case DGUS_Data::Heater::H1:
          value = ExtUI::getPIDValues_Kd(ExtUI::E1);
=======
        value = ExtUI::getPID_Kd(ExtUI::E0);
        break;
      #if HAS_MULTI_HOTEND
        case DGUS_Data::Heater::H1:
          value = ExtUI::getPID_Kd(ExtUI::E1);
>>>>>>> origin/release-2.1.3-beta2
          break;
      #endif
    #endif
  }

<<<<<<< HEAD
  const int32_t data = dgus_display.ToFixedPoint<float, int32_t, 2>(value);
  dgus_display.Write((uint16_t)vp.addr, dgus_display.SwapBytes(data));
}

void DGUSTxHandler::BuildVolume(DGUS_VP &vp) {
  char buffer[vp.size];
  snprintf_P(buffer, vp.size, PSTR("%dx%dx%d"), X_BED_SIZE, Y_BED_SIZE, (Z_MAX_POS - Z_MIN_POS));

  dgus_display.WriteString((uint16_t)vp.addr, buffer, vp.size);
}

void DGUSTxHandler::TotalPrints(DGUS_VP &vp) {
  #if ENABLED(PRINTCOUNTER)
    dgus_display.Write((uint16_t)vp.addr, dgus_display.SwapBytes(print_job_timer.getStats().totalPrints));
=======
  const int32_t data = dgus.toFixedPoint<float, int32_t, 2>(value);
  dgus.write((uint16_t)vp.addr, dgus.swapBytes(data));
}

void DGUSTxHandler::buildVolume(DGUS_VP &vp) {
  char buffer[vp.size];
  snprintf_P(buffer, vp.size, PSTR("%dx%dx%d"), X_BED_SIZE, Y_BED_SIZE, (Z_MAX_POS - Z_MIN_POS));

  dgus.writeString((uint16_t)vp.addr, buffer, vp.size);
}

void DGUSTxHandler::totalPrints(DGUS_VP &vp) {
  #if ENABLED(PRINTCOUNTER)
    dgus.write((uint16_t)vp.addr, dgus.swapBytes(print_job_timer.getStats().totalPrints));
>>>>>>> origin/release-2.1.3-beta2
  #else
    UNUSED(vp);
  #endif
}

<<<<<<< HEAD
void DGUSTxHandler::FinishedPrints(DGUS_VP &vp) {
  #if ENABLED(PRINTCOUNTER)
    dgus_display.Write((uint16_t)vp.addr, dgus_display.SwapBytes(print_job_timer.getStats().finishedPrints));
=======
void DGUSTxHandler::finishedPrints(DGUS_VP &vp) {
  #if ENABLED(PRINTCOUNTER)
    dgus.write((uint16_t)vp.addr, dgus.swapBytes(print_job_timer.getStats().finishedPrints));
>>>>>>> origin/release-2.1.3-beta2
  #else
    UNUSED(vp);
  #endif
}

<<<<<<< HEAD
void DGUSTxHandler::PrintTime(DGUS_VP &vp) {
=======
void DGUSTxHandler::printTime(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  #if ENABLED(PRINTCOUNTER)
    char buffer[21];
    ExtUI::getTotalPrintTime_str(buffer);

<<<<<<< HEAD
    dgus_display.WriteString((uint16_t)vp.addr, buffer, vp.size);
  #else
    dgus_display.WriteStringPGM((uint16_t)vp.addr, DGUS_MSG_UNDEF, vp.size);
  #endif
}

void DGUSTxHandler::LongestPrint(DGUS_VP &vp) {
=======
    dgus.writeString((uint16_t)vp.addr, buffer, vp.size);
  #else
    dgus.writeString((uint16_t)vp.addr, F("-"), vp.size);
  #endif
}

void DGUSTxHandler::longestPrint(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  #if ENABLED(PRINTCOUNTER)
    char buffer[21];
    ExtUI::getLongestPrint_str(buffer);

<<<<<<< HEAD
    dgus_display.WriteString((uint16_t)vp.addr, buffer, vp.size);
  #else
    dgus_display.WriteStringPGM((uint16_t)vp.addr, DGUS_MSG_UNDEF, vp.size);
  #endif
}

void DGUSTxHandler::FilamentUsed(DGUS_VP &vp) {
=======
    dgus.writeString((uint16_t)vp.addr, buffer, vp.size);
  #else
    dgus.writeString((uint16_t)vp.addr, F("-"), vp.size);
  #endif
}

void DGUSTxHandler::filamentUsed(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  #if ENABLED(PRINTCOUNTER)
    char buffer[21];
    ExtUI::getFilamentUsed_str(buffer);

<<<<<<< HEAD
    dgus_display.WriteString((uint16_t)vp.addr, buffer, vp.size);
  #else
    dgus_display.WriteStringPGM((uint16_t)vp.addr, DGUS_MSG_UNDEF, vp.size);
  #endif
}

void DGUSTxHandler::WaitIcons(DGUS_VP &vp) {
=======
    dgus.writeString((uint16_t)vp.addr, buffer, vp.size);
  #else
    dgus.writeString((uint16_t)vp.addr, F("-"), vp.size);
  #endif
}

void DGUSTxHandler::waitIcons(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  uint16_t icons = 0;

  if (ExtUI::isPrintingPaused()) {
    icons |= (uint16_t)DGUS_Data::WaitIcon::ABORT;

<<<<<<< HEAD
    dgus_display.EnableControl(DGUS_Screen::WAIT,
=======
    dgus.enableControl(DGUS_ScreenID::WAIT,
>>>>>>> origin/release-2.1.3-beta2
                               DGUSDisplay::POPUP_WINDOW,
                               DGUS_Control::ABORT);
  }
  else {
<<<<<<< HEAD
    dgus_display.DisableControl(DGUS_Screen::WAIT,
=======
    dgus.disableControl(DGUS_ScreenID::WAIT,
>>>>>>> origin/release-2.1.3-beta2
                                DGUSDisplay::POPUP_WINDOW,
                                DGUS_Control::ABORT);
  }

<<<<<<< HEAD
  if (dgus_screen_handler.wait_continue) {
    icons |= (uint16_t)DGUS_Data::WaitIcon::CONTINUE;

    dgus_display.EnableControl(DGUS_Screen::WAIT,
=======
  if (screen.wait_continue) {
    icons |= (uint16_t)DGUS_Data::WaitIcon::CONTINUE;

    dgus.enableControl(DGUS_ScreenID::WAIT,
>>>>>>> origin/release-2.1.3-beta2
                               DGUSDisplay::RETURN_KEY_CODE,
                               DGUS_Control::CONTINUE);
  }
  else {
<<<<<<< HEAD
    dgus_display.DisableControl(DGUS_Screen::WAIT,
=======
    dgus.disableControl(DGUS_ScreenID::WAIT,
>>>>>>> origin/release-2.1.3-beta2
                                DGUSDisplay::RETURN_KEY_CODE,
                                DGUS_Control::CONTINUE);
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::FanSpeed(DGUS_VP &vp) {
=======
  dgus.write((uint16_t)vp.addr, Swap16(icons));
}

void DGUSTxHandler::fanSpeed(DGUS_VP &vp) {
>>>>>>> origin/release-2.1.3-beta2
  uint16_t fan_speed;

  switch (vp.addr) {
    default: return;
    case DGUS_Addr::FAN0_Speed: fan_speed = ExtUI::getTargetFan_percent(ExtUI::FAN0); break;
  }

<<<<<<< HEAD
  dgus_display.Write((uint16_t)vp.addr, Swap16(fan_speed));
}

void DGUSTxHandler::Volume(DGUS_VP &vp) {
  const uint16_t volume = dgus_display.GetVolume();

  dgus_display.Write((uint16_t)vp.addr, Swap16(volume));
}

void DGUSTxHandler::Brightness(DGUS_VP &vp) {
  const uint16_t brightness = dgus_display.GetBrightness();

  dgus_display.Write((uint16_t)vp.addr, Swap16(brightness));
}

void DGUSTxHandler::ExtraToString(DGUS_VP &vp) {
  if (!vp.size || !vp.extra) return;

  dgus_display.WriteString((uint16_t)vp.addr, vp.extra, vp.size, true, false, false);
}

void DGUSTxHandler::ExtraPGMToString(DGUS_VP &vp) {
  if (!vp.size || !vp.extra) return;

  dgus_display.WriteStringPGM((uint16_t)vp.addr, vp.extra, vp.size, true, false, false);
=======
  dgus.write((uint16_t)vp.addr, Swap16(fan_speed));
}

void DGUSTxHandler::volume(DGUS_VP &vp) {
  const uint16_t volume = dgus.getVolume();

  dgus.write((uint16_t)vp.addr, Swap16(volume));
}

void DGUSTxHandler::brightness(DGUS_VP &vp) {
  const uint16_t brightness = dgus.getBrightness();

  dgus.write((uint16_t)vp.addr, Swap16(brightness));
}

void DGUSTxHandler::extraToString(DGUS_VP &vp) {
  if (!vp.size || !vp.extra) return;

  dgus.writeString((uint16_t)vp.addr, vp.extra, vp.size, true, false, false);
}

void DGUSTxHandler::extraPGMToString(DGUS_VP &vp) {
  if (!vp.size || !vp.extra) return;

  dgus.writeStringPGM((uint16_t)vp.addr, vp.extra, vp.size, true, false, false);
>>>>>>> origin/release-2.1.3-beta2
}

#endif // DGUS_LCD_UI_RELOADED
