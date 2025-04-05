/**
 * Marlin 3D Printer Firmware
<<<<<<<< HEAD:Marlin/src/gcode/control/M282.cpp
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
========
 * Copyright (c) 2024 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/HAL/RP2040/MarlinSerial.cpp
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
<<<<<<<< HEAD:Marlin/src/gcode/control/M282.cpp
========
#include "../platforms.h"

#ifdef __PLAT_RP2040__
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/HAL/RP2040/MarlinSerial.cpp

#include "../../inc/MarlinConfig.h"
#include "MarlinSerial.h"

<<<<<<<< HEAD:Marlin/src/gcode/control/M282.cpp
#if ENABLED(SERVO_DETACH_GCODE)

#include "../gcode.h"
#include "../../module/servo.h"

/**
 * M282: Detach Servo. P<index>
 */
void GcodeSuite::M282() {

  if (!parser.seenval('P')) return;

  const int servo_index = parser.value_int();
  if (WITHIN(servo_index, 0, NUM_SERVOS - 1))
    servo[servo_index].detach();
  else
    SERIAL_ECHO_MSG("Servo ", servo_index, " out of range");

}

#endif // SERVO_DETACH_GCODE
========
#if ENABLED(EMERGENCY_PARSER)
  #include "../../feature/e_parser.h"
#endif

#define _IMPLEMENT_SERIAL(X) DefaultSerial##X MSerial##X(false, Serial##X)
#define IMPLEMENT_SERIAL(X)  _IMPLEMENT_SERIAL(X)
#if WITHIN(SERIAL_PORT, 0, 3)
  IMPLEMENT_SERIAL(SERIAL_PORT);
#endif

#endif // __PLAT_RP2040__
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/HAL/RP2040/MarlinSerial.cpp
