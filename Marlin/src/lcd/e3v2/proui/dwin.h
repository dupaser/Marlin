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

/**
 * DWIN Enhanced implementation for PRO UI
<<<<<<< HEAD
 * Author: Miguel A. Risco-Castillo (MRISCOC)
 * Version: 3.17.2
 * Date: 2022/04/08
 */

#include "dwin_defines.h"
#include "dwinui.h"
#include "../common/encoder.h"
#include "../../../libs/BL24CXX.h"

#include "../../../inc/MarlinConfig.h"

enum processID : uint8_t {
  // Process ID
  MainMenu,
  Menu,
  SetInt,
  SetPInt,
  SetIntNoDraw,
  SetFloat,
  SetPFloat,
  SelectFile,
  PrintProcess,
  Popup,
  Leveling,
  Locked,
  Reboot,
  PrintDone,
  ESDiagProcess,
  WaitResponse,
  Homing,
  PidProcess,
  NothingToDo
};

enum pidresult_t : uint8_t {
  PID_BAD_EXTRUDER_NUM,
  PID_TEMP_TOO_HIGH,
  PID_TUNING_TIMEOUT,
  PID_EXTR_START,
  PID_BED_START,
  PID_DONE
};
=======
 * Based on the original work of: Miguel Risco-Castillo (MRISCOC)
 * https://github.com/mriscoc/Ender3V2S1
 * Version: 3.25.3
 * Date: 2023/05/18
 */

#include "../../../inc/MarlinConfig.h"

#include "dwin_defines.h"
#include "dwinui.h"
#include "../common/encoder.h"
#include "../common/limits.h"
#include "../../../libs/BL24CXX.h"
#if ENABLED(LED_CONTROL_MENU)
  #include "../../../feature/leds/leds.h"
#endif

namespace GET_LANG(LCD_LANGUAGE) {
  #define _MSG_PREHEAT(N) \
    LSTR MSG_PREHEAT_##N                  = _UxGT("Preheat ") PREHEAT_## N ##_LABEL; \
    LSTR MSG_PREHEAT_## N ##_SETTINGS     = _UxGT("Preheat ") PREHEAT_## N ##_LABEL _UxGT(" Conf");
  #if PREHEAT_COUNT > 1
    REPEAT_S(2, INCREMENT(PREHEAT_COUNT), _MSG_PREHEAT)
  #endif
}

enum processID : uint8_t {
  // Process ID
  ID_MainMenu,
  ID_Menu,
  ID_SetInt,
  ID_SetFloat,
  ID_SetPInt,
  ID_SetPFloat,
  ID_SetIntNoDraw,
  ID_PrintProcess,
  ID_Popup,
  ID_Leveling,
  ID_Locked,
  ID_ESDiagProcess,
  ID_PrintDone,
  ID_WaitResponse,
  ID_Homing,
  ID_PIDProcess,
  ID_PlotProcess,
  ID_MPCProcess,
  ID_NothingToDo
};

#if ANY(HAS_PID_HEATING, MPC_AUTOTUNE)

  enum TempControl {
    AUTOTUNE_DONE,
    #if HAS_PID_HEATING
      #if ENABLED(PIDTEMP)
        PIDTEMP_START,
      #endif
      #if ENABLED(PIDTEMPBED)
        PIDTEMPBED_START,
      #endif
      #if ENABLED(PIDTEMPCHAMBER)
        PIDTEMPCHAMBER_START,
      #endif
      PID_BAD_HEATER_ID,
      PID_TEMP_TOO_HIGH,
      PID_TUNING_TIMEOUT,
    #endif
    #if ENABLED(MPC_AUTOTUNE)
      MPC_STARTED,
      MPC_TEMP_ERROR,
      MPC_INTERRUPTED,
    #endif
    TEMPCONTROL_COUNT
  };

  typedef bits_t(TEMPCONTROL_COUNT) tempcontrol_t;

