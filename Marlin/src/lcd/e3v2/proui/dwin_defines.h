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
 * DWIN general defines and data structs for PRO UI
<<<<<<< HEAD
 * Author: Miguel A. Risco-Castillo (MRISCOC)
 * Version: 3.11.2
 * Date: 2022/02/28
 */

#define HAS_GCODE_PREVIEW 1
#define HAS_PIDPLOT 1
#define HAS_ESDIAG 1
#define HAS_LOCKSCREEN 1
//#define DEBUG_DWIN 1
//#define NEED_HEX_PRINT 1

#include "../../../inc/MarlinConfigPre.h"
#include "../common/dwin_color.h"
#if ENABLED(LED_CONTROL_MENU)
  #include "../../../feature/leds/leds.h"
#endif
#include <stddef.h>
=======
 * Based on the original work of: Miguel Risco-Castillo (MRISCOC)
 * https://github.com/mriscoc/Ender3V2S1
 * Version: 3.12.2
 * Date: 2022/08/08
 */

#include "../../../inc/MarlinConfigPre.h"

//#define TJC_DISPLAY           // Enable for TJC display
//#define DACAI_DISPLAY         // Enable for DACAI display
//#define TITLE_CENTERED        // Center Menu Title Text

#if HAS_MESH
  #define PROUI_MESH_EDIT       // Add a menu to edit mesh points
  #if ENABLED(PROUI_MESH_EDIT)
    #define Z_OFFSET_MIN  -3.0  // (mm)
    #define Z_OFFSET_MAX   3.0  // (mm)
  #endif
#endif
>>>>>>> origin/release-2.1.3-beta2

#if defined(__STM32F1__) || defined(STM32F1)
  #define DASH_REDRAW 1
#endif

<<<<<<< HEAD
#define Def_Background_Color  RGB( 1, 12,  8)
#define Def_Cursor_color      RGB(20, 49, 31)
#define Def_TitleBg_color     RGB( 0, 23, 16)
#define Def_TitleTxt_color    Color_White
#define Def_Text_Color        Color_White
#define Def_Selected_Color    Select_Color
#define Def_SplitLine_Color   RGB( 0, 23, 16)
#define Def_Highlight_Color   Color_White
#define Def_StatusBg_Color    RGB( 0, 23, 16)
#define Def_StatusTxt_Color   Color_Yellow
#define Def_PopupBg_color     Color_Bg_Window
#define Def_PopupTxt_Color    Popup_Text_Color
#define Def_AlertBg_Color     Color_Bg_Red
#define Def_AlertTxt_Color    Color_Yellow
#define Def_PercentTxt_Color  Percent_Color
#define Def_Barfill_Color     BarFill_Color
#define Def_Indicator_Color   Color_White
#define Def_Coordinate_Color  Color_White
#define Def_Button_Color      RGB( 0, 23, 16)
#if BOTH(LED_CONTROL_MENU, HAS_COLOR_LEDS)
  #define Def_Leds_Color      LEDColorWhite()
#endif

typedef struct {
  // Color settings
  uint16_t Background_Color = Def_Background_Color;
  uint16_t Cursor_color     = Def_Cursor_color;
  uint16_t TitleBg_color    = Def_TitleBg_color;
  uint16_t TitleTxt_color   = Def_TitleTxt_color;
  uint16_t Text_Color       = Def_Text_Color;
  uint16_t Selected_Color   = Def_Selected_Color;
  uint16_t SplitLine_Color  = Def_SplitLine_Color;
  uint16_t Highlight_Color  = Def_Highlight_Color;
  uint16_t StatusBg_Color   = Def_StatusBg_Color;
  uint16_t StatusTxt_Color  = Def_StatusTxt_Color;
  uint16_t PopupBg_color    = Def_PopupBg_color;
  uint16_t PopupTxt_Color   = Def_PopupTxt_Color;
  uint16_t AlertBg_Color    = Def_AlertBg_Color;
  uint16_t AlertTxt_Color   = Def_AlertTxt_Color;
  uint16_t PercentTxt_Color = Def_PercentTxt_Color;
  uint16_t Barfill_Color    = Def_Barfill_Color;
  uint16_t Indicator_Color  = Def_Indicator_Color;
  uint16_t Coordinate_Color = Def_Coordinate_Color;
  // Temperatures
  #if HAS_HOTEND && defined(PREHEAT_1_TEMP_HOTEND)
    int16_t HotendPidT = PREHEAT_1_TEMP_HOTEND;
  #endif
  #if HAS_HEATED_BED && defined(PREHEAT_1_TEMP_BED)
    int16_t BedPidT = PREHEAT_1_TEMP_BED;
  #endif
  #if HAS_HOTEND || HAS_HEATED_BED
    int16_t PidCycles = 10;
  #endif
  #if ENABLED(PREVENT_COLD_EXTRUSION)
    int16_t ExtMinT = EXTRUDE_MINTEMP;
  #endif
  #if BOTH(HAS_HEATED_BED, PREHEAT_BEFORE_LEVELING)
    int16_t BedLevT = LEVELING_BED_TEMP;
  #endif
  #if ENABLED(BAUD_RATE_GCODE)
    bool Baud115K = false;
  #endif
  bool FullManualTramming = false;
  #if ENABLED(MESH_BED_LEVELING)
    float ManualZOffset = 0;
  #endif
  // Led
  #if BOTH(LED_CONTROL_MENU, HAS_COLOR_LEDS)
    LEDColor Led_Color = Def_Leds_Color;
  #endif
} HMI_data_t;

