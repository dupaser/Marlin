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

#include "../../../inc/MarlinConfigPre.h"

#if HAS_DGUS_LCD_CLASSIC

#include "DGUSScreenHandler.h"

#include "../../../MarlinCore.h"
#include "../../../gcode/queue.h"
#include "../../../libs/duration_t.h"
#include "../../../module/settings.h"
#include "../../../module/temperature.h"
#include "../../../module/motion.h"
#include "../../../module/planner.h"
#include "../../../module/printcounter.h"
#include "../../../sd/cardreader.h"
<<<<<<< HEAD
#include "../../../feature/runout.h"


#include "../../../feature/hotend_idle.h" //Свое для ресета таймаута

=======
>>>>>>> origin/release-2.1.3-beta2

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../../feature/powerloss.h"
#endif

<<<<<<< HEAD
DGUSScreenHandlerClass ScreenHandler;

uint16_t DGUSScreenHandler::ConfirmVP;
DGUSLCD_Screens DGUSScreenHandler::current_screen;
DGUSLCD_Screens DGUSScreenHandler::past_screens[NUM_PAST_SCREENS];
uint8_t DGUSScreenHandler::update_ptr;
uint16_t DGUSScreenHandler::skipVP;
bool DGUSScreenHandler::ScreenComplete;

void (*DGUSScreenHandler::confirm_action_cb)() = nullptr;

#if ENABLED(SDSUPPORT)
=======
DGUSScreenHandlerClass screen;

uint16_t DGUSScreenHandler::confirmVP;

DGUS_ScreenID DGUSScreenHandler::current_screenID;
DGUS_ScreenID DGUSScreenHandler::past_screenIDs[NUM_PAST_SCREENS];
uint8_t DGUSScreenHandler::update_ptr;
uint16_t DGUSScreenHandler::skipVP;
bool DGUSScreenHandler::screenComplete;

void (*DGUSScreenHandler::confirm_action_cb)() = nullptr;

#if HAS_MEDIA
>>>>>>> origin/release-2.1.3-beta2
  int16_t DGUSScreenHandler::top_file = 0,
          DGUSScreenHandler::file_to_print = 0;
  ExtUI::FileList filelist;
#endif

#if ENABLED(DGUS_FILAMENT_LOADUNLOAD)
  filament_data_t filament_data;
#endif

<<<<<<< HEAD
void DGUSScreenHandler::sendinfoscreen(PGM_P const line1, PGM_P const line2, PGM_P const line3, PGM_P const line4, bool l1inflash, bool l2inflash, bool l3inflash, bool l4inflash) {
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_MSGSTR1, &ramcopy)) {
    ramcopy.memadr = (void*) line1;
    l1inflash ? DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::DGUSLCD_SendStringToDisplay(ramcopy);
  }
  if (populate_VPVar(VP_MSGSTR2, &ramcopy)) {
    ramcopy.memadr = (void*) line2;
    l2inflash ? DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::DGUSLCD_SendStringToDisplay(ramcopy);
  }
  if (populate_VPVar(VP_MSGSTR3, &ramcopy)) {
    ramcopy.memadr = (void*) line3;
    l3inflash ? DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::DGUSLCD_SendStringToDisplay(ramcopy);
=======
void DGUSScreenHandler::sendInfoScreen_P(PGM_P const line1, PGM_P const line2, PGM_P const line3, PGM_P const line4, bool l1inflash, bool l2inflash, bool l3inflash, bool l4inflash) {
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_MSGSTR1, &ramcopy)) {
    ramcopy.memadr = (void*) line1;
    l1inflash ? DGUSScreenHandler::sendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::sendStringToDisplay(ramcopy);
  }
  if (populate_VPVar(VP_MSGSTR2, &ramcopy)) {
    ramcopy.memadr = (void*) line2;
    l2inflash ? DGUSScreenHandler::sendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::sendStringToDisplay(ramcopy);
  }
  if (populate_VPVar(VP_MSGSTR3, &ramcopy)) {
    ramcopy.memadr = (void*) line3;
    l3inflash ? DGUSScreenHandler::sendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::sendStringToDisplay(ramcopy);
>>>>>>> origin/release-2.1.3-beta2
  }
  #ifdef VP_MSGSTR4
    if (populate_VPVar(VP_MSGSTR4, &ramcopy)) {
      ramcopy.memadr = (void*) line4;
<<<<<<< HEAD
      l4inflash ? DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::DGUSLCD_SendStringToDisplay(ramcopy);
=======
      l4inflash ? DGUSScreenHandler::sendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::sendStringToDisplay(ramcopy);
>>>>>>> origin/release-2.1.3-beta2
    }
  #endif
}

<<<<<<< HEAD
void DGUSScreenHandler::HandleUserConfirmationPopUp(uint16_t VP, PGM_P const line1, PGM_P const line2, PGM_P const line3, PGM_P const line4, bool l1, bool l2, bool l3, bool l4) {
  if (current_screen == DGUSLCD_SCREEN_CONFIRM) // Already showing a pop up, so we need to cancel that first.
    PopToOldScreen();

  ConfirmVP = VP;
  sendinfoscreen(line1, line2, line3, line4, l1, l2, l3, l4);
  GotoScreen(DGUSLCD_SCREEN_CONFIRM);
}

void DGUSScreenHandler::setstatusmessage(const char *msg) {
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_M117, &ramcopy)) {
    ramcopy.memadr = (void*) msg;
    DGUSLCD_SendStringToDisplay(ramcopy);
=======
void DGUSScreenHandler::handleUserConfirmationPopUp(uint16_t VP, PGM_P const line1, PGM_P const line2, PGM_P const line3, PGM_P const line4, bool l1, bool l2, bool l3, bool l4) {
  if (current_screenID == DGUS_SCREEN_CONFIRM) // Already showing a pop up, so we need to cancel that first.
    popToOldScreen();

  confirmVP = VP;
  sendInfoScreen_P(line1, line2, line3, line4, l1, l2, l3, l4);
  gotoScreen(DGUS_SCREEN_CONFIRM);
}

void DGUSScreenHandler::setStatusMessage(const char *msg) {
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_M117, &ramcopy)) {
    ramcopy.memadr = (void*) msg;
    sendStringToDisplay(ramcopy);
>>>>>>> origin/release-2.1.3-beta2
  }
}

void DGUSScreenHandler::setstatusmessagePGM(PGM_P const msg) {
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_M117, &ramcopy)) {
    ramcopy.memadr = (void*) msg;
<<<<<<< HEAD
    DGUSLCD_SendStringToDisplayPGM(ramcopy);
=======
    sendStringToDisplayPGM(ramcopy);
>>>>>>> origin/release-2.1.3-beta2
  }
}

// Send an 8 bit or 16 bit value to the display.
<<<<<<< HEAD
void DGUSScreenHandler::DGUSLCD_SendWordValueToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    //DEBUG_ECHOPGM(" DGUS_LCD_SendWordValueToDisplay ", var.VP);
    //DEBUG_ECHOLNPGM(" data ", *(uint16_t *)var.memadr);
    if (var.size > 1)
      dgusdisplay.WriteVariable(var.VP, *(int16_t*)var.memadr);
    else
      dgusdisplay.WriteVariable(var.VP, *(int8_t*)var.memadr);
=======
void DGUSScreenHandler::sendWordValueToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    if (var.size > 1)
      dgus.writeVariable(var.VP, *(int16_t*)var.memadr);
    else
      dgus.writeVariable(var.VP, *(int8_t*)var.memadr);
>>>>>>> origin/release-2.1.3-beta2
  }
}

// Send an uint8_t between 0 and 255 to the display, but scale to a percentage (0..100)
<<<<<<< HEAD
void DGUSScreenHandler::DGUSLCD_SendPercentageToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    //DEBUG_ECHOPGM(" DGUS_LCD_SendWordValueToDisplay ", var.VP);
    //DEBUG_ECHOLNPGM(" data ", *(uint16_t *)var.memadr);
    uint16_t tmp = *(uint8_t *) var.memadr + 1; // +1 -> avoid rounding issues for the display.
    tmp = map(tmp, 0, 255, 0, 100);
    dgusdisplay.WriteVariable(var.VP, tmp);
=======
void DGUSScreenHandler::sendPercentageToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    uint16_t tmp = *(uint8_t *) var.memadr + 1; // +1 -> avoid rounding issues for the display.
    tmp = map(tmp, 0, 255, 0, 100);
    dgus.writeVariable(var.VP, tmp);
>>>>>>> origin/release-2.1.3-beta2
  }
}

