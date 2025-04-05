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

#include "../../inc/MarlinConfig.h"

#if HAS_MEDIA

#include "../gcode.h"
#include "../../sd/cardreader.h"

<<<<<<< HEAD
#if ENABLED(DWIN_LCD_PROUI)
  #include "../../lcd/e3v2/proui/dwin.h"
=======
#if ENABLED(EXTENSIBLE_UI)
  #include "../../lcd/extui/ui_api.h"
>>>>>>> origin/release-2.1.3-beta2
#endif

/**
 * M524: Abort the current SD print job (started with M24)
 */
void GcodeSuite::M524() {

<<<<<<< HEAD
  #if ENABLED(DWIN_LCD_PROUI)

    HMI_flag.abort_flag = true;    // The LCD will handle it
=======
  #if ENABLED(EXTENSIBLE_UI)

    ExtUI::stopPrint(); // Calls ui.abort_print() which does the same as below
>>>>>>> origin/release-2.1.3-beta2

  #else

    if (IS_SD_PRINTING())
      card.abortFilePrintSoon();
    else if (card.isMounted())
      card.closefile();

  #endif

}

#endif // HAS_MEDIA
