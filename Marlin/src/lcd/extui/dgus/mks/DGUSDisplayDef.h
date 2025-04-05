/**
<<<<<<< HEAD
 * Marlin 3D Printer Firmware 
=======
 * Marlin 3D Printer Firmware
>>>>>>> origin/release-2.1.3-beta2
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
#pragma once

#include "../DGUSDisplayDef.h"

<<<<<<< HEAD
#include <vector>

//#define DGUS_MKS_RUNOUT_SENSOR

#define LOGO_TIME_DELAY TERN(USE_MKS_GREEN_UI, 2000, 1500)  //8000

#if ENABLED(DGUS_MKS_RUNOUT_SENSOR)
  #define MT_DET_1_PIN     1
  #define MT_DET_2_PIN     2
  #define MT_DET_PIN_STATE LOW
#endif

#define MKS_FINSH

struct TempPreset {
  celsius_t temperature = 0;
  uint8_t isOn = 0;
};


extern xyze_pos_t position_before_pause; //Свое перенес из файлика
extern feedRate_t feedrate_before_pause;

extern std::vector<std::string> errors;

extern TempPreset nozzlePreset;
extern TempPreset bedPreset;
extern TempPreset chamberPreset;
extern uint16_t  manualMoveStep; // TODO убрать
extern uint16_t manualExtruderDistance;
extern uint16_t manualExtruderSpeed;
extern uint16_t fan_0_Step;
extern celsius_t t_E0_pr;
extern uint16_t distanceFilament;
extern uint16_t filamentSpeed_mm_s;
extern uint16_t BabyStep_Step;
extern uint16_t Zoffset_Step;
extern float KFactorStep;

extern float    mesh_adj_distance;
extern float    Z_distance;

extern uint16_t PrintSettingsStep;

=======
//#define DGUS_MKS_RUNOUT_SENSOR

#define LOGO_TIME_DELAY TERN(USE_MKS_GREEN_UI, 8000, 1500)

#define MKS_FINSH

extern uint16_t manualMoveStep;
extern uint16_t distanceFilament;
extern uint16_t filamentSpeed_mm_s;
extern float    ZOffset_distance;
extern float    mesh_adj_distance;
extern float    Z_distance;

>>>>>>> origin/release-2.1.3-beta2
//extern struct { uint16_t h, m, s; } dgus_time;

extern xy_int_t mks_corner_offsets[5];
extern xyz_int_t mks_park_pos;
extern celsius_t mks_min_extrusion_temp;

void MKS_reset_settings(); // Restore persistent settings to defaults

void MKS_pause_print_move();
void MKS_resume_print_move();

<<<<<<< HEAD
extern float babystep_add;
=======
extern float z_offset_add;
>>>>>>> origin/release-2.1.3-beta2

extern xyz_int_t tmc_step;

extern uint16_t lcd_default_light;

<<<<<<< HEAD
extern uint16_t Pid_Autotune_E0_Temp;
extern uint16_t Pid_Autotune_Bed_Temp; //Свое

extern uint16_t Auto_Leveling_Temp_1;
extern uint16_t Auto_Leveling_Temp_2; //Свое


=======
>>>>>>> origin/release-2.1.3-beta2
#if X_HAS_STEALTHCHOP
  extern uint16_t tmc_x_current;
#endif
#if Y_HAS_STEALTHCHOP
  extern uint16_t tmc_y_current;
#endif
#if Z_HAS_STEALTHCHOP
  extern uint16_t tmc_z_current;
#endif
#if E0_HAS_STEALTHCHOP
  extern uint16_t tmc_e0_current;
#endif
#if E1_HAS_STEALTHCHOP
  extern uint16_t tmc_e1_current;
#endif

typedef enum {
  EX_HEATING,
  EX_HEAT_STARUS,
  EX_CHANGING,
  EX_CHANGE_STATUS,
  EX_NONE,
} EX_STATUS_DEF;

typedef struct {
  //uint8_t ex_change_flag:1;
  //uint8_t ex_heat_flag:1;
  uint8_t ex_load_unload_flag:1;  //0:unload  1:load
  EX_STATUS_DEF ex_status;
  uint32_t ex_tick_start;
  uint32_t ex_tick_end;
  uint32_t ex_speed;
  uint32_t ex_length;
  uint32_t ex_need_time;
} EX_FILAMENT_DEF;

extern EX_FILAMENT_DEF ex_filament;

typedef enum {
  UNRUNOUT_STATUS,
  RUNOUT_STATUS,
  RUNOUT_WAITING_STATUS,
  RUNOUT_BEGIN_STATUS,
} RUNOUT_MKS_STATUS_DEF;

typedef struct {
  RUNOUT_MKS_STATUS_DEF runout_status;
  uint8_t pin_status;
  uint8_t de_count;
  uint8_t de_times;
} RUNOUT_MKS_DEF;

extern RUNOUT_MKS_DEF runout_mks;

typedef struct {
  uint8_t print_pause_start_flag:1;
  uint8_t runout_flag:1;
<<<<<<< HEAD
  bool filament_change = 0;
=======
  bool blstatus;
>>>>>>> origin/release-2.1.3-beta2
  uint16_t x_pos;
  uint16_t y_pos;
  uint16_t z_pos;
} NOZZLE_PARK_DEF;

extern NOZZLE_PARK_DEF nozzle_park_mks;

<<<<<<< HEAD
enum DGUSLCD_Screens : uint8_t {
  #if ENABLED(USE_MKS_GREEN_UI)

    DGUSLCD_SCREEN_BOOT                 =  0, //33
    DGUSLCD_SCREEN_MAIN                 =  1 , //60
    DGUSLCD_SCREEN_STATUS               =  1, //60
    DGUSLCD_SCREEN_STATUS2              =  1, //60

    MKSLCD_SCREEN_BOOT                  =  0, //33
    MKSLCD_SCREEN_HOME                  =  1,   //60 MKS main page1
    MKSLCD_SCREEN_PREHEAT               =  7,   //своя преднагрев
    MKSLCD_SCREEN_TOOL                  =  3,   //64 переделано на сервис
    MKSLCD_SCREEN_K_FACTOR              =  77, //свое страница настройки к фактора
    MKSLCD_SCREEN_EXTRUDE_P1            =  11, //75 переделано на смену пластика
    MKSLCD_SCREEN_LEVEL                 =  9, //73

   #if HAS_BED_PROBE
    MKSLCD_AUTO_LEVEL                   =  81,
    MKSLCD_AUTO_LEVEL_DONE              =  83,
    MKSLCD_Zoffset_Set                  =  85, 
   #endif

    MKSLCD_SCREEN_MOVE                  =  5, //66 движение
    MKSLCD_SCREEN_PRINT                 =  13, //68
    MKSLCD_SCREEN_PAUSE                 =  15, //70
    MKSLCD_SCREEN_PRINT_REHEAT          =  27, //свое страница при остывании при паузе

    MKSLCD_SCREEN_CHOOSE_FILE           =  40, // 87  страница без перелистывания
    MKSLCD_SCREEN_CHOOSE_FILE_1         =  41, //своя страница с перелистыванием вправо
    MKSLCD_SCREEN_CHOOSE_FILE_2         =  42, //своя страница с перелистыванием влево
    MKSLCD_SCREEN_CHOOSE_FILE_3         =  43, //своя страница с перелистыванием в обе стороны
       
    MKSLCD_SCREEN_CHOOSE_FILE_FOLDER    =  45, // 87  страница без перелистывания
    MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_1  =  46, //своя страница с перелистыванием вправо
    MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_2  =  47, //своя страница с перелистыванием влево
    MKSLCD_SCREEN_CHOOSE_FILE_FOLDER_3  =  48, //своя страница с перелистыванием в обе стороны

    MKSLCD_SCREEN_ERROR                 =  50, //страница с возвратом
    MKSLCD_SCREEN_ERROR_1               =  51, //страница без возврата

    MKSLCD_SCREEN_PRINT_TEMP            =  21, //свое страница температур в процессе печати
    MKSLCD_SCREEN_PRINT_CONFIG          =  23, //72 переделано на центральную страницу параметров в процессе печати
    MKSLCD_Screen_Baby                  =  25, //79 страница  Babystepping
    MKSLCD_SCREEN_PRINT_K_FACTOR        =  79, //свое страница настройки к фактора


    MKSLCD_PID                          =  31, //108 подбор PID
    MKSLCD_PID_PROCESS                  =  33,   //своя подбор PID во время подбора
    MKSLCD_PID_COMPLETE                 =  35,   //своя подбор PID когда завершено успешно или нет
   
    MKSLCD_PAUSE_SETTING_EX             =  19,//96 переделано на смену пластика во время печати
    MKSLCD_SCREEN_PRINT_CONFIRM         =  64, //94 подтверждение запуска печати
    MKSLCD_SCREEN_PrintDone             =  17, //92
   
    MKSLCD_Screen_PMove                 =  158, //98 думаю можно позже прикрутить
    MKSLCD_PAUSE_SETTING_MOVE           =  98,

    MKSLCD_ABOUT                        =  75, //83
    
    DGUSLCD_SCREEN_PREHEAT              =  18, //18 какая то фигня

    // MKSLCD_SCREEN_LEVEL_DATA            = 106, // думаю понадобится позже

    /////////// то что не надо по идее
    // DGUSLCD_SCREEN_POWER_LOSS           = 100, //100
    // DGUSLCD_SCREEN_MANUALMOVE           = 192, //192
    // DGUSLCD_SCREEN_UTILITY              = 120, //120
    // DGUSLCD_SCREEN_FILAMENT_UNLOADING   = 158, //158
    // DGUSLCD_SCREEN_SDFILELIST           =  15, //15
    // DGUSLCD_SCREEN_SDPRINTMANIPULATION  =  15, //15
    // DGUSLCD_SCREEN_SDPRINTTUNE          =  217, //17

    // MKSLCD_SCREEN_SETTING               =  62,   //62 MKS Setting page / no wifi whit
    // MKSLCD_SCREEN_EXTRUDE_P2            =  177, //
    // MKSLCD_SCREEN_NO_CHOOSE_FILE        =  88, // убрать и заменить вывод на обычную с текстом ПУСТО
    // MKSLCD_SCREEN_EEP_Config            =  89,
    // MKSLCD_SCREEN_Config                = 101,
    // MKSLCD_SCREEN_Config_MOTOR          = 103,
    // MKSLCD_SCREEN_MOTOR_PLUSE           = 104,
    // MKSLCD_SCREEN_MOTOR_SPEED           = 102,
    // MKSLCD_SCREEN_MOTOR_ACC_MAX         = 105,
    // MKSLCD_PrintPause_SET               = 107,
    // MKSLCD_FILAMENT_DATA                =  50, // не существуует
    // MKSLCD_PAUSE_SETTING_EX2            =  97,
    // MKSLCD_SCREEN_TMC_Config            = 111,
    // MKSLCD_SCREEN_EX_CONFIG             = 112,
    // MKSLCD_Screen_Offset_Config         = 109,


  #else

    DGUSLCD_SCREEN_BOOT                 = 120,
    DGUSLCD_SCREEN_MAIN                 =   1,

    DGUSLCD_SCREEN_STATUS               =   1,
    DGUSLCD_SCREEN_STATUS2              =   1,
    DGUSLCD_SCREEN_PREHEAT              =  18,
    DGUSLCD_SCREEN_POWER_LOSS           = 100,
    DGUSLCD_SCREEN_MANUALMOVE           = 192,
    DGUSLCD_SCREEN_UTILITY              = 120,
    DGUSLCD_SCREEN_FILAMENT_UNLOADING   = 158,
    DGUSLCD_SCREEN_SDFILELIST           =  15,
    DGUSLCD_SCREEN_SDPRINTMANIPULATION  =  15,
    DGUSLCD_SCREEN_SDPRINTTUNE          =  17,
=======
enum DGUS_ScreenID : uint8_t {
  #if ENABLED(USE_MKS_GREEN_UI)

    DGUS_SCREEN_BOOT                 =  33,
    DGUS_SCREEN_MAIN                 =  60,
    DGUS_SCREEN_STATUS               =  60,
    DGUS_SCREEN_STATUS2              =  60,
    DGUS_SCREEN_PREHEAT              =  18,
    DGUS_SCREEN_POWER_LOSS           = 100,
    DGUS_SCREEN_MANUALMOVE           = 192,
    DGUS_SCREEN_UTILITY              = 120,
    DGUS_SCREEN_FILAMENT_UNLOADING   = 158,
    DGUS_SCREEN_SDFILELIST           =  15,
    DGUS_SCREEN_SDPRINTMANIPULATION  =  15,
    DGUS_SCREEN_SDPRINTTUNE          =  17,

    MKSLCD_SCREEN_BOOT                  =  33,
    MKSLCD_SCREEN_HOME                  =  60,   // MKS main page
    MKSLCD_SCREEN_SETTING               =  62,   // MKS Setting page / no wifi whit
    MKSLCD_SCREEM_TOOL                  =  64,   // MKS Tool page
    MKSLCD_SCREEN_EXTRUDE_P1            =  75,
    MKSLCD_SCREEN_EXTRUDE_P2            =  77,
    MKSLCD_SCREEN_LEVEL                 =  73,
    MKSLCD_AUTO_LEVEL                   =  81,
    MKSLCD_SCREEN_MOVE                  =  66,
    MKSLCD_SCREEN_PRINT                 =  68,
    MKSLCD_SCREEN_PAUSE                 =  70,
    MKSLCD_SCREEN_CHOOSE_FILE           =  87,
    MKSLCD_SCREEN_NO_CHOOSE_FILE        =  88,
    MKSLCD_SCREEN_Config                = 101,
    MKSLCD_SCREEN_Config_MOTOR          = 103,
    MKSLCD_SCREEN_MOTOR_PLUSE           = 104,
    MKSLCD_SCREEN_MOTOR_SPEED           = 102,
    MKSLCD_SCREEN_MOTOR_ACC_MAX         = 105,
    MKSLCD_SCREEN_PRINT_CONFIG          =  72,
    MKSLCD_SCREEN_LEVEL_DATA            = 106,
    MKSLCD_PrintPause_SET               = 107,
    MKSLCD_FILAMENT_DATA                =  50,
    MKSLCD_ABOUT                        =  83,
    MKSLCD_PID                          = 108,
    MKSLCD_PAUSE_SETTING_MOVE           =  98,
    MKSLCD_PAUSE_SETTING_EX             =  96,
    MKSLCD_PAUSE_SETTING_EX2            =  97,
    MKSLCD_SCREEN_PRINT_CONFIRM         =  94,
    MKSLCD_SCREEN_EX_CONFIG             = 112,
    MKSLCD_SCREEN_EEP_Config            =  89,
    MKSLCD_SCREEN_PrintDone             =  92,
    MKSLCD_SCREEN_TMC_Config            = 111,
    MKSLCD_Screen_Offset_Config         = 109,
    MKSLCD_Screen_PMove                 =  98,
    MKSLCD_Screen_Baby                  =  79,

  #else

    DGUS_SCREEN_BOOT                 = 120,
    DGUS_SCREEN_MAIN                 =   1,

    DGUS_SCREEN_STATUS               =   1,
    DGUS_SCREEN_STATUS2              =   1,
    DGUS_SCREEN_PREHEAT              =  18,
    DGUS_SCREEN_POWER_LOSS           = 100,
    DGUS_SCREEN_MANUALMOVE           = 192,
    DGUS_SCREEN_UTILITY              = 120,
    DGUS_SCREEN_FILAMENT_UNLOADING   = 158,
    DGUS_SCREEN_SDFILELIST           =  15,
    DGUS_SCREEN_SDPRINTMANIPULATION  =  15,
    DGUS_SCREEN_SDPRINTTUNE          =  17,
>>>>>>> origin/release-2.1.3-beta2

    MKSLCD_SCREEN_BOOT                  =   0,
    MKSLCD_SCREEN_HOME                  =   1,   // MKS main page
    MKSLCD_SCREEN_SETTING               =   2,   // MKS Setting page / no wifi whit
<<<<<<< HEAD
    MKSLCD_SCREEN_TOOL                  =   3,   // MKS Tool page
=======
    MKSLCD_SCREEM_TOOL                  =   3,   // MKS Tool page
>>>>>>> origin/release-2.1.3-beta2
    MKSLCD_SCREEN_EXTRUDE_P1            =   4,
    MKSLCD_SCREEN_EXTRUDE_P2            =  11,
    MKSLCD_SCREEN_LEVEL                 =   5,
    MKSLCD_AUTO_LEVEL                   =  73,
    MKSLCD_SCREEN_LEVEL_PRESS           =   9,
    MKSLCD_SCREEN_MOVE                  =   6,
    MKSLCD_SCREEN_PRINT                 =   7,
    MKSLCD_SCREEN_PRINT_PRESS           =  13,
    MKSLCD_SCREEN_PAUSE                 =  26,
    MKSLCD_SCREEN_PAUSE_PRESS           =  26,
    MKSLCD_SCREEN_CHOOSE_FILE           =  15,
    MKSLCD_SCREEN_NO_CHOOSE_FILE        =  17,
    MKSLCD_SCREEN_Config                =  46,
    MKSLCD_SCREEN_Config_MOTOR          =  47,
    MKSLCD_SCREEN_MOTOR_PLUSE           =  51,
    MKSLCD_SCREEN_MOTOR_SPEED           =  55,
    MKSLCD_SCREEN_MOTOR_ACC_MAX         =  53,
    MKSLCD_SCREEN_PRINT_CONFIG          =  60,
    MKSLCD_SCREEN_LEVEL_DATA            =  48,
    MKSLCD_PrintPause_SET               =  49,
    MKSLCD_FILAMENT_DATA                =  50,
    MKSLCD_ABOUT                        =  36,
    MKSLCD_PID                          =  56,
    MKSLCD_PAUSE_SETTING_MOVE           =  58,
    MKSLCD_PAUSE_SETTING_EX             =  57,
    MKSLCD_PAUSE_SETTING_EX2            =  61,
    MKSLCD_SCREEN_NO_FILE               =  42,
    MKSLCD_SCREEN_PRINT_CONFIRM         =  43,
    MKSLCD_SCREEN_EX_CONFIG             =  65,
    MKSLCD_SCREEN_EEP_Config            =  20,
    MKSLCD_SCREEN_PrintDone             =  25,
    MKSLCD_SCREEN_TMC_Config            =  70,
    MKSLCD_Screen_Offset_Config         =  30,
    MKSLCD_Screen_PMove                 =  64,
    MKSLCD_Screen_Baby                  =  71,

  #endif

<<<<<<< HEAD
  DGUSLCD_SCREEN_CONFIRM                = 240,
  DGUSLCD_SCREEN_KILL                   = 250, ///< Kill Screen. Must always be 250 (to be able to display "Error wrong LCD Version")
  DGUSLCD_SCREEN_WAITING                = 251,
  DGUSLCD_SCREEN_POPUP                  = 252, ///< special target, popup screen will also return this code to say "return to previous screen"
  DGUSLCD_SCREEN_UNUSED                 = 255
};


// Place for status messages.
constexpr uint16_t VP_M117 = 0x7100;
=======
  DGUS_SCREEN_CONFIRM                = 240,
  DGUS_SCREEN_KILL                   = 250, //!< Kill Screen. Must always be 250 (to be able to display "Error wrong LCD Version")
  DGUS_SCREEN_WAITING                = 251,
  DGUS_SCREEN_POPUP                  = 252, //!< special target, popup screen will also return this code to say "return to previous screen"
  DGUS_SCREEN_UNUSED                 = 255
};

// Place for status messages.
constexpr uint16_t VP_M117 = 0x7020;
>>>>>>> origin/release-2.1.3-beta2
constexpr uint8_t VP_M117_LEN = 0x20;

// Heater status
constexpr uint16_t VP_E0_STATUS = 0x3410;
constexpr uint16_t VP_E1_STATUS = 0x3412;
//constexpr uint16_t VP_E2_STATUS = 0x3414;
//constexpr uint16_t VP_E3_STATUS = 0x3416;
//constexpr uint16_t VP_E4_STATUS = 0x3418;
//constexpr uint16_t VP_E5_STATUS = 0x341A;
<<<<<<< HEAD
//constexpr uint16_t VP_MOVE_OPTION = 0x3500;

// // PIDs
// constexpr uint16_t VP_E0_PID_P = 0x3700; // at the moment , 2 byte unsigned int , 0~1638.4
// constexpr uint16_t VP_E0_PID_I = 0x3702;
// constexpr uint16_t VP_E0_PID_D = 0x3704;
// constexpr uint16_t VP_E1_PID_P = 0x3706; // at the moment , 2 byte unsigned int , 0~1638.4
=======
constexpr uint16_t VP_MOVE_OPTION = 0x3500;

// // PIDs
// constexpr uint16_t VP_E0_PID_P = 0x3700; // at the moment , uint16_t , 0~1638.4
// constexpr uint16_t VP_E0_PID_I = 0x3702;
// constexpr uint16_t VP_E0_PID_D = 0x3704;
// constexpr uint16_t VP_E1_PID_P = 0x3706; // at the moment , uint16_t , 0~1638.4
>>>>>>> origin/release-2.1.3-beta2
// constexpr uint16_t VP_E1_PID_I = 0x3708;
// constexpr uint16_t VP_E1_PID_D = 0x370A;
// constexpr uint16_t VP_BED_PID_P = 0x3710;
// constexpr uint16_t VP_BED_PID_I = 0x3712;
// constexpr uint16_t VP_BED_PID_D = 0x3714;

// Waiting screen status
<<<<<<< HEAD
//constexpr uint16_t VP_WAITING_STATUS = 0x3800;
=======
constexpr uint16_t VP_WAITING_STATUS = 0x3800;
>>>>>>> origin/release-2.1.3-beta2

// SPs for certain variables...
// located at 0x5000 and up
// Not used yet!
// This can be used e.g to make controls / data display invisible
constexpr uint16_t SP_T_E0_Is     = 0x5000;
constexpr uint16_t SP_T_E0_Set    = 0x5010;
constexpr uint16_t SP_T_E1_Is     = 0x5020;
constexpr uint16_t SP_T_Bed_Is    = 0x5030;
constexpr uint16_t SP_T_Bed_Set   = 0x5040;

/*************************************************************************************************************************
 *************************************************************************************************************************
 *                                                 DGUS for MKS Mem layout
 ************************************************************************************************************************
 ************************************************************************************************************************/

