/**
 * Marlin 3D Printer Firmware
<<<<<<<< HEAD:Marlin/src/HAL/LINUX/MarlinSPI.h
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
========
 * Copyright (c) 2024 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/feature/mmu3/mmu3_power.h
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

<<<<<<<< HEAD:Marlin/src/HAL/LINUX/MarlinSPI.h
#include <SPI.h>

using MarlinSPI = SPIClass;
========
/**
 * mmu2_power.h
 */

namespace MMU3 {

void power_on();

void power_off();

void power_reset();

} // MMU3
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/feature/mmu3/mmu3_power.h