// Send the current print progress to the display.
<<<<<<< HEAD
void DGUSScreenHandler::DGUSLCD_SendPrintProgressToDisplay(DGUS_VP_Variable &var) {
  //DEBUG_ECHOPGM(" DGUSLCD_SendPrintProgressToDisplay ", var.VP);
  uint16_t tmp = ExtUI::getProgress_percent();
  //DEBUG_ECHOLNPGM(" data ", tmp);
  dgusdisplay.WriteVariable(var.VP, tmp);
=======
void DGUSScreenHandler::sendPrintProgressToDisplay(DGUS_VP_Variable &var) {
  uint16_t tmp = ExtUI::getProgress_percent();
  dgus.writeVariable(var.VP, tmp);
>>>>>>> origin/release-2.1.3-beta2
}

// Send the current print time to the display.
// It is using a hex display for that: It expects BSD coded data in the format xxyyzz
<<<<<<< HEAD
void DGUSScreenHandler::DGUSLCD_SendPrintTimeToDisplay(DGUS_VP_Variable &var) {
  duration_t elapsed = print_job_timer.duration();
  char buf[32];
  elapsed.toString(buf);
  dgusdisplay.WriteVariable(VP_PrintTime, buf, var.size, true);
}

// Send an uint8_t between 0 and 100 to a variable scale to 0..255
void DGUSScreenHandler::DGUSLCD_PercentageToUint8(DGUS_VP_Variable &var, void *val_ptr) {
  if (var.memadr) {
    uint16_t value = swap16(*(uint16_t*)val_ptr);
    DEBUG_ECHOLNPGM("FAN value get:", value);
    *(uint8_t*)var.memadr = map(constrain(value, 0, 100), 0, 100, 0, 255);
    DEBUG_ECHOLNPGM("FAN value change:", *(uint8_t*)var.memadr);
=======
void DGUSScreenHandler::sendPrintTimeToDisplay(DGUS_VP_Variable &var) {
  duration_t elapsed = print_job_timer.duration();
  char buf[32];
  elapsed.toString(buf);
  dgus.writeVariable(VP_PrintTime, buf, var.size, true);
}

// Send an uint8_t between 0 and 100 to a variable scale to 0..255
void DGUSScreenHandler::percentageToUint8(DGUS_VP_Variable &var, void *val_ptr) {
  if (var.memadr) {
    const uint16_t value = BE16_P(val_ptr);
    *(uint8_t*)var.memadr = map(constrain(value, 0, 100), 0, 100, 0, 255);
>>>>>>> origin/release-2.1.3-beta2
  }
}

// Sends a (RAM located) string to the DGUS Display
// (Note: The DGUS Display does not clear after the \0, you have to
// overwrite the remainings with spaces.// var.size has the display buffer size!
<<<<<<< HEAD
void DGUSScreenHandler::DGUSLCD_SendStringToDisplay(DGUS_VP_Variable &var) {
  char *tmp = (char*) var.memadr;
  dgusdisplay.WriteVariable(var.VP, tmp, var.size, true);
=======
void DGUSScreenHandler::sendStringToDisplay(DGUS_VP_Variable &var) {
  char *tmp = (char*) var.memadr;
  dgus.writeVariable(var.VP, tmp, var.size, true);
>>>>>>> origin/release-2.1.3-beta2
}

// Sends a (flash located) string to the DGUS Display
// (Note: The DGUS Display does not clear after the \0, you have to
// overwrite the remainings with spaces.// var.size has the display buffer size!
<<<<<<< HEAD
void DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(DGUS_VP_Variable &var) {
  char *tmp = (char*) var.memadr;
  dgusdisplay.WriteString(var.VP, tmp, var.size);
}

// #if HAS_PID_HEATING //ЗАКОМЕНТИЛ
//   void DGUSScreenHandler::DGUSLCD_SendTemperaturePID(DGUS_VP_Variable &var) {
//     float value = *(float *)var.memadr;
//     value /= 10;
//     float valuesend = 0;
//     switch (var.VP) {
//       default: return;
//       #if HAS_HOTEND
//         case VP_E0_PID_P: valuesend = value; break;
//         case VP_E0_PID_I: valuesend = unscalePID_i(value); break;
//         case VP_E0_PID_D: valuesend = unscalePID_d(value); break;
//       #endif
//       #if HAS_MULTI_HOTEND
//         case VP_E1_PID_P: valuesend = value; break;
//         case VP_E1_PID_I: valuesend = unscalePID_i(value); break;
//         case VP_E1_PID_D: valuesend = unscalePID_d(value); break;
//       #endif
//       #if HAS_HEATED_BED
//         case VP_BED_PID_P: valuesend = value; break;
//         case VP_BED_PID_I: valuesend = unscalePID_i(value); break;
//         case VP_BED_PID_D: valuesend = unscalePID_d(value); break;
//       #endif
//     }

//     valuesend *= cpow(10, 1);
//     union { int16_t i; char lb[2]; } endian;

//     char tmp[2];
//     endian.i = valuesend;
//     tmp[0] = endian.lb[1];
//     tmp[1] = endian.lb[0];
//     dgusdisplay.WriteVariable(var.VP, tmp, 2);
//   }
// #endif
=======
void DGUSScreenHandler::sendStringToDisplayPGM(DGUS_VP_Variable &var) {
  char *tmp = (char*) var.memadr;
  dgus.writeVariablePGM(var.VP, tmp, var.size, true);
}

#if HAS_PID_HEATING
  void DGUSScreenHandler::sendTemperaturePID(DGUS_VP_Variable &var) {
    float value = *(float *)var.memadr;
    value /= 10;
    float valuesend = 0;
    switch (var.VP) {
      default: return;
      #if HAS_HOTEND
        case VP_E0_PID_P: valuesend = value; break;
        case VP_E0_PID_I: valuesend = unscalePID_i(value); break;
        case VP_E0_PID_D: valuesend = unscalePID_d(value); break;
      #endif
      #if HAS_MULTI_HOTEND
        case VP_E1_PID_P: valuesend = value; break;
        case VP_E1_PID_I: valuesend = unscalePID_i(value); break;
        case VP_E1_PID_D: valuesend = unscalePID_d(value); break;
      #endif
      #if HAS_HEATED_BED
        case VP_BED_PID_P: valuesend = value; break;
        case VP_BED_PID_I: valuesend = unscalePID_i(value); break;
        case VP_BED_PID_D: valuesend = unscalePID_d(value); break;
      #endif
    }

    valuesend *= cpow(10, 1);
    union { int16_t i; char lb[2]; } endian;

    char tmp[2];
    endian.i = valuesend;
    tmp[0] = endian.lb[1];
    tmp[1] = endian.lb[0];
    dgus.writeVariable(var.VP, tmp, 2);
  }
#endif
>>>>>>> origin/release-2.1.3-beta2

#if ENABLED(PRINTCOUNTER)

  // Send the accumulate print time to the display.
  // It is using a hex display for that: It expects BSD coded data in the format xxyyzz
<<<<<<< HEAD
  void DGUSScreenHandler::DGUSLCD_SendPrintAccTimeToDisplay(DGUS_VP_Variable &var) {
=======
  void DGUSScreenHandler::sendPrintAccTimeToDisplay(DGUS_VP_Variable &var) {
>>>>>>> origin/release-2.1.3-beta2
    printStatistics state = print_job_timer.getStats();
    char buf[22];
    duration_t elapsed = state.printTime;
    elapsed.toString(buf);
<<<<<<< HEAD
    dgusdisplay.WriteVariable(VP_PrintAccTime, buf, var.size, true);
  }

  void DGUSScreenHandler::DGUSLCD_SendPrintsTotalToDisplay(DGUS_VP_Variable &var) {
    printStatistics state = print_job_timer.getStats();
    char buf[10];
    sprintf_P(buf, PSTR("%u"), state.totalPrints);
    dgusdisplay.WriteVariable(VP_PrintsTotal, buf, var.size, true);
=======
    dgus.writeVariable(VP_PrintAccTime, buf, var.size, true);
  }

  void DGUSScreenHandler::sendPrintsTotalToDisplay(DGUS_VP_Variable &var) {
    printStatistics state = print_job_timer.getStats();
    char buf[10];
    sprintf_P(buf, PSTR("%u"), state.totalPrints);
    dgus.writeVariable(VP_PrintsTotal, buf, var.size, true);
>>>>>>> origin/release-2.1.3-beta2
  }

#endif

// Send fan status value to the display.
#if HAS_FAN

<<<<<<< HEAD
  void DGUSScreenHandler::DGUSLCD_SendFanStatusToDisplay(DGUS_VP_Variable &var) {
    if (var.memadr) {
      DEBUG_ECHOPGM(" DGUSLCD_SendFanStatusToDisplay ", var.VP);
      DEBUG_ECHOLNPGM(" data ", *(uint8_t *)var.memadr);
      uint16_t data_to_send = 0;
      if (*(uint8_t *) var.memadr) data_to_send = 1;
      dgusdisplay.WriteVariable(var.VP, data_to_send);
=======
  void DGUSScreenHandler::sendFanStatusToDisplay(DGUS_VP_Variable &var) {
    if (var.memadr) {
      uint16_t data_to_send = 0;
      if (*(uint8_t *) var.memadr) data_to_send = 1;
      dgus.writeVariable(var.VP, data_to_send);
>>>>>>> origin/release-2.1.3-beta2
    }
  }

#endif

// Send heater status value to the display.
<<<<<<< HEAD
void DGUSScreenHandler::DGUSLCD_SendHeaterStatusToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    DEBUG_ECHOPGM(" DGUSLCD_SendHeaterStatusToDisplay ", var.VP);
    DEBUG_ECHOLNPGM(" data ", *(int16_t *)var.memadr);
    uint16_t data_to_send = 0;
    if (*(int16_t *) var.memadr) data_to_send = 1;
    dgusdisplay.WriteVariable(var.VP, data_to_send);
  }
}

// Свое обновление иконки "примонтирована ли флешка".
void DGUSScreenHandler::DGUSLCD_SendFlashIconStatus(DGUS_VP_Variable &var) {
  if(DiskIODriver_USBFlash::isInserted()){
    dgusdisplay.WriteVariable(var.VP, (uint16_t)1);
  } else {
    dgusdisplay.WriteVariable(var.VP, (uint16_t)0);
  }
}


void DGUSScreenHandler::DGUSLCD_SendFilamentChangeStatus(DGUS_VP_Variable &var) {
   uint8_t hotend_too_cold = 0;
  if (thermalManager.tooColdToExtrude(0))
          hotend_too_cold = 1;
        
      
  if (hotend_too_cold) //thermalManager.targetTooColdToExtrude(hotend_too_cold - 1
  dgusdisplay.WriteString(VP_FILAMENT_CHANGE_STATUS, GET_TEXT_F(MSG_HOTEND_TOO_COLD), VP_Status_LEN);
  else
  dgusdisplay.WriteString(VP_FILAMENT_CHANGE_STATUS, "", VP_Status_LEN);
}


// Свое обновление иконки "высокая температура".
void DGUSScreenHandler::DGUSLCD_SendAlarmTemperature(DGUS_VP_Variable &var) {
  if(thermalManager.temp_hotend[0].celsius > ALARM_TEMPERATURE_ICON ||
     thermalManager.temp_bed.celsius > ALARM_TEMPERATURE_ICON ||
     thermalManager.temp_chamber.celsius > ALARM_TEMPERATURE_ICON  ) {
    dgusdisplay.WriteVariable(var.VP, (uint16_t)1);
  } else {
    dgusdisplay.WriteVariable(var.VP, (uint16_t)0);
  }
}

// Свое обновление иконки сработал ли датчик филамента 
void DGUSScreenHandler::DGUSLCD_SendFilamentRunoutStatus(DGUS_VP_Variable &var) {

//uint8_t filament_status = FilamentSensorBase::poll_runout_states();
//bool mem3 = FilamentSensorBase::poll_runout_pin_switch();
 
 if (ExtUI::isPrintingFromMedia())
 {
  if(!runout.filament_ran_out) { 
      dgusdisplay.WriteVariable(var.VP, (uint16_t)1);
    } else {
      dgusdisplay.WriteVariable(var.VP, (uint16_t)0);
    }
 }
 else {
    if(FilamentSensorBase::poll_runout_pin_switch()) { //!runout.filament_ran_out
      dgusdisplay.WriteVariable(var.VP, (uint16_t)1);
    } else {
      dgusdisplay.WriteVariable(var.VP, (uint16_t)0);
    }
 }
}


//Иконка индикатор состояния датчика движения филамента
void DGUSScreenHandler::DGUSLCD_FIlamentSensorUpdateIcon(DGUS_VP_Variable &var) {
  if(runout.enabled){ //
    dgusdisplay.WriteVariable(var.VP, (uint16_t)1);
  } else {
    dgusdisplay.WriteVariable(var.VP, (uint16_t)0);
  }
}




// Свое вкл/выкл сенсора филамента.
void DGUSScreenHandler::DGUSLCD_FIlamentSensorUpdate(DGUS_VP_Variable &var, void *val_ptr) {
  
  runout.enabled = !runout.enabled;

  // if(runout.enabled) {
  //   runout.enabled = false;
  // } else {
  //   runout.enabled = true;
  // }
  //EEPROM_WRITE(e_factors);
   if (!ExtUI::isPrintingFromMedia())
 {
  settings.save(); //не было раньше добавил
 }

  ForceCompleteUpdate(); 
}

#if ENABLED(DGUS_UI_WAITING)

  void DGUSScreenHandler::DGUSLCD_SendWaitingStatusToDisplay(DGUS_VP_Variable &var) {
    // In FYSETC UI design there are 10 statuses to loop
    static uint16_t period = 0;
    static uint16_t index = 0;
    //DEBUG_ECHOPGM(" DGUSLCD_SendWaitingStatusToDisplay ", var.VP);
    //DEBUG_ECHOLNPGM(" data ", swap16(index));
    if (period++ > DGUS_UI_WAITING_STATUS_PERIOD) {
      dgusdisplay.WriteVariable(var.VP, index);
      //DEBUG_ECHOLNPGM(" data ", swap16(index));
=======
void DGUSScreenHandler::sendHeaterStatusToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    uint16_t data_to_send = 0;
    if (*(int16_t *) var.memadr) data_to_send = 1;
    dgus.writeVariable(var.VP, data_to_send);
  }
}

#if ENABLED(DGUS_UI_WAITING)

  void DGUSScreenHandler::sendWaitingStatusToDisplay(DGUS_VP_Variable &var) {
    // In FYSETC UI design there are 10 statuses to loop
    static uint16_t period = 0;
    static uint16_t index = 0;
    if (period++ > DGUS_UI_WAITING_STATUS_PERIOD) {
      dgus.writeVariable(var.VP, index);
>>>>>>> origin/release-2.1.3-beta2
      if (++index >= DGUS_UI_WAITING_STATUS) index = 0;
      period = 0;
    }
  }

#endif

<<<<<<< HEAD
#if ENABLED(SDSUPPORT)

  // void DGUSScreenHandler::ScreenChangeHookIfSD(DGUS_VP_Variable &var, void *val_ptr) {  //ЗАКОМЕНТИЛ
  //   // default action executed when there is a SD card, but not printing
  //   if (ExtUI::isMediaInserted() && !ExtUI::isPrintingFromMedia()) {
  //     ScreenChangeHook(var, val_ptr);
  //     dgusdisplay.RequestScreen(current_screen);
  //     return;
  //   }

  //   // if we are printing, we jump to two screens after the requested one.
  //   // This should host e.g a print pause / print abort / print resume dialog.
  //   // This concept allows to recycle this hook for other file
  //   if (ExtUI::isPrintingFromMedia() && !card.flag.abort_sd_printing) {
  //     GotoScreen(DGUSLCD_SCREEN_SDPRINTMANIPULATION);
  //     return;
  //   }

  //   // Don't let the user in the dark why there is no reaction.
  //   if (!ExtUI::isMediaInserted()) {
  //     setstatusmessagePGM(GET_TEXT(MSG_NO_MEDIA));
  //     return;
  //   }
  //   if (card.flag.abort_sd_printing) {
  //     setstatusmessagePGM(GET_TEXT(MSG_MEDIA_ABORTING));
  //     return;
  //   }
  // }

  void DGUSScreenHandler::DGUSLCD_SD_ScrollFilelist(DGUS_VP_Variable& var, void *val_ptr) {
    auto old_top = top_file;
    const int16_t scroll = (int16_t)swap16(*(uint16_t*)val_ptr); // TODO: использоать swap16 в выводе utf-16 строк
    if (scroll) {
      switch (scroll)
      {
      case 1:
        top_file += DGUS_SD_FILESPERSCREEN;
        break;
      case 2: 
        top_file -= DGUS_SD_FILESPERSCREEN;
        break;
      case 3: //добавил чтобы выходить из папки назад
        filelist.upDir();
        break;
      default:        
        break;
      }        
      
      DEBUG_ECHOPGM("new topfile calculated:", top_file);
      if (top_file < 0) {
        top_file = 0;
        DEBUG_ECHOLNPGM("Top of filelist reached");
      }
      else {
        int16_t max_top = filelist.count();
        NOLESS(max_top, 0);
        // NOMORE(top_file, max_top);
        if (max_top < top_file) top_file = old_top;
      }
      DEBUG_ECHOPGM("new topfile adjusted:", top_file);
=======
#if HAS_MEDIA

  void DGUSScreenHandler::screenChangeHookIfSD(DGUS_VP_Variable &var, void *val_ptr) {
    // default action executed when there is a SD card, but not printing
    if (ExtUI::isMediaMounted() && !ExtUI::isPrintingFromMedia()) {
      screenChangeHook(var, val_ptr);
      dgus.requestScreen(current_screenID);
      return;
    }

    // if we are printing, we jump to two screens after the requested one.
    // This should host e.g a print pause / print abort / print resume dialog.
    // This concept allows to recycle this hook for other file
    if (ExtUI::isPrintingFromMedia() && !card.flag.abort_sd_printing) {
      gotoScreen(DGUS_SCREEN_SDPRINTMANIPULATION);
      return;
    }

    // Don't let the user in the dark why there is no reaction.
    if (!ExtUI::isMediaMounted()) {
      setStatusMessage(GET_TEXT_F(MSG_NO_MEDIA));
      return;
    }
    if (card.flag.abort_sd_printing) {
      setStatusMessage(GET_TEXT_F(MSG_MEDIA_ABORTING));
      return;
    }
  }

  void DGUSScreenHandler::sdScrollFilelist(DGUS_VP_Variable& var, void *val_ptr) {
    auto old_top = top_file;
    const int16_t scroll = (int16_t)BE16_P(val_ptr);
    if (scroll) {
      top_file += scroll;
      if (top_file < 0) {
        top_file = 0;
      }
      else {
        int16_t max_top = filelist.count() -  DGUS_SD_FILESPERSCREEN;
        NOLESS(max_top, 0);
        NOMORE(top_file, max_top);
      }
>>>>>>> origin/release-2.1.3-beta2
    }
    else if (!filelist.isAtRootDir()) {
      IF_DISABLED(DGUS_LCD_UI_MKS, filelist.upDir());
      top_file = 0;
<<<<<<< HEAD
      ForceCompleteUpdate();
    }

    if (old_top != top_file) ForceCompleteUpdate();

    if (filelist.isAtRootDir()){
      if (top_file == 0)
      {
        GotoScreen(MKSLCD_SCREEN_CHOOSE_FILE_1);
      } else if(filelist.count() - top_file <= DGUS_SD_FILESPERSCREEN){
        GotoScreen(MKSLCD_SCREEN_CHOOSE_FILE_2);
      } else {
        GotoScreen(MKSLCD_SCREEN_CHOOSE_FILE_3);
      }
    } else {
      if (top_file == 0)
      {
        GotoScreen(MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_1);
      }
      else if (filelist.count() - top_file <= DGUS_SD_FILESPERSCREEN)
      {
        GotoScreen(MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_2);
      }
      else
      {
        GotoScreen(MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_3);
      }
    }
  }

  void DGUSScreenHandler::DGUSLCD_SD_ReallyAbort(DGUS_VP_Variable &var, void *val_ptr) {
   
    ExtUI::stopPrint();
    GotoScreen(MKSLCD_SCREEN_PrintDone);
  }

  // void DGUSScreenHandler::DGUSLCD_SD_PrintTune(DGUS_VP_Variable &var, void *val_ptr) { //ЗАКОМЕНТИЛ
  //   if (!ExtUI::isPrintingFromMedia()) return; // avoid race condition when user stays in this menu and printer finishes.
  //   GotoScreen(DGUSLCD_SCREEN_SDPRINTTUNE);
  // }

  void DGUSScreenHandler::SDCardError() {
    DGUSScreenHandler::SDCardRemoved();
    // sendinfoscreen(F("NOTICE"), nullptr, F("SD card error"), nullptr, true, true, true, true);
    // SetupConfirmAction(nullptr);
    // GotoScreen(DGUSLCD_SCREEN_POPUP);
  }

#endif // SDSUPPORT

void DGUSScreenHandler::ScreenConfirmedOK(DGUS_VP_Variable &var, void *val_ptr) {
  DGUS_VP_Variable ramcopy;
  if (!populate_VPVar(ConfirmVP, &ramcopy)) return;
  if (ramcopy.set_by_display_handler) ramcopy.set_by_display_handler(ramcopy, val_ptr);
}

const uint16_t* DGUSLCD_FindScreenVPMapList(uint8_t screen) {
=======
      forceCompleteUpdate();
    }

    if (old_top != top_file) forceCompleteUpdate();
  }

  void DGUSScreenHandler::sdReallyAbort(DGUS_VP_Variable &var, void *val_ptr) {
    ExtUI::stopPrint();
    gotoScreen(DGUS_SCREEN_MAIN);
  }

  void DGUSScreenHandler::sdPrintTune(DGUS_VP_Variable &var, void *val_ptr) {
    if (!ExtUI::isPrintingFromMedia()) return; // avoid race condition when user stays in this menu and printer finishes.
    gotoScreen(DGUS_SCREEN_SDPRINTTUNE);
  }

  void DGUSScreenHandler::sdCardError() {
    DGUSScreenHandler::sdCardRemoved();
    sendInfoScreen(F("NOTICE"), nullptr, F("SD card error"), nullptr, true, true, true, true);
    setupConfirmAction(nullptr);
    gotoScreen(DGUS_SCREEN_POPUP);
  }

#endif // HAS_MEDIA

void DGUSScreenHandler::screenConfirmedOK(DGUS_VP_Variable &var, void *val_ptr) {
  DGUS_VP_Variable ramcopy;
  if (!populate_VPVar(confirmVP, &ramcopy)) return;
  if (ramcopy.set_by_display_handler) ramcopy.set_by_display_handler(ramcopy, val_ptr);
}

const uint16_t* findScreenVPMapList(uint8_t screen) {
>>>>>>> origin/release-2.1.3-beta2
  const uint16_t *ret;
  const struct VPMapping *map = VPMap;
  while ((ret = (uint16_t*) pgm_read_ptr(&(map->VPList)))) {
    if (pgm_read_byte(&(map->screen)) == screen) return ret;
    map++;
  }
  return nullptr;
}

<<<<<<< HEAD
const DGUS_VP_Variable* DGUSLCD_FindVPVar(const uint16_t vp) {
=======
const DGUS_VP_Variable* findVPVar(const uint16_t vp) {
>>>>>>> origin/release-2.1.3-beta2
  const DGUS_VP_Variable *ret = ListOfVP;
  do {
    const uint16_t vpcheck = pgm_read_word(&(ret->VP));
    if (vpcheck == 0) break;
    if (vpcheck == vp) return ret;
    ++ret;
  } while (1);

<<<<<<< HEAD
  DEBUG_ECHOLNPGM("FindVPVar NOT FOUND ", vp);
  return nullptr;
}

void DGUSScreenHandler::ScreenChangeHookIfIdle(DGUS_VP_Variable &var, void *val_ptr) {
  if (!ExtUI::isPrinting()) {
    ScreenChangeHook(var, val_ptr);
    dgusdisplay.RequestScreen(current_screen);
  }
}

void DGUSScreenHandler::HandleAllHeatersOff(DGUS_VP_Variable &var, void *val_ptr) {  ////есть своя аналогия VP_Cool_Down
  thermalManager.disable_all_heaters();
  ForceCompleteUpdate(); // hint to send all data.
}

void DGUSScreenHandler::SendTemperatureStatus(DGUS_VP_Variable &var) {
  //manualMoveStep = thermalManager.temp_hotend[0].target;
  switch (var.VP)
  {
  case VP_T_E0_ON:
    if(thermalManager.temp_hotend[0].target)
      dgusdisplay.WriteVariable(VP_T_E0_ON, (uint16_t)1); // uint16_t обязателен, чтобы было 00 01, а не 01 00(uint8_t).
    else 
      dgusdisplay.WriteVariable(VP_T_E0_ON, (uint16_t)0); // uint16_t обязателен, чтобы было 00 01, а не 01 00(uint8_t).
    break;
  case VP_T_Bed_ON:
    if(thermalManager.temp_bed.target)
      dgusdisplay.WriteVariable(VP_T_Bed_ON, (uint16_t)1); // uint16_t обязателен, чтобы было 00 01, а не 01 00(uint8_t).
    else 
      dgusdisplay.WriteVariable(VP_T_Bed_ON, (uint16_t)0); // uint16_t обязателен, чтобы было 00 01, а не 01 00(uint8_t).
    break;
  case VP_T_Chamber_ON:
    if(thermalManager.temp_chamber.target)
      dgusdisplay.WriteVariable(VP_T_Chamber_ON, (uint16_t)1); // uint16_t обязателен, чтобы было 00 01, а не 01 00(uint8_t).
    else 
      dgusdisplay.WriteVariable(VP_T_Chamber_ON, (uint16_t)0); // uint16_t обязателен, чтобы было 00 01, а не 01 00(uint8_t).
    break;
  default:
    break;
  }
}

void DGUSScreenHandler::HandleTemperatureChanged(DGUS_VP_Variable &var, void *val_ptr) {
  //if(!val_ptr) return; // Проверка своя.
  celsius_t newvalue = swap16(*(uint16_t*)val_ptr);
  celsius_t acceptedvalue;

  hotend_idle.reset_timed_out(); //типо если включил то сбросил таймер

=======
  return nullptr;
}

void DGUSScreenHandler::screenChangeHookIfIdle(DGUS_VP_Variable &var, void *val_ptr) {
  if (!ExtUI::isPrinting()) {
    screenChangeHook(var, val_ptr);
    dgus.requestScreen(current_screenID);
  }
}

void DGUSScreenHandler::handleAllHeatersOff(DGUS_VP_Variable &var, void *val_ptr) {
  thermalManager.disable_all_heaters();
  forceCompleteUpdate(); // hint to send all data.
}

void DGUSScreenHandler::handleTemperatureChanged(DGUS_VP_Variable &var, void *val_ptr) {
  celsius_t newvalue = BE16_P(val_ptr);
  celsius_t acceptedvalue;

>>>>>>> origin/release-2.1.3-beta2
  switch (var.VP) {
    default: return;
    #if HAS_HOTEND
      case VP_T_E0_Set:
<<<<<<< HEAD
        NOMORE(newvalue, HEATER_0_MAXTEMP);
=======
        NOMORE(newvalue, thermalManager.hotend_max_target(0));
>>>>>>> origin/release-2.1.3-beta2
        thermalManager.setTargetHotend(newvalue, 0);
        acceptedvalue = thermalManager.degTargetHotend(0);
        break;
    #endif
    #if HAS_MULTI_HOTEND
      case VP_T_E1_Set:
<<<<<<< HEAD
        NOMORE(newvalue, HEATER_1_MAXTEMP);
=======
        NOMORE(newvalue, thermalManager.hotend_max_target(1));
>>>>>>> origin/release-2.1.3-beta2
        thermalManager.setTargetHotend(newvalue, 1);
        acceptedvalue = thermalManager.degTargetHotend(1);
        break;
    #endif
    #if HAS_HEATED_BED
      case VP_T_Bed_Set:
<<<<<<< HEAD
        NOMORE(newvalue, BED_MAXTEMP);
        thermalManager.setTargetBed(newvalue);
        acceptedvalue = thermalManager.degTargetBed();
        break;
    #endif    
    #if HAS_HEATED_CHAMBER
      case VP_T_Chamber_Set:
        NOMORE(newvalue, CHAMBER_MAXTEMP);
        thermalManager.setTargetChamber(newvalue);
        acceptedvalue = thermalManager.degTargetChamber();
        break;
    #endif


  case VP_T_E0_ON:
        // Choose Tempreture  //Данные с вкладки Configuration
    if (nozzlePreset.temperature == 0x00) nozzlePreset.temperature =      PREHEAT_1_TEMP_HOTEND; //PLA
    else if (nozzlePreset.temperature == 0x01) nozzlePreset.temperature = PREHEAT_2_TEMP_HOTEND; //PETG
    else if (nozzlePreset.temperature == 0x02) nozzlePreset.temperature = PREHEAT_3_TEMP_HOTEND; //ABS
    else if (nozzlePreset.temperature == 0x03) nozzlePreset.temperature = PREHEAT_4_TEMP_HOTEND; //NYLON
    else if (nozzlePreset.temperature == 0x04) nozzlePreset.temperature = PREHEAT_5_TEMP_HOTEND; //MAX
    nozzlePreset.isOn = newvalue;
    NOMORE(nozzlePreset.temperature, HEATER_0_MAXTEMP);
    if(nozzlePreset.isOn){
      thermalManager.setTargetHotend(nozzlePreset.temperature, 0);
    } else {
      thermalManager.setTargetHotend(0, 0);
    }
    acceptedvalue = thermalManager.degTargetHotend(0);
    newvalue = nozzlePreset.temperature;
  break;

  case VP_T_Bed_ON:
          // Choose Tempreture  //Данные с вкладки Configuration
    if (bedPreset.temperature == 0x00) bedPreset.temperature =      PREHEAT_1_TEMP_BED; //PLA
    else if (bedPreset.temperature == 0x01) bedPreset.temperature = PREHEAT_2_TEMP_BED; //PETG
    else if (bedPreset.temperature == 0x02) bedPreset.temperature = PREHEAT_3_TEMP_BED; //ABS
    else if (bedPreset.temperature == 0x03) bedPreset.temperature = PREHEAT_4_TEMP_BED; //NYLON
    else if (bedPreset.temperature == 0x04) bedPreset.temperature = PREHEAT_5_TEMP_BED; //MAX

    bedPreset.isOn = newvalue;
    NOMORE(bedPreset.temperature, BED_MAXTEMP);
    if(bedPreset.isOn){
    thermalManager.setTargetBed(bedPreset.temperature);
    } else {
    thermalManager.setTargetBed(0);
    }
    acceptedvalue = thermalManager.degTargetBed();
    newvalue = bedPreset.temperature;
  break;

  case VP_T_Chamber_ON:
        // Choose Tempreture  //Данные с вкладки Configuration
    if (chamberPreset.temperature == 0x00) chamberPreset.temperature =      PREHEAT_1_TEMP_CHAMBER; //PLA
    else if (chamberPreset.temperature == 0x01) chamberPreset.temperature = PREHEAT_2_TEMP_CHAMBER; //PETG
    else if (chamberPreset.temperature == 0x02) chamberPreset.temperature = PREHEAT_3_TEMP_CHAMBER; //ABS
    else if (chamberPreset.temperature == 0x03) chamberPreset.temperature = PREHEAT_4_TEMP_CHAMBER; //NYLON
    else if (chamberPreset.temperature == 0x04) chamberPreset.temperature = PREHEAT_5_TEMP_CHAMBER; //MAX

    chamberPreset.isOn = newvalue;
    NOMORE(chamberPreset.temperature, CHAMBER_MAXTEMP);
    if(chamberPreset.isOn){
    thermalManager.setTargetChamber(chamberPreset.temperature);
    } else {
    thermalManager.setTargetChamber(0);
    }
    acceptedvalue = thermalManager.degTargetChamber();
    newvalue = chamberPreset.temperature;
  break;      
=======
        NOMORE(newvalue, BED_MAX_TARGET);
        thermalManager.setTargetBed(newvalue);
        acceptedvalue = thermalManager.degTargetBed();
        break;
    #endif
>>>>>>> origin/release-2.1.3-beta2
  }

  // reply to display the new value to update the view if the new value was rejected by the Thermal Manager.
  if (newvalue != acceptedvalue && var.send_to_display_handler) var.send_to_display_handler(var);
  skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
<<<<<<< HEAD
  ForceCompleteUpdate(); 
}

void DGUSScreenHandler::HandleFlowRateChanged(DGUS_VP_Variable &var, void *val_ptr) {
  #if HAS_EXTRUDERS
    uint16_t newvalue = swap16(*(uint16_t*)val_ptr);
=======
}

void DGUSScreenHandler::handleFlowRateChanged(DGUS_VP_Variable &var, void *val_ptr) {
  #if HAS_EXTRUDERS
    const uint16_t newvalue = BE16_P(val_ptr);
>>>>>>> origin/release-2.1.3-beta2
    uint8_t target_extruder;
    switch (var.VP) {
      default: return;
      case VP_Flowrate_E0: target_extruder = 0; break;
      #if HAS_MULTI_EXTRUDER
        case VP_Flowrate_E1: target_extruder = 1; break;
      #endif
    }

    planner.set_flow(target_extruder, newvalue);
    skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
  #else
    UNUSED(var); UNUSED(val_ptr);
  #endif
}

<<<<<<< HEAD
void DGUSScreenHandler::HandleManualExtrude(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleManualExtrude");

  int16_t movevalue = swap16(*(uint16_t*)val_ptr);

  // Choose Move distance
       if (manualMoveStep == 0x01) manualMoveStep = 10; 
  else if (manualMoveStep == 0x02) manualMoveStep = 100; 
  else if (manualMoveStep == 0x03) manualMoveStep = 500; 
  else if (manualMoveStep == 0x04) manualMoveStep = 1000;
  else if (manualMoveStep == 0x05) manualMoveStep = 5000;
  else if (manualMoveStep == 0x06) manualMoveStep = 10000;

    if (!print_job_timer.isPaused() && !queue.ring_buffer.empty())
  return;


  switch (movevalue) {
        case 0x0001: movevalue =  manualMoveStep; break;
        case 0x0002: movevalue = -manualMoveStep; break;
        default:     movevalue = 0; break;
      }

 // int16_t movevalue = swap16(*(uint16_t*)val_ptr);
=======
void DGUSScreenHandler::handleManualExtrude(DGUS_VP_Variable &var, void *val_ptr) {
  const int16_t movevalue = BE16_P(val_ptr);
>>>>>>> origin/release-2.1.3-beta2
  float target = movevalue * 0.01f;
  ExtUI::extruder_t target_extruder;

  switch (var.VP) {
    #if HAS_HOTEND
      case VP_MOVE_E0: target_extruder = ExtUI::extruder_t::E0; break;
      #if HAS_MULTI_EXTRUDER
        case VP_MOVE_E1: target_extruder = ExtUI::extruder_t::E1; break;
      #endif
    #endif
    default: return;
  }

  target += ExtUI::getAxisPosition_mm(target_extruder);
  ExtUI::setAxisPosition_mm(target, target_extruder);
  skipVP = var.VP;
}

#if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
<<<<<<< HEAD
  void DGUSScreenHandler::HandleManualMoveOption(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleManualMoveOption");
    *(uint16_t*)var.memadr = swap16(*(uint16_t*)val_ptr);
  }
#endif

void DGUSScreenHandler::HandleMotorLockUnlock(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleMotorLockUnlock");
  const int16_t lock = swap16(*(uint16_t*)val_ptr);
  queue.enqueue_one_now(lock ? F("M18") : F("M17"));
}

void DGUSScreenHandler::HandleSettings(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleSettings");
  uint16_t value = swap16(*(uint16_t*)val_ptr);
=======
  void DGUSScreenHandler::handleManualMoveOption(DGUS_VP_Variable &var, void *val_ptr) {
    *(uint16_t*)var.memadr = BE16_P(val_ptr);
  }
#endif

void DGUSScreenHandler::handleMotorLockUnlock(DGUS_VP_Variable &var, void *val_ptr) {
  const int16_t lock = BE16_P(val_ptr);
  queue.enqueue_one_now(lock ? F("M18") : F("M17"));
}

void DGUSScreenHandler::handleSettings(DGUS_VP_Variable &var, void *val_ptr) {
  const uint16_t value = BE16_P(val_ptr);
>>>>>>> origin/release-2.1.3-beta2
  switch (value) {
    default: break;
    case 1:
      TERN_(PRINTCOUNTER, print_job_timer.initStats());
      settings.reset();
      settings.save();
      break;
    case 2: settings.load(); break;
    case 3: settings.save(); break;
  }
}

<<<<<<< HEAD
// void DGUSScreenHandler::HandleStepPerMMChanged(DGUS_VP_Variable &var, void *val_ptr) { //ЗАКОМЕНТИЛ
//   DEBUG_ECHOLNPGM("HandleStepPerMMChanged");

//   uint16_t value_raw = swap16(*(uint16_t*)val_ptr);
//   DEBUG_ECHOLNPGM("value_raw:", value_raw);
//   float value = (float)value_raw / 10;
//   ExtUI::axis_t axis;
//   switch (var.VP) {
//     case VP_X_STEP_PER_MM: axis = ExtUI::axis_t::X; break;
//     case VP_Y_STEP_PER_MM: axis = ExtUI::axis_t::Y; break;
//     case VP_Z_STEP_PER_MM: axis = ExtUI::axis_t::Z; break;
//     default: return;
//   }
//   DEBUG_ECHOLNPGM("value:", value);
//   ExtUI::setAxisSteps_per_mm(value, axis);
//   DEBUG_ECHOLNPGM("value_set:", ExtUI::getAxisSteps_per_mm(axis));
//   skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
//   return;
// }


// void DGUSScreenHandler::HandleStepPerMMExtruderChanged(DGUS_VP_Variable &var, void *val_ptr) { //ЗАКОМЕНТИЛ
//   DEBUG_ECHOLNPGM("HandleStepPerMMExtruderChanged");

//   uint16_t value_raw = swap16(*(uint16_t*)val_ptr);
//   DEBUG_ECHOLNPGM("value_raw:", value_raw);
//   float value = (float)value_raw / 10;
//   ExtUI::extruder_t extruder;
//   switch (var.VP) {
//     default: return;
//       #if HAS_EXTRUDERS
//         case VP_E0_STEP_PER_MM: extruder = ExtUI::extruder_t::E0; break;
//         #if HAS_MULTI_EXTRUDER
//           case VP_E1_STEP_PER_MM: extruder = ExtUI::extruder_t::E1; break;
//         #endif
//       #endif
//   }
//   DEBUG_ECHOLNPGM("value:", value);
//   ExtUI::setAxisSteps_per_mm(value, extruder);
//   DEBUG_ECHOLNPGM("value_set:", ExtUI::getAxisSteps_per_mm(extruder));
//   skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
// }


//Свое частично 
void DGUSScreenHandler::HandlePIDAutotune(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandlePIDAutotune");

  char buf[32] = {0};
  char buf1[32] = {0};
  char buf2[32] = {0};

  switch (var.VP) {
    default: break;
      #if ENABLED(PIDTEMP)
        #if HAS_HOTEND
          case VP_PID_AUTOTUNE_E0: // Autotune Extruder 0
            thermalManager.fan_speed[0] = 70; //врубаем вентилятор
            queue.inject(F("G4 S1")); //команда ожидания выполнения след команды, без нее происходит игнор вентилятора
            sprintf_P(buf, PSTR("M303 E%d C8 S%d U1"), ExtUI::extruder_t::E0, Pid_Autotune_E0_Temp); 
            sprintf_P(buf1, PSTR("M106 S0")); //M106 S100
            queue.enqueue_one_now(buf);
            queue.enqueue_one_now(buf1);
            break;
        #endif
        #if HAS_MULTI_HOTEND
          case VP_PID_AUTOTUNE_E1:
            sprintf_P(buf, PSTR("M303 E%d C5 S210 U1"), ExtUI::extruder_t::E1);
            queue.enqueue_one_now(buf);
            break;
        #endif
      #endif
      #if ENABLED(PIDTEMPBED)
        case VP_PID_AUTOTUNE_BED:
          sprintf_P(buf1, PSTR("M303 E-1 C8 S%d U1"),Pid_Autotune_Bed_Temp);
          queue.enqueue_one_now(buf1);
          break;
      #endif
          case VP_PID_AUTOTUNE_ALL: // Autotune Extruder + bed свое
          thermalManager.fan_speed[0] = 100; //врубаем вентилятор
          queue.inject(F("G4 S1")); //команда ожидания выполнения след команды, без нее происходит игнор вентилятора
          sprintf_P(buf, PSTR("M303 E%d C8 S%d U1"), ExtUI::extruder_t::E0, Pid_Autotune_E0_Temp);
          sprintf_P(buf1, PSTR("M106 S0")); //M106 S100
          sprintf_P(buf2, PSTR("M303 E-1 C8 S%d U1"),Pid_Autotune_Bed_Temp);
          queue.enqueue_one_now(buf);
          queue.enqueue_one_now(buf1);
          queue.enqueue_one_now(buf2);
          break;
  }
  //#if ENABLED(DGUS_UI_WAITING)
    //sendinfoscreen(F("PID is autotuning"), F("please wait"), NUL_STR, NUL_STR, true, true, true, true);
    //GotoScreen(MKSLCD_PID_PROCESS); //свое - изменил экран куда переход
  //#endif
}

//Свое
void DGUSScreenHandler::HandlePIDAbort(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandlePIDAbort");
  wait_for_heatup = false;
}

//Свое
#if HAS_BED_PROBE
  void DGUSScreenHandler::HandleProbeOffsetZChanged(DGUS_VP_Variable &var, void *val_ptr) { //есть на других дисплеях, но не на нашем
    DEBUG_ECHOLNPGM("HandleProbeOffsetZChanged");

    const float offset = float(int16_t(swap16(*(uint16_t*)val_ptr))) / 100.0f;
=======
#if ENABLED(EDITABLE_STEPS_PER_UNIT)

  void DGUSScreenHandler::handleStepPerMMChanged(DGUS_VP_Variable &var, void *val_ptr) {
    const uint16_t value_raw = BE16_P(val_ptr);
    const float value = (float)value_raw / 10;
    ExtUI::axis_t axis;
    switch (var.VP) {
      case VP_X_STEP_PER_MM: axis = ExtUI::axis_t::X; break;
      case VP_Y_STEP_PER_MM: axis = ExtUI::axis_t::Y; break;
      case VP_Z_STEP_PER_MM: axis = ExtUI::axis_t::Z; break;
      default: return;
    }
    ExtUI::setAxisSteps_per_mm(value, axis);
    skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
  }

  void DGUSScreenHandler::handleStepPerMMExtruderChanged(DGUS_VP_Variable &var, void *val_ptr) {
    const uint16_t value_raw = BE16_P(val_ptr);
    const float value = (float)value_raw / 10;
    ExtUI::extruder_t extruder;
    switch (var.VP) {
      default: return;
        #if HAS_EXTRUDERS
          case VP_E0_STEP_PER_MM: extruder = ExtUI::extruder_t::E0; break;
          #if HAS_MULTI_EXTRUDER
            case VP_E1_STEP_PER_MM: extruder = ExtUI::extruder_t::E1; break;
          #endif
        #endif
    }
    ExtUI::setAxisSteps_per_mm(value, extruder);
    skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
  }

#endif // EDITABLE_STEPS_PER_UNIT

#if HAS_PID_HEATING
  void DGUSScreenHandler::handlePIDAutotune(DGUS_VP_Variable &var, void *val_ptr) {
    char buf[32] = {0};

    switch (var.VP) {
      default: break;
        #if ENABLED(PIDTEMP)
          #if HAS_HOTEND
            case VP_PID_AUTOTUNE_E0: // Autotune Extruder 0
              sprintf_P(buf, PSTR("M303 E%d C5 S210 U1"), ExtUI::extruder_t::E0);
              queue.enqueue_one_now(buf);
              break;
          #endif
          #if HAS_MULTI_HOTEND
            case VP_PID_AUTOTUNE_E1:
              sprintf_P(buf, PSTR("M303 E%d C5 S210 U1"), ExtUI::extruder_t::E1);
              queue.enqueue_one_now(buf);
              break;
          #endif
        #endif
        #if ENABLED(PIDTEMPBED)
          case VP_PID_AUTOTUNE_BED:
            queue.enqueue_one_now(F("M303 E-1 C5 S70 U1"));
            break;
        #endif
    }

    #if ENABLED(DGUS_UI_WAITING)
      sendInfoScreen(F("PID is autotuning"), F("please wait"), NUL_STR, NUL_STR, true, true, true, true);
      gotoScreen(DGUS_SCREEN_WAITING);
    #endif
  }
#endif // HAS_PID_HEATING

#if HAS_BED_PROBE
  void DGUSScreenHandler::handleProbeOffsetZChanged(DGUS_VP_Variable &var, void *val_ptr) {
    const float offset = float(int16_t(BE16_P(val_ptr))) / 100.0f;
>>>>>>> origin/release-2.1.3-beta2
    ExtUI::setZOffset_mm(offset);
    skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
    return;
  }
<<<<<<< HEAD

  void DGUSScreenHandler::HandleAutoCalibrationStartStop(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleAutoCalibrationStartStop");
    int16_t movevalue = swap16(*(uint16_t*)val_ptr);

    thermalManager.zero_fan_speeds(); //вырубаем вентиляторы

    // char buf1[32] = {0};
    // char buf2[32] = {0};
    // char buf3[32] = {0};
    // char buf4[32] = {0};


    uint16_t vp_step = VP_Level_Point_2 - VP_Level_Point_1;
    char buf[52] = {0};
    char buf1[100] = {0};

    switch (movevalue) {
    case 0x0001: // Калибровка стандартная на 1 температуру
      thermalManager.setTargetHotend(EXTRUDE_MINTEMP, 0);
      GcodeSuite::should_stop = false;
      dgusdisplay.WriteString(VP_LEVELING_STATUS, GET_TEXT_F(MSG_PREPARATION), VP_Status_LEN); //TODO переделать с нагрева стола на ИДЕТ НАГРЕВ

      for (uint8_t pt_index = 0; pt_index < GRID_MAX_POINTS; pt_index++)
      {
        dgusdisplay.WriteVariable(VP_Level_Point_1 + vp_step * pt_index, static_cast<uint16_t>(0));
      }

      sprintf_P(buf, PSTR("M190 S%d\nG4 S20\nG28\nG29\nM140 S0\nM104 S0"), Auto_Leveling_Temp_1);
      queue.inject(buf);
      GotoScreen(MKSLCD_AUTO_LEVEL);
    break;

    case 0x0002: //Калибровка своя для двух температур TODO
      thermalManager.setTargetHotend(EXTRUDE_MINTEMP, 0);
      GcodeSuite::should_stop = false;
      dgusdisplay.WriteString(VP_LEVELING_STATUS, GET_TEXT_F(MSG_PREPARATION), VP_Status_LEN);
      
      for (uint8_t pt_index = 0; pt_index < GRID_MAX_POINTS; pt_index++)
      {
        dgusdisplay.WriteVariable(VP_Level_Point_1 + vp_step * pt_index, static_cast<uint16_t>(0));
      }

      sprintf_P(buf1, PSTR("M190 S%d\nG4 S20\nG28\nG29 M1\nM190 S%d\nG4 S20\nG29 M2\nM140 S0\nM104 S0"), Auto_Leveling_Temp_1, Auto_Leveling_Temp_2); //больше 8 команд нельзя почему то М104 уже не работает
      queue.inject(buf1);
      GotoScreen(MKSLCD_AUTO_LEVEL);
    break;

    case 0x0003: //отмена
    {
      dgusdisplay.WriteString(VP_LEVELING_STATUS, GET_TEXT_F(MSG_LEVEL_BED_ABORTED), VP_Status_LEN); // выводить отмену калибровки

       thermalManager.setTargetBed(0);
       thermalManager.setTargetHotend(0, 0);
       sprintf_P(buf, PSTR("M140 S0"));
       queue.enqueue_one_now(buf);

      // IF_DISABLED(NO_SD_AUTOSTART, card.autofile_cancel());
      // card.abortFilePrintNow(TERN_(SD_RESORT, true));
      for (size_t i = 0; i < BUFSIZE-1; i++)  // TODO: задача с отменой команд
      {
        queue.get_available_commands();
        queue.clear();
        planner.clear_block_buffer();
        GCodeQueue::injected_commands_P = nullptr;
        GCodeQueue::injected_commands[0] = 0;
      }

      //   xyze_pos_t position_before_1 = current_position;
      //   destination.set(position_before_1.x, position_before_1.y, position_before_1.z); //два последних чтобы стол и экструдер не ехали
      // prepare_internal_move_to_destination(50);
      // quickstop_stepper();
      //   planner.quick_stop();
      // planner.synchronize();

      // print_job_timer.abort();
      GcodeSuite::should_stop = true; 
      // queue.enqueue_one_now(buf);
      thermalManager.setTargetBed(0);
      GotoScreen(MKSLCD_AUTO_LEVEL_DONE);}
    break;    
    
    case 0x0004: //готово и возврат назад
      sprintf_P(buf, PSTR("M140 S0\nM104 S0")); // не проверял 
      queue.enqueue_one_now(buf);
      GotoScreen(MKSLCD_SCREEN_LEVEL);
      settings.save();
      //надо сделать сохранение сетки в епром
    break;    
    default: break;
    }
    
  }
#endif



#if HAS_FAN
  void DGUSScreenHandler::HandleFanControl(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleFanControl");
    *(uint8_t*)var.memadr = *(uint8_t*)var.memadr > 0 ? 0 : 255;
    dgusdisplay.WriteVariable(VP_T_Fan0_ON, thermalManager.fan_speed[0] > 0 ? (uint16_t)1 : (uint16_t)0); // Свое, без этого работало, но можно было встретить баг с реверсом иконки
    ForceCompleteUpdate(); 
  }
#endif

// void DGUSScreenHandler::HandleHeaterControl(DGUS_VP_Variable &var, void *val_ptr) { //Коммент
//   DEBUG_ECHOLNPGM("HandleHeaterControl");

//   uint8_t preheat_temp = 0;
//   switch (var.VP) {
//     #if HAS_HOTEND
//       case VP_E0_CONTROL:
//       #if HAS_MULTI_HOTEND
//         case VP_E1_CONTROL:
//         #if HOTENDS >= 3
//           case VP_E2_CONTROL:
//         #endif
//       #endif
//       preheat_temp = PREHEAT_1_TEMP_HOTEND;
//       break;
//     #endif

//     #if HAS_HEATED_BED
//       case VP_BED_CONTROL:
//         preheat_temp = PREHEAT_1_TEMP_BED;
//         break;
//     #endif
//   }

//   *(int16_t*)var.memadr = *(int16_t*)var.memadr > 0 ? 0 : preheat_temp;
// }

#if ENABLED(DGUS_PREHEAT_UI)

  void DGUSScreenHandler::HandlePreheat(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandlePreheat");

    const uint16_t preheat_option = swap16(*(uint16_t*)val_ptr);
=======
#endif

#if HAS_FAN
  void DGUSScreenHandler::handleFanControl(DGUS_VP_Variable &var, void *val_ptr) {
    *(uint8_t*)var.memadr = *(uint8_t*)var.memadr > 0 ? 0 : 255;
  }
#endif

void DGUSScreenHandler::handleHeaterControl(DGUS_VP_Variable &var, void *val_ptr) {
  uint8_t preheat_temp = 0;
  switch (var.VP) {
    #if HAS_HOTEND
      case VP_E0_CONTROL:
      #if HAS_MULTI_HOTEND
        case VP_E1_CONTROL:
        #if HOTENDS >= 3
          case VP_E2_CONTROL:
        #endif
      #endif
      preheat_temp = PREHEAT_1_TEMP_HOTEND;
      break;
    #endif

    #if HAS_HEATED_BED
      case VP_BED_CONTROL:
        preheat_temp = PREHEAT_1_TEMP_BED;
        break;
    #endif
  }

  *(int16_t*)var.memadr = *(int16_t*)var.memadr > 0 ? 0 : preheat_temp;
}

#if ENABLED(DGUS_PREHEAT_UI)

  void DGUSScreenHandler::handlePreheat(DGUS_VP_Variable &var, void *val_ptr) {
    const uint16_t preheat_option = BE16_P(val_ptr);
>>>>>>> origin/release-2.1.3-beta2
    switch (preheat_option) {
      default:
      switch (var.VP) {
        default: return;
        case VP_E0_BED_PREHEAT: TERN_(HAS_HOTEND, ui.preheat_all(0)); break;
        #if DISABLED(DGUS_LCD_UI_HIPRECY) && HAS_MULTI_HOTEND
          case VP_E1_BED_PREHEAT: ui.preheat_all(1); break;
        #endif
      }
      case 7: break; // Custom preheat
      case 9: thermalManager.cooldown(); break; // Cool down
    }

    // Go to the preheat screen to show the heating progress
<<<<<<< HEAD
    GotoScreen(DGUSLCD_SCREEN_PREHEAT);
=======
    gotoScreen(DGUS_SCREEN_PREHEAT);
>>>>>>> origin/release-2.1.3-beta2
  }

#endif // DGUS_PREHEAT_UI

#if ENABLED(POWER_LOSS_RECOVERY)

<<<<<<< HEAD
  void DGUSScreenHandler::HandlePowerLossRecovery(DGUS_VP_Variable &var, void *val_ptr) {
    uint16_t value = swap16(*(uint16_t*)val_ptr);
    if (value) {
      queue.inject(F("M1000"));
      dgusdisplay.WriteVariable(VP_SD_Print_Filename, filelist.filename(), 32, true);
      GotoScreen(PLR_SCREEN_RECOVER);
    }
    else {
      recovery.cancel();
      GotoScreen(PLR_SCREEN_CANCEL);
=======
  void DGUSScreenHandler::handlePowerLossRecovery(DGUS_VP_Variable &var, void *val_ptr) {
    uint16_t value = BE16_P(val_ptr);
    if (value) {
      queue.inject(F("M1000"));
      dgus.writeVariable(VP_SD_Print_Filename, filelist.filename(), 32, true);
      gotoScreen(PLR_SCREEN_RECOVER);
    }
    else {
      recovery.cancel();
      gotoScreen(PLR_SCREEN_CANCEL);
>>>>>>> origin/release-2.1.3-beta2
    }
  }

#endif

<<<<<<< HEAD



void DGUSScreenHandler::UpdateNewScreen(DGUSLCD_Screens newscreen, bool popup) {
  DEBUG_ECHOLNPGM("SetNewScreen: ", newscreen);
  if (!popup) {
    memmove(&past_screens[1], &past_screens[0], sizeof(past_screens) - 1);
    past_screens[0] = current_screen;
  }
  current_screen = newscreen;
  skipVP = 0;
  ForceCompleteUpdate();
}

void DGUSScreenHandler::PopToOldScreen() {
  DEBUG_ECHOLNPGM("PopToOldScreen s=", past_screens[0]);
  GotoScreen(past_screens[0], true);
  memmove(&past_screens[0], &past_screens[1], sizeof(past_screens) - 1);
  past_screens[sizeof(past_screens) - 1] = DGUSLCD_SCREEN_MAIN;
}

void DGUSScreenHandler::UpdateScreenVPData() {
  DEBUG_ECHOPGM(" UpdateScreenVPData Screen: ", current_screen);

  const uint16_t *VPList = DGUSLCD_FindScreenVPMapList(current_screen);
  if (!VPList) {
    DEBUG_ECHOLNPGM(" NO SCREEN FOR: ", current_screen);
    ScreenComplete = true;
=======
void DGUSScreenHandler::updateNewScreen(const DGUS_ScreenID screenID, const bool popup) {
  if (!popup) {
    memmove(&past_screenIDs[1], &past_screenIDs[0], sizeof(past_screenIDs) - 1);
    past_screenIDs[0] = current_screenID;
  }
  current_screenID = screenID;
  skipVP = 0;
  forceCompleteUpdate();
}

void DGUSScreenHandler::popToOldScreen() {
  gotoScreen(past_screenIDs[0], true);
  memmove(&past_screenIDs[0], &past_screenIDs[1], sizeof(past_screenIDs) - 1);
  past_screenIDs[sizeof(past_screenIDs) - 1] = DGUS_SCREEN_MAIN;
}

void DGUSScreenHandler::updateScreenVPData() {
  const uint16_t *VPList = findScreenVPMapList(current_screenID);
  if (!VPList) {
    screenComplete = true;
>>>>>>> origin/release-2.1.3-beta2
    return; // nothing to do, likely a bug or boring screen.
  }

  // Round-robin updating of all VPs.
  VPList += update_ptr;

  bool sent_one = false;
  do {
    uint16_t VP = pgm_read_word(VPList);
<<<<<<< HEAD
    DEBUG_ECHOPGM(" VP: ", VP);
    if (!VP) {
      update_ptr = 0;
      DEBUG_ECHOLNPGM(" UpdateScreenVPData done");
      ScreenComplete = true;
=======
    if (!VP) {
      update_ptr = 0;
      screenComplete = true;
>>>>>>> origin/release-2.1.3-beta2
      return; // Screen completed.
    }

    if (VP == skipVP) { skipVP = 0; continue; }

    DGUS_VP_Variable rcpy;
    if (populate_VPVar(VP, &rcpy)) {
      uint8_t expected_tx = 6 + rcpy.size; // expected overhead is 6 bytes + payload.
      // Send the VP to the display, but try to avoid overrunning the Tx Buffer.
      // But send at least one VP, to avoid getting stalled.
<<<<<<< HEAD
      if (rcpy.send_to_display_handler && (!sent_one || expected_tx <= dgusdisplay.GetFreeTxBuffer())) {
        //DEBUG_ECHOPGM(" calling handler for ", rcpy.VP);
=======
      if (rcpy.send_to_display_handler && (!sent_one || expected_tx <= dgus.getFreeTxBuffer())) {
>>>>>>> origin/release-2.1.3-beta2
        sent_one = true;
        rcpy.send_to_display_handler(rcpy);
      }
      else {
<<<<<<< HEAD
        // auto x=dgusdisplay.GetFreeTxBuffer();
        //DEBUG_ECHOLNPGM(" tx almost full: ", x);
        //DEBUG_ECHOPGM(" update_ptr ", update_ptr);
        ScreenComplete = false;
=======
        screenComplete = false;
>>>>>>> origin/release-2.1.3-beta2
        return; // please call again!
      }
    }

  } while (++update_ptr, ++VPList, true);
}

<<<<<<< HEAD
void DGUSScreenHandler::GotoScreen(DGUSLCD_Screens screen, bool ispopup) {
  dgusdisplay.RequestScreen(screen);
  UpdateNewScreen(screen, ispopup);
}

void DGUSDisplay::RequestScreen(DGUSLCD_Screens screen) {
  DEBUG_ECHOLNPGM("GotoScreen ", screen);
  const unsigned char gotoscreen[] = { 0x5A, 0x01, (unsigned char) (screen >> 8U), (unsigned char) (screen & 0xFFU) };
  WriteVariable(0x84, gotoscreen, sizeof(gotoscreen));
}


=======
void DGUSScreenHandler::gotoScreen(const DGUS_ScreenID screenID, const bool popup/*=false*/) {
  dgus.requestScreen(screenID);
  updateNewScreen(screenID, popup);
}

void DGUSDisplay::requestScreen(const DGUS_ScreenID screenID) {
  const unsigned char gotoscreen[] = { 0x5A, 0x01, (unsigned char) (screenID >> 8U), (unsigned char) (screenID & 0xFFU) };
  writeVariable(0x84, gotoscreen, sizeof(gotoscreen));
}

>>>>>>> origin/release-2.1.3-beta2
#endif // HAS_DGUS_LCD_CLASSIC