#if ENABLED(MKS_FINSH)
  /* -------------------------------0x1000-0x1FFF------------------------------- */
  constexpr uint16_t VP_MSGSTR1                       = 0x1100;
  constexpr uint8_t  VP_MSGSTR1_LEN                   = 0x20;  // might be more place for it...
  constexpr uint16_t VP_MSGSTR2                       = 0x1140;
  constexpr uint8_t  VP_MSGSTR2_LEN                   = 0x20;
  constexpr uint16_t VP_MSGSTR3                       = 0x1180;
  constexpr uint8_t  VP_MSGSTR3_LEN                   = 0x20;
  constexpr uint16_t VP_MSGSTR4                       = 0x11C0;
  constexpr uint8_t  VP_MSGSTR4_LEN                   = 0x20;

<<<<<<< HEAD

=======
  constexpr uint16_t VP_MARLIN_VERSION                = 0x1A00;
  constexpr uint8_t VP_MARLIN_VERSION_LEN             = 16;       // there is more space on the display, if needed.
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_SCREENCHANGE_ASK              = 0x1500;
  constexpr uint16_t VP_SCREENCHANGE                  = 0x1501;   // Key-Return button to new menu pressed. Data contains target screen in low byte and info in high byte.
  constexpr uint16_t VP_TEMP_ALL_OFF                  = 0x1502;   // Turn all heaters off. Value arbitrary ;)=
