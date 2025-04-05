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

#include "DGUSRxHandler.h"

#include "DGUSScreenHandler.h"
<<<<<<< HEAD
#include "config/DGUS_Screen.h"
=======
#include "config/DGUS_ScreenID.h"
>>>>>>> origin/release-2.1.3-beta2

#include "../ui_api.h"
#include "../../../core/language.h"
#include "../../../module/temperature.h"
#include "../../../module/printcounter.h"
#include "../../../module/stepper.h"
#include "../../../gcode/queue.h"
#if ENABLED(ADVANCED_PAUSE_FEATURE)
  #include "../../../feature/pause.h"
#endif
#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../../feature/powerloss.h"
#endif

<<<<<<< HEAD
void DGUSRxHandler::ScreenChange(DGUS_VP &vp, void *data_ptr) {
  const DGUS_Screen screen = (DGUS_Screen)((uint8_t*)data_ptr)[1];

  if (vp.addr == DGUS_Addr::SCREENCHANGE_SD) {
    #if ENABLED(SDSUPPORT)
      IF_DISABLED(HAS_SD_DETECT, card.mount());

      if (!ExtUI::isMediaInserted()) {
        dgus_screen_handler.SetStatusMessage(GET_TEXT_F(MSG_NO_MEDIA));
=======
void DGUSRxHandler::screenChange(DGUS_VP &vp, void *data_ptr) {
  const DGUS_ScreenID screenID = (DGUS_ScreenID)((uint8_t*)data_ptr)[1];

  if (vp.addr == DGUS_Addr::SCREENCHANGE_SD) {
    #if HAS_MEDIA
      IF_DISABLED(HAS_SD_DETECT, card.mount());

      if (!ExtUI::isMediaMounted()) {
        screen.setStatusMessage(GET_TEXT_F(MSG_NO_MEDIA));
>>>>>>> origin/release-2.1.3-beta2
        return;
      }

      card.cdroot();
    #else
<<<<<<< HEAD
      dgus_screen_handler.SetStatusMessage(GET_TEXT_F(MSG_NO_MEDIA));
=======
      screen.setStatusMessage(GET_TEXT_F(MSG_NO_MEDIA));
>>>>>>> origin/release-2.1.3-beta2
      return;
    #endif
  }

  if (vp.addr == DGUS_Addr::SCREENCHANGE_Idle
      && (ExtUI::isPrinting() || ExtUI::isPrintingPaused())) {
<<<<<<< HEAD
    dgus_screen_handler.SetStatusMessage(F("Impossible while printing"));
=======
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_NOT_WHILE_PRINTING));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  if (vp.addr == DGUS_Addr::SCREENCHANGE_Printing
      && (!ExtUI::isPrinting() && !ExtUI::isPrintingPaused())) {
<<<<<<< HEAD
    dgus_screen_handler.SetStatusMessage(F("Impossible while idle"));
    return;
  }

  dgus_screen_handler.TriggerScreenChange(screen);
}

#if ENABLED(SDSUPPORT)
  void DGUSRxHandler::Scroll(DGUS_VP &vp, void *data_ptr) {
=======
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_NOT_WHILE_IDLE));
    return;
  }

  screen.triggerScreenChange(screenID);
}

#if HAS_MEDIA
  void DGUSRxHandler::scroll(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
    UNUSED(vp);

    const DGUS_Data::Scroll scroll = (DGUS_Data::Scroll)((uint8_t*)data_ptr)[1];

    switch (scroll) {
      case DGUS_Data::Scroll::GO_BACK:
<<<<<<< HEAD
        if (dgus_screen_handler.filelist.isAtRootDir()) {
          return;
        }

        dgus_screen_handler.filelist_offset = 0;
        dgus_screen_handler.filelist_selected = -1;
        dgus_screen_handler.filelist.upDir();
        break;
      case DGUS_Data::Scroll::UP:
        if (dgus_screen_handler.filelist_offset < 1) {
          return;
        }

        --dgus_screen_handler.filelist_offset;
        break;
      case DGUS_Data::Scroll::DOWN:
        if (dgus_screen_handler.filelist_offset + 1 + DGUS_FILE_COUNT > dgus_screen_handler.filelist.count()) {
          return;
        }

        ++dgus_screen_handler.filelist_offset;
        break;
    }

    dgus_screen_handler.TriggerFullUpdate();
  }

  void DGUSRxHandler::SelectFile(DGUS_VP &vp, void *data_ptr) {
=======
        if (screen.filelist.isAtRootDir()) {
          return;
        }

        screen.filelist_offset = 0;
        screen.filelist_selected = -1;
        screen.filelist.upDir();
        break;
      case DGUS_Data::Scroll::UP:
        if (screen.filelist_offset < 1) {
          return;
        }

        --screen.filelist_offset;
        break;
      case DGUS_Data::Scroll::DOWN:
        if (screen.filelist_offset + 1 + DGUS_FILE_COUNT > screen.filelist.count()) {
          return;
        }

        ++screen.filelist_offset;
        break;
    }

    screen.triggerFullUpdate();
  }

  void DGUSRxHandler::selectFile(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
    UNUSED(vp);

    const uint8_t index = ((uint8_t*)data_ptr)[1];

<<<<<<< HEAD
    if (!dgus_screen_handler.filelist.seek(dgus_screen_handler.filelist_offset + index)) {
      return;
    }

    if (dgus_screen_handler.filelist.isDir()) {
      dgus_screen_handler.filelist_offset = 0;
      dgus_screen_handler.filelist_selected = -1;
      dgus_screen_handler.filelist.changeDir(dgus_screen_handler.filelist.filename());
    }
    else {
      dgus_screen_handler.filelist_selected = dgus_screen_handler.filelist_offset + index;
    }

    dgus_screen_handler.TriggerFullUpdate();
  }

  void DGUSRxHandler::PrintFile(DGUS_VP &vp, void *data_ptr) {
    UNUSED(vp);
    UNUSED(data_ptr);

    if (dgus_screen_handler.filelist_selected < 0) {
      dgus_screen_handler.SetStatusMessage(F("No file selected"));
      return;
    }

    if (!dgus_screen_handler.filelist.seek(dgus_screen_handler.filelist_selected)
        || dgus_screen_handler.filelist.isDir()) {
      return;
    }

    if (!dgus_screen_handler.IsPrinterIdle()) {
      dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
      return;
    }

    ExtUI::printFile(dgus_screen_handler.filelist.shortFilename());
    dgus_screen_handler.TriggerScreenChange(DGUS_Screen::PRINT_STATUS);
  }
