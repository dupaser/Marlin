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

#include "../../../../inc/MarlinConfigPre.h"

#if ENABLED(DGUS_LCD_UI_MKS)

#include "DGUSDisplayDef.h"
#include "../DGUSDisplay.h"
#include "../DGUSScreenHandler.h"
#include "../DGUSScreenHandlerBase.h"


#include "../../../../module/temperature.h"
#include "../../../../module/motion.h"
#include "../../../../module/planner.h"

#include "../../../../feature/runout.h"//Свое

#include "../../ui_api.h"
#include "../../../marlinui.h"

#if HAS_STEALTHCHOP
  #include "../../../../module/stepper/trinamic.h"
#endif

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../../../feature/powerloss.h"
#endif

#if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
  uint16_t distanceToMove = 10;
#endif

TempPreset nozzlePreset;
TempPreset bedPreset;
TempPreset chamberPreset;

uint16_t fan_0_Step = 0;
uint16_t  manualMoveStep = 1;
uint16_t manualExtruderDistance = 1;
uint16_t manualExtruderSpeed = 1;
uint16_t PrintSettingsStep = 1; //свое


uint16_t distanceFilament = 10;
uint16_t filamentSpeed_mm_s = 25;
uint16_t BabyStep_Step = 0;
uint16_t Zoffset_Step = 0;
float mesh_adj_distance = 0.01;
float Z_distance = 0.1;

float KFactorStep = 0.001;

std::vector<std::string> errors;

//struct { uint16_t h, m, s; } dgus_time;

//
// Persistent settings
//
xy_int_t mks_corner_offsets[5];   // Initialized by settings.load()
xyz_int_t mks_park_pos;           // Initialized by settings.load()
celsius_t mks_min_extrusion_temp; // Initialized by settings.load()

void MKS_reset_settings() {
  constexpr xy_int_t init_dgus_level_offsets[5] = {
    { 10, 10 }, { 10, 10 },
    { 10, 10 }, { 10, 10 },
    { X_CENTER, Y_CENTER }
  };
  mks_language_index = MKS_SimpleChinese;
  COPY(mks_corner_offsets, init_dgus_level_offsets);
  mks_park_pos.set(NOZZLE_PARK_POINT_X, NOZZLE_PARK_POINT_Y, NOZZLE_PARK_POINT_Z); 
  mks_min_extrusion_temp = 0;
}
xyze_pos_t position_before_pause;
feedRate_t feedrate_before_pause;


constexpr feedRate_t park_speed_xy = TERN(NOZZLE_PARK_FEATURE, NOZZLE_PARK_XY_FEEDRATE, 100),
                     park_speed_z  = TERN(NOZZLE_PARK_FEATURE, NOZZLE_PARK_Z_FEEDRATE,    10);

void MKS_pause_print_move() {
  if (!ExtUI::isPrinting()) return;

  if (nozzle_park_mks.print_pause_start_flag) 
  { queue.exhaust(); } 
  feedrate_before_pause = feedrate_mm_s;
  position_before_pause = current_position;


 // Save the current position, the raise amount, and 'already raised'
 TERN_(POWER_LOSS_RECOVERY, if (recovery.enabled) recovery.save(true, mks_park_pos.z, true));

  if (all_axes_homed()) { //чтобы не ударить соплом об стол если нет парковки
 destination.e = position_before_pause.e - PAUSE_PARK_RETRACT_LENGTH;
 prepare_internal_move_to_destination(PAUSE_PARK_RETRACT_FEEDRATE);

  destination.z = _MIN(current_position.z + mks_park_pos.z, Z_MAX_POS);
  prepare_internal_move_to_destination(park_speed_z);

  destination.set(NOZZLE_PARK_POINT_X, NOZZLE_PARK_POINT_Y); //два последних чтобы стол и экструдер не ехали
  prepare_internal_move_to_destination(park_speed_xy);
  }

  if (!nozzle_park_mks.filament_change){
  DGUSScreenHandler::GotoScreen(MKSLCD_SCREEN_PAUSE); //Переход только если не была нажата кнопка смены филамента во время печати
  }
}

void MKS_resume_print_move() {
  feedrate_mm_s = feedrate_before_pause;

  if (all_axes_homed()) { //чтобы не ударить соплом об стол если нет парковки
  destination.set(position_before_pause.x, position_before_pause.y);
  prepare_internal_move_to_destination(park_speed_xy);
  destination.z = position_before_pause.z;
  prepare_internal_move_to_destination(park_speed_z);
  

  destination.e = position_before_pause.e;
  prepare_internal_move_to_destination(PAUSE_PARK_RETRACT_FEEDRATE);
  }
  
  TERN_(POWER_LOSS_RECOVERY, if (recovery.enabled) recovery.save(true));

  FilamentMonitorBase::filament_ran_out = false;
  RunoutResponseDelayed::reset();
  nozzle_park_mks.print_pause_start_flag = 0;
  nozzle_park_mks.filament_change = 0;
}

float babystep_add = 0;

#if HAS_BED_PROBE
  float z_offset_set = probe.offset.z;
#endif

//xyz_int_t tmc_step; // = { 0, 0, 0 }

uint16_t lcd_default_light = 50;

uint16_t Pid_Autotune_E0_Temp =  PID_TEMPERATURE_HOTEND; //Свое
uint16_t Pid_Autotune_Bed_Temp = PID_TEMPERATURE_BED;

uint16_t Auto_Leveling_Temp_1 = LEVELING_TEMPERATURE_1;
uint16_t Auto_Leveling_Temp_2 = LEVELING_TEMPERATURE_2;

EX_FILAMENT_DEF ex_filament;
RUNOUT_MKS_DEF runout_mks;
NOZZLE_PARK_DEF nozzle_park_mks;

const uint16_t VPList_Boot[] PROGMEM = {
  VP_T_E0_Is, VP_T_E0_Set,
  VP_T_Bed_Is, VP_T_Bed_Set, 
  VP_T_Chamber_Is, VP_T_Chamber_Set,
  VP_Fan0_Percentage,
  VP_FLASH_STATUS,
  VP_HOT_STATUS,
  VP_FILAMENT_RUNOUT_STATUS,

  0x0000
};

#define MKSLIST_E_ITEM(N) VP_T_E##N##_Is, VP_T_E##N##_Set,