static constexpr size_t eeprom_data_size = sizeof(HMI_data_t);
extern HMI_data_t HMI_data;
=======
#if DISABLED(PROBE_MANUALLY) && ANY(AUTO_BED_LEVELING_BILINEAR, AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_3POINT, AUTO_BED_LEVELING_UBL)
  #define HAS_ONESTEP_LEVELING 1
#endif

#if !HAS_BED_PROBE && ENABLED(BABYSTEPPING)
  #define JUST_BABYSTEP 1
#endif

#if ANY(BABYSTEPPING, HAS_BED_PROBE, HAS_WORKSPACE_OFFSET)
  #define HAS_ZOFFSET_ITEM 1
#endif

#define defColorBackground  RGB(1, 12, 8)
#define defColorCursor      RGB(20, 49, 31)
#define defColorTitleBg     RGB(0, 23, 16)
#define defColorTitleTxt    COLOR_WHITE
#define defColorText        COLOR_WHITE
#define defColorSelected    COLOR_SELECT
#define defColorSplitLine   RGB(0, 23, 16)
#define defColorHighlight   COLOR_WHITE
#define defColorStatusBg    RGB(0, 23, 16)
#define defColorStatusTxt   COLOR_YELLOW
#define defColorPopupBg     COLOR_BG_WINDOW
#define defColorPopupTxt    COLOR_POPUP_TEXT
#define defColorAlertBg     COLOR_BG_RED
#define defColorAlertTxt    COLOR_YELLOW
#define defColorPercentTxt  COLOR_PERCENT
#define defColorBarfill     COLOR_BARFILL
#define defColorIndicator   COLOR_WHITE
#define defColorCoordinate  COLOR_WHITE
#define defColorButton      RGB(0, 23, 16)
#if ALL(LED_CONTROL_MENU, HAS_COLOR_LEDS)
  #define defColorLeds      LEDColorWhite()
#endif
#if CASELIGHT_USES_BRIGHTNESS
  #define defCaseLightBrightness 255
#endif

#ifdef Z_AFTER_HOMING
  #define DEF_Z_AFTER_HOMING Z_AFTER_HOMING
#else
  #define DEF_Z_AFTER_HOMING 0
#endif

#ifdef PREHEAT_1_TEMP_HOTEND
  #define DEF_HOTENDPIDT PREHEAT_1_TEMP_HOTEND
#else
  #define DEF_HOTENDPIDT 195
#endif
#ifdef PREHEAT_1_TEMP_BED
  #define DEF_BEDPIDT PREHEAT_1_TEMP_BED
#else
  #define DEF_BEDPIDT 60
#endif
#ifdef PREHEAT_1_TEMP_CHAMBER
  #define DEF_CHAMBERPIDT PREHEAT_1_TEMP_CHAMBER
#else
  #define DEF_CHAMBERPIDT 0
#endif
#define DEF_PIDCYCLES 5

/**
 * ProUI internal feature flags
 */
#if ALL(SDCARD_SORT_ALPHA, SDSORT_GCODE)
  #define PROUI_MEDIASORT     // Enable option to sort G-code files
#endif
#if ENABLED(POWER_LOSS_RECOVERY)
  #define PROUI_ITEM_PLR      // Tune > Power-loss Recovery
#endif
#if ENABLED(HAS_JUNCTION_DEVIATION)
  #define PROUI_ITEM_JD       // Tune > Junction Deviation
#endif
#if ENABLED(LIN_ADVANCE)
  #define PROUI_ITEM_ADVK     // Tune > Linear Advance
#endif
#if ANY(HAS_PID_HEATING, MPC_AUTOTUNE) && DISABLED(DISABLE_TUNING_GRAPH)
  #define PROUI_TUNING_GRAPH 1
#endif
#if PROUI_TUNING_GRAPH
  #define PROUI_ITEM_PLOT     // Plot temp graph viewer
#endif
#define HAS_GCODE_PREVIEW 1   // Preview G-code model thumbnail
#define HAS_CUSTOM_COLORS 1   // Change display colors
#define HAS_ESDIAG 1          // View End-stop/Runout switch continuity
#define HAS_LOCKSCREEN 1      // Simple lockscreen
#define HAS_SD_EXTENDER 1     // Enable to support SD card extender cables
>>>>>>> origin/release-2.1.3-beta2