#endif // SDSUPPORT

void DGUSRxHandler::PrintAbort(DGUS_VP &vp, void *data_ptr) {
=======
    if (!screen.filelist.seek(screen.filelist_offset + index)) {
      return;
    }

    if (screen.filelist.isDir()) {
      screen.filelist_offset = 0;
      screen.filelist_selected = -1;
      screen.filelist.changeDir(screen.filelist.filename());
    }
    else {
      screen.filelist_selected = screen.filelist_offset + index;
    }

    screen.triggerFullUpdate();
  }

  void DGUSRxHandler::printFile(DGUS_VP &vp, void *data_ptr) {
    UNUSED(vp);
    UNUSED(data_ptr);

    if (screen.filelist_selected < 0) {
      screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_NO_FILE_SELECTED));
      return;
    }

    if (!screen.filelist.seek(screen.filelist_selected)
        || screen.filelist.isDir()) {
      return;
    }

    if (!screen.isPrinterIdle()) {
      screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
      return;
    }

    ExtUI::printFile(screen.filelist.shortFilename());
    screen.triggerScreenChange(DGUS_ScreenID::PRINT_STATUS);
  }
#endif // HAS_MEDIA

void DGUSRxHandler::printAbort(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::Popup result = (DGUS_Data::Popup)((uint8_t*)data_ptr)[1];

  if (result != DGUS_Data::Popup::CONFIRMED) {
    return;
  }

  if (!ExtUI::isPrinting() && !ExtUI::isPrintingPaused()) {
<<<<<<< HEAD
    dgus_screen_handler.TriggerFullUpdate();
=======
    screen.triggerFullUpdate();
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  ExtUI::stopPrint();
}

<<<<<<< HEAD
void DGUSRxHandler::PrintPause(DGUS_VP &vp, void *data_ptr) {
=======
void DGUSRxHandler::printPause(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::Popup result = (DGUS_Data::Popup)((uint8_t*)data_ptr)[1];

  if (result != DGUS_Data::Popup::CONFIRMED) {
    return;
  }

  if (!ExtUI::isPrinting()) {
<<<<<<< HEAD
    dgus_screen_handler.TriggerFullUpdate();
=======
    screen.triggerFullUpdate();
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  ExtUI::pausePrint();
}

<<<<<<< HEAD
void DGUSRxHandler::PrintResume(DGUS_VP &vp, void *data_ptr) {
=======
void DGUSRxHandler::printResume(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::Popup result = (DGUS_Data::Popup)((uint8_t*)data_ptr)[1];

  if (result != DGUS_Data::Popup::CONFIRMED) {
    return;
  }

  if (!ExtUI::isPrintingPaused()) {
<<<<<<< HEAD
    dgus_screen_handler.TriggerFullUpdate();
    return;
  }

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
    screen.triggerFullUpdate();
    return;
  }

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  ExtUI::resumePrint();
}

<<<<<<< HEAD
void DGUSRxHandler::Feedrate(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const int16_t feedrate = Swap16(*(int16_t*)data_ptr);

  ExtUI::setFeedrate_percent(feedrate);

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::Flowrate(DGUS_VP &vp, void *data_ptr) {
  const int16_t flowrate = Swap16(*(int16_t*)data_ptr);
=======
void DGUSRxHandler::feedrate(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const int16_t feedrate = BE16_P(data_ptr);

  ExtUI::setFeedrate_percent(feedrate);

  screen.triggerFullUpdate();
}

void DGUSRxHandler::flowrate(DGUS_VP &vp, void *data_ptr) {
  const int16_t flowrate = BE16_P(data_ptr);
>>>>>>> origin/release-2.1.3-beta2

  switch (vp.addr) {
    default: return;
    case DGUS_Addr::ADJUST_SetFlowrate_CUR:
      ExtUI::setFlow_percent(flowrate, TERN(HAS_MULTI_EXTRUDER, ExtUI::getActiveTool(), ExtUI::E0));
      break;
    #if HAS_MULTI_EXTRUDER
      case DGUS_Addr::ADJUST_SetFlowrate_E0:
        ExtUI::setFlow_percent(flowrate, ExtUI::E0);
        break;
      case DGUS_Addr::ADJUST_SetFlowrate_E1:
        ExtUI::setFlow_percent(flowrate, ExtUI::E1);
        break;
    #endif
  }

<<<<<<< HEAD
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::BabystepSet(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const int16_t data = Swap16(*(int16_t*)data_ptr);
  const float offset = dgus_display.FromFixedPoint<int16_t, float, 2>(data);
=======
  screen.triggerFullUpdate();
}

void DGUSRxHandler::babystepSet(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const int16_t data = BE16_P(data_ptr);
  const float offset = dgus.fromFixedPoint<int16_t, float, 2>(data);
>>>>>>> origin/release-2.1.3-beta2

  const int16_t steps = ExtUI::mmToWholeSteps(offset - ExtUI::getZOffset_mm(), ExtUI::Z);

  ExtUI::smartAdjustAxis_steps(steps, ExtUI::Z, true);

<<<<<<< HEAD
  dgus_screen_handler.TriggerEEPROMSave();
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::Babystep(DGUS_VP &vp, void *data_ptr) {
=======
  screen.triggerEEPROMSave();
  screen.triggerFullUpdate();
}

void DGUSRxHandler::babystep(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::Adjust adjust = (DGUS_Data::Adjust)((uint8_t*)data_ptr)[1];
  int16_t steps;

  switch (adjust) {
    default: return;
    case DGUS_Data::Adjust::INCREMENT:
      steps = ExtUI::mmToWholeSteps(DGUS_PRINT_BABYSTEP, ExtUI::Z);
      break;
    case DGUS_Data::Adjust::DECREMENT:
      steps = ExtUI::mmToWholeSteps(-DGUS_PRINT_BABYSTEP, ExtUI::Z);
      break;
  }

  ExtUI::smartAdjustAxis_steps(steps, ExtUI::Z, true);

<<<<<<< HEAD
  dgus_screen_handler.TriggerEEPROMSave();
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::TempPreset(DGUS_VP &vp, void *data_ptr) {
=======
  screen.triggerEEPROMSave();
  screen.triggerFullUpdate();
}

void DGUSRxHandler::tempPreset(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::TempPreset preset = (DGUS_Data::TempPreset)((uint8_t*)data_ptr)[1];

  switch (preset) {
    case DGUS_Data::TempPreset::PLA:
      #if HOTENDS < 2
        ExtUI::setTargetTemp_celsius(DGUS_PLA_TEMP_HOTEND, ExtUI::H0);
      #else
        ExtUI::setTargetTemp_celsius(DGUS_PLA_TEMP_HOTEND, ExtUI::getActiveTool());
      #endif
      ExtUI::setTargetTemp_celsius(DGUS_PLA_TEMP_BED, ExtUI::BED);
      break;
    case DGUS_Data::TempPreset::ABS:
      #if HOTENDS < 2
        ExtUI::setTargetTemp_celsius(DGUS_ABS_TEMP_HOTEND, ExtUI::H0);
      #else
        ExtUI::setTargetTemp_celsius(DGUS_ABS_TEMP_HOTEND, ExtUI::getActiveTool());
      #endif
      ExtUI::setTargetTemp_celsius(DGUS_ABS_TEMP_BED, ExtUI::BED);
      break;
    case DGUS_Data::TempPreset::PETG:
      #if HOTENDS < 2
        ExtUI::setTargetTemp_celsius(DGUS_PETG_TEMP_HOTEND, ExtUI::H0);
      #else
        ExtUI::setTargetTemp_celsius(DGUS_PETG_TEMP_HOTEND, ExtUI::getActiveTool());
      #endif
      ExtUI::setTargetTemp_celsius(DGUS_PETG_TEMP_BED, ExtUI::BED);
      break;
  }

<<<<<<< HEAD
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::TempTarget(DGUS_VP &vp, void *data_ptr) {
  const int16_t temp = Swap16(*(int16_t*)data_ptr);
=======
  screen.triggerFullUpdate();
}

void DGUSRxHandler::tempTarget(DGUS_VP &vp, void *data_ptr) {
  const int16_t temp = BE16_P(data_ptr);
>>>>>>> origin/release-2.1.3-beta2

  switch (vp.addr) {
    default: return;
    case DGUS_Addr::TEMP_SetTarget_Bed:
      ExtUI::setTargetTemp_celsius(temp, ExtUI::BED);
      break;
    case DGUS_Addr::TEMP_SetTarget_H0:
      ExtUI::setTargetTemp_celsius(temp, ExtUI::H0);
      break;
    #if HAS_MULTI_HOTEND
      case DGUS_Addr::TEMP_SetTarget_H1:
        ExtUI::setTargetTemp_celsius(temp, ExtUI::H1);
        break;
    #endif
  }

<<<<<<< HEAD
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::TempCool(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const DGUS_Data::Heater heater = (DGUS_Data::Heater)Swap16(*(uint16_t*)data_ptr);
=======
  screen.triggerFullUpdate();
}

void DGUSRxHandler::tempCool(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const DGUS_Data::Heater heater = (DGUS_Data::Heater)BE16_P(data_ptr);
>>>>>>> origin/release-2.1.3-beta2

  switch (heater) {
    default: return;
    case DGUS_Data::Heater::ALL:
      ExtUI::setTargetTemp_celsius(0, ExtUI::BED);
      ExtUI::setTargetTemp_celsius(0, ExtUI::H0);
      #if HAS_MULTI_HOTEND
        ExtUI::setTargetTemp_celsius(0, ExtUI::H1);
      #endif
      break;
    case DGUS_Data::Heater::BED:
      ExtUI::setTargetTemp_celsius(0, ExtUI::BED);
      break;
    case DGUS_Data::Heater::H0:
      ExtUI::setTargetTemp_celsius(0, ExtUI::H0);
      break;
    #if HAS_MULTI_HOTEND
      case DGUS_Data::Heater::H1:
        ExtUI::setTargetTemp_celsius(0, ExtUI::H1);
        break;
    #endif
  }

<<<<<<< HEAD
  dgus_screen_handler.SetStatusMessage(F("Cooling..."));

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::Steppers(DGUS_VP &vp, void *data_ptr) {
=======
  screen.setStatusMessage(GET_TEXT_F(MSG_COOLING));

  screen.triggerFullUpdate();
}

void DGUSRxHandler::steppers(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::Control control = (DGUS_Data::Control)((uint8_t*)data_ptr)[1];

  switch (control) {
    case DGUS_Data::Control::ENABLE:
      stepper.enable_all_steppers();
      break;
    case DGUS_Data::Control::DISABLE:
      stepper.disable_all_steppers();
      break;
  }

<<<<<<< HEAD
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::ZOffset(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!ExtUI::isAxisPositionKnown(ExtUI::Z)) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_HOMING_REQUIRED));
    return;
  }

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
    return;
  }

  const int16_t data = Swap16(*(int16_t*)data_ptr);
  const float offset = dgus_display.FromFixedPoint<int16_t, float, 2>(data);
=======
  screen.triggerFullUpdate();
}

void DGUSRxHandler::zOffset(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (TERN0(NO_MOTION_BEFORE_HOMING, !ExtUI::isAxisPositionKnown(ExtUI::Z))) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_HOMING_REQUIRED));
    return;
  }

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
    return;
  }

  const int16_t data = BE16_P(data_ptr);
  const float offset = dgus.fromFixedPoint<int16_t, float, 2>(data);
>>>>>>> origin/release-2.1.3-beta2

  const int16_t steps = ExtUI::mmToWholeSteps(offset - ExtUI::getZOffset_mm(), ExtUI::Z);

  ExtUI::smartAdjustAxis_steps(steps, ExtUI::Z, true);

<<<<<<< HEAD
  dgus_screen_handler.TriggerEEPROMSave();
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::ZOffsetStep(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!ExtUI::isAxisPositionKnown(ExtUI::Z)) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_HOMING_REQUIRED));
    return;
  }

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
  screen.triggerEEPROMSave();
  screen.triggerFullUpdate();
}

