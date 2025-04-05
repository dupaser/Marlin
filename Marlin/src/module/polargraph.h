/**
 * Marlin 3D Printer Firmware
<<<<<<< HEAD
 * Copyright (c) 2024 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
=======
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>> origin/release-2.1.3-beta2
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
<<<<<<< HEAD
<<<<<<<< HEAD:Marlin/src/module/polargraph.h
=======
>>>>>>> origin/release-2.1.3-beta2
 * polargraph.h - Polargraph-specific functions
 */

#include "../core/types.h"
#include "../core/macros.h"

extern float segments_per_second;
extern xy_pos_t draw_area_min, draw_area_max;
<<<<<<< HEAD
extern xy_float_t draw_area_size;
extern float polargraph_max_belt_len;

void inverse_kinematics(const xyz_pos_t &raw);
========
 * Define SPI Pins: SCK, MISO, MOSI, SS
 */
#ifndef SD_SCK_PIN
  #define SD_SCK_PIN  PIN_SPI_SCK
#endif
#ifndef SD_MISO_PIN
  #define SD_MISO_PIN PIN_SPI_MISO
#endif
#ifndef SD_MOSI_PIN
  #define SD_MOSI_PIN PIN_SPI_MOSI
#endif
#ifndef SD_SS_PIN
  #define SD_SS_PIN   PIN_SPI_SS
#endif
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/HAL/RP2040/spi_pins.h
=======
extern float polargraph_max_belt_len;

void inverse_kinematics(const xyz_pos_t &raw);
>>>>>>> origin/release-2.1.3-beta2