#endif
>>>>>>> origin/release-2.1.3-beta2

#define DWIN_CHINESE 123
#define DWIN_ENGLISH 0

typedef struct {
<<<<<<< HEAD
  int8_t Color[3];                    // Color components
  pidresult_t pidresult   = PID_DONE;
  uint8_t Select          = 0;        // Auxiliary selector variable
  AxisEnum axis           = X_AXIS;   // Axis Select
} HMI_value_t;

typedef struct {
  uint8_t language;
  bool percent_flag:1;  // percent was override by M73
  bool remain_flag:1;   // remain was override by M73
  bool pause_flag:1;    // printing is paused
  bool pause_action:1;  // flag a pause action
  bool abort_flag:1;    // printing is aborting
  bool abort_action:1;  // flag a aborting action
  bool print_finish:1;  // print was finished
  bool select_flag:1;   // Popup button selected
  bool home_flag:1;     // homing in course
  bool heat_flag:1;     // 0: heating done  1: during heating
} HMI_flag_t;

extern HMI_value_t HMI_value;
extern HMI_flag_t HMI_flag;
extern uint8_t checkkey;
extern millis_t dwin_heat_time;

// Popups
#if HAS_HOTEND || HAS_HEATED_BED
  void DWIN_Popup_Temperature(const bool toohigh);
#endif
#if ENABLED(POWER_LOSS_RECOVERY)
  void Popup_PowerLossRecovery();
#endif

// Tool Functions
#if ENABLED(EEPROM_SETTINGS)
  void WriteEeprom();
  void ReadEeprom();
  void ResetEeprom();
  #if HAS_MESH
    void SaveMesh();
  #endif
#endif
void RebootPrinter();
void DisableMotors();
void AutoLev();
void AutoHome();
#if HAS_PREHEAT
  void DoPreheat0();
  void DoPreheat1();
  void DoPreheat2();
#endif
void DoCoolDown();
#if HAS_HOTEND
  void HotendPID();
#endif
#if HAS_HEATED_BED
  void BedPID();
#endif
#if ENABLED(BAUD_RATE_GCODE)
  void HMI_SetBaudRate();
  void SetBaud115K();
  void SetBaud250K();
#endif
#if HAS_LCD_BRIGHTNESS
  void TurnOffBacklight();
#endif
void ApplyExtMinT();
void ParkHead();
#if HAS_ONESTEP_LEVELING
  void Trammingwizard();
#endif
#if BOTH(LED_CONTROL_MENU, HAS_COLOR_LEDS)
  void ApplyLEDColor();
#endif
#if ENABLED(AUTO_BED_LEVELING_UBL)
  void UBLTiltMesh();
  bool UBLValidMesh();
  void UBLSaveMesh();
  void UBLLoadMesh();
#endif

// Other
void Goto_PrintProcess();
void Goto_Main_Menu();
void Goto_Info_Menu();
void Goto_PowerLossRecovery();
void Goto_ConfirmToPrint();
void DWIN_Draw_Dashboard(const bool with_update); // Status Area
void Draw_Main_Area();      // Redraw main area
void DWIN_DrawStatusLine(); // Draw simple status text
void DWIN_RedrawDash();     // Redraw Dash and Status line
void DWIN_RedrawScreen();   // Redraw all screen elements
void HMI_MainMenu();        // Main process screen
void HMI_SelectFile();      // File page
void HMI_Printing();        // Print page
void HMI_ReturnScreen();    // Return to previous screen before popups
void HMI_WaitForUser();
void HMI_SaveProcessID(const uint8_t id);
void HMI_SDCardInit();
void HMI_SDCardUpdate();
void EachMomentUpdate();
void update_variable();
void DWIN_InitScreen();
void DWIN_HandleScreen();
void DWIN_CheckStatusMessage();
void DWIN_HomingStart();
void DWIN_HomingDone();
#if HAS_MESH
  void DWIN_MeshUpdate(const int8_t xpos, const int8_t ypos, const_float_t zval);