void DGUSRxHandler::zOffsetStep(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (TERN0(NO_MOTION_BEFORE_HOMING, !ExtUI::isAxisPositionKnown(ExtUI::Z))) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_HOMING_REQUIRED));
    return;
  }

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  const DGUS_Data::Adjust adjust = (DGUS_Data::Adjust)((uint8_t*)data_ptr)[1];
  int16_t steps;

<<<<<<< HEAD
  switch (dgus_screen_handler.offset_steps) {
=======
  switch (screen.offset_steps) {
>>>>>>> origin/release-2.1.3-beta2
    default: return;
    case DGUS_Data::StepSize::MMP1:
      steps = ExtUI::mmToWholeSteps((adjust == DGUS_Data::Adjust::INCREMENT ? 0.1f : -0.1f), ExtUI::Z);
      break;
    case DGUS_Data::StepSize::MMP01:
      steps = ExtUI::mmToWholeSteps((adjust == DGUS_Data::Adjust::INCREMENT ? 0.01f : -0.01f), ExtUI::Z);
      break;
  }

  ExtUI::smartAdjustAxis_steps(steps, ExtUI::Z, true);

<<<<<<< HEAD
  dgus_screen_handler.TriggerEEPROMSave();
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::ZOffsetSetStep(DGUS_VP &vp, void *data_ptr) {
=======
  screen.triggerEEPROMSave();
  screen.triggerFullUpdate();
}

void DGUSRxHandler::zOffsetSetStep(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::StepSize size = (DGUS_Data::StepSize)((uint8_t*)data_ptr)[1];

<<<<<<< HEAD
  dgus_screen_handler.offset_steps = size;

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::MoveToPoint(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!ExtUI::isPositionKnown()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_HOMING_REQUIRED));
    return;
  }

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
  screen.offset_steps = size;

  screen.triggerFullUpdate();
}

