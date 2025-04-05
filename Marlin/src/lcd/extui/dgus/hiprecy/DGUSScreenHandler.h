/**
 * Marlin 3D Printer Firmware
<<<<<<< HEAD
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
=======
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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

<<<<<<< HEAD
=======
<<<<<<<< HEAD:Marlin/src/HAL/STM32/sdio.h
#define SDIO_D0_PIN   PC8
#define SDIO_D1_PIN   PC9
#define SDIO_D2_PIN   PC10
#define SDIO_D3_PIN   PC11
#define SDIO_CK_PIN   PC12
#define SDIO_CMD_PIN  PD2
========
>>>>>>> origin/release-2.1.3-beta2
#include "../DGUSScreenHandlerBase.h"

typedef DGUSScreenHandler DGUSScreenHandlerClass;

#if ENABLED(POWER_LOSS_RECOVERY)
<<<<<<< HEAD
  #define PLR_SCREEN_RECOVER DGUSLCD_SCREEN_SDPRINTMANIPULATION
  #define PLR_SCREEN_CANCEL DGUSLCD_SCREEN_STATUS
#endif
=======
  #define PLR_SCREEN_RECOVER DGUS_SCREEN_SDPRINTMANIPULATION
  #define PLR_SCREEN_CANCEL DGUS_SCREEN_STATUS
#endif
>>>>>>>> origin/release-2.1.3-beta2:Marlin/src/lcd/extui/dgus/hiprecy/DGUSScreenHandler.h
>>>>>>> origin/release-2.1.3-beta2
