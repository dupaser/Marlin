<<<<<<< HEAD
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
=======
/*****************************
 * custom_user_menu.cpp *
 *****************************/

/****************************************************************************
 *   Written By Brian Kahl      2023 - FAME3D.                              *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <https://www.gnu.org/licenses/>.                             *
 ****************************************************************************/
>>>>>>> origin/release-2.1.3-beta2

#include "../config.h"
#include "../screens.h"

#ifdef FTDI_CUSTOM_USER_MENUS

using namespace FTDI;
using namespace ExtUI;
using namespace Theme;

#define _ITEM_TAG(N) (10+N)
#define _USER_DESC(N) MAIN_MENU_ITEM_##N##_DESC
#define _USER_GCODE(N) MAIN_MENU_ITEM_##N##_GCODE
#define _USER_ITEM(N) .tag(_ITEM_TAG(N)).button(USER_ITEM_POS(N), _USER_DESC(N))
<<<<<<< HEAD
#define _USER_ACTION(N) case _ITEM_TAG(N): injectCommands(F(_USER_GCODE(N))); TERN_(USER_SCRIPT_RETURN, GOTO_SCREEN(StatusScreen)); break;
=======
#define _USER_ACTION(N) case _ITEM_TAG(N): injectCommands(F(_USER_GCODE(N))); TERN_(CUSTOM_MENU_MAIN_SCRIPT_RETURN, GOTO_SCREEN(StatusScreen)); break;
>>>>>>> origin/release-2.1.3-beta2