void DGUSRxHandler::moveToPoint(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!ExtUI::isPositionKnown()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_HOMING_REQUIRED));
    return;
  }

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  const uint8_t point = ((uint8_t*)data_ptr)[1];
  constexpr float lfrb[4] = BED_TRAMMING_INSET_LFRB;
  float x, y;

  switch (point) {
    default: return;
    case 1:
      x = DGUS_LEVEL_CENTER_X;
      y = DGUS_LEVEL_CENTER_Y;
      break;
    case 2:
<<<<<<< HEAD
      x = X_MIN_POS + lfrb[0];
      y = Y_MIN_POS + lfrb[1];
      break;
    case 3:
      x = X_MAX_POS - lfrb[2];
      y = Y_MIN_POS + lfrb[1];
      break;
    case 4:
      x = X_MAX_POS - lfrb[2];
      y = Y_MAX_POS - lfrb[3];
      break;
    case 5:
      x = X_MIN_POS + lfrb[0];
      y = Y_MAX_POS - lfrb[3];
      break;
  }

  if (ExtUI::getAxisPosition_mm(ExtUI::Z) < Z_MIN_POS + BED_TRAMMING_Z_HOP) {
    ExtUI::setAxisPosition_mm(Z_MIN_POS + BED_TRAMMING_Z_HOP, ExtUI::Z);
  }
  ExtUI::setAxisPosition_mm(x, ExtUI::X);
  ExtUI::setAxisPosition_mm(y, ExtUI::Y);
  ExtUI::setAxisPosition_mm(Z_MIN_POS + BED_TRAMMING_HEIGHT, ExtUI::Z);
}

void DGUSRxHandler::Probe(DGUS_VP &vp, void *data_ptr) {
=======
      x = X_MIN_BED + lfrb[0];
      y = Y_MIN_BED + lfrb[1];
      break;
    case 3:
      x = X_MAX_BED - lfrb[2];
      y = Y_MIN_BED + lfrb[1];
      break;
    case 4:
      x = X_MAX_BED - lfrb[2];
      y = Y_MAX_BED - lfrb[3];
      break;
    case 5:
      x = X_MIN_BED + lfrb[0];
      y = Y_MAX_BED - lfrb[3];
      break;
  }

  if (BED_TRAMMING_Z_HOP)
    ExtUI::setAxisPosition_mm(ExtUI::getAxisPosition_mm(ExtUI::Z) + (BED_TRAMMING_Z_HOP), ExtUI::Z);
  ExtUI::setAxisPosition_mm(x, ExtUI::X);
  ExtUI::setAxisPosition_mm(y, ExtUI::Y);
  ExtUI::setAxisPosition_mm((Z_MIN_POS) + (BED_TRAMMING_HEIGHT), ExtUI::Z);
}

void DGUSRxHandler::probe(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);
  UNUSED(data_ptr);

  #if ENABLED(MESH_BED_LEVELING)
<<<<<<< HEAD
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_ABL_REQUIRED));
=======
    screen.setStatusMessage(FPSTR(DGUS_MSG_ABL_REQUIRED));
>>>>>>> origin/release-2.1.3-beta2
    return;
  #endif

  if (!ExtUI::isPositionKnown()) {
<<<<<<< HEAD
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_HOMING_REQUIRED));
    return;
  }

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
    return;
  }

  dgus_screen_handler.TriggerScreenChange(DGUS_Screen::LEVELING_PROBING);
=======
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_HOMING_REQUIRED));
    return;
  }

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
    return;
  }

  screen.triggerScreenChange(DGUS_ScreenID::LEVELING_PROBING);