<<<<<<< HEAD
  //constexpr uint16_t VP_SCREENCHANGE_WHENSD           = 0x1503;   // "Print" Button touched -- go only there if there is an SD Card.
  constexpr uint16_t VP_CONFIRMED                     = 0x1510;   // OK on confirm screen.

  constexpr uint16_t VP_BACK_PAGE                     = 0x1600;
  constexpr uint16_t VP_SETTINGS                      = 0x1620; //оставим на потом
=======
  constexpr uint16_t VP_SCREENCHANGE_WHENSD           = 0x1503;   // "Print" Button touched -- go only there if there is an SD Card.
  constexpr uint16_t VP_CONFIRMED                     = 0x1510;   // OK on confirm screen.

  constexpr uint16_t VP_BACK_PAGE                     = 0x1600;
  constexpr uint16_t VP_SETTINGS                      = 0x1620;
>>>>>>> origin/release-2.1.3-beta2
  // Power loss recovery
  constexpr uint16_t VP_POWER_LOSS_RECOVERY           = 0x1680;
  /* -------------------------------0x2000-0x2FFF------------------------------- */
  // Temperatures.
  constexpr uint16_t VP_T_E0_Is                       = 0x2000;   // 4 Byte Integer
  constexpr uint16_t VP_T_E0_Set                      = 0x2004;   // 2 Byte Integer
  constexpr uint16_t VP_T_E1_Is                       = 0x2008;   // 4 Byte Integer
  constexpr uint16_t VP_T_E1_Set                      = 0x200B;   // 2 Byte Integer
  constexpr uint16_t VP_T_E2_Is                       = 0x2010;   // 4 Byte Integer
  constexpr uint16_t VP_T_E2_Set                      = 0x2014;   // 2 Byte Integer
  constexpr uint16_t VP_T_E3_Is                       = 0x2018;   // 4 Byte Integer
  constexpr uint16_t VP_T_E3_Set                      = 0x201B;   // 2 Byte Integer
  constexpr uint16_t VP_T_E4_Is                       = 0x2020;   // 4 Byte Integer
  constexpr uint16_t VP_T_E4_Set                      = 0x2024;   // 2 Byte Integer
  constexpr uint16_t VP_T_E5_Is                       = 0x2028;   // 4 Byte Integer
  constexpr uint16_t VP_T_E5_Set                      = 0x202B;   // 2 Byte Integer
  constexpr uint16_t VP_T_E6_Is                       = 0x2030;   // 4 Byte Integer
  constexpr uint16_t VP_T_E6_Set                      = 0x2034;   // 2 Byte Integer
  constexpr uint16_t VP_T_E7_Is                       = 0x2038;   // 4 Byte Integer
  constexpr uint16_t VP_T_E7_Set                      = 0x203B;   // 2 Byte Integer
<<<<<<< HEAD
  constexpr uint16_t VP_TEST_PAGE                     = 0x2002;   // 2 Byte Integer

  constexpr uint16_t VP_T_Bed_Is                      = 0x2040;   // 4 Byte Integer
  constexpr uint16_t VP_T_Bed_Set                     = 0x2044;   // 2 Byte Integer
  constexpr uint16_t VP_T_Chamber_Is                  = 0x2048;   // 4 Byte Integer
  constexpr uint16_t VP_T_Chamber_Set                 = 0x204C;   // 2 Byte Integer

  // constexpr uint16_t VP_Min_EX_T_E                    = 0x2100;

constexpr uint16_t VP_T_E0_Pr                         = 0x2050; //свое preset nozzle
constexpr uint16_t VP_T_Bed_Pr                        = 0x2052; //свое preset bed
constexpr uint16_t VP_T_Chamber_Pr                    = 0x2054; //свое preset chamber
constexpr uint16_t VP_T_Fan0_Step                     = 0x2056; //свое выбор шага вентилятора fan0

constexpr uint16_t VP_T_E0_ON                         = 0x2060; //свое кнопка+индикатор включения сопла
constexpr uint16_t VP_T_Bed_ON                        = 0x2064; //свое кнопка+индикатор включения стола
constexpr uint16_t VP_T_Chamber_ON                    = 0x2068; //свое кнопка+индикатор включения камеры
constexpr uint16_t VP_T_Fan0_ON                       = 0x2072; //свое кнопка+индикатор включения вентилятора
constexpr uint16_t VP_T_Fan0_Set                      = 0x2076; //свое кнопка + - вентилятор

=======

  constexpr uint16_t VP_T_Bed_Is                      = 0x2040;   // 4 Byte Integer
  constexpr uint16_t VP_T_Bed_Set                     = 0x2044;   // 2 Byte Integer

  constexpr uint16_t VP_Min_EX_T_E                    = 0x2100;
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_Flowrate_E0                   = 0x2200;   // 2 Byte Integer
  constexpr uint16_t VP_Flowrate_E1                   = 0x2202;   // 2 Byte Integer
  constexpr uint16_t VP_Flowrate_E2                   = 0x2204;
  constexpr uint16_t VP_Flowrate_E3                   = 0x2206;
  constexpr uint16_t VP_Flowrate_E4                   = 0x2208;
  constexpr uint16_t VP_Flowrate_E5                   = 0x220A;
  constexpr uint16_t VP_Flowrate_E6                   = 0x220C;
  constexpr uint16_t VP_Flowrate_E7                   = 0x220E;

<<<<<<< HEAD
constexpr uint16_t VP_Cool_Down                       = 0x2220 ; //выключить нагрев и вентиляторы

=======
>>>>>>> origin/release-2.1.3-beta2
  // Move
  constexpr uint16_t VP_MOVE_X                        = 0x2300;
  constexpr uint16_t VP_MOVE_Y                        = 0x2302;
  constexpr uint16_t VP_MOVE_Z                        = 0x2304;
  constexpr uint16_t VP_MOVE_E0                       = 0x2310;
  constexpr uint16_t VP_MOVE_E1                       = 0x2312;
  constexpr uint16_t VP_MOVE_E2                       = 0x2314;
  constexpr uint16_t VP_MOVE_E3                       = 0x2316;
  constexpr uint16_t VP_MOVE_E4                       = 0x2318;
  constexpr uint16_t VP_MOVE_E5                       = 0x231A;
  constexpr uint16_t VP_MOVE_E6                       = 0x231C;
  constexpr uint16_t VP_MOVE_E7                       = 0x231E;
  constexpr uint16_t VP_HOME_ALL                      = 0x2320;
  constexpr uint16_t VP_MOTOR_LOCK_UNLOK              = 0x2330;
  constexpr uint16_t VP_MOVE_DISTANCE                 = 0x2334;
  constexpr uint16_t VP_X_HOME                        = 0x2336;
  constexpr uint16_t VP_Y_HOME                        = 0x2338;
  constexpr uint16_t VP_Z_HOME                        = 0x233A;