void CustomUserMenus::onRedraw(draw_mode_t what) {
  if (what & BACKGROUND) {
    CommandProcessor cmd;
    cmd.cmd(CLEAR_COLOR_RGB(Theme::bg_color))
       .cmd(CLEAR(true, true, true));
  }

<<<<<<< HEAD
  #if HAS_USER_ITEM(16, 17, 18, 19, 20)
    #define _MORE_THAN_FIFTEEN 1
  #else
    #define _MORE_THAN_FIFTEEN 0
  #endif
  #if _MORE_THAN_FIFTEEN || HAS_USER_ITEM(11, 12, 13, 14, 15)
    #define _MORE_THAN_TEN 1
  #else
    #define _MORE_THAN_TEN 0
  #endif

  #if ENABLED(TOUCH_UI_PORTRAIT)
    #define GRID_COLS (1 + _MORE_THAN_TEN)
    #define GRID_ROWS 11
    #define USER_ITEM_POS(N) BTN_POS((1+((N-1)/10)), ((N-1) % 10 + 1)), BTN_SIZE(1,1)
    #define BACK_POS         BTN_POS(1,11), BTN_SIZE(1,1)
  #else
    #if _MORE_THAN_TEN || HAS_USER_ITEM(6, 7, 8, 9, 10)
      #define _MORE_THAN_FIVE 1
    #else
      #define _MORE_THAN_FIVE 0
    #endif
    #define GRID_COLS (1 + _MORE_THAN_FIVE + _MORE_THAN_TEN + _MORE_THAN_FIFTEEN)
    #define GRID_ROWS 6
    #define USER_ITEM_POS(N) BTN_POS((1+((N-1)/5)), ((N-1) % 5 + 1)), BTN_SIZE(1,1)
    #define BACK_POS         BTN_POS(1,6), BTN_SIZE(GRID_COLS,1)
  #endif

=======
  #if ENABLED(TOUCH_UI_PORTRAIT)
    #if defined(TOOLHEAD_Legacy_Universal)
      #define GRID_ROWS 10
    #else
      #define GRID_ROWS 7
    #endif
    #define GRID_COLS 1
    #define TOOLHEAD_LABL_POS BTN_POS(1, 1), BTN_SIZE(GRID_COLS,1)
    #define USER_ITEM_POS(N)  BTN_POS(1, N), BTN_SIZE(GRID_COLS,1)
    #define TOOLHEAD_SWAP_POS BTN_POS(1,GRID_ROWS-1), BTN_SIZE(GRID_COLS,1)
    #define BACK_POS          BTN_POS(1,GRID_ROWS), BTN_SIZE(GRID_COLS,1)
  #else
    #define GRID_ROWS 9
    #define GRID_COLS 1
    #define TOOLHEAD_LABL_POS BTN_POS(1, 1), BTN_SIZE(GRID_COLS,1)
    #define USER_ITEM_POS(N)  BTN_POS(1, N), BTN_SIZE(GRID_COLS,1)
    #define TOOLHEAD_SWAP_POS BTN_POS(1,GRID_ROWS-1), BTN_SIZE(GRID_COLS,1)
    #define BACK_POS          BTN_POS(1,GRID_ROWS), BTN_SIZE(GRID_COLS,1)
  #endif

btn_colors thcolor[8] = {normal_btn};


//.color(TH_color[1])
>>>>>>> origin/release-2.1.3-beta2
  if (what & FOREGROUND) {
    CommandProcessor cmd;
    cmd.colors(normal_btn)
       .font(Theme::font_medium)
<<<<<<< HEAD
       #if HAS_USER_ITEM(1)
        _USER_ITEM(1)
       #endif
       #if HAS_USER_ITEM(2)
        _USER_ITEM(2)
       #endif
       #if HAS_USER_ITEM(3)
        _USER_ITEM(3)
       #endif
       #if HAS_USER_ITEM(4)
        _USER_ITEM(4)
       #endif
       #if HAS_USER_ITEM(5)
        _USER_ITEM(5)
       #endif
       #if HAS_USER_ITEM(6)
        _USER_ITEM(6)
       #endif
       #if HAS_USER_ITEM(7)
        _USER_ITEM(7)
       #endif
       #if HAS_USER_ITEM(8)
        _USER_ITEM(8)
       #endif
       #if HAS_USER_ITEM(9)
        _USER_ITEM(9)
       #endif
       #if HAS_USER_ITEM(10)
        _USER_ITEM(10)
       #endif
       #if HAS_USER_ITEM(11)
        _USER_ITEM(11)
       #endif
       #if HAS_USER_ITEM(12)
        _USER_ITEM(12)
       #endif
       #if HAS_USER_ITEM(13)
        _USER_ITEM(13)
       #endif
       #if HAS_USER_ITEM(14)
        _USER_ITEM(14)
       #endif
       #if HAS_USER_ITEM(15)
        _USER_ITEM(15)
       #endif
       #if HAS_USER_ITEM(16)
        _USER_ITEM(16)
       #endif
       #if HAS_USER_ITEM(17)
        _USER_ITEM(17)
       #endif
       #if HAS_USER_ITEM(18)
        _USER_ITEM(18)
       #endif
       #if HAS_USER_ITEM(19)
        _USER_ITEM(19)
       #endif
       #if HAS_USER_ITEM(20)
        _USER_ITEM(20)
       #endif
      .colors(action_btn)
      .tag(1).button(BACK_POS, GET_TEXT_F(MSG_BUTTON_DONE));
=======
       .tag(0).text(TOOLHEAD_LABL_POS, GET_TEXT_F(MSG_CUSTOM_MENU_MAIN_TITLE));
    cmd.colors(accent_btn)
       .font(Theme::font_medium)
       #if defined(MAIN_MENU_ITEM_1_DESC)
        //_USER_ITEM(1)
        .tag(_ITEM_TAG(11)).button(USER_ITEM_POS(1), MAIN_MENU_ITEM_1_DESC)
       #endif
      .colors(thcolor[1])
       #if defined(MAIN_MENU_ITEM_2_DESC)
        //_USER_ITEM(2)
        .tag(_ITEM_TAG(12)).button(USER_ITEM_POS(2), MAIN_MENU_ITEM_2_DESC)
       #endif
       .colors(thcolor[2])
       #if defined(MAIN_MENU_ITEM_3_DESC)
        //_USER_ITEM(3)
        .tag(_ITEM_TAG(13)).button(USER_ITEM_POS(3), MAIN_MENU_ITEM_3_DESC)
       #endif
       .colors(thcolor[3])
       #if defined(MAIN_MENU_ITEM_4_DESC)
        //_USER_ITEM(4)
        .tag(_ITEM_TAG(14)).button(USER_ITEM_POS(4), MAIN_MENU_ITEM_4_DESC)
       #endif
       .colors(thcolor[4])
       #if defined(MAIN_MENU_ITEM_5_DESC)
        //_USER_ITEM(5)
        .tag(_ITEM_TAG(15)).button(USER_ITEM_POS(5), MAIN_MENU_ITEM_5_DESC)
       #endif
       .colors(thcolor[5])
       #if defined(MAIN_MENU_ITEM_6_DESC)
        //_USER_ITEM(6)
        .tag(_ITEM_TAG(16)).button(USER_ITEM_POS(6), MAIN_MENU_ITEM_6_DESC)
       #endif
       .colors(thcolor[6])
       #if defined(MAIN_MENU_ITEM_7_DESC)
        //_USER_ITEM(7)
        .tag(_ITEM_TAG(17)).button(USER_ITEM_POS(7), MAIN_MENU_ITEM_7_DESC)
       #endif
       .colors(thcolor[7])
       #if defined(MAIN_MENU_ITEM_8_DESC)
        //_USER_ITEM(8)
        .tag(_ITEM_TAG(18)).button(USER_ITEM_POS(8), MAIN_MENU_ITEM_8_DESC)
       #endif

       #if DISABLED(TOOLHEAD_Legacy_Universal)
        #undef GRID_ROWS
        #define GRID_ROWS 8
       #endif
      #ifdef PARKING_COMMAND_GCODE
        .tag(20).colors(normal_btn).button(TOOLHEAD_SWAP_POS, GET_TEXT_F(MSG_TOOL_HEAD_SWAP))
      #endif
      .tag(1).colors(action_btn).button(BACK_POS, GET_TEXT_F(MSG_BUTTON_DONE));
>>>>>>> origin/release-2.1.3-beta2
  }
}