>>>>>>> origin/release-2.1.3-beta2

  #if ENABLED(AUTO_BED_LEVELING_UBL)
    queue.enqueue_now(F("G29P1\nG29P3\nG29P5C"));
  #else
    queue.enqueue_now(F("G29"));
  #endif
<<<<<<< HEAD
  queue.enqueue_now_P(DGUS_CMD_EEPROM_SAVE);
}

void DGUSRxHandler::DisableABL(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
  queue.enqueue_now(F("M500"));
}

void DGUSRxHandler::disableABL(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  ExtUI::setLevelingActive(false);

<<<<<<< HEAD
  dgus_screen_handler.TriggerEEPROMSave();
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::FilamentSelect(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const DGUS_Data::Extruder extruder = (DGUS_Data::Extruder)Swap16(*(uint16_t*)data_ptr);
=======
  screen.triggerEEPROMSave();
  screen.triggerFullUpdate();
}

void DGUSRxHandler::filamentSelect(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const DGUS_Data::Extruder extruder = (DGUS_Data::Extruder)BE16_P(data_ptr);
>>>>>>> origin/release-2.1.3-beta2

  switch (extruder) {
    default: return;
    case DGUS_Data::Extruder::CURRENT:
    case DGUS_Data::Extruder::E0:
    E_TERN_(case DGUS_Data::Extruder::E1:)
<<<<<<< HEAD
      dgus_screen_handler.filament_extruder = extruder;
      break;
  }

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::FilamentLength(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const uint16_t length = Swap16(*(uint16_t*)data_ptr);

  dgus_screen_handler.filament_length = constrain(length, 0, EXTRUDE_MAXLENGTH);

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::FilamentMove(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
      screen.filament_extruder = extruder;
      break;
  }

  screen.triggerFullUpdate();
}

void DGUSRxHandler::filamentLength(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const uint16_t length = BE16_P(data_ptr);

  screen.filament_length = constrain(length, 0, EXTRUDE_MAXLENGTH);

  screen.triggerFullUpdate();
}

void DGUSRxHandler::filamentMove(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  ExtUI::extruder_t extruder;

<<<<<<< HEAD
  switch (dgus_screen_handler.filament_extruder) {
=======
  switch (screen.filament_extruder) {
>>>>>>> origin/release-2.1.3-beta2
    default: return;
    case DGUS_Data::Extruder::CURRENT:
      #if HAS_MULTI_EXTRUDER
        extruder = ExtUI::getActiveTool();
        break;
      #endif
    case DGUS_Data::Extruder::E0:
      extruder = ExtUI::E0;
      break;
    #if HAS_MULTI_EXTRUDER
      case DGUS_Data::Extruder::E1:
        extruder = ExtUI::E1;
        break;
    #endif
  }

  if (ExtUI::getActualTemp_celsius(extruder) < (float)EXTRUDE_MINTEMP) {
<<<<<<< HEAD
    dgus_screen_handler.SetStatusMessage(F("Temperature too low"));
=======
    screen.setStatusMessage(GET_TEXT_F(MSG_TEMP_TOO_LOW));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  const DGUS_Data::FilamentMove move = (DGUS_Data::FilamentMove)((uint8_t*)data_ptr)[1];

  switch (move) {
    case DGUS_Data::FilamentMove::RETRACT:
<<<<<<< HEAD
      UI_DECREMENT_BY(AxisPosition_mm, (float)dgus_screen_handler.filament_length, extruder);
      break;
    case DGUS_Data::FilamentMove::EXTRUDE:
      UI_INCREMENT_BY(AxisPosition_mm, (float)dgus_screen_handler.filament_length, extruder);
=======
      UI_DECREMENT_BY(AxisPosition_mm, (float)screen.filament_length, extruder);
      break;
    case DGUS_Data::FilamentMove::EXTRUDE:
      UI_INCREMENT_BY(AxisPosition_mm, (float)screen.filament_length, extruder);
>>>>>>> origin/release-2.1.3-beta2
      break;
  }
}

<<<<<<< HEAD
void DGUSRxHandler::Home(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
void DGUSRxHandler::home(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  DGUS_Data::Axis axis = (DGUS_Data::Axis)((uint8_t*)data_ptr)[1];

<<<<<<< HEAD
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 1);
  dgus_screen_handler.SetMessageLinePGM(DGUS_MSG_HOMING, 2);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 3);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 4);
  dgus_screen_handler.ShowWaitScreen(dgus_screen_handler.GetCurrentScreen());
=======
  screen.showWaitScreen(GET_TEXT_F(DGUS_MSG_HOMING), screen.getCurrentScreen());
>>>>>>> origin/release-2.1.3-beta2

  switch (axis) {
    case DGUS_Data::Axis::X_Y_Z:
      queue.enqueue_now(F("G28XYZ"));
      break;
    case DGUS_Data::Axis::X_Y:
      queue.enqueue_now(F("G28XY"));
      break;
    case DGUS_Data::Axis::Z:
      queue.enqueue_now(F("G28Z"));
      break;
  }
}

<<<<<<< HEAD
void DGUSRxHandler::Move(DGUS_VP &vp, void *data_ptr) {
  const int16_t data = Swap16(*(int16_t*)data_ptr);
  const float position = dgus_display.FromFixedPoint<int16_t, float, 1>(data);
=======
void DGUSRxHandler::move(DGUS_VP &vp, void *data_ptr) {
  const int16_t data = BE16_P(data_ptr);
  const float position = dgus.fromFixedPoint<int16_t, float, 1>(data);
>>>>>>> origin/release-2.1.3-beta2
  ExtUI::axis_t axis;

  switch (vp.addr) {
    default: return;
<<<<<<< HEAD
    case DGUS_Addr::MOVE_SetX:
      axis = ExtUI::X;
      break;
    case DGUS_Addr::MOVE_SetY:
      axis = ExtUI::Y;
      break;
    case DGUS_Addr::MOVE_SetZ:
      axis = ExtUI::Z;
      break;
  }

  if (!ExtUI::isAxisPositionKnown(axis)) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_HOMING_REQUIRED));
=======
    case DGUS_Addr::MOVE_SetX: axis = ExtUI::X; break;
    case DGUS_Addr::MOVE_SetY: axis = ExtUI::Y; break;
    case DGUS_Addr::MOVE_SetZ: axis = ExtUI::Z; break;
  }

  if (TERN0(NO_MOTION_BEFORE_HOMING, !ExtUI::isAxisPositionKnown(axis))) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_HOMING_REQUIRED));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  ExtUI::setAxisPosition_mm(position, axis);