#endif
void DWIN_LevelingStart();
void DWIN_LevelingDone();
void DWIN_PidTuning(pidresult_t result);
void DWIN_Print_Started(const bool sd=false);
void DWIN_Print_Pause();
void DWIN_Print_Resume();
void DWIN_Print_Finished();
void DWIN_Print_Aborted();
#if HAS_FILAMENT_SENSOR
  void DWIN_FilamentRunout(const uint8_t extruder);
#endif
void DWIN_M73();
void DWIN_Print_Header(const char *text);
void DWIN_SetColorDefaults();
void DWIN_ApplyColor();
void DWIN_CopySettingsTo(char * const buff);
void DWIN_CopySettingsFrom(const char * const buff);
void DWIN_SetDataDefaults();
void DWIN_RebootScreen();

#if ENABLED(ADVANCED_PAUSE_FEATURE)
  void DWIN_Popup_Pause(FSTR_P const fmsg, uint8_t button=0);
  void Draw_Popup_FilamentPurge();
  void Goto_FilamentPurge();
  void HMI_FilamentPurge();
=======
  // Color settings
  uint16_t colorBackground;
  uint16_t colorCursor;
  uint16_t colorTitleBg;
  uint16_t colorTitleTxt;
  uint16_t colorText;
  uint16_t colorSelected;
  uint16_t colorSplitLine;
  uint16_t colorHighlight;
  uint16_t colorStatusBg;
  uint16_t colorStatusTxt;
  uint16_t colorPopupBg;
  uint16_t colorPopupTxt;
  uint16_t colorAlertBg;
  uint16_t colorAlertTxt;
  uint16_t colorPercentTxt;
  uint16_t colorBarfill;
  uint16_t colorIndicator;
  uint16_t colorCoordinate;

  // Temperatures
  #if HAS_PID_HEATING
    int16_t pidCycles = DEF_PIDCYCLES;
    #if ENABLED(PIDTEMP)
      celsius_t hotendPIDT = DEF_HOTENDPIDT;
    #endif
    #if ENABLED(PIDTEMPBED)
      celsius_t bedPIDT = DEF_BEDPIDT;
    #endif
    #if ENABLED(PIDTEMPCHAMBER)
      celsius_t chamberPIDT = DEF_CHAMBERPIDT;
    #endif
  #endif
  #if ENABLED(PREVENT_COLD_EXTRUSION)
    celsius_t extMinT = EXTRUDE_MINTEMP;
  #endif
  #if ENABLED(PREHEAT_BEFORE_LEVELING)
    celsius_t bedLevT = LEVELING_BED_TEMP;
  #endif
  #if ENABLED(BAUD_RATE_GCODE)
    bool baud115K = false;
  #endif
  #if ALL(LCD_BED_TRAMMING, HAS_BED_PROBE)
    bool fullManualTramming = false;
  #endif
  #if ENABLED(PROUI_MEDIASORT)
    bool mediaSort = true;
  #endif
  bool mediaAutoMount = ENABLED(HAS_SD_EXTENDER);
  #if ALL(INDIVIDUAL_AXIS_HOMING_SUBMENU, MESH_BED_LEVELING)
    uint8_t zAfterHoming = DEF_Z_AFTER_HOMING;
    #define Z_POST_CLEARANCE hmiData.zAfterHoming
  #endif
  #if ALL(LED_CONTROL_MENU, HAS_COLOR_LEDS)
    LEDColor ledColor = defColorLeds;
  #endif
  #if HAS_GCODE_PREVIEW
    bool enablePreview = true;
  #endif
} hmi_data_t;

extern hmi_data_t hmiData;

#define EXTUI_EEPROM_DATA_SIZE sizeof(hmi_data_t)