const uint16_t VPList_Main[] PROGMEM = {
  // VP_M117, for completeness, but it cannot be auto-uploaded.
  #if HAS_HOTEND
    MKSLIST_E_ITEM(0) VP_E0_STATUS,
    #if HAS_MULTI_HOTEND
      MKSLIST_E_ITEM(1) VP_E1_STATUS,
    #endif
  #endif
  #if HAS_HEATED_BED
    VP_T_Bed_Is, VP_T_Bed_Set,// VP_BED_STATUS,
  #endif
  #if HAS_FAN
    VP_Fan0_Percentage,// VP_FAN0_STATUS,
  #endif
  VP_XPos, VP_YPos, VP_ZPos,
  VP_Fan0_Percentage,
  VP_Feedrate_Percentage,
  VP_T_Chamber_Is, VP_T_Chamber_Set,
  #if ENABLED(LCD_SET_PROGRESS_MANUALLY)
    VP_PrintProgress_Percentage,
  #endif
  0x0000
};

const uint16_t MKSList_Home[] PROGMEM = {
  REPEAT(EXTRUDERS, MKSLIST_E_ITEM)
  VP_T_Bed_Is, VP_T_Bed_Set, 
  VP_T_Chamber_Is, VP_T_Chamber_Set,
  VP_Fan0_Percentage,
  VP_FLASH_STATUS,
  VP_HOT_STATUS,
  VP_FILAMENT_RUNOUT_STATUS,

  0x0000
};
 

const uint16_t MKSList_Preheat[] PROGMEM = {   ///свое детище
  REPEAT(EXTRUDERS, MKSLIST_E_ITEM)
  VP_T_Bed_Is, VP_T_Bed_Set,
  VP_T_Chamber_Is, VP_T_Chamber_Set,
  VP_T_E0_ON, VP_T_Bed_ON, VP_T_Chamber_ON, //VP_T_Fan0_ON,
  VP_Fan0_Percentage,

  0x0000
};


const uint16_t MKSList_K_Factor[] PROGMEM = {   ///свое детище
  VP_K_Factor_Value,
  
  0x0000
};


const uint16_t MKSList_Tool[] PROGMEM = {
  VP_FILAMENT_SENSOR_STATUS,

  0x0000
};

const uint16_t MKSList_EXTRUE[] PROGMEM = {
  REPEAT(EXTRUDERS, MKSLIST_E_ITEM)
  VP_FILAMENT_CHANGE_STATUS,
  VP_T_E0_ON,

  0x0000
};

const uint16_t MKSList_LEVEL[] PROGMEM = {
  #if HAS_BED_PROBE
    VP_LEVELING_TEMP_1,
    VP_LEVELING_TEMP_2,
    VP_LEVELING_STATUS,
  #else
    REPEAT(EXTRUDERS, MKSLIST_E_ITEM)
    VP_T_Bed_Is, VP_T_Bed_Set,
    VP_T_E0_ON, VP_T_Bed_ON,
  #endif

  0x0000
};


#if HAS_BED_PROBE
const uint16_t MKSList_AUTO_LEVEL[] PROGMEM = {
    //VP_LEVELING_STATUS,
    REPEAT(EXTRUDERS, MKSLIST_E_ITEM)
    VP_T_Bed_Is, VP_T_Bed_Set,

  0x0000
};
#endif


const uint16_t MKSList_MOVE[] PROGMEM = {
  VP_XPos,
  VP_YPos,
  VP_ZPos,

  0x0000
};

const uint16_t MKSList_Print[] PROGMEM = {
  REPEAT(EXTRUDERS, MKSLIST_E_ITEM)
  VP_T_Bed_Is, VP_T_Bed_Set,
  VP_T_Chamber_Is, VP_T_Chamber_Set,
  VP_Fan0_Percentage,

  VP_PrintProgress_Percentage,
  VP_PrintTime,
  VP_Flowrate_E0,
  VP_Flowrate_E1,
  VP_Feedrate_Percentage,

  VP_PrintTime_H,
  VP_PrintTime_M,
  VP_PrintTime_S,

  VP_FLASH_STATUS,
  VP_HOT_STATUS,
  VP_FILAMENT_RUNOUT_STATUS,
  VP_ZPos,

  0x0000
};

const uint16_t MKSList_Print_Done[] PROGMEM = {
  REPEAT(EXTRUDERS, MKSLIST_E_ITEM)
  VP_T_Bed_Is, VP_T_Bed_Set,
  VP_T_Chamber_Is, VP_T_Chamber_Set,
  VP_Fan0_Percentage,

   VP_PrintProgress_Percentage,

  VP_Flowrate_E0,
  VP_Flowrate_E1,
  VP_Feedrate_Percentage,

  VP_FLASH_STATUS,
  VP_HOT_STATUS,
  VP_FILAMENT_RUNOUT_STATUS,
  VP_ZPos,

  0x0000
};

const uint16_t MKSList_Errors[] PROGMEM = {
  VP_ErrorName3,
  VP_ErrorName4,
  VP_ErrorName5,
  VP_ErrorName6, 
  VP_ErrorName7,
  VP_ErrorName8,
  VP_ErrorName0, 
  VP_ErrorName1,
  VP_ErrorName2, 
  //VP_TEST_PAGE, //VP_SD_FileName9,

  0x0000
};

const uint16_t MKSList_SD_File[] PROGMEM = {
  VP_SD_FileName0, 
  VP_SD_FileName1,
  VP_SD_FileName2, 
  VP_SD_FileName3,
  VP_SD_FileName4,
  VP_SD_FileName5,
  #if !HAS_BED_PROBE
  VP_SD_FileName6, 
  VP_SD_FileName7,
  VP_SD_FileName8,
  #endif
  //VP_TEST_PAGE, //VP_SD_FileName9,

  0x0000
};


const uint16_t MKSList_PID[] PROGMEM = { 
  VP_T_E0_Is,
  VP_T_Bed_Is,
  VP_PID_AUTOTUNE_E0_TEMP,
  VP_PID_AUTOTUNE_BED_TEMP,

  0x0000
};


const uint16_t MKSList_PID_Process[] PROGMEM = {
  VP_T_E0_Is,
  VP_T_Bed_Is,

  0x0000
};


const uint16_t MKSList_PrintConfig[] PROGMEM = {
  VP_Flowrate_E0,
  //VP_Flowrate_E1,
  
  #if !HAS_BED_PROBE
    VP_Fan0_Percentage, // для вертикального дисплея
  #endif

  VP_Feedrate_Percentage,
  VP_FILAMENT_SENSOR_STATUS,

  0x0000
};


const uint16_t MKSList_PrintTemp[] PROGMEM = { //свое
  VP_T_Chamber_Set,
  VP_T_E0_Set,
  //VP_T_E1_Set,
  VP_T_Bed_Set,
  #if HAS_BED_PROBE
    VP_Fan0_Percentage, // тут для горизонтального дисплея
  #endif

  0x0000
};

