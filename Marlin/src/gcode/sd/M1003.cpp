/**
 * Marlin 3D Printer Firmware
<<<<<<<< HEAD:Marlin/src/gcode/host/M154.cpp
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
========
 * Copyright (c) 2024 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/gcode/sd/M1003.cpp
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

#include "../../inc/MarlinConfigPre.h"

<<<<<<<< HEAD:Marlin/src/gcode/host/M154.cpp
#if ENABLED(AUTO_REPORT_POSITION)

#include "../gcode.h"
#include "../../module/motion.h"

/**
 * M154: Set position auto-report interval. M154 S<seconds>
 */
void GcodeSuite::M154() {

  if (parser.seenval('S'))
    position_auto_reporter.set_interval(parser.value_byte());

}

#endif // AUTO_REPORT_POSITION
========
#if ENABLED(ONE_CLICK_PRINT)

#include "../gcode.h"
#include "../../sd/cardreader.h"

/**
 * M1003: Set the current dir to /. Should come after 'M24'.
 *        Prevents the SD menu getting stuck in the newest file's workDir.
 */
void GcodeSuite::M1003() { card.cdroot(); }

#endif // ONE_CLICK_PRINT
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/gcode/sd/M1003.cpp