typedef struct {
  int8_t r, g, b;
  void set(int8_t _r, int8_t _g, int8_t _b) { r = _r; g = _g; b = _b; }
  int8_t& operator[](const int i) {
    switch (i) {
      default:
      case 0: return r;
      case 1: return g;
      case 2: return b;
    }
  }
} rgb_t;

typedef struct {
  rgb_t color;                        // Color
  #if ANY(HAS_PID_HEATING, MPCTEMP)
    tempcontrol_t tempControl = AUTOTUNE_DONE;
  #endif
  uint8_t select = 0;                 // Auxiliary selector variable
  AxisEnum axis = X_AXIS;             // Axis Select
} hmi_value_t;

extern hmi_value_t hmiValue;

typedef struct {
  uint8_t language;
  bool printing_flag:1; // sd or host printing
  bool abort_flag:1;    // sd or host was aborted
  bool pause_flag:1;    // printing is paused
  bool select_flag:1;   // Popup button selected
  bool home_flag:1;     // homing in course
} hmi_flag_t;

extern hmi_flag_t hmiFlag;
extern uint8_t checkkey;

// Popups
#if HAS_HOTEND || HAS_HEATED_BED || HAS_HEATED_CHAMBER
  void dwinPopupTemperature(const int_fast8_t heater_id, const uint8_t state);
#endif
#if ENABLED(POWER_LOSS_RECOVERY)
  void popupPowerLossRecovery();
#endif

// Tool Functions
uint32_t getHash(char * str);
#if ENABLED(EEPROM_SETTINGS)
  void writeEEPROM();
  void readEEPROM();
  void resetEEPROM();
  #if HAS_MESH
    void saveMesh();
  #endif
#endif
void rebootPrinter();
void disableMotors();
void autoLevel();
void autoHome();
#if HAS_PREHEAT
  #define _DOPREHEAT(N) void DoPreheat##N();
  REPEAT_1(PREHEAT_COUNT, _DOPREHEAT)
#endif
void doCoolDown();
#if ENABLED(BAUD_RATE_GCODE)
  void hmiSetBaudRate();
  void setBaud115K();
  void setBaud250K();
#endif
#if HAS_LCD_BRIGHTNESS
  void turnOffBacklight();
#endif
#if ENABLED(PREVENT_COLD_EXTRUSION)
  void applyExtMinT();
#endif
#if ENABLED(NOZZLE_PARK_FEATURE)
  void parkHead();
#endif
#if HAS_ONESTEP_LEVELING
  void trammingwizard();
#endif
#if ALL(LED_CONTROL_MENU, HAS_COLOR_LEDS)
  void applyLEDColor();
#endif
#if ENABLED(AUTO_BED_LEVELING_UBL)
  void ublMeshTilt();
  void ublMeshSave();
  void ublMeshLoad();
#endif
#if DISABLED(HAS_BED_PROBE)
  void homeZAndDisable();
#endif

// Other
void gotoPrintProcess();
void gotoMainMenu();
void gotoInfoMenu();
void gotoPowerLossRecovery();
void gotoConfirmToPrint();
void dwinDrawDashboard(); // Status Area
void drawMainArea();      // Redraw main area
void dwinDrawStatusLine(const char *text = ""); // Draw simple status text
void dwinRedrawDash();     // Redraw Dash and Status line
void dwinRedrawScreen();   // Redraw all screen elements
void hmiMainMenu();        // Main process screen
void hmiPrinting();        // Print page
void hmiReturnScreen();    // Return to previous screen before popups
void hmiWaitForUser();
void hmiSaveProcessID(const uint8_t id);
void hmiSDCardUpdate();
void eachMomentUpdate();
void updateVariable();
void dwinInitScreen();
void dwinHandleScreen();
void dwinCheckStatusMessage();
void dwinHomingStart();
void dwinHomingDone();
#if HAS_MESH
  void dwinMeshUpdate(const int8_t cpos, const int8_t tpos, const_float_t zval);