<<<<<<< HEAD
  constexpr uint16_t VP_XY_HOME                       = 0x233C;

=======
>>>>>>> origin/release-2.1.3-beta2

  // Fan Control Buttons , switch between "off" and "on"
  constexpr uint16_t VP_FAN0_CONTROL                  = 0x2350;
  constexpr uint16_t VP_FAN1_CONTROL                  = 0x2352;
  constexpr uint16_t VP_FAN2_CONTROL                  = 0x2354;
  constexpr uint16_t VP_FAN3_CONTROL                  = 0x2356;
  constexpr uint16_t VP_FAN4_CONTROL                  = 0x2358;
  constexpr uint16_t VP_FAN5_CONTROL                  = 0x235A;

  constexpr uint16_t VP_LANGUAGE_CHANGE               = 0x2380;
  constexpr uint16_t VP_LANGUAGE_CHANGE1              = 0x2382;
  constexpr uint16_t VP_LANGUAGE_CHANGE2              = 0x2384;
  constexpr uint16_t VP_LANGUAGE_CHANGE3              = 0x2386;
  constexpr uint16_t VP_LANGUAGE_CHANGE4              = 0x2388;
  constexpr uint16_t VP_LANGUAGE_CHANGE5              = 0x238A;

  // LEVEL
<<<<<<< HEAD
  #if !HAS_BED_PROBE
    constexpr uint16_t VP_LEVEL_POINT                   = 0x2400; // пять точек для ручного выставления зазора
    constexpr uint16_t VP_LEVEL_BUTTON                  = 0x2420; //выход из меню ручной калибровки
  #endif

  #if HAS_BED_PROBE
    constexpr uint16_t VP_LEVELING_START_STOP           = 0x2422; //кнопка запуска авто калибровки 1-обычная 2-две темп 3-стоп 4-готово
    constexpr uint16_t VP_LEVELING_TEMP_1_SET           = 0x2424; //+- кнопки первой температуры калибровки
    constexpr uint16_t VP_LEVELING_TEMP_2_SET           = 0x2426; //+- кнопки второй температуры калибровки
    constexpr uint16_t VP_LEVELING_TEMP_1               = 0x2428; //свое значение температуры 1 для автокалибровки
    constexpr uint16_t VP_LEVELING_TEMP_2               = 0x242A; //свое значение температуры 2 для автокалибровки
    constexpr uint16_t VP_LEVELING_STATUS               = 0x242C; //свое статус калибровки
  #endif


  // constexpr uint16_t VP_E0_FILAMENT_LOAD_UNLOAD       = 0x2500; //не используется 
  // constexpr uint16_t VP_E1_FILAMENT_LOAD_UNLOAD       = 0x2504; //не используется
  constexpr uint16_t VP_LOAD_Filament                 = 0x2508; //загрузка обычная кнопка +
  constexpr uint16_t VP_Filament_CONST                = 0x2510; //своя загрузка подготовительная из катушки
  // constexpr uint16_t VP_LOAD_UNLOAD_Cancle         = 0x250A; //что это
  constexpr uint16_t VP_UNLOAD_Filament               = 0x250B; //выгрузка обычная  кнопка -



  constexpr uint16_t VP_Fil_Speed_Pr                  = 0x2520; //свое кнопка выбора скорости выдавливания на меню замены филамента
  constexpr uint16_t VP_Fil_Step_Pr                   = 0x2522; //свое кнопка выбора шага выдавливания на меню замены филамента

  constexpr uint16_t VP_FILAMENT_SENSOR_ON            = 0x2550; //свое кнопка активации датчика филамента 

  constexpr uint16_t VP_FILAMENT_CHANGE_STATUS        = 0x2552; //своя текстовое поле вывода состояния смены печати

  constexpr uint16_t VP_Filament_distance             = 0x2600;
  constexpr uint16_t VP_Filament_speed                = 0x2604;
  // constexpr uint16_t VP_MIN_EX_T                      = 0x2606;

  // constexpr uint16_t VP_E1_MIN_EX_T                   = 0x2618; //??????? что это

=======
  constexpr uint16_t VP_LEVEL_POINT                   = 0x2400;
  constexpr uint16_t VP_MESH_LEVEL_POINT              = 0x2410;
  constexpr uint16_t VP_MESH_LEVEL_ADJUST             = 0x2412;
  constexpr uint16_t VP_MESH_LEVEL_DIP                = 0x2414;
  constexpr uint16_t VP_MESH_LEVEL_POINT_X            = 0x2416;
  constexpr uint16_t VP_MESH_LEVEL_POINT_Y            = 0x2418;
  constexpr uint16_t VP_LEVEL_BUTTON                  = 0x2420;
  constexpr uint16_t VP_MESH_LEVEL_POINT_DIS          = 0x2422;
  constexpr uint16_t VP_MESH_LEVEL_BACK               = 0x2424;

  constexpr uint16_t VP_E0_FILAMENT_LOAD_UNLOAD       = 0x2500;
  constexpr uint16_t VP_E1_FILAMENT_LOAD_UNLOAD       = 0x2504;
  constexpr uint16_t VP_LOAD_Filament                 = 0x2508;
  // constexpr uint16_t VP_LOAD_UNLOAD_Cancle            = 0x250A;
  constexpr uint16_t VP_UNLOAD_Filament               = 0x250B;
  constexpr uint16_t VP_Filament_distance             = 0x2600;
  constexpr uint16_t VP_Filament_speed                = 0x2604;
  constexpr uint16_t VP_MIN_EX_T                      = 0x2606;

  constexpr uint16_t VP_E1_Filament_distance          = 0x2614;
  constexpr uint16_t VP_E1_Filament_speed             = 0x2616;
  constexpr uint16_t VP_E1_MIN_EX_T                   = 0x2618;
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_Fan0_Percentage               = 0x2700;   // 2 Byte Integer (0..100)
  constexpr uint16_t VP_Fan1_Percentage               = 0x2702;   // 2 Byte Integer (0..100)
  constexpr uint16_t VP_Fan2_Percentage               = 0x2704;   // 2 Byte Integer (0..100)
  constexpr uint16_t VP_Fan3_Percentage               = 0x2706;   // 2 Byte Integer (0..100)
  constexpr uint16_t VP_Feedrate_Percentage           = 0x2708;   // 2 Byte Integer (0..100)

  // Fan status
