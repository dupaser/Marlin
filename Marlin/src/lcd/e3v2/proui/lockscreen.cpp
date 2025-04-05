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

/**
 * Lock screen implementation for PRO UI
<<<<<<< HEAD
 * Author: Miguel A. Risco-Castillo (MRISCOC)
 * Version: 2.2.0
 * Date: 2022/04/11
=======
 * Based on the original work of: Miguel Risco-Castillo (MRISCOC)
 * https://github.com/mriscoc/Ender3V2S1
 * Version: 2.3.2
 * Date: 2022/11/20
>>>>>>> origin/release-2.1.3-beta2
 */

#include "../../../inc/MarlinConfigPre.h"

#if ENABLED(DWIN_LCD_PROUI)

#include "dwin_defines.h"

#if HAS_LOCKSCREEN

<<<<<<< HEAD
#include "dwinui.h"
#include "dwin.h"
#include "lockscreen.h"

LockScreenClass lockScreen;

uint8_t LockScreenClass::lock_pos = 0;
bool LockScreenClass::unlocked = false;
uint8_t LockScreenClass::rprocess = 0;

void LockScreenClass::init() {
=======
#include "dwin.h"
#include "lockscreen.h"

LockScreen lockScreen;

uint8_t LockScreen::lock_pos = 0;
bool LockScreen::unlocked = false;
uint8_t LockScreen::rprocess = 0;

void LockScreen::init() {
>>>>>>> origin/release-2.1.3-beta2
  lock_pos = 0;
  unlocked = false;
  draw();
}

<<<<<<< HEAD
void LockScreenClass::draw() {
  Title.SetCaption(GET_TEXT_F(MSG_LOCKSCREEN));
  DWINUI::ClearMainArea();
  DWINUI::Draw_Icon(ICON_LOGO, 71, 120);  // CREALITY logo
  DWINUI::Draw_CenteredString(Color_White, 180, GET_TEXT_F(MSG_LOCKSCREEN_LOCKED));
  DWINUI::Draw_CenteredString(Color_White, 200, GET_TEXT_F(MSG_LOCKSCREEN_UNLOCK));
  DWINUI::Draw_CenteredString(Color_White, 240, F("-> | <-"));
  DWIN_Draw_Box(1, HMI_data.Barfill_Color, 0, 260, DWIN_WIDTH, 20);
  DWIN_Draw_VLine(Color_Yellow, lock_pos * DWIN_WIDTH / 255, 260, 20);
  DWIN_UpdateLCD();
}

void LockScreenClass::onEncoder(EncoderState encoder_diffState) {
=======
void LockScreen::draw() {
  title.setCaption(GET_TEXT_F(MSG_LOCKSCREEN));
  DWINUI::clearMainArea();
  DWINUI::drawIcon(ICON_LOGO, 71, 120);  // CREALITY logo
  DWINUI::drawCenteredString(COLOR_WHITE, 180, GET_TEXT_F(MSG_LOCKSCREEN_LOCKED));
  DWINUI::drawCenteredString(COLOR_WHITE, 200, GET_TEXT_F(MSG_LOCKSCREEN_UNLOCK));
  DWINUI::drawCenteredString(COLOR_WHITE, 240, F("-> | <-"));
  dwinDrawBox(1, hmiData.colorBarfill, 0, 260, DWIN_WIDTH, 20);
  dwinDrawVLine(COLOR_YELLOW, lock_pos * DWIN_WIDTH / 255, 260, 20);
  dwinUpdateLCD();
}

void LockScreen::onEncoder(EncoderState encoder_diffState) {
>>>>>>> origin/release-2.1.3-beta2
  switch (encoder_diffState) {
    case ENCODER_DIFF_CW:    lock_pos += 8; break;
    case ENCODER_DIFF_CCW:   lock_pos -= 8; break;
    case ENCODER_DIFF_ENTER: unlocked = (lock_pos == 128); break;
    default: break;
  }
<<<<<<< HEAD
  DWIN_Draw_Box(1, HMI_data.Barfill_Color, 0, 260, DWIN_WIDTH, 20);
  DWIN_Draw_VLine(Color_Yellow, lock_pos * DWIN_WIDTH / 255, 260, 20);
  DWIN_UpdateLCD();
}

#endif // HAS_LOCKSCREEN

=======
  dwinDrawBox(1, hmiData.colorBarfill, 0, 260, DWIN_WIDTH, 20);
  dwinDrawVLine(COLOR_YELLOW, lock_pos * DWIN_WIDTH / 255, 260, 20);
  dwinUpdateLCD();
}

#endif // HAS_LOCKSCREEN
>>>>>>> origin/release-2.1.3-beta2
#endif // DWIN_LCD_PROUI