bool CustomUserMenus::onTouchEnd(uint8_t tag) {
  switch (tag) {
<<<<<<< HEAD
    #if HAS_USER_ITEM(1)
      _USER_ACTION(1)
    #endif
    #if HAS_USER_ITEM(2)
      _USER_ACTION(2)
    #endif
    #if HAS_USER_ITEM(3)
      _USER_ACTION(3)
    #endif
    #if HAS_USER_ITEM(4)
      _USER_ACTION(4)
    #endif
    #if HAS_USER_ITEM(5)
      _USER_ACTION(5)
    #endif
    #if HAS_USER_ITEM(6)
      _USER_ACTION(6)
    #endif
    #if HAS_USER_ITEM(7)
      _USER_ACTION(7)
    #endif
    #if HAS_USER_ITEM(8)
      _USER_ACTION(8)
    #endif
    #if HAS_USER_ITEM(9)
      _USER_ACTION(9)
    #endif
    #if HAS_USER_ITEM(10)
      _USER_ACTION(10)
    #endif
    #if HAS_USER_ITEM(11)
      _USER_ACTION(11)
    #endif
    #if HAS_USER_ITEM(12)
      _USER_ACTION(12)
    #endif
    #if HAS_USER_ITEM(13)
      _USER_ACTION(13)
    #endif
    #if HAS_USER_ITEM(14)
      _USER_ACTION(14)
    #endif
    #if HAS_USER_ITEM(15)
      _USER_ACTION(15)
    #endif
    #if HAS_USER_ITEM(16)
      _USER_ACTION(16)
    #endif
    #if HAS_USER_ITEM(17)
      _USER_ACTION(17)
    #endif
    #if HAS_USER_ITEM(18)
      _USER_ACTION(18)
    #endif
    #if HAS_USER_ITEM(19)
      _USER_ACTION(19)
    #endif
    #if HAS_USER_ITEM(20)
      _USER_ACTION(20)
    #endif

    case 1: GOTO_PREVIOUS(); break;
=======
    #if defined(MAIN_MENU_ITEM_1_DESC)
      //_USER_ACTION(1)
      case _ITEM_TAG(11): injectCommands_P(PSTR(MAIN_MENU_ITEM_1_GCODE));sound.play(chimes, PLAY_ASYNCHRONOUS); GOTO_SCREEN(StatusScreen); break;
    #endif
    #if defined(MAIN_MENU_ITEM_2_DESC)
      //_USER_ACTION(2)
      case _ITEM_TAG(12): injectCommands_P(PSTR(MAIN_MENU_ITEM_2_GCODE));sound.play(chimes, PLAY_ASYNCHRONOUS); GOTO_SCREEN(StatusScreen); break;
    #endif
    #if defined(MAIN_MENU_ITEM_3_DESC)
      //_USER_ACTION(3)
      case _ITEM_TAG(13): injectCommands_P(PSTR(MAIN_MENU_ITEM_3_GCODE));sound.play(chimes, PLAY_ASYNCHRONOUS); GOTO_SCREEN(StatusScreen); break;
    #endif
    #if defined(MAIN_MENU_ITEM_4_DESC)
      //_USER_ACTION(4)
      case _ITEM_TAG(14): injectCommands_P(PSTR(MAIN_MENU_ITEM_4_GCODE));sound.play(chimes, PLAY_ASYNCHRONOUS); GOTO_SCREEN(StatusScreen); break;
    #endif
    #if defined(MAIN_MENU_ITEM_5_DESC)
      //_USER_ACTION(5)
      case _ITEM_TAG(15): injectCommands_P(PSTR(MAIN_MENU_ITEM_5_GCODE));sound.play(chimes, PLAY_ASYNCHRONOUS); GOTO_SCREEN(StatusScreen); break;
    #endif
    #if defined(MAIN_MENU_ITEM_6_DESC)
      //_USER_ACTION(6)
      case _ITEM_TAG(16): injectCommands_P(PSTR(MAIN_MENU_ITEM_6_GCODE));sound.play(chimes, PLAY_ASYNCHRONOUS); GOTO_SCREEN(StatusScreen); break;
    #endif
    #if defined(MAIN_MENU_ITEM_7_DESC)
      //_USER_ACTION(7)
      case _ITEM_TAG(17): injectCommands_P(PSTR(MAIN_MENU_ITEM_7_GCODE));sound.play(chimes, PLAY_ASYNCHRONOUS); GOTO_SCREEN(StatusScreen);break;
    #endif
    #if defined(MAIN_MENU_ITEM_8_DESC)
      //_USER_ACTION(8)
      case _ITEM_TAG(18): injectCommands_P(PSTR(MAIN_MENU_ITEM_8_GCODE));sound.play(chimes, PLAY_ASYNCHRONOUS); GOTO_SCREEN(StatusScreen);break;
    #endif

    case 1: GOTO_PREVIOUS(); break;
    #ifdef PARKING_COMMAND_GCODE
      case 20: injectCommands(F(PARKING_COMMAND_GCODE)); break;
    #endif
>>>>>>> origin/release-2.1.3-beta2
    default: return false;
  }
  return true;
}

#endif // FTDI_CUSTOM_USER_MENUS