<<<<<<< HEAD
  constexpr uint16_t VP_FAN0_STATUS                   = 0x2710; //наверное это все не надо
  constexpr uint16_t VP_FAN1_STATUS                   = 0x2712; //наверное это все не надо
  constexpr uint16_t VP_FAN2_STATUS                   = 0x2714; //наверное это все не надо
  constexpr uint16_t VP_FAN3_STATUS                   = 0x2716; //наверное это все не надо


 /// настройки вов ремя печати
 constexpr uint16_t VP_PRINTING_SETTINGS_STEP        = 0x2720; //кнопка карусельки в меню настроек во время печати
 constexpr uint16_t VP_E0_TEMP_SET                   = 0x2722; //кнопка + - в меню настроек во время печати
 constexpr uint16_t VP_BED_TEMP_SET                  = 0x2724; //кнопка + - в меню настроек во время печати
 constexpr uint16_t VP_CHAMBER_TEMP_SET              = 0x2726; //кнопка + - в меню настроек во время печати

 constexpr uint16_t VP_SPEED_SET                     = 0x2728; //кнопка + - в меню настроек во время печати
 constexpr uint16_t VP_FLOW_SET                      = 0x2730; //кнопка + - в меню настроек во время печати
 constexpr uint16_t VP_FAN0_SET                      = 0x2732; //кнопка + - в меню настроек во время печати


  // Step per mm
  // constexpr uint16_t VP_X_STEP_PER_MM                 = 0x2900;   // at the moment , 2 byte unsigned int , 0~1638.4
  // constexpr uint16_t VP_Y_STEP_PER_MM                 = 0x2904;
  // constexpr uint16_t VP_Z_STEP_PER_MM                 = 0x2908;
  // constexpr uint16_t VP_E0_STEP_PER_MM                = 0x2910;
  // constexpr uint16_t VP_E1_STEP_PER_MM                = 0x2912;
  // constexpr uint16_t VP_E2_STEP_PER_MM                = 0x2914;
  // constexpr uint16_t VP_E3_STEP_PER_MM                = 0x2916;
  // constexpr uint16_t VP_E4_STEP_PER_MM                = 0x2918;
  // constexpr uint16_t VP_E5_STEP_PER_MM                = 0x291A;
  // constexpr uint16_t VP_E6_STEP_PER_MM                = 0x291C;
  // constexpr uint16_t VP_E7_STEP_PER_MM                = 0x291E;

  // constexpr uint16_t VP_X_MAX_SPEED                   = 0x2A00;
  // constexpr uint16_t VP_Y_MAX_SPEED                   = 0x2A04;
  // constexpr uint16_t VP_Z_MAX_SPEED                   = 0x2A08;
  // constexpr uint16_t VP_E0_MAX_SPEED                  = 0x2A0C;
  // constexpr uint16_t VP_E1_MAX_SPEED                  = 0x2A10;

  // constexpr uint16_t VP_X_ACC_MAX_SPEED               = 0x2A28;
  // constexpr uint16_t VP_Y_ACC_MAX_SPEED               = 0x2A2C;
  // constexpr uint16_t VP_Z_ACC_MAX_SPEED               = 0x2A30;
  // constexpr uint16_t VP_E0_ACC_MAX_SPEED              = 0x2A34;
  // constexpr uint16_t VP_E1_ACC_MAX_SPEED              = 0x2A38;

  // constexpr uint16_t VP_TRAVEL_SPEED                  = 0x2A3C;
  // constexpr uint16_t VP_FEEDRATE_MIN_SPEED            = 0x2A40;
  // constexpr uint16_t VP_T_F_SPEED                     = 0x2A44;
  // constexpr uint16_t VP_ACC_SPEED                     = 0x2A48;

  /* -------------------------------0x3000-0x3FFF------------------------------- */
  // Buttons on the SD-Card File listing.
  constexpr uint16_t VP_SD_Open                       = 0x3000; //свое, запрос на открытие списка файлов на флешке


  constexpr uint16_t VP_SD_ScrollEvent                = 0x3020; // Data: 0 for "up a directory", numbers are the amount to scroll, e.g -1 one up, 1 one down, 3 назад из папки
  constexpr uint16_t VP_SD_FileSelected               = 0x3022; // Кнопка для нажатия на файл Number of file field selected.
  constexpr uint16_t VP_SD_FileSelectConfirm          = 0x3024; // кнопка запуска печати (This is a virtual VP and emulated by the Confirm Screen when a file has been confirmed)
  constexpr uint16_t VP_SD_ResumePauseAbort           = 0x3026; // Resume(Data=0), Pause(Data=1), Abort(Data=2) SD Card prints, нагреть зановов = 3
  constexpr uint16_t VP_SD_AbortPrintConfirmed        = 0x3028; // Отмена печати Abort print confirmation (virtual, will be injected by the confirm dialog)
  constexpr uint16_t VP_SD_FileSelectCancel           = 0x3030; // свое кнопка отмена старта печати - выход на страницу выбора файла
  constexpr uint16_t VP_SD_Print_Settings_Back        = 0x3032; // свое кнопка перехода ИЗ меню настроек назад в печать или паузу/ и еще из отмены печати назад
  //constexpr uint16_t VP_SD_Print_Setting            = 0x3040; //?? не используется 

  constexpr uint16_t VP_SD_Filament_Change            = 0x3042; //свое кнопка перехода в меню смена филамента
  constexpr uint16_t VP_SD_Filament_Change_Back       = 0x3044; //свое кнопка перехода ИЗ меню смена филамента


  ////Babystepping
  #if ENABLED(BABYSTEPPING)
    constexpr uint16_t VP_SD_Print_BabyStep_Set           = 0x3050; // +- babystep оффсета Data: 0 down, 1 up
    constexpr uint16_t VP_BabyStep_Step                   = 0x3052; // шаг оффсета
    constexpr uint16_t VP_BabyStep_Distance               = 0x3054; //сумма сдвига
    //constexpr uint16_t VP_SD_Print_LiveAdjustZ_Confirm  = 0x3060; // пока не нужно нам
  #endif

  ////Z offset свое
  #if HAS_BED_PROBE
    constexpr uint16_t VP_Zoffset_Set                    = 0x3060; // +- Z оффсета Data: 0 down, 1 up
    //constexpr uint16_t VP_Zoffset_ReWrite                = 0x3062; // вроде что то свое для теста переделать в сохранить
    constexpr uint16_t VP_Zoffset_Distance               = 0x3062; // сумма сдвига
    constexpr uint16_t VP_Zoffset_Start                  = 0x3066; // Кнопка для выставления зазора, сопло должно подъехать
    constexpr uint16_t VP_Zoffset_Save                   = 0x3068; // Кнопка для сохранения зазора и карты
    constexpr uint16_t VP_Zoffset_Step                   = 0x3070; // шаг оффсета сделаем такой же чтоб не париться
    constexpr uint16_t VP_Zoffset_Status                 = 0x3072; // Статус выставления зазора
  #endif
 

  ////K factor Linear advance свое
  constexpr uint16_t VP_K_Factor_Save                  = 0x3090; //кнопка сохранить в EEPROM
  constexpr uint16_t VP_K_Factor_Value                 = 0x30A0; //значение K factor ;;
  constexpr uint16_t VP_K_Factor_Set                   = 0x30B0; //+- K factor Data: 0 down, 1 up
  constexpr uint16_t VP_K_Factor_Step                  = 0x30C0; //каруселька шага

 //constexpr uint16_t VP_SD_FileSelect_Back            = 0x6082; //0x3082 старое кнопка назад из списка файлов


  // SDCard File Listing
  #if !HAS_BED_PROBE
    constexpr uint16_t VP_SD_FileName_LEN          = 44;                  // 32 LEN is shared for all entries.
    constexpr uint16_t DGUS_SD_FILESPERSCREEN      = 9;                   // FIXME move that info to the display and read it from there
    constexpr uint16_t VP_SD_FileName0             = 0x3100;    ///шаг VP в вертикальном экране 20
    constexpr uint16_t VP_SD_FileName1             = 0x3120;
    constexpr uint16_t VP_SD_FileName2             = 0x3140;
    constexpr uint16_t VP_SD_FileName3             = 0x3160;
    constexpr uint16_t VP_SD_FileName4             = 0x3180;
    constexpr uint16_t VP_SD_FileName5             = 0x31A0;
    constexpr uint16_t VP_SD_FileName6             = 0x31C0;
    constexpr uint16_t VP_SD_FileName7             = 0x31E0;
    constexpr uint16_t VP_SD_FileName8             = 0x3200;
  #elif HAS_BED_PROBE //под горизонтальный дисплей
    constexpr uint16_t VP_SD_FileName_LEN          = 80;                  
    constexpr uint16_t DGUS_SD_FILESPERSCREEN      = 6;                   // FIXME move that info to the display and read it from there
    constexpr uint16_t VP_SD_FileName0             = 0x3100;    ///шаг VP в горизонтальном экране 30
    constexpr uint16_t VP_SD_FileName1             = 0x3130;
    constexpr uint16_t VP_SD_FileName2             = 0x3160;
    constexpr uint16_t VP_SD_FileName3             = 0x3190;
    constexpr uint16_t VP_SD_FileName4             = 0x31C0;
    constexpr uint16_t VP_SD_FileName5             = 0x31F0;
  #endif


  constexpr uint16_t VP_Status_LEN      = 38;                  // 32 LEN is shared for all entries.
  constexpr uint16_t VP_SD_FileName_Select            = 0x3230; // свое выбранный файл 


  //constexpr uint16_t VP_SD_Print_ProbeOffsetZ       = 0x32A0; //не нашел на дисплее
  constexpr uint16_t VP_SD_Print_Baby                 = 0x32B0;  // не наше такого
  constexpr uint16_t VP_SD_Print_Filename             = 0x32C0;  //имя печатаемого файла
=======
  constexpr uint16_t VP_FAN0_STATUS                   = 0x2710;
  constexpr uint16_t VP_FAN1_STATUS                   = 0x2712;
  constexpr uint16_t VP_FAN2_STATUS                   = 0x2714;
  constexpr uint16_t VP_FAN3_STATUS                   = 0x2716;

  // Step per mm
  constexpr uint16_t VP_X_STEP_PER_MM                 = 0x2900;   // at the moment , uint16_t , 0~1638.4
  constexpr uint16_t VP_Y_STEP_PER_MM                 = 0x2904;
  constexpr uint16_t VP_Z_STEP_PER_MM                 = 0x2908;
  constexpr uint16_t VP_E0_STEP_PER_MM                = 0x2910;
  constexpr uint16_t VP_E1_STEP_PER_MM                = 0x2912;
  constexpr uint16_t VP_E2_STEP_PER_MM                = 0x2914;
  constexpr uint16_t VP_E3_STEP_PER_MM                = 0x2916;
  constexpr uint16_t VP_E4_STEP_PER_MM                = 0x2918;
  constexpr uint16_t VP_E5_STEP_PER_MM                = 0x291A;
  constexpr uint16_t VP_E6_STEP_PER_MM                = 0x291C;
  constexpr uint16_t VP_E7_STEP_PER_MM                = 0x291E;

  constexpr uint16_t VP_X_MAX_SPEED                   = 0x2A00;
  constexpr uint16_t VP_Y_MAX_SPEED                   = 0x2A04;
  constexpr uint16_t VP_Z_MAX_SPEED                   = 0x2A08;
  constexpr uint16_t VP_E0_MAX_SPEED                  = 0x2A0C;
  constexpr uint16_t VP_E1_MAX_SPEED                  = 0x2A10;

  constexpr uint16_t VP_X_ACC_MAX_SPEED               = 0x2A28;
  constexpr uint16_t VP_Y_ACC_MAX_SPEED               = 0x2A2C;
  constexpr uint16_t VP_Z_ACC_MAX_SPEED               = 0x2A30;
  constexpr uint16_t VP_E0_ACC_MAX_SPEED              = 0x2A34;
  constexpr uint16_t VP_E1_ACC_MAX_SPEED              = 0x2A38;

  constexpr uint16_t VP_TRAVEL_SPEED                  = 0x2A3C;
  constexpr uint16_t VP_FEEDRATE_MIN_SPEED            = 0x2A40;
  constexpr uint16_t VP_T_F_SPEED                     = 0x2A44;
  constexpr uint16_t VP_ACC_SPEED                     = 0x2A48;

  /* -------------------------------0x3000-0x3FFF------------------------------- */
  // Buttons on the SD-Card File listing.
  constexpr uint16_t VP_SD_ScrollEvent                = 0x3020; // Data: 0 for "up a directory", numbers are the amount to scroll, e.g -1 one up, 1 one down
  constexpr uint16_t VP_SD_FileSelected               = 0x3022; // Number of file field selected.
  constexpr uint16_t VP_SD_FileSelectConfirm          = 0x3024; // (This is a virtual VP and emulated by the Confirm Screen when a file has been confirmed)
  constexpr uint16_t VP_SD_ResumePauseAbort           = 0x3026; // Resume(Data=0), Pause(Data=1), Abort(Data=2) SD Card prints
  constexpr uint16_t VP_SD_AbortPrintConfirmed        = 0x3028; // Abort print confirmation (virtual, will be injected by the confirm dialog)
  constexpr uint16_t VP_SD_Print_Setting              = 0x3040;
  constexpr uint16_t VP_SD_Print_LiveAdjustZ          = 0x3050; // Data: 0 down, 1 up
  constexpr uint16_t VP_SD_Print_LiveAdjustZ_Confirm  = 0x3060;
  constexpr uint16_t VP_ZOffset_Distance              = 0x3070;
  constexpr uint16_t VP_ZOffset_DE_DIS                = 0x3080;
  constexpr uint16_t VP_SD_FileSelect_Back            = 0x3082;
  // SDCard File Listing
  constexpr uint16_t VP_SD_FileName_LEN = 32;                   // LEN is shared for all entries.
  constexpr uint16_t DGUS_SD_FILESPERSCREEN = 10;               // FIXME move that info to the display and read it from there.
  constexpr uint16_t VP_SD_FileName0                  = 0x3100;
  constexpr uint16_t VP_SD_FileName1                  = 0x3120;
  constexpr uint16_t VP_SD_FileName2                  = 0x3140;
  constexpr uint16_t VP_SD_FileName3                  = 0x3160;
  constexpr uint16_t VP_SD_FileName4                  = 0x3180;
  constexpr uint16_t VP_SD_FileName5                  = 0x31A0;
  constexpr uint16_t VP_SD_FileName6                  = 0x31C0;
  constexpr uint16_t VP_SD_FileName7                  = 0x31E0;
  constexpr uint16_t VP_SD_FileName8                  = 0x3200;
  constexpr uint16_t VP_SD_FileName9                  = 0x3220;

  constexpr uint16_t VP_SD_Print_ProbeOffsetZ         = 0x32A0;
  constexpr uint16_t VP_SD_Print_Baby                 = 0x32B0;
  constexpr uint16_t VP_SD_Print_Filename             = 0x32C0;