#endif
void dwinLevelingStart();
void dwinLevelingDone();
void dwinPrintStarted();
void dwinPrintPause();
void dwinPrintResume();
void dwinPrintFinished();
void dwinPrintAborted();
#if HAS_FILAMENT_SENSOR
  void dwinFilamentRunout(const uint8_t extruder);
#endif
void dwinPrintHeader(const char * const cstr=nullptr);
void dwinSetColorDefaults();
void dwinCopySettingsTo(char * const buff);
void dwinCopySettingsFrom(const char * const buff);
void dwinSetDataDefaults();
void dwinRebootScreen();

#if ENABLED(ADVANCED_PAUSE_FEATURE)
  void dwinPopupPause(FSTR_P const fmsg, uint8_t button=0);
  void drawPopupFilamentPurge();
  void gotoFilamentPurge();
>>>>>>> origin/release-2.1.3-beta2
#endif

// Utility and extensions
#if HAS_LOCKSCREEN
<<<<<<< HEAD
  void DWIN_LockScreen();
  void DWIN_UnLockScreen();
  void HMI_LockScreen();
#endif
#if HAS_MESH
  void DWIN_MeshViewer();
#endif
#if HAS_GCODE_PREVIEW
  void HMI_ConfirmToPrint();
#endif
#if HAS_ESDIAG
  void Draw_EndStopDiag();
#endif
#if ENABLED(PRINTCOUNTER)
  void Draw_PrintStats();
#endif

// Menu drawing functions
void Draw_Control_Menu();
void Draw_AdvancedSettings_Menu();
void Draw_Prepare_Menu();
void Draw_Move_Menu();
void Draw_Tramming_Menu();
#if HAS_HOME_OFFSET
  void Draw_HomeOffset_Menu();
#endif
#if HAS_BED_PROBE
  void Draw_ProbeSet_Menu();
#endif
void Draw_FilSet_Menu();
#if ENABLED(NOZZLE_PARK_FEATURE)
  void Draw_ParkPos_Menu();
#endif
void Draw_PhySet_Menu();
void Draw_SelectColors_Menu();
void Draw_GetColor_Menu();
#if BOTH(CASE_LIGHT_MENU, CASELIGHT_USES_BRIGHTNESS)
  void Draw_CaseLight_Menu();
#endif
#if ENABLED(LED_CONTROL_MENU)
  void Draw_LedControl_Menu();
#endif
void Draw_Tune_Menu();
void Draw_Motion_Menu();
#if ENABLED(ADVANCED_PAUSE_FEATURE)
  void Draw_FilamentMan_Menu();
#endif
#if ENABLED(MESH_BED_LEVELING)
  void Draw_ManualMesh_Menu();
#endif
#if HAS_HOTEND
  void Draw_Preheat1_Menu();
  void Draw_Preheat2_Menu();
  void Draw_Preheat3_Menu();
  void Draw_HotendPID_Menu();
#endif
void Draw_Temperature_Menu();
void Draw_MaxSpeed_Menu();
void Draw_MaxAccel_Menu();
#if HAS_CLASSIC_JERK
  void Draw_MaxJerk_Menu();
#endif
void Draw_Steps_Menu();
#if HAS_HEATED_BED
  void Draw_BedPID_Menu();
#endif
#if EITHER(HAS_BED_PROBE, BABYSTEPPING)
  void Draw_ZOffsetWiz_Menu();
#endif
#if ENABLED(INDIVIDUAL_AXIS_HOMING_SUBMENU)
  void Draw_Homing_Menu();
#endif
#if ENABLED(FWRETRACT)
  void Draw_FWRetract_Menu();
#endif
#if HAS_MESH
  void Draw_MeshSet_Menu();
  #if ENABLED(MESH_EDIT_MENU)
    void Draw_EditMesh_Menu();
  #endif
#endif
=======
  void dwinLockScreen();
  void dwinUnLockScreen();
  void hmiLockScreen();