<<<<<<< HEAD
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::MoveStep(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  float offset;

  switch (dgus_screen_handler.move_steps) {
    default: return;
    case DGUS_Data::StepSize::MM10:
      offset = 10.0f;
      break;
    case DGUS_Data::StepSize::MM1:
      offset = 1.0f;
      break;
    case DGUS_Data::StepSize::MMP1:
      offset = 0.1f;
      break;
=======
  screen.triggerFullUpdate();
}

void DGUSRxHandler::moveStep(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  float offset;
  switch (screen.move_steps) {
    default: return;
    case DGUS_Data::StepSize::MM10: offset = 10.0f; break;
    case DGUS_Data::StepSize::MM1: offset = 1.0f; break;
    case DGUS_Data::StepSize::MMP1: offset = 0.1f; break;
>>>>>>> origin/release-2.1.3-beta2
  }

  const DGUS_Data::MoveDirection direction = (DGUS_Data::MoveDirection)((uint8_t*)data_ptr)[1];
  ExtUI::axis_t axis;

  switch (direction) {
    default: return;
<<<<<<< HEAD
    case DGUS_Data::MoveDirection::XP:
      axis = ExtUI::X;
      break;
    case DGUS_Data::MoveDirection::XM:
      axis = ExtUI::X;
      offset = -offset;
      break;
    case DGUS_Data::MoveDirection::YP:
      axis = ExtUI::Y;
      break;
    case DGUS_Data::MoveDirection::YM:
      axis = ExtUI::Y;
      offset = -offset;
      break;
    case DGUS_Data::MoveDirection::ZP:
      axis = ExtUI::Z;
      break;
    case DGUS_Data::MoveDirection::ZM:
      axis = ExtUI::Z;
      offset = -offset;
      break;
  }

  if (!ExtUI::isAxisPositionKnown(axis)) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_HOMING_REQUIRED));
=======
    case DGUS_Data::MoveDirection::XM: offset = -offset;
    case DGUS_Data::MoveDirection::XP: axis = ExtUI::X; break;
    case DGUS_Data::MoveDirection::YM: offset = -offset;
    case DGUS_Data::MoveDirection::YP: axis = ExtUI::Y; break;
    case DGUS_Data::MoveDirection::ZM: offset = -offset;
    case DGUS_Data::MoveDirection::ZP: axis = ExtUI::Z; break;
  }

  if (TERN0(NO_MOTION_BEFORE_HOMING, !ExtUI::isAxisPositionKnown(axis))) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_HOMING_REQUIRED));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  UI_INCREMENT_BY(AxisPosition_mm, offset, axis);

<<<<<<< HEAD
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::MoveSetStep(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const DGUS_Data::StepSize size = (DGUS_Data::StepSize)((uint8_t*)data_ptr)[1];

  dgus_screen_handler.move_steps = size;

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::GcodeClear(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  ZERO(dgus_screen_handler.gcode);

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::GcodeExecute(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  if (!strlen(dgus_screen_handler.gcode)) {
    return;
  }

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
    return;
  }

  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 1);
  dgus_screen_handler.SetMessageLinePGM(PSTR("Executing command..."), 2);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 3);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 4);
  dgus_screen_handler.ShowWaitScreen(DGUS_Screen::GCODE);

  queue.enqueue_one_now(dgus_screen_handler.gcode);
}

void DGUSRxHandler::ResetEEPROM(DGUS_VP &vp, void *data_ptr) {
=======
  screen.triggerFullUpdate();
}

void DGUSRxHandler::moveSetStep(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const DGUS_Data::StepSize size = (DGUS_Data::StepSize)((uint8_t*)data_ptr)[1];
  screen.move_steps = size;

  screen.triggerFullUpdate();
}

void DGUSRxHandler::gcodeClear(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  ZERO(screen.gcode);

  screen.triggerFullUpdate();
}

void DGUSRxHandler::gcodeExecute(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  if (!strlen(screen.gcode)) return;

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
    return;
  }

  screen.showWaitScreen(GET_TEXT_F(DGUS_MSG_EXECUTING_COMMAND), DGUS_ScreenID::GCODE);

  queue.enqueue_one_now(screen.gcode);
}

void DGUSRxHandler::resetEEPROM(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::Popup result = (DGUS_Data::Popup)((uint8_t*)data_ptr)[1];

<<<<<<< HEAD
  if (result != DGUS_Data::Popup::CONFIRMED) {
    return;
  }

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
  if (result != DGUS_Data::Popup::CONFIRMED) return;

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  queue.enqueue_now(F("M502"));
<<<<<<< HEAD
  queue.enqueue_now_P(DGUS_CMD_EEPROM_SAVE);
}

void DGUSRxHandler::SettingsExtra(DGUS_VP &vp, void *data_ptr) {
=======
  queue.enqueue_now(F("M500"));
}