>>>>>>> origin/release-2.1.3-beta2

  // X Y Z Point
  constexpr uint16_t VP_XPos = 0x3300;  // 4 Byte Fixed point number; format xxx.yy
  constexpr uint16_t VP_YPos = 0x3302;  // 4 Byte Fixed point number; format xxx.yy
  constexpr uint16_t VP_ZPos = 0x3304;  // 4 Byte Fixed point number; format xxx.yy
  constexpr uint16_t VP_EPos = 0x3306;  // 4 Byte Fixed point number; format xxx.yy

<<<<<<< HEAD
/////// свое отправка принтера на координату
  constexpr uint16_t VP_XPos_Set = 0x3310;  // 4 Byte Fixed point number; format xxx.yy
  constexpr uint16_t VP_YPos_Set = 0x3312;  // 4 Byte Fixed point number; format xxx.yy
  constexpr uint16_t VP_ZPos_Set = 0x3314;  // 4 Byte Fixed point number; format xxx.yy


  // Print
  constexpr uint16_t VP_PrintProgress_Percentage      = 0x3330; // 2 Byte Integer (0..100)
  constexpr uint16_t VP_PrintStatus                   = 0x3332;  //свое вывод состояния печати
=======
  // Print
  constexpr uint16_t VP_PrintProgress_Percentage      = 0x3330; // 2 Byte Integer (0..100)
>>>>>>> origin/release-2.1.3-beta2
  constexpr uint16_t VP_PrintTime                     = 0x3340;
  constexpr uint16_t VP_PrintTime_LEN                 = 32;
  constexpr uint16_t VP_PrintAccTime                  = 0x3360;
  constexpr uint16_t VP_PrintAccTime_LEN              = 32;
  constexpr uint16_t VP_PrintsTotal                   = 0x3380;
  constexpr uint16_t VP_PrintsTotal_LEN               = 16;

<<<<<<< HEAD



  constexpr uint16_t VP_File_Pictutr0                 = 0x3400; //было, но видимо не использовалось
=======
  constexpr uint16_t VP_File_Pictutr0                 = 0x3400;
>>>>>>> origin/release-2.1.3-beta2
  constexpr uint16_t VP_File_Pictutr1                 = 0x3402;
  constexpr uint16_t VP_File_Pictutr2                 = 0x3404;
  constexpr uint16_t VP_File_Pictutr3                 = 0x3406;
  constexpr uint16_t VP_File_Pictutr4                 = 0x3408;
  constexpr uint16_t VP_File_Pictutr5                 = 0x340A;
  constexpr uint16_t VP_File_Pictutr6                 = 0x340C;
  constexpr uint16_t VP_File_Pictutr7                 = 0x340E;
  constexpr uint16_t VP_File_Pictutr8                 = 0x3410;
<<<<<<< HEAD
  //constexpr uint16_t VP_File_Pictutr9                 = 0x3412;

  constexpr uint16_t VP_BED_STATUS                    = 0x341C; //не нашел //наверное это все не надо

  // constexpr uint16_t VP_TMC_X_STEP                    = 0x3430;
  // constexpr uint16_t VP_TMC_Y_STEP                    = 0x3432;
  // constexpr uint16_t VP_TMC_Z_STEP                    = 0x3434;

  // constexpr uint16_t VP_TMC_X1_Current                = 0x3436;
  // constexpr uint16_t VP_TMC_Y1_Current                = 0x3438;
  // constexpr uint16_t VP_TMC_X_Current                 = 0x343A;
  // constexpr uint16_t VP_TMC_Y_Current                 = 0x343C;
  // constexpr uint16_t VP_TMC_Z_Current                 = 0x343E;
  // constexpr uint16_t VP_TMC_E0_Current                = 0x3440;
  // constexpr uint16_t VP_TMC_E1_Current                = 0x3442;
  // constexpr uint16_t VP_TMC_Z1_Current                = 0x3444;

=======
  constexpr uint16_t VP_File_Pictutr9                 = 0x3412;

  constexpr uint16_t VP_BED_STATUS                    = 0x341C;

  constexpr uint16_t VP_TMC_X_STEP                    = 0x3430;
  constexpr uint16_t VP_TMC_Y_STEP                    = 0x3432;
  constexpr uint16_t VP_TMC_Z_STEP                    = 0x3434;

  constexpr uint16_t VP_TMC_X1_Current                = 0x3436;
  constexpr uint16_t VP_TMC_Y1_Current                = 0x3438;
  constexpr uint16_t VP_TMC_X_Current                 = 0x343A;
  constexpr uint16_t VP_TMC_Y_Current                 = 0x343C;
  constexpr uint16_t VP_TMC_Z_Current                 = 0x343E;
  constexpr uint16_t VP_TMC_E0_Current                = 0x3440;
  constexpr uint16_t VP_TMC_E1_Current                = 0x3442;
  constexpr uint16_t VP_TMC_Z1_Current                = 0x3444;
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_PrintTime_H                   = 0x3500;
  constexpr uint16_t VP_PrintTime_M                   = 0x3502;
  constexpr uint16_t VP_PrintTime_S                   = 0x3504;

<<<<<<< HEAD
  #if HAS_BED_PROBE
    constexpr uint16_t VP_PrintTime_H_R                   = 0x3510; //свое остаток печати
    constexpr uint16_t VP_PrintTime_M_R                   = 0x3512;
    constexpr uint16_t VP_PrintTime_S_R                   = 0x3514;
  #endif

  // PIDs
  // constexpr uint16_t VP_E0_PID_P = 0x3700; // at the moment , 2 byte unsigned int , 0~1638.4
  // constexpr uint16_t VP_E0_PID_I = 0x3702;
  // constexpr uint16_t VP_E0_PID_D = 0x3704;
  // constexpr uint16_t VP_E1_PID_P = 0x3706; // at the moment , 2 byte unsigned int , 0~1638.4
  // constexpr uint16_t VP_E1_PID_I = 0x3708;
  // constexpr uint16_t VP_E1_PID_D = 0x370A;
  // constexpr uint16_t VP_BED_PID_P = 0x3710;
  // constexpr uint16_t VP_BED_PID_I = 0x3712;
  // constexpr uint16_t VP_BED_PID_D = 0x3714;
=======
  // PIDs
  constexpr uint16_t VP_E0_PID_P = 0x3700; // at the moment , uint16_t , 0~1638.4
  constexpr uint16_t VP_E0_PID_I = 0x3702;
  constexpr uint16_t VP_E0_PID_D = 0x3704;
  constexpr uint16_t VP_E1_PID_P = 0x3706; // at the moment , uint16_t , 0~1638.4
  constexpr uint16_t VP_E1_PID_I = 0x3708;
  constexpr uint16_t VP_E1_PID_D = 0x370A;
  constexpr uint16_t VP_BED_PID_P = 0x3710;
  constexpr uint16_t VP_BED_PID_I = 0x3712;
  constexpr uint16_t VP_BED_PID_D = 0x3714;
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_EEPROM_CTRL = 0x3720;

  constexpr uint16_t VP_OFFSET_X = 0x3724;
  constexpr uint16_t VP_OFFSET_Y = 0x3728;
  constexpr uint16_t VP_OFFSET_Z = 0x372B;

  // PID autotune
  constexpr uint16_t VP_PID_AUTOTUNE_E0 = 0x3800;
  constexpr uint16_t VP_PID_AUTOTUNE_E1 = 0x3802;
  constexpr uint16_t VP_PID_AUTOTUNE_E2 = 0x3804;
  constexpr uint16_t VP_PID_AUTOTUNE_E3 = 0x3806;
  constexpr uint16_t VP_PID_AUTOTUNE_E4 = 0x3808;
  constexpr uint16_t VP_PID_AUTOTUNE_E5 = 0x380A;
  constexpr uint16_t VP_PID_AUTOTUNE_BED = 0x380C;
<<<<<<< HEAD
  constexpr uint16_t VP_PID_AUTOTUNE_ALL =          0x380E; //свое автоподбор сопла и стола поочередно
  constexpr uint16_t VP_PID_AUTOTUNE_E0_TEMP =      0x3812; //свое значение температуры для калибровки
  constexpr uint16_t VP_PID_AUTOTUNE_BED_TEMP =     0x3814; //свое значение температуры для калибровки
  constexpr uint16_t VP_PID_AUTOTUNE_E0_TEMP_SET =  0x3816; //свое кнопка + - выбора температуры автоподбора пид
  constexpr uint16_t VP_PID_AUTOTUNE_BED_TEMP_SET = 0x3818; //свое кнопка + - выбора температуры  автоподбора пид
  constexpr uint16_t VP_PID_AUTOTUNE_ABORT =        0x3820; //свое кнопка отмена подбора командой M108
  constexpr uint16_t VP_PID_AUTOTUNE_STATUS =       0x3822; //Свое вывод надписи состояния
  constexpr uint16_t VP_PID_AUTOTUNE_CYCLES =       0x3840; //Свое вывод надписи состояния





  constexpr uint16_t VP_AutoTurnOffSw =    0x3882; //было 0x3812
  constexpr uint16_t VP_LCD_BLK =          0x3884; //было 0x3814
  constexpr uint16_t VP_CASE_LIGHT_ON =    0x3886; //мое включение выключение подсветки