#if ENABLED(BABYSTEPPING)
  const uint16_t MKSBabyStep[] PROGMEM = {
      VP_BabyStep_Distance,

    0x0000
  };
#endif

#if HAS_BED_PROBE
  const uint16_t MKS_Zoffset[] PROGMEM = {
    VP_Zoffset_Distance,

    0x0000
  };
#endif

const uint16_t MKSList_About[] PROGMEM = {
  VP_MARLIN_VERSION,
  //VP_MKS_H43_VERSION,
  VP_PRINTER_VERSION,

  0x0000
};

// Page data updata
const struct VPMapping VPMap[] PROGMEM = {
  { MKSLCD_SCREEN_BOOT, VPList_Boot },                        // Boot Page to show logo  0
  { MKSLCD_SCREEN_HOME, MKSList_Home },                       // Home, Page 1
  //{ MKSLCD_SCREEN_SETTING, MKSList_Setting },                 // Setting, Page 2
  { MKSLCD_SCREEN_PREHEAT, MKSList_Preheat },                 // Setting, Page 2
  { MKSLCD_SCREEN_TOOL, MKSList_Tool },                       // Page 3
  { MKSLCD_SCREEN_EXTRUDE_P1, MKSList_EXTRUE },               // Page 4
  //{ MKSLCD_SCREEN_EXTRUDE_P2, MKSList_EXTRUE },               // Page 11
  { MKSLCD_PAUSE_SETTING_EX, MKSList_EXTRUE },                // Page 57
  //{ MKSLCD_PAUSE_SETTING_EX2, MKSList_EXTRUE },               // Page 61
  { MKSLCD_SCREEN_LEVEL, MKSList_LEVEL },                     // Page 5
  
  #if HAS_BED_PROBE
  { MKSLCD_AUTO_LEVEL, MKSList_AUTO_LEVEL},                     
  { MKSLCD_AUTO_LEVEL_DONE, MKSList_AUTO_LEVEL},   
  { MKSLCD_Zoffset_Set, MKS_Zoffset }, 
  { MKSLCD_Screen_Baby, MKS_Zoffset },                        
  #endif

  { MKSLCD_SCREEN_MOVE, MKSList_MOVE },                       // Page 6
  { MKSLCD_SCREEN_PRINT, MKSList_Print },                     // Page 7
  { MKSLCD_SCREEN_PAUSE, MKSList_Print },                     // Page 26
  { MKSLCD_SCREEN_CHOOSE_FILE, MKSList_SD_File },             // Page 40
  { MKSLCD_SCREEN_CHOOSE_FILE_1, MKSList_SD_File },             // Page 41
  { MKSLCD_SCREEN_CHOOSE_FILE_2, MKSList_SD_File },             // Page 42
  { MKSLCD_SCREEN_CHOOSE_FILE_3, MKSList_SD_File },             // Page 43

  { MKSLCD_SCREEN_CHOOSE_FILE_FOLDER, MKSList_SD_File },             // Page 40
  { MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_1, MKSList_SD_File },             // Page 41
  { MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_2, MKSList_SD_File },             // Page 42
  { MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_3, MKSList_SD_File },             // Page 43

  //{ MKSLCD_SCREEN_MOTOR_PLUSE, MKSList_Pluse },               // Page 51
  //{ MKSLCD_SCREEN_MOTOR_SPEED, MKSList_MaxSpeed },            // Page 55
  //{ MKSLCD_SCREEN_MOTOR_ACC_MAX, MKSList_MaxAcc },            // Page 53
  //{ MKSLCD_SCREEN_LEVEL_DATA, MKSList_Level_Point },          // Page 48
  //{ MKSLCD_PrintPause_SET, MKSList_PrintPauseConfig },        // Page 49
  { MKSLCD_SCREEN_ERROR, MKSList_Errors },                 // Page 50
  { MKSLCD_SCREEN_ERROR_1, MKSList_Errors },                 // Page 50
  //{ MKSLCD_SCREEN_Config, MKSList_TempOnly },                 // Page 46
  //{ MKSLCD_SCREEN_Config_MOTOR, MKSList_MotoConfig },         // Page 47
  { MKSLCD_PID, MKSList_PID },                                // Page 56
  { MKSLCD_PID_PROCESS, MKSList_PID_Process },                        // Page 56
  { MKSLCD_PID_COMPLETE, MKSList_PID_Process },                       // Page 56
  { MKSLCD_ABOUT, MKSList_About },                            // Page 36
  { MKSLCD_SCREEN_PRINT_CONFIG, MKSList_PrintConfig },  // Page 60
  { MKSLCD_SCREEN_PRINT_TEMP, MKSList_PrintTemp },      // Свое
  // { MKSLCD_SCREEN_EX_CONFIG, MKSList_EX_Config },             // Page 65
  // { MKSLCD_SCREEN_TMC_Config, MKSTMC_Config },                // Page 70
  // { MKSLCD_AUTO_LEVEL, MKSAuto_Level },                       // Page 73
  // { MKSLCD_Screen_Offset_Config, MKSOffset_Config },          // Page 30
  { MKSLCD_Screen_PMove, MKSList_MOVE },                      // Page 64
  #if ENABLED(BABYSTEPPING)
    { MKSLCD_Screen_Baby, MKSBabyStep },                        // Page 71 
  #endif


  { MKSLCD_SCREEN_PrintDone, MKSList_Print_Done },                 // Page 71
  { MKSLCD_SCREEN_K_FACTOR, MKSList_K_Factor },
  { MKSLCD_SCREEN_PRINT_K_FACTOR, MKSList_K_Factor },                
  { MKSLCD_SCREEN_PRINT_REHEAT, MKSList_Print },     
           
  //{ MKSLCD_SCREEN_LEVEL_DATA, MKSList_SD_File},
  //{ MKSLCD_SCREEN_HOME, VPList_Boot },
  { 0, nullptr } // List is terminated with an nullptr as table entry.
};