void DGUSRxHandler::settingsExtra(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::Extra extra = (DGUS_Data::Extra)((uint8_t*)data_ptr)[1];

  switch (extra) {
    default: return;
    case DGUS_Data::Extra::BUTTON1:
      #if ENABLED(BLTOUCH)
<<<<<<< HEAD
        if (!dgus_screen_handler.IsPrinterIdle()) {
          dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
        if (!screen.isPrinterIdle()) {
          screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
          return;
        }

        queue.enqueue_now(F(DGUS_RESET_BLTOUCH));
      #else
<<<<<<< HEAD
        dgus_screen_handler.TriggerScreenChange(DGUS_Screen::INFOS);
=======
        screen.triggerScreenChange(DGUS_ScreenID::INFOS);
>>>>>>> origin/release-2.1.3-beta2
      #endif
      break;
    #if ENABLED(BLTOUCH)
      case DGUS_Data::Extra::BUTTON2:
<<<<<<< HEAD
        dgus_screen_handler.TriggerScreenChange(DGUS_Screen::INFOS);
=======
        screen.triggerScreenChange(DGUS_ScreenID::INFOS);
>>>>>>> origin/release-2.1.3-beta2
        break;
    #endif
  }
}

<<<<<<< HEAD
void DGUSRxHandler::PIDSelect(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const DGUS_Data::Heater heater = (DGUS_Data::Heater)Swap16(*(uint16_t*)data_ptr);
=======
void DGUSRxHandler::pidSelect(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  const DGUS_Data::Heater heater = (DGUS_Data::Heater)BE16_P(data_ptr);
>>>>>>> origin/release-2.1.3-beta2

  switch (heater) {
    default: return;
    case DGUS_Data::Heater::BED:
<<<<<<< HEAD
      dgus_screen_handler.pid_temp = DGUS_PLA_TEMP_BED;
      dgus_screen_handler.pid_heater = heater;
=======
      screen.pid_temp = DGUS_PLA_TEMP_BED;
      screen.pid_heater = heater;
>>>>>>> origin/release-2.1.3-beta2
      break;
    case DGUS_Data::Heater::H0:
    #if HAS_MULTI_HOTEND
      case DGUS_Data::Heater::H1:
    #endif
<<<<<<< HEAD
      dgus_screen_handler.pid_temp = DGUS_PLA_TEMP_HOTEND;
      dgus_screen_handler.pid_heater = heater;
      break;
  }

  dgus_screen_handler.pid_cycles = 5;

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::PIDSetTemp(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
    return;
  }

  uint16_t temp = Swap16(*(uint16_t*)data_ptr);

  switch (dgus_screen_handler.pid_heater) {
    default: return;
    case DGUS_Data::Heater::BED:
      temp = constrain(temp, BED_MINTEMP, BED_MAX_TARGET);
      break;
    case DGUS_Data::Heater::H0:
      temp = constrain(temp, HEATER_0_MINTEMP, (HEATER_0_MAXTEMP - HOTEND_OVERSHOOT));
      break;
    #if HAS_MULTI_HOTEND
      case DGUS_Data::Heater::H1:
        temp = constrain(temp, HEATER_1_MINTEMP, (HEATER_1_MAXTEMP - HOTEND_OVERSHOOT));
=======
      screen.pid_temp = DGUS_PLA_TEMP_HOTEND;
      screen.pid_heater = heater;
      break;
  }

  screen.pid_cycles = 5;

  screen.triggerFullUpdate();
}

void DGUSRxHandler::pidSetTemp(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
    return;
  }

  celsius_t temp = BE16_P(data_ptr);

  switch (screen.pid_heater) {
    default: return;
    #if HAS_HEATED_BED
      case DGUS_Data::Heater::BED:
        LIMIT(temp, celsius_t(BED_MINTEMP), celsius_t(BED_MAX_TARGET));
        break;
    #endif
    #if HAS_HOTEND
      case DGUS_Data::Heater::H0:
        LIMIT(temp, celsius_t(HEATER_0_MINTEMP), thermalManager.hotend_max_target(0));
        break;
    #endif
    #if HAS_MULTI_HOTEND
      case DGUS_Data::Heater::H1:
        LIMIT(temp, celsius_t(HEATER_1_MINTEMP), thermalManager.hotend_max_target(0));
>>>>>>> origin/release-2.1.3-beta2
        break;
    #endif
  }

<<<<<<< HEAD
  dgus_screen_handler.pid_temp = temp;

  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::PIDRun(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  if (!dgus_screen_handler.IsPrinterIdle()) {
    dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
  screen.pid_temp = temp;

  screen.triggerFullUpdate();
}

void DGUSRxHandler::pidRun(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  if (!screen.isPrinterIdle()) {
    screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  heater_id_t heater;
<<<<<<< HEAD
  uint8_t cycles = constrain(dgus_screen_handler.pid_cycles, 3, 10);

  switch (dgus_screen_handler.pid_heater) {
=======
  uint8_t cycles = constrain(screen.pid_cycles, 3, 10);

  switch (screen.pid_heater) {
>>>>>>> origin/release-2.1.3-beta2
    default: return;
    case DGUS_Data::Heater::BED:
      #if ENABLED(PIDTEMPBED)
        heater = H_BED;
        break;
      #else
<<<<<<< HEAD
        dgus_screen_handler.SetStatusMessage(F("Bed PID disabled"));
=======
        screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BED_PID_DISABLED));
>>>>>>> origin/release-2.1.3-beta2
        return;
      #endif
    case DGUS_Data::Heater::H0:
      #if ENABLED(PIDTEMP)
        heater = H_E0;
        break;
      #else
<<<<<<< HEAD
        dgus_screen_handler.SetStatusMessage(F("PID disabled"));
=======
        screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_PID_DISABLED));
>>>>>>> origin/release-2.1.3-beta2
        return;
      #endif
    #if HAS_MULTI_HOTEND
      case DGUS_Data::Heater::H1:
        #if ENABLED(PIDTEMP)
          heater = H_E1;
          break;
        #else
<<<<<<< HEAD
          dgus_screen_handler.SetStatusMessage(F("PID disabled"));
=======
          screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_PID_DISABLED));
>>>>>>> origin/release-2.1.3-beta2
          return;
        #endif
    #endif
  }

  char buffer[24];
<<<<<<< HEAD
  snprintf_P(buffer, sizeof(buffer), PSTR("M303C%dE%dS%dU1"), cycles, heater, dgus_screen_handler.pid_temp);

  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 1);
  dgus_screen_handler.SetMessageLinePGM(PSTR("PID autotuning..."), 2);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 3);
  dgus_screen_handler.SetMessageLinePGM(NUL_STR, 4);
  dgus_screen_handler.ShowWaitScreen(DGUS_Screen::PID);

  queue.enqueue_one_now(buffer);
  queue.enqueue_now_P(DGUS_CMD_EEPROM_SAVE);
}