=======
  // Calibrate Z
  constexpr uint16_t VP_Z_CALIBRATE = 0x3810;

  constexpr uint16_t VP_AutoTurnOffSw = 0x3812;
  constexpr uint16_t VP_LCD_BLK = 0x3814;
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_X_PARK_POS = 0x3900;
  constexpr uint16_t VP_Y_PARK_POS = 0x3902;
  constexpr uint16_t VP_Z_PARK_POS = 0x3904;

  /* -------------------------------0x4000-0x4FFF------------------------------- */
<<<<<<< HEAD
  // Heater Control Buttons , triged between "cool down" and "heat PLA" state у нас своя логика получше
  //constexpr uint16_t VP_E0_CONTROL = 0x4010;
  //constexpr uint16_t VP_E1_CONTROL = 0x4012;
=======
  // Heater Control Buttons , triged between "cool down" and "heat PLA" state
  constexpr uint16_t VP_E0_CONTROL = 0x4010;
  constexpr uint16_t VP_E1_CONTROL = 0x4012;
>>>>>>> origin/release-2.1.3-beta2
  //constexpr uint16_t VP_E2_CONTROL = 0x2214;
  //constexpr uint16_t VP_E3_CONTROL = 0x2216;
  //constexpr uint16_t VP_E4_CONTROL = 0x2218;
  //constexpr uint16_t VP_E5_CONTROL = 0x221A;
<<<<<<< HEAD
  //constexpr uint16_t VP_BED_CONTROL = 0x401C;

  // Preheat //тоже не надо у нас свое
  //constexpr uint16_t VP_E0_BED_PREHEAT = 0x4020;
  //constexpr uint16_t VP_E1_BED_PREHEAT = 0x4022;
=======
  constexpr uint16_t VP_BED_CONTROL = 0x401C;

  // Preheat
  constexpr uint16_t VP_E0_BED_PREHEAT = 0x4020;
  constexpr uint16_t VP_E1_BED_PREHEAT = 0x4022;
>>>>>>> origin/release-2.1.3-beta2
  //constexpr uint16_t VP_E2_BED_PREHEAT = 0x4024;
  //constexpr uint16_t VP_E3_BED_PREHEAT = 0x4026;
  //constexpr uint16_t VP_E4_BED_PREHEAT = 0x4028;
  //constexpr uint16_t VP_E5_BED_PREHEAT = 0x402A;

  // Filament load and unload
  // constexpr uint16_t VP_E0_FILAMENT_LOAD_UNLOAD = 0x4030;
  // constexpr uint16_t VP_E1_FILAMENT_LOAD_UNLOAD = 0x4032;

  // Settings store , reset

<<<<<<< HEAD
  // Level data не надо такое, возьму адреса для иконок автокалибровки
  // constexpr uint16_t VP_Level_Point_One_X              = 0x4100;
  // constexpr uint16_t VP_Level_Point_One_Y              = 0x4102;
  // constexpr uint16_t VP_Level_Point_Two_X              = 0x4104;
  // constexpr uint16_t VP_Level_Point_Two_Y              = 0x4106;
  // constexpr uint16_t VP_Level_Point_Three_X            = 0x4108;
  // constexpr uint16_t VP_Level_Point_Three_Y            = 0x410A;
  // constexpr uint16_t VP_Level_Point_Four_X             = 0x410C;
  // constexpr uint16_t VP_Level_Point_Four_Y             = 0x410E;
  // constexpr uint16_t VP_Level_Point_Five_X             = 0x4110;
  // constexpr uint16_t VP_Level_Point_Five_Y             = 0x4112;


///свое иконки кружков точек пройденных калибровочных точек - шаг 2
#if GRID_MAX_POINTS_X == 2 || GRID_MAX_POINTS_X == 3 || GRID_MAX_POINTS_X == 4 || GRID_MAX_POINTS_X == 5
  constexpr uint16_t VP_Level_Point_1              = 0x4100;
  constexpr uint16_t VP_Level_Point_2              = 0x4102;
  constexpr uint16_t VP_Level_Point_3              = 0x4104;
  constexpr uint16_t VP_Level_Point_4              = 0x4106;
#elif GRID_MAX_POINTS_X == 3 || GRID_MAX_POINTS_X == 4 || GRID_MAX_POINTS_X == 5
  constexpr uint16_t VP_Level_Point_5              = 0x4108;
  constexpr uint16_t VP_Level_Point_6              = 0x410A;
  constexpr uint16_t VP_Level_Point_7              = 0x410C;
  constexpr uint16_t VP_Level_Point_8              = 0x410E;
  constexpr uint16_t VP_Level_Point_9              = 0x4110;
#elif GRID_MAX_POINTS_X == 4 || GRID_MAX_POINTS_X == 5
  constexpr uint16_t VP_Level_Point_10             = 0x4112;
  constexpr uint16_t VP_Level_Point_11             = 0x4114;
  constexpr uint16_t VP_Level_Point_12             = 0x4116;
  constexpr uint16_t VP_Level_Point_13             = 0x4118;
  constexpr uint16_t VP_Level_Point_14             = 0x411A;
  constexpr uint16_t VP_Level_Point_15             = 0x411C;
  constexpr uint16_t VP_Level_Point_16             = 0x411E; //первые 16шт для модели А3
#elif  GRID_MAX_POINTS_X == 5
  constexpr uint16_t VP_Level_Point_17             = 0x4120;
  constexpr uint16_t VP_Level_Point_18             = 0x4122;
  constexpr uint16_t VP_Level_Point_19             = 0x4124;
  constexpr uint16_t VP_Level_Point_20             = 0x4126;
  constexpr uint16_t VP_Level_Point_21             = 0x4128;
  constexpr uint16_t VP_Level_Point_22             = 0x412A;
  constexpr uint16_t VP_Level_Point_23             = 0x412C;
  constexpr uint16_t VP_Level_Point_24             = 0x412E;
  constexpr uint16_t VP_Level_Point_25             = 0x4130; // первые 25шт для модели A4
#endif



  /// иконки свое
  constexpr uint16_t VP_ERROR_STATUS                  = 0x4210; // свое Иконка наличия ошибок, значение 0/1
  constexpr uint16_t VP_CASE_LIGHT_STATUS             = 0x4212; // свое Иконка подсветки, значение 0/1
  constexpr uint16_t VP_FLASH_STATUS                  = 0x4214; // свое Иконка наличия флешки, значение 0/1
  constexpr uint16_t VP_FILAMENT_RUNOUT_STATUS        = 0x4216; // свое Иконка наличия филамента, значение 0/1
  constexpr uint16_t VP_HOT_STATUS                    = 0x4218; // свое Иконка наличия высокой температуры, значение 0/1
  constexpr uint16_t VP_FILAMENT_SENSOR_STATUS        = 0x4220; // свое Иконка вкл/выкл датчик филамента


=======
  // Level data
  constexpr uint16_t VP_Level_Point_One_X              = 0x4100;
  constexpr uint16_t VP_Level_Point_One_Y              = 0x4102;
  constexpr uint16_t VP_Level_Point_Two_X              = 0x4104;
  constexpr uint16_t VP_Level_Point_Two_Y              = 0x4106;
  constexpr uint16_t VP_Level_Point_Three_X            = 0x4108;
  constexpr uint16_t VP_Level_Point_Three_Y            = 0x410A;
  constexpr uint16_t VP_Level_Point_Four_X             = 0x410C;
  constexpr uint16_t VP_Level_Point_Four_Y             = 0x410E;
  constexpr uint16_t VP_Level_Point_Five_X             = 0x4110;
  constexpr uint16_t VP_Level_Point_Five_Y             = 0x4112;

  /* H43 Version */
  constexpr uint16_t VP_MKS_H43_VERSION                = 0x4A00;   // MKS H43 V1.0.0
  constexpr uint16_t VP_MKS_H43_VERSION_LEN            = 16;
  constexpr uint16_t VP_MKS_H43_UpdataVERSION          = 0x4A10;   // MKS H43 V1.0.0
  constexpr uint16_t VP_MKS_H43_UpdataVERSION_LEN      = 16;
>>>>>>> origin/release-2.1.3-beta2

  /* -------------------------------0x5000-0xFFFF------------------------------- */
  constexpr uint16_t VP_HOME_Dis                      = 0x5000;
  constexpr uint16_t VP_Setting_Dis                   = 0x5010;
  constexpr uint16_t VP_Tool_Dis                      = 0x5020;
  constexpr uint16_t VP_Printing_Dis                  = 0x5030;

  constexpr uint16_t VP_Language_Dis                  = 0x5080;
  constexpr uint16_t VP_LossPoint_Dis                 = 0x5090;

<<<<<<< HEAD
  // constexpr uint16_t VP_PrintPauseConfig_Dis          = 0x5120;
  // constexpr uint16_t VP_MotorPluse_Dis                = 0x5140;
  // constexpr uint16_t VP_MotorMaxSpeed_Dis             = 0x5150;
  // constexpr uint16_t VP_MotorMaxAcc_Dis               = 0x5160;

  // constexpr uint16_t VP_X_Pluse_Dis                   = 0x5170;
  // constexpr uint16_t VP_Y_Pluse_Dis                   = 0x5180;
  // constexpr uint16_t VP_Z_Pluse_Dis                   = 0x5190;
  // constexpr uint16_t VP_E0_Pluse_Dis                  = 0x51A0;
  // constexpr uint16_t VP_E1_Pluse_Dis                  = 0x51B0;

  // constexpr uint16_t VP_X_Max_Speed_Dis               = 0x5280;
  // constexpr uint16_t VP_Y_Max_Speed_Dis               = 0x5290;
  // constexpr uint16_t VP_Z_Max_Speed_Dis               = 0x52A0;
  // constexpr uint16_t VP_E0_Max_Speed_Dis              = 0x52B0;
  // constexpr uint16_t VP_E1_Max_Speed_Dis              = 0x52C0;

  // constexpr uint16_t VP_X_Max_Acc_Speed_Dis           = 0x51E0;
  // constexpr uint16_t VP_Y_Max_Acc_Speed_Dis           = 0x51F0;
  // constexpr uint16_t VP_Z_Max_Acc_Speed_Dis           = 0x5200;
  // constexpr uint16_t VP_E0_Max_Acc_Speed_Dis          = 0x5210;
  // constexpr uint16_t VP_E1_Max_Acc_Speed_Dis          = 0x5220;