const char MarlinVersion[] PROGMEM = SHORT_BUILD_VERSION;
const char H43Version[] PROGMEM = CUSTOM_SCREEN_VERSION;
const char Updata_Time[] PROGMEM = STRING_DISTRIBUTION_DATE;
const char Printer_Name[] PROGMEM = CUSTOM_MACHINE_NAME; 

  uint16_t a = ((unsigned char) (DGUSScreenHandler::current_screen >> 8U)) + ( (unsigned char) (DGUSScreenHandler::current_screen & 0xFFU));
  uint16_t b = DGUSScreenHandler::current_screen;
  // int* b = &a;

  const struct DGUS_VP_Variable ListOfVP[] PROGMEM = {
  // Helper to detect touch events
  VPHELPER(VP_SCREENCHANGE, nullptr, ScreenHandler.ScreenChangeHook, nullptr),
  VPHELPER(VP_SCREENCHANGE_ASK, nullptr, ScreenHandler.ScreenChangeHookIfIdle, nullptr),

  #if ENABLED(SDSUPPORT)
    //VPHELPER(VP_SCREENCHANGE_WHENSD, nullptr, ScreenHandler.ScreenChangeHookIfSD, nullptr), //ЗАКОМЕНТИЛ
  #endif

  VPHELPER(VP_CONFIRMED, nullptr, ScreenHandler.ScreenConfirmedOK, nullptr),

  // Back Button 
  VPHELPER(VP_BACK_PAGE, nullptr, ScreenHandler.ScreenBackChange, nullptr),
  VPHELPER(VP_TEMP_ALL_OFF, nullptr, ScreenHandler.HandleAllHeatersOff, nullptr),

  VPHELPER(VP_MOVE_X, nullptr, ScreenHandler.HandleManualMove, nullptr),
  VPHELPER(VP_MOVE_Y, nullptr, ScreenHandler.HandleManualMove, nullptr),
  VPHELPER(VP_MOVE_Z, nullptr, ScreenHandler.HandleManualMove, nullptr),
  VPHELPER(VP_HOME_ALL, nullptr, ScreenHandler.HandleManualMove, nullptr),

  VPHELPER(VP_X_HOME, nullptr, ScreenHandler.HandleManualMove, nullptr),
  VPHELPER(VP_Y_HOME, nullptr, ScreenHandler.HandleManualMove, nullptr),
  VPHELPER(VP_Z_HOME, nullptr, ScreenHandler.HandleManualMove, nullptr),
  VPHELPER(VP_XY_HOME, nullptr, ScreenHandler.HandleManualMove, nullptr),



  ////////////////////////// Свое

  VPHELPER(VP_T_Fan0_ON, &thermalManager.fan_speed[0], ScreenHandler.HandleFanControl, nullptr),

  VPHELPER(VP_XPos_Set, nullptr, ScreenHandler.HandleManualMoveToPos, nullptr), 
  VPHELPER(VP_YPos_Set, nullptr, ScreenHandler.HandleManualMoveToPos, nullptr),
  VPHELPER(VP_ZPos_Set, nullptr, ScreenHandler.HandleManualMoveToPos, nullptr),

  VPHELPER(VP_T_Fan0_Set, nullptr, ScreenHandler.HandleFanSpeedChange, nullptr),
  VPHELPER(VP_E0_TEMP_SET, nullptr, ScreenHandler.HandleSettingsPrintChange, nullptr),
  VPHELPER(VP_BED_TEMP_SET, nullptr, ScreenHandler.HandleSettingsPrintChange, nullptr),
  VPHELPER(VP_CHAMBER_TEMP_SET, nullptr, ScreenHandler.HandleSettingsPrintChange, nullptr),
  VPHELPER(VP_SPEED_SET, nullptr, ScreenHandler.HandleSettingsPrintChange, nullptr),
  VPHELPER(VP_FLOW_SET, nullptr, ScreenHandler.HandleSettingsPrintChange, nullptr),
  VPHELPER(VP_FAN0_SET, nullptr, ScreenHandler.HandleSettingsPrintChange, nullptr),

  VPHELPER(VP_T_E0_ON, nullptr, ScreenHandler.HandleTemperatureChanged, ScreenHandler.SendTemperatureStatus),
  VPHELPER(VP_T_Bed_ON, nullptr, ScreenHandler.HandleTemperatureChanged, ScreenHandler.SendTemperatureStatus),
  VPHELPER(VP_T_Chamber_ON, nullptr, ScreenHandler.HandleTemperatureChanged, ScreenHandler.SendTemperatureStatus),

  VPHELPER(VP_SD_Filament_Change, nullptr, ScreenHandler.GoToFilamentChangeScreen, nullptr),
  VPHELPER(VP_SD_Filament_Change_Back, nullptr, ScreenHandler.GoFromFilamentChangeScreen, nullptr),
  VPHELPER(VP_SD_Print_Settings_Back, nullptr, ScreenHandler.GoFromPrintSettingsScreen, nullptr),
  VPHELPER(VP_Error_Back, nullptr, ScreenHandler.GoFromPrintSettingsScreen, nullptr),

  VPHELPER(VP_PRINTING_SETTINGS_STEP,nullptr ,ScreenHandler.GetPrintSettingsStep, nullptr),

  VPHELPER(VP_K_Factor_Save, nullptr, ScreenHandler.KFactorSave, nullptr), 

  VPHELPER(VP_K_Factor_Value, &planner.extruder_advance_K[0], ScreenHandler.GetKfactorValue, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<3>),
  VPHELPER(VP_K_Factor_Set, nullptr, ScreenHandler.HandleKFactorSet, nullptr),

  VPHELPER(VP_PID_AUTOTUNE_ALL, nullptr, ScreenHandler.HandlePIDAutotune, nullptr),
  VPHELPER(VP_PID_AUTOTUNE_E0_TEMP_SET, nullptr, ScreenHandler.HandlePidTempChange, nullptr),
  VPHELPER(VP_PID_AUTOTUNE_BED_TEMP_SET, nullptr, ScreenHandler.HandlePidTempChange, nullptr),
  VPHELPER(VP_PID_AUTOTUNE_E0_TEMP, &Pid_Autotune_E0_Temp, nullptr, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  VPHELPER(VP_PID_AUTOTUNE_BED_TEMP, &Pid_Autotune_Bed_Temp, nullptr, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  #if HAS_BED_PROBE
    VPHELPER(VP_LEVELING_START_STOP, nullptr, ScreenHandler.HandleAutoCalibrationStartStop, nullptr),
    VPHELPER(VP_Zoffset_Save, nullptr, ScreenHandler.KFactorSave, nullptr), //Todo надо сделать наверное отдельную
    VPHELPER(VP_LEVELING_TEMP_1_SET, nullptr, ScreenHandler.HandleBedCalibrationTempChange, nullptr),
    VPHELPER(VP_LEVELING_TEMP_2_SET, nullptr, ScreenHandler.HandleBedCalibrationTempChange, nullptr),
    VPHELPER(VP_LEVELING_TEMP_1, &Auto_Leveling_Temp_1, nullptr, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_LEVELING_TEMP_2, &Auto_Leveling_Temp_2, nullptr, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

    VPHELPER(VP_Zoffset_Set, nullptr, ScreenHandler.HandleLiveZoffset, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>), //свое
    VPHELPER(VP_Zoffset_Distance, &z_offset_set, nullptr, ScreenHandler.DGUSLCD_SendZoffset<2>),  //свое
    VPHELPER(VP_Zoffset_Start, nullptr, ScreenHandler.Zoffset_Start, nullptr),  //свое

    VPHELPER(VP_Zoffset_Step,nullptr ,ScreenHandler.GetZoffset_Step, nullptr),
  #endif


  VPHELPER(VP_MOVE_DISTANCE, &manualMoveStep, ScreenHandler.GetManualMovestep, nullptr),
  VPHELPER(VP_Fil_Speed_Pr, &manualExtruderSpeed, ScreenHandler.GetManualExtruderSpeed, nullptr),
  VPHELPER(VP_Fil_Step_Pr, &manualExtruderDistance, ScreenHandler.GetManualExtruderDistance, nullptr),
  VPHELPER(VP_T_Fan0_Step, &fan_0_Step, ScreenHandler.GetFanStep, nullptr), //свое
  VPHELPER(VP_T_E0_Pr, &nozzlePreset.temperature, ScreenHandler.GetPresetTemperature, nullptr),
  VPHELPER(VP_T_Bed_Pr, &bedPreset.temperature, ScreenHandler.GetPresetTemperature, nullptr),
  VPHELPER(VP_T_Chamber_Pr, &chamberPreset.temperature, ScreenHandler.GetPresetTemperature, nullptr),
  VPHELPER(VP_FLASH_STATUS, nullptr, nullptr, ScreenHandler.DGUSLCD_SendFlashIconStatus),
  VPHELPER(VP_HOT_STATUS, nullptr, nullptr, ScreenHandler.DGUSLCD_SendAlarmTemperature),
  VPHELPER(VP_FILAMENT_RUNOUT_STATUS, nullptr, nullptr, ScreenHandler.DGUSLCD_SendFilamentRunoutStatus),
  VPHELPER(VP_FILAMENT_SENSOR_ON, nullptr, ScreenHandler.DGUSLCD_FIlamentSensorUpdate, nullptr),
  VPHELPER(VP_FILAMENT_SENSOR_STATUS, nullptr, nullptr, ScreenHandler.DGUSLCD_FIlamentSensorUpdateIcon),
  VPHELPER(VP_SD_Open, nullptr, ScreenHandler.OpenFileSelectScreen, nullptr),
  VPHELPER(VP_Error_Open, nullptr, ScreenHandler.OpenErrorScreen, nullptr),
  VPHELPER(VP_SD_FileSelectCancel, nullptr, ScreenHandler.FileSelectCancel, nullptr),

  VPHELPER(VP_FILAMENT_CHANGE_STATUS, nullptr, nullptr, ScreenHandler.DGUSLCD_SendFilamentChangeStatus),

  VPHELPER_STR(VP_ErrorName0, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),
  VPHELPER_STR(VP_ErrorName1, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),
  VPHELPER_STR(VP_ErrorName2, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),
  VPHELPER_STR(VP_ErrorName3, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),
  VPHELPER_STR(VP_ErrorName4, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),
  VPHELPER_STR(VP_ErrorName5, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),
  VPHELPER_STR(VP_ErrorName6, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),
  VPHELPER_STR(VP_ErrorName7, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),
  VPHELPER_STR(VP_ErrorName8, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.SendErrorMessage),

  ////////////// Конец Свое



  VPHELPER(VP_MOTOR_LOCK_UNLOK, nullptr, ScreenHandler.HandleManualMove, nullptr),


  #if ENABLED(POWER_LOSS_RECOVERY)
    VPHELPER(VP_POWER_LOSS_RECOVERY, nullptr, ScreenHandler.HandlePowerLossRecovery, nullptr),
  #endif
  VPHELPER(VP_SETTINGS, nullptr, ScreenHandler.HandleSettings, nullptr),
  #if ENABLED(SINGLE_Z_CALIBRATION)
    VPHELPER(VP_Z_CALIBRATE, nullptr, ScreenHandler.HandleZCalibration, nullptr),
  #endif
  #if ENABLED(FIRST_LAYER_CAL)
    VPHELPER(VP_Z_FIRST_LAYER_CAL, nullptr, ScreenHandler.HandleFirstLayerCal, nullptr),
  #endif
  {.VP = VP_MARLIN_VERSION, .memadr = (void *)MarlinVersion, .size = VP_MARLIN_VERSION_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM},
  // // M117 LCD String (We don't need the string in memory but "just" push it to the display on demand, hence the nullptr
  //{.VP = VP_M117, .memadr = nullptr, .size = VP_M117_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay},
  //{.VP = VP_MKS_H43_VERSION, .memadr = (void *)H43Version, .size = VP_MARLIN_VERSION_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM},
  {.VP = VP_PRINTER_VERSION, .memadr = (void *)Printer_Name, .size = VP_MARLIN_VERSION_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM},



  // Temperature Data
  #if HAS_HOTEND
    VPHELPER(VP_T_E0_Is, &thermalManager.temp_hotend[0].celsius, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<0>),
    VPHELPER(VP_T_E0_Set, &thermalManager.temp_hotend[0].target, ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_Flowrate_E0, &planner.flow_percentage[ExtUI::extruder_t::E0], ScreenHandler.HandleFlowRateChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_EPos, &destination.e, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<2>),
    VPHELPER(VP_MOVE_E0, nullptr, ScreenHandler.HandleManualExtrude, nullptr),
    //VPHELPER(VP_E0_CONTROL, &thermalManager.temp_hotend[0].target, ScreenHandler.HandleHeaterControl, nullptr),
    VPHELPER(VP_E0_STATUS, &thermalManager.temp_hotend[0].target, nullptr, ScreenHandler.DGUSLCD_SendHeaterStatusToDisplay),
    #if ENABLED(DGUS_PREHEAT_UI)
      VPHELPER(VP_E0_BED_PREHEAT, nullptr, ScreenHandler.HandlePreheat, nullptr),
    #endif
    #if ENABLED(PIDTEMP)
      // VPHELPER(VP_E0_PID_P, &thermalManager.temp_hotend[0].pid.Kp, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      // VPHELPER(VP_E0_PID_I, &thermalManager.temp_hotend[0].pid.Ki, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      // VPHELPER(VP_E0_PID_D, &thermalManager.temp_hotend[0].pid.Kd, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      VPHELPER(VP_PID_AUTOTUNE_E0, nullptr, ScreenHandler.HandlePIDAutotune, nullptr), //переделано в свое
      VPHELPER(VP_PID_AUTOTUNE_ABORT, nullptr, ScreenHandler.HandlePIDAbort, nullptr), //Свое

    #endif
    #if ENABLED(DGUS_FILAMENT_LOADUNLOAD)
      VPHELPER(VP_LOAD_Filament, nullptr, ScreenHandler.FilamentLoad, nullptr),
      VPHELPER(VP_UNLOAD_Filament, nullptr, ScreenHandler.FilamentUnLoad, nullptr),
      VPHELPER(VP_Filament_CONST, nullptr, ScreenHandler.FilamentLoad, nullptr),
      VPHELPER(VP_Filament_distance, &distanceFilament, ScreenHandler.GetManualFilament, ScreenHandler.DGUSLCD_SendWordValueToDisplay), // TODO Старые, не используются
      VPHELPER(VP_Filament_speed, &filamentSpeed_mm_s, ScreenHandler.GetManualFilamentSpeed, ScreenHandler.DGUSLCD_SendWordValueToDisplay), // TODO Старые, не используются
    #endif
  #endif



  #if HAS_MULTI_HOTEND
    VPHELPER(VP_T_E1_Is, &thermalManager.temp_hotend[1].celsius, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<0>),
    VPHELPER(VP_T_E1_Set, &thermalManager.temp_hotend[1].target, ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_Flowrate_E1, &planner.flow_percentage[ExtUI::extruder_t::E1], ScreenHandler.HandleFlowRateChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_MOVE_E1, nullptr, ScreenHandler.HandleManualExtrude, nullptr),
    //VPHELPER(VP_E1_CONTROL, &thermalManager.temp_hotend[1].target, ScreenHandler.HandleHeaterControl, nullptr),
    VPHELPER(VP_E1_STATUS, &thermalManager.temp_hotend[1].target, nullptr, ScreenHandler.DGUSLCD_SendHeaterStatusToDisplay),

    #if ENABLED(DGUS_FILAMENT_LOADUNLOAD)
      VPHELPER(VP_Filament_distance, &distanceFilament, ScreenHandler.GetManualFilament, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
      VPHELPER(VP_Filament_speed, &filamentSpeed_mm_s, ScreenHandler.GetManualFilamentSpeed, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    #endif

    #if ENABLED(PIDTEMP)
      VPHELPER(VP_PID_AUTOTUNE_E1, nullptr, ScreenHandler.HandlePIDAutotune, nullptr),
    #endif

    VPHELPER(VP_E1_FILAMENT_LOAD_UNLOAD, nullptr, ScreenHandler.HandleFilamentOption, ScreenHandler.HandleFilamentLoadUnload),
  #endif

  #if HAS_HEATED_BED  
    VPHELPER(VP_T_Bed_Is, &thermalManager.temp_bed.celsius, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<0>),
    VPHELPER(VP_T_Bed_Set, &thermalManager.temp_bed.target, ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    //VPHELPER(VP_BED_CONTROL, &thermalManager.temp_bed.target, ScreenHandler.HandleHeaterControl, nullptr),
    //VPHELPER(VP_TEST_PAGE, &manualMoveStep, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<0>),
    VPHELPER(VP_BED_STATUS, &thermalManager.temp_bed.target, nullptr, ScreenHandler.DGUSLCD_SendHeaterStatusToDisplay),
    #if ENABLED(PIDTEMPBED)
      // VPHELPER(VP_BED_PID_P, &thermalManager.temp_bed.pid.Kp, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      // VPHELPER(VP_BED_PID_I, &thermalManager.temp_bed.pid.Ki, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      // VPHELPER(VP_BED_PID_D, &thermalManager.temp_bed.pid.Kd, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      VPHELPER(VP_PID_AUTOTUNE_BED, nullptr, ScreenHandler.HandlePIDAutotune, nullptr),
    #endif
  #endif

  //свое
  VPHELPER(VP_T_Chamber_Is, &thermalManager.temp_chamber.celsius, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<0>),
  VPHELPER(VP_T_Chamber_Set,  &thermalManager.temp_chamber.target, ScreenHandler.HandleTemperatureChanged, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  // Fan Data
  #if HAS_FAN
    #define FAN_VPHELPER(N)                                                                                                                    \
      VPHELPER(VP_Fan##N##_Percentage, &thermalManager.fan_speed[N], ScreenHandler.DGUSLCD_SetUint8, ScreenHandler.DGUSLCD_SendFanToDisplay), \
      VPHELPER(VP_FAN##N##_CONTROL, &thermalManager.fan_speed[N], ScreenHandler.HandleFanControl, nullptr),                               \
      VPHELPER(VP_FAN##N##_STATUS, &thermalManager.fan_speed[N], nullptr, ScreenHandler.DGUSLCD_SendFanStatusToDisplay),
    REPEAT(FAN_COUNT, FAN_VPHELPER)
  #endif

  // Feedrate
  VPHELPER(VP_Feedrate_Percentage, &feedrate_percentage, ScreenHandler.DGUSLCD_SetValueDirectly<int16_t>, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  // Position Data
  VPHELPER(VP_XPos, &current_position.x, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<2>), //&current_position.x
  VPHELPER(VP_YPos, &current_position.y, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<2>),
  VPHELPER(VP_ZPos, &current_position.z, nullptr, ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<2>),

  // Level Point Set // коммент
  // VPHELPER(VP_Level_Point_One_X, &mks_corner_offsets[0].x, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_One_Y, &mks_corner_offsets[0].y, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_Two_X, &mks_corner_offsets[1].x, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_Two_Y, &mks_corner_offsets[1].y, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_Three_X, &mks_corner_offsets[2].x, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_Three_Y, &mks_corner_offsets[2].y, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_Four_X, &mks_corner_offsets[3].x, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_Four_Y, &mks_corner_offsets[3].y, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_Five_X, &mks_corner_offsets[4].x, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Level_Point_Five_Y, &mks_corner_offsets[4].y, ScreenHandler.HandleChangeLevelPoint, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  // Print Progress
  VPHELPER(VP_PrintProgress_Percentage, nullptr, nullptr, ScreenHandler.DGUSLCD_SendPrintProgressToDisplay),

  // LCD Control
  VPHELPER(VP_LCD_BLK, &lcd_default_light, ScreenHandler.LCD_BLK_Adjust, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  // SD File - Back
  //VPHELPER(VP_SD_FileSelect_Back, nullptr, ScreenHandler.SD_FileBack, nullptr),

  // Print Time
  VPHELPER_STR(VP_PrintTime, nullptr, VP_PrintTime_LEN, nullptr, ScreenHandler.DGUSLCD_SendPrintTimeToDisplay),

  #if ENABLED(PRINTCOUNTER)
    VPHELPER_STR(VP_PrintAccTime, nullptr, VP_PrintAccTime_LEN, nullptr, ScreenHandler.DGUSLCD_SendPrintAccTimeToDisplay),
    VPHELPER_STR(VP_PrintsTotal, nullptr, VP_PrintsTotal_LEN, nullptr, ScreenHandler.DGUSLCD_SendPrintsTotalToDisplay),
  #endif

  // VPHELPER(VP_X_STEP_PER_MM, &planner.settings.axis_steps_per_mm[X_AXIS], ScreenHandler.HandleStepPerMMChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
  // VPHELPER(VP_Y_STEP_PER_MM, &planner.settings.axis_steps_per_mm[Y_AXIS], ScreenHandler.HandleStepPerMMChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
  // VPHELPER(VP_Z_STEP_PER_MM, &planner.settings.axis_steps_per_mm[Z_AXIS], ScreenHandler.HandleStepPerMMChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
  // VPHELPER(VP_X_MAX_SPEED, &planner.settings.max_feedrate_mm_s[X_AXIS], ScreenHandler.HandleMaxSpeedChange, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
  // VPHELPER(VP_Y_MAX_SPEED, &planner.settings.max_feedrate_mm_s[Y_AXIS], ScreenHandler.HandleMaxSpeedChange, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
  // VPHELPER(VP_Z_MAX_SPEED, &planner.settings.max_feedrate_mm_s[Z_AXIS], ScreenHandler.HandleMaxSpeedChange, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),

  #if HAS_HOTEND
    // VPHELPER(VP_E0_MAX_SPEED, &planner.settings.max_feedrate_mm_s[E_AXIS_N(0)], ScreenHandler.HandleExtruderMaxSpeedChange, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
    #if HAS_MULTI_HOTEND
      VPHELPER(VP_E1_MAX_SPEED, &planner.settings.max_feedrate_mm_s[E_AXIS_N(1)], ScreenHandler.HandleExtruderMaxSpeedChange, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
    #endif
  #endif

  // VPHELPER(VP_X_ACC_MAX_SPEED, (uint16_t *)&planner.settings.max_acceleration_mm_per_s2[X_AXIS], ScreenHandler.HandleMaxAccChange, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Y_ACC_MAX_SPEED, (uint16_t *)&planner.settings.max_acceleration_mm_per_s2[Y_AXIS], ScreenHandler.HandleMaxAccChange, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Z_ACC_MAX_SPEED, (uint16_t *)&planner.settings.max_acceleration_mm_per_s2[Z_AXIS], ScreenHandler.HandleMaxAccChange, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  #if HAS_HOTEND
    // VPHELPER(VP_E0_ACC_MAX_SPEED, (uint16_t *)&planner.settings.max_acceleration_mm_per_s2[E_AXIS_N(0)], ScreenHandler.HandleExtruderAccChange, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    #if HAS_MULTI_HOTEND
      VPHELPER(VP_E1_ACC_MAX_SPEED, (uint16_t *)&planner.settings.max_acceleration_mm_per_s2[E_AXIS_N(1)], ScreenHandler.HandleExtruderAccChange, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    #endif
  #endif

  // VPHELPER(VP_TRAVEL_SPEED, (uint16_t *)&planner.settings.travel_acceleration, ScreenHandler.HandleTravelAccChange, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
  // VPHELPER(VP_FEEDRATE_MIN_SPEED, (uint16_t *)&planner.settings.min_feedrate_mm_s, ScreenHandler.HandleFeedRateMinChange, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
  // VPHELPER(VP_T_F_SPEED, (uint16_t *)&planner.settings.min_travel_feedrate_mm_s, ScreenHandler.HandleMin_T_F, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
  // VPHELPER(VP_ACC_SPEED, (uint16_t *)&planner.settings.acceleration, ScreenHandler.HandleAccChange, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  // VPHELPER(VP_X_PARK_POS, &mks_park_pos.x, ScreenHandler.GetParkPos, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Y_PARK_POS, &mks_park_pos.y, ScreenHandler.GetParkPos, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // VPHELPER(VP_Z_PARK_POS, &mks_park_pos.z, ScreenHandler.GetParkPos, ScreenHandler.DGUSLCD_SendWordValueToDisplay),

  // #if ENABLED(PREVENT_COLD_EXTRUSION)
  //   VPHELPER(VP_MIN_EX_T, &thermalManager.extrude_min_temp, ScreenHandler.HandleGetExMinTemp, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // #endif

  // #if ENABLED(SENSORLESS_HOMING)  // TMC SENSORLESS Setting
  //   #if X_HAS_STEALTHCHOP
  //     VPHELPER(VP_TMC_X_STEP, &tmc_step.x, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendTMCStepValue),
  //   #endif
  //   #if Y_HAS_STEALTHCHOP
  //     VPHELPER(VP_TMC_Y_STEP, &tmc_step.y, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendTMCStepValue),
  //   #endif
  //   #if Z_HAS_STEALTHCHOP
  //     VPHELPER(VP_TMC_Z_STEP, &tmc_step.z, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendTMCStepValue),
  //   #endif
  // #endif

  // #if HAS_TRINAMIC_CONFIG   // TMC Current Setting
  //   #if AXIS_IS_TMC(X)
  //     VPHELPER(VP_TMC_X_Current, &stepperX.val_mA, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  //   #endif
  //   #if AXIS_IS_TMC(Y)
  //     VPHELPER(VP_TMC_Y_Current, &stepperY.val_mA, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  //   #endif
  //   #if AXIS_IS_TMC(Z)
  //     VPHELPER(VP_TMC_Z_Current, &stepperZ.val_mA, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  //   #endif
  //   #if AXIS_IS_TMC(E0)
  //     VPHELPER(VP_TMC_E0_Current, &stepperE0.val_mA, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  //   #endif
  //   #if AXIS_IS_TMC(E1)
  //     VPHELPER(VP_TMC_E1_Current, &stepperE1.val_mA, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  //   #endif
  //   #if AXIS_IS_TMC(X2)
  //     VPHELPER(VP_TMC_X1_Current, &stepperX2.val_mA, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  //   #endif
  //   #if AXIS_IS_TMC(Y2)
  //     VPHELPER(VP_TMC_Y1_Current, &stepperY2.val_mA, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  //   #endif
  //   #if AXIS_IS_TMC(Z2)
  //     VPHELPER(VP_TMC_Z1_Current, &stepperZ2.val_mA, ScreenHandler.TMC_ChangeConfig, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  //   #endif
  // #endif

  //VPHELPER(VP_EEPROM_CTRL, nullptr, ScreenHandler.EEPROM_CTRL, nullptr),
  #if !HAS_BED_PROBE
    VPHELPER(VP_LEVEL_BUTTON, nullptr, ScreenHandler.Level_Ctrl, nullptr),
    VPHELPER(VP_LEVEL_POINT, nullptr, ScreenHandler.ManualAssistLeveling, nullptr),
  #endif

  VPHELPER(VP_LANGUAGE_CHANGE, nullptr, ScreenHandler.LanguageChange, nullptr),

  VPHELPER(VP_Cool_Down, nullptr, ScreenHandler.Cool_Down, nullptr), //своя кнопка выкл все
  VPHELPER(VP_CASE_LIGHT_ON, nullptr, ScreenHandler.Case_Light_On, nullptr), //своя кнопка включения подсветки VP_CASE_LIGHT_ON

  VPHELPER(VP_K_Factor_Step,nullptr ,ScreenHandler.GetKFactorStep, nullptr), //Свое


  //VPHELPER(VP_MESH_LEVEL_ADJUST, nullptr, ScreenHandler.MeshLevelDistanceConfig, nullptr),
  //VPHELPER(VP_MESH_LEVEL_POINT,nullptr, ScreenHandler.MeshLevel,nullptr), 

  // #if ENABLED(PREVENT_COLD_EXTRUSION)
  //   VPHELPER(VP_Min_EX_T_E, &thermalManager.extrude_min_temp, ScreenHandler.GetMinExtrudeTemp, ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  // #endif

  VPHELPER(VP_AutoTurnOffSw, nullptr, ScreenHandler.GetTurnOffCtrl, nullptr),

  #if HAS_HOTEND
    // VPHELPER(VP_E0_STEP_PER_MM, &planner.settings.axis_steps_per_mm[E_AXIS_N(0)], ScreenHandler.HandleStepPerMMExtruderChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
    #if HAS_MULTI_HOTEND
      VPHELPER(VP_E1_STEP_PER_MM, &planner.settings.axis_steps_per_mm[E_AXIS_N(1)], ScreenHandler.HandleStepPerMMExtruderChanged, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
    #endif
  #endif

  // SDCard File listing

  #if ENABLED(SDSUPPORT)
    VPHELPER(VP_SD_FileSelected, nullptr, ScreenHandler.DGUSLCD_SD_FileSelected, nullptr),
    VPHELPER(VP_SD_ScrollEvent, nullptr, ScreenHandler.DGUSLCD_SD_ScrollFilelist, nullptr),
    VPHELPER(VP_SD_FileSelectConfirm, nullptr, ScreenHandler.DGUSLCD_SD_StartPrint, nullptr),
    VPHELPER_STR(VP_SD_FileName0, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName1, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName2, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName3, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName4, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    VPHELPER_STR(VP_SD_FileName5, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    #if !HAS_BED_PROBE
      VPHELPER_STR(VP_SD_FileName6, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
      VPHELPER_STR(VP_SD_FileName7, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
      VPHELPER_STR(VP_SD_FileName8, nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename),
    #endif
    VPHELPER(VP_SD_ResumePauseAbort, nullptr, ScreenHandler.DGUSLCD_SD_ResumePauseAbort, nullptr),
    VPHELPER(VP_SD_AbortPrintConfirmed, nullptr, ScreenHandler.DGUSLCD_SD_ReallyAbort, nullptr),
    //VPHELPER(VP_SD_Print_Setting, nullptr, ScreenHandler.DGUSLCD_SD_PrintTune, nullptr),

    #if ENABLED(BABYSTEPPING)
      //VPHELPER(VP_SD_Print_LiveAdjustZ_Confirm, nullptr, ScreenHandler.ZoffsetConfirm, nullptr),
      VPHELPER(VP_BabyStep_Step,nullptr ,ScreenHandler.GetBabyStep_Step, nullptr),
      VPHELPER(VP_SD_Print_BabyStep_Set, nullptr, ScreenHandler.HandleLiveBabyStep, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
      VPHELPER(VP_BabyStep_Distance, &babystep_add, nullptr, ScreenHandler.DGUSLCD_SendBabyStep<0>),
    #endif

    //#if HAS_BED_PROBE
      // VPHELPER(VP_Zoffset_ReWrite, nullptr, ScreenHandler.RewriteBedGrid, nullptr),  //свое
      // VPHELPER(VP_OFFSET_X, &probe.offset.x, ScreenHandler.GetOffsetValue,ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<2>),
      // VPHELPER(VP_OFFSET_Y, &probe.offset.y, ScreenHandler.GetOffsetValue,ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<2>),
      // VPHELPER(VP_OFFSET_Z, &probe.offset.z, ScreenHandler.GetOffsetValue,ScreenHandler.DGUSLCD_SendFloatAsLongValueToDisplay<2>),
    //#endif
  #else
    VPHELPER(VP_SD_FileSelected, nullptr, ScreenHandler.PrintReturn, nullptr),
  #endif

  #if ENABLED(DGUS_UI_WAITING)
    VPHELPER(VP_WAITING_STATUS, nullptr, nullptr, ScreenHandler.DGUSLCD_SendWaitingStatusToDisplay),
  #endif

  // Messages for the User, shared by the popup and the kill screen. They can't be autouploaded as we do not buffer content.
  //{.VP = VP_MSGSTR1, .memadr = nullptr, .size = VP_MSGSTR1_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM},
  //{.VP = VP_MSGSTR2, .memadr = nullptr, .size = VP_MSGSTR2_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM},
  //{.VP = VP_MSGSTR3, .memadr = nullptr, .size = VP_MSGSTR3_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM},
  //{.VP = VP_MSGSTR4, .memadr = nullptr, .size = VP_MSGSTR4_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplayPGM},

  {.VP = VP_MSGSTR1, .memadr = nullptr, .size = VP_MSGSTR1_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay_Language},
  {.VP = VP_MSGSTR2, .memadr = nullptr, .size = VP_MSGSTR2_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay_Language},
  {.VP = VP_MSGSTR3, .memadr = nullptr, .size = VP_MSGSTR3_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay_Language},
  {.VP = VP_MSGSTR4, .memadr = nullptr, .size = VP_MSGSTR4_LEN, .set_by_display_handler = nullptr, .send_to_display_handler = ScreenHandler.DGUSLCD_SendStringToDisplay_Language},

  VPHELPER(0, 0, 0, 0) // must be last entry.
};

#endif // DGUS_LCD_UI_MKS