#if ENABLED(POWER_LOSS_RECOVERY)
  void DGUSRxHandler::PowerLossAbort(DGUS_VP &vp, void *data_ptr) {
=======
  snprintf_P(buffer, sizeof(buffer), PSTR("M303C%dE%dS%dU1"), cycles, heater, screen.pid_temp);

  screen.showWaitScreen(GET_TEXT_F(DGUS_MSG_PID_AUTOTUNING), DGUS_ScreenID::PID);

  queue.enqueue_one_now(buffer);
  queue.enqueue_now(F("M500"));
}

#if ENABLED(POWER_LOSS_RECOVERY)
  void DGUSRxHandler::powerLossAbort(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
    UNUSED(vp);

    const DGUS_Data::Popup result = (DGUS_Data::Popup)((uint8_t*)data_ptr)[1];

    if (result != DGUS_Data::Popup::CONFIRMED) {
      return;
    }

<<<<<<< HEAD
    if (!dgus_screen_handler.IsPrinterIdle()) {
      dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
      return;
    }

    dgus_screen_handler.TriggerScreenChange(DGUS_Screen::HOME);
=======
    if (!screen.isPrinterIdle()) {
      screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
      return;
    }

    screen.triggerScreenChange(DGUS_ScreenID::HOME);
>>>>>>> origin/release-2.1.3-beta2

    queue.enqueue_now(F("M1000C"));
  }

<<<<<<< HEAD
  void DGUSRxHandler::PowerLossResume(DGUS_VP &vp, void *data_ptr) {
=======
  void DGUSRxHandler::powerLossResume(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
    UNUSED(vp);

    const DGUS_Data::Popup result = (DGUS_Data::Popup)((uint8_t*)data_ptr)[1];

    if (result != DGUS_Data::Popup::CONFIRMED) {
      return;
    }

<<<<<<< HEAD
    if (!dgus_screen_handler.IsPrinterIdle()) {
      dgus_screen_handler.SetStatusMessage(FPSTR(DGUS_MSG_BUSY));
=======
    if (!screen.isPrinterIdle()) {
      screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_BUSY));
>>>>>>> origin/release-2.1.3-beta2
      return;
    }

    if (!recovery.valid()) {
<<<<<<< HEAD
      dgus_screen_handler.SetStatusMessage(F("Invalid recovery data"));
      return;
    }

    dgus_screen_handler.TriggerScreenChange(DGUS_Screen::PRINT_STATUS);
=======
      screen.setStatusMessage(GET_TEXT_F(DGUS_MSG_INVALID_RECOVERY_DATA));
      return;
    }

    screen.triggerScreenChange(DGUS_ScreenID::PRINT_STATUS);
>>>>>>> origin/release-2.1.3-beta2

    queue.enqueue_now(F("M1000"));
  }
#endif // POWER_LOSS_RECOVERY

<<<<<<< HEAD
void DGUSRxHandler::WaitAbort(DGUS_VP &vp, void *data_ptr) {
=======
void DGUSRxHandler::waitAbort(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);

  const DGUS_Data::Popup result = (DGUS_Data::Popup)((uint8_t*)data_ptr)[1];

  if (result != DGUS_Data::Popup::CONFIRMED) {
    return;
  }

  if (!ExtUI::isPrintingPaused()) {
<<<<<<< HEAD
    dgus_screen_handler.TriggerFullUpdate();
=======
    screen.triggerFullUpdate();
>>>>>>> origin/release-2.1.3-beta2
    return;
  }

  ExtUI::stopPrint();

<<<<<<< HEAD
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::WaitContinue(DGUS_VP &vp, void *data_ptr) {
=======
  screen.triggerFullUpdate();
}

void DGUSRxHandler::waitContinue(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  UNUSED(vp);
  UNUSED(data_ptr);

  ExtUI::setUserConfirmed();

<<<<<<< HEAD
  dgus_screen_handler.TriggerFullUpdate();
}

void DGUSRxHandler::FanSpeed(DGUS_VP &vp, void *data_ptr) {
=======
  screen.triggerFullUpdate();
}

void DGUSRxHandler::fanSpeed(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  uint8_t speed = ((uint8_t*)data_ptr)[1];
  switch (vp.addr) {
    default: return;
    case DGUS_Addr::FAN0_Speed:
      ExtUI::setTargetFan_percent(speed, ExtUI::FAN0);
      break;
  }
}

<<<<<<< HEAD
void DGUSRxHandler::Volume(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  uint8_t volume = ((uint8_t*)data_ptr)[1];
  dgus_display.SetVolume(volume);

  dgus_screen_handler.TriggerEEPROMSave();
}

void DGUSRxHandler::Brightness(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  uint8_t brightness = ((uint8_t*)data_ptr)[1];
  dgus_display.SetBrightness(brightness);

  dgus_screen_handler.TriggerEEPROMSave();
}

void DGUSRxHandler::Debug(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  ++dgus_screen_handler.debug_count;

  if (dgus_screen_handler.debug_count >= 10) {
    dgus_screen_handler.TriggerScreenChange(DGUS_Screen::DEBUG);
  }
}

void DGUSRxHandler::StringToExtra(DGUS_VP &vp, void *data_ptr) {
=======
void DGUSRxHandler::volume(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  uint8_t volume = ((uint8_t*)data_ptr)[1];
  dgus.setVolume(volume);

  screen.triggerEEPROMSave();
}

void DGUSRxHandler::brightness(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);

  uint8_t brightness = ((uint8_t*)data_ptr)[1];
  dgus.setBrightness(brightness);

  screen.triggerEEPROMSave();
}

void DGUSRxHandler::debug(DGUS_VP &vp, void *data_ptr) {
  UNUSED(vp);
  UNUSED(data_ptr);

  ++screen.debug_count;

  if (screen.debug_count >= 10) {
    screen.triggerScreenChange(DGUS_ScreenID::DEBUG);
  }
}

void DGUSRxHandler::stringToExtra(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
  if (!vp.size || !vp.extra) return;
  memcpy(vp.extra, data_ptr, vp.size);
}

#endif // DGUS_LCD_UI_RELOADED