=======
  constexpr uint16_t VP_PrintPauseConfig_Dis          = 0x5120;
  constexpr uint16_t VP_MotorPluse_Dis                = 0x5140;
  constexpr uint16_t VP_MotorMaxSpeed_Dis             = 0x5150;
  constexpr uint16_t VP_MotorMaxAcc_Dis               = 0x5160;

  constexpr uint16_t VP_X_Pluse_Dis                   = 0x5170;
  constexpr uint16_t VP_Y_Pluse_Dis                   = 0x5180;
  constexpr uint16_t VP_Z_Pluse_Dis                   = 0x5190;
  constexpr uint16_t VP_E0_Pluse_Dis                  = 0x51A0;
  constexpr uint16_t VP_E1_Pluse_Dis                  = 0x51B0;

  constexpr uint16_t VP_X_Max_Speed_Dis               = 0x5280;
  constexpr uint16_t VP_Y_Max_Speed_Dis               = 0x5290;
  constexpr uint16_t VP_Z_Max_Speed_Dis               = 0x52A0;
  constexpr uint16_t VP_E0_Max_Speed_Dis              = 0x52B0;
  constexpr uint16_t VP_E1_Max_Speed_Dis              = 0x52C0;

  constexpr uint16_t VP_X_Max_Acc_Speed_Dis           = 0x51E0;
  constexpr uint16_t VP_Y_Max_Acc_Speed_Dis           = 0x51F0;
  constexpr uint16_t VP_Z_Max_Acc_Speed_Dis           = 0x5200;
  constexpr uint16_t VP_E0_Max_Acc_Speed_Dis          = 0x5210;
  constexpr uint16_t VP_E1_Max_Acc_Speed_Dis          = 0x5220;
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_PrintTime_Dis                 = 0x5470;
  constexpr uint16_t VP_E0_Temp_Dis                   = 0x5310;
  constexpr uint16_t VP_E1_Temp_Dis                   = 0x5320;
  constexpr uint16_t VP_HB_Temp_Dis                   = 0x5330;
  constexpr uint16_t VP_Feedrate_Dis                  = 0x5350;
  constexpr uint16_t VP_PrintAcc_Dis                  = 0x5340;
  constexpr uint16_t VP_Fan_Speed_Dis                 = 0x5360;

<<<<<<< HEAD
  // constexpr uint16_t VP_Min_Ex_Temp_Dis               = 0x5380;


  // constexpr uint16_t VP_X_PARK_POS_Dis                = 0x53E0;
  // constexpr uint16_t VP_Y_PARK_POS_Dis                = 0x53F0;
  // constexpr uint16_t VP_Z_PARK_POS_Dis                = 0x5400;

=======
  constexpr uint16_t VP_Min_Ex_Temp_Dis               = 0x5380;

  constexpr uint16_t VP_X_PARK_POS_Dis                = 0x53E0;
  constexpr uint16_t VP_Y_PARK_POS_Dis                = 0x53F0;
  constexpr uint16_t VP_Z_PARK_POS_Dis                = 0x5400;
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_TravelAcc_Dis                 = 0x5440;
  constexpr uint16_t VP_FeedRateMin_Dis               = 0x5450;
  constexpr uint16_t VP_TravelFeeRateMin_Dis          = 0x5460;
  constexpr uint16_t VP_ACC_Dis                       = 0x5480;

  constexpr uint16_t VP_Extrusion_Dis                 = 0x5230;
  constexpr uint16_t VP_HeatBed_Dis                   = 0x5240;

  constexpr uint16_t VP_Printting_Dis                 = 0x5430;
  constexpr uint16_t VP_FactoryDefaults_Dis           = 0x54C0;
  constexpr uint16_t VP_StoreSetting_Dis              = 0x54B0;
  constexpr uint16_t VP_Info_EEPROM_2_Dis             = 0x54D0;
  constexpr uint16_t VP_Info_EEPROM_1_Dis             = 0x54E0;

  constexpr uint16_t VP_AutoLevel_1_Dis               = 0x55F0;

<<<<<<< HEAD
  // constexpr uint16_t VP_TMC_X_Step_Dis                = 0x7530; // замена адреса
  // constexpr uint16_t VP_TMC_Y_Step_Dis                = 0x7540;
  // constexpr uint16_t VP_TMC_Z_Step_Dis                = 0x7550;
  // constexpr uint16_t VP_TMC_X1_Current_Dis            = 0x7560;
  // constexpr uint16_t VP_TMC_Y1_Current_Dis            = 0x7570;
  // constexpr uint16_t VP_TMC_X_Current_Dis             = 0x7580;
  // constexpr uint16_t VP_TMC_Y_Current_Dis             = 0x7590;
  // constexpr uint16_t VP_TMC_Z_Current_Dis             = 0x75A0;
  // constexpr uint16_t VP_TMC_E0_Current_Dis            = 0x75B0;
  // constexpr uint16_t VP_TMC_E1_Current_Dis            = 0x75C0;
  // constexpr uint16_t VP_TMC_Z1_Current_Dis            = 0x75E0;
=======
  constexpr uint16_t VP_TMC_X_Step_Dis                = 0x5530;
  constexpr uint16_t VP_TMC_Y_Step_Dis                = 0x5540;
  constexpr uint16_t VP_TMC_Z_Step_Dis                = 0x5550;
  constexpr uint16_t VP_TMC_X1_Current_Dis            = 0x5560;
  constexpr uint16_t VP_TMC_Y1_Current_Dis            = 0x5570;
  constexpr uint16_t VP_TMC_X_Current_Dis             = 0x5580;
  constexpr uint16_t VP_TMC_Y_Current_Dis             = 0x5590;
  constexpr uint16_t VP_TMC_Z_Current_Dis             = 0x55A0;
  constexpr uint16_t VP_TMC_E0_Current_Dis            = 0x55B0;
  constexpr uint16_t VP_TMC_E1_Current_Dis            = 0x55C0;
  constexpr uint16_t VP_TMC_Z1_Current_Dis            = 0x55E0;
>>>>>>> origin/release-2.1.3-beta2

  constexpr uint16_t VP_AutoLEVEL_INFO1               = 0x5600;
  constexpr uint16_t VP_EX_TEMP_INFO1_Dis             = 0x5610;
  constexpr uint16_t VP_EX_TEMP_INFO2_Dis             = 0x5620;
  constexpr uint16_t VP_EX_TEMP_INFO3_Dis             = 0x5630;
  constexpr uint16_t VP_LCD_BLK_Dis                   = 0x56A0;
  constexpr uint16_t VP_Info_PrintFinish_1_Dis        = 0x5C00;
  constexpr uint16_t VP_Info_PrintFinish_2_Dis        = 0x5C10;

  constexpr uint16_t VP_Length_Dis                    = 0x5B00;

  constexpr uint16_t VP_PrintConfrim_Info_Dis         = 0x5B90;
  constexpr uint16_t VP_StopPrintConfrim_Info_Dis     = 0x5B80;

  constexpr uint16_t VP_Point_One_Dis                 = 0x5BA0;
  constexpr uint16_t VP_Point_Two_Dis                 = 0x5BB0;
  constexpr uint16_t VP_Point_Three_Dis               = 0x5BC0;
  constexpr uint16_t VP_Point_Four_Dis                = 0x5BD0;
  constexpr uint16_t VP_Point_Five_Dis                = 0x5BE0;

  constexpr uint16_t VP_Print_Dis                     = 0x5250;

  constexpr uint16_t VP_About_Dis                     = 0x5A00;
  constexpr uint16_t VP_Config_Dis                    = 0x5A10;
  constexpr uint16_t VP_Filament_Dis                  = 0x5A20;
  constexpr uint16_t VP_Move_Dis                      = 0x5A30;
  constexpr uint16_t VP_Level_Dis                     = 0x5A50;
  constexpr uint16_t VP_Speed_Dis                     = 0x5A70;
  constexpr uint16_t VP_InOut_Dis                     = 0x5A80;

  constexpr uint16_t VP_MotorConfig_Dis               = 0x5100;
  constexpr uint16_t VP_LevelConfig_Dis               = 0x5110;
  constexpr uint16_t VP_Advance_Dis                   = 0x5130;
  constexpr uint16_t VP_TemperatureConfig_Dis         = 0x5390;

<<<<<<< HEAD

  constexpr uint16_t VP_MARLIN_VERSION                = 0x7060;
  constexpr uint8_t VP_MARLIN_VERSION_LEN             = 44;       // there is more space on the display, if needed.

  constexpr uint16_t VP_PRINTER_VERSION               = 0x7020; //свое 

  /* H43 Version */
  constexpr uint16_t VP_MKS_H43_VERSION                = 0x7100;   // MKS H43 V1.0.0
  //constexpr uint16_t VP_MKS_H43_VERSION_LEN            = 32;
  //constexpr uint16_t VP_MKS_H43_UpdataVERSION          = 0x4A10;   // MKS H43 V1.0.0
  //constexpr uint16_t VP_MKS_H43_UpdataVERSION_LEN      = 16;


  ///Свое ошибки
  constexpr uint16_t VP_Error_Open                  = 0x3002; //свое, запрос на открытие списка ошибок
  constexpr uint16_t VP_Error_Back                  = 0x3034; // свое кнопка перехода ИЗ меню настроек назад в печать или паузу
  constexpr uint16_t VP_Error_Selected              = 0x5500; // Свое выбор ошибки (наверное не надо пока что)
  constexpr uint16_t VP_ErrorName0                  = 0x5520;
  constexpr uint16_t VP_ErrorName1                  = 0x5540;
  constexpr uint16_t VP_ErrorName2                  = 0x5560;
  constexpr uint16_t VP_ErrorName3                  = 0x5580;
  constexpr uint16_t VP_ErrorName4                  = 0x55A0;
  constexpr uint16_t VP_ErrorName5                  = 0x55C0;
  constexpr uint16_t VP_ErrorName6                  = 0x55E0;
  constexpr uint16_t VP_ErrorName7                  = 0x5600;
  constexpr uint16_t VP_ErrorName8                  = 0x5620;




=======
>>>>>>> origin/release-2.1.3-beta2
#endif // MKS_FINSH