#endif
#if HAS_MESH
  void dwinMeshViewer();
#endif
#if HAS_ESDIAG
  void drawEndStopDiag();
#endif
#if ALL(PROUI_TUNING_GRAPH, PROUI_ITEM_PLOT)
  void dwinDrawPlot(tempcontrol_t result);
  void drawHPlot();
  void drawBPlot();
#endif

// Menu drawing functions
void drawPrintFileMenu();
void drawControlMenu();
void drawAdvancedSettingsMenu();
void drawPrepareMenu();
void drawMoveMenu();
void drawTrammingMenu();
#if HAS_HOME_OFFSET
  void drawHomeOffsetMenu();
#endif
#if HAS_BED_PROBE
  void drawProbeSetMenu();
#endif
void drawFilSetMenu();
#if ALL(CASE_LIGHT_MENU, CASELIGHT_USES_BRIGHTNESS)
  void drawCaseLightMenu();
#endif
#if ENABLED(LED_CONTROL_MENU)
  void drawLedControlMenu();
#endif
void drawTuneMenu();
void drawMotionMenu();
void drawFilamentManMenu();
#if ENABLED(MESH_BED_LEVELING)
  void drawManualMeshMenu();
#endif
void drawTemperatureMenu();
void drawMaxSpeedMenu();
void drawMaxAccelMenu();
#if ENABLED(CLASSIC_JERK)
  void drawMaxJerkMenu();
#endif
#if ENABLED(EDITABLE_STEPS_PER_UNIT)
  void drawStepsMenu();
#endif
#if ANY(HAS_BED_PROBE, BABYSTEPPING)
  void drawZOffsetWizMenu();
#endif
#if ENABLED(INDIVIDUAL_AXIS_HOMING_SUBMENU)
  void drawHomingMenu();
#endif
#if ENABLED(EDITABLE_HOMING_FEEDRATE)
  void drawHomingFRMenu();
#endif
#if ENABLED(FWRETRACT)
  void drawFWRetractMenu();
#endif
#if HAS_MESH
  void drawMeshSetMenu();
  #if ENABLED(PROUI_MESH_EDIT)
    void drawEditMeshMenu();
  #endif
#endif
#if HAS_TRINAMIC_CONFIG
  void drawTrinamicConfigMenu();
#endif

// Custom colors editing
#if HAS_CUSTOM_COLORS
  void dwinApplyColor();
  void drawSelectColorsMenu();
  void drawGetColorMenu();
#endif

// PID
#if HAS_PID_HEATING
  #include "../../../module/temperature.h"
  void dwinStartM303(const int count, const heater_id_t hid, const celsius_t temp);
  void dwinPIDTuning(tempcontrol_t result);
  #if ANY(PID_AUTOTUNE_MENU, PID_EDIT_MENU)
    #if ENABLED(PIDTEMP)
      #if ENABLED(PID_AUTOTUNE_MENU)
        void hotendPID();
      #endif
      void drawHotendPIDMenu();
    #endif
    #if ENABLED(PIDTEMPBED)
      #if ENABLED(PID_AUTOTUNE_MENU)
        void bedPID();
      #endif
      void drawBedPIDMenu();
    #endif
    #if ENABLED(PIDTEMPCHAMBER)
      #if ENABLED(PID_AUTOTUNE_MENU)
        void chamberPID();
      #endif
      void drawChamberPIDMenu();
    #endif
  #endif
#endif

// MPC
#if ENABLED(MPCTEMP)
  #if ANY(MPC_EDIT_MENU, MPC_AUTOTUNE_MENU)
    void drawHotendMPCMenu();
  #endif
  #if ENABLED(MPC_AUTOTUNE)
    void dwinMPCTuning(tempcontrol_t result);
  #endif
#endif

#if PROUI_TUNING_GRAPH
  void dwinDrawPIDMPCPopup();
#endif
>>>>>>> origin/release-2.1.3-beta2
