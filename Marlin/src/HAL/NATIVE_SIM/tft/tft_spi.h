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

#include "../../../inc/MarlinConfig.h"

#ifndef LCD_READ_ID
  #define LCD_READ_ID  0x04   // Read display identification information (0xD3 on ILI9341)
#endif
#ifndef LCD_READ_ID4
  #define LCD_READ_ID4 0xD3   // Read display identification information (0xD3 on ILI9341)
#endif

#define DATASIZE_8BIT    8
<<<<<<< HEAD
#define DATASIZE_16BIT   16
#define TFT_IO_DRIVER TFT_SPI

#define DMA_MINC_ENABLE 1
=======
#define DATASIZE_16BIT  16
#define TFT_IO_DRIVER   TFT_SPI
#define DMA_MAX_WORDS   0xFFFF

#define DMA_MINC_ENABLE  1
>>>>>>> origin/release-2.1.3-beta2
#define DMA_MINC_DISABLE 0

class TFT_SPI {
private:
<<<<<<< HEAD
  static uint32_t ReadID(uint16_t Reg);
  static void Transmit(uint16_t Data);
  static void TransmitDMA(uint32_t MemoryIncrease, uint16_t *Data, uint16_t Count);
=======
  static uint32_t readID(const uint16_t inReg);
  static void transmit(uint16_t data);
  static void transmitDMA(uint32_t memoryIncrease, uint16_t *data, uint16_t count);
>>>>>>> origin/release-2.1.3-beta2

public:
  // static SPIClass SPIx;

<<<<<<< HEAD
  static void Init();
  static uint32_t GetID();
  static bool isBusy();
  static void Abort();

  static void DataTransferBegin(uint16_t DataWidth = DATASIZE_16BIT);
  static void DataTransferEnd();
  static void DataTransferAbort();

  static void WriteData(uint16_t Data);
  static void WriteReg(uint16_t Reg);

  static void WriteSequence(uint16_t *Data, uint16_t Count);
  // static void WriteMultiple(uint16_t Color, uint16_t Count);
  static void WriteMultiple(uint16_t Color, uint32_t Count);
=======
  static void init();
  static uint32_t getID();
  static bool isBusy();
  static void abort();

  static void dataTransferBegin(uint16_t dataWidth=DATASIZE_16BIT);
  static void dataTransferEnd();
  static void dataTransferAbort();

  static void writeData(uint16_t data);
  static void writeReg(const uint16_t inReg);

  static void writeSequence_DMA(uint16_t *data, uint16_t count) { writeSequence(data, count); }
  static void writeMultiple_DMA(uint16_t color, uint16_t count) { writeMultiple(color, count); }

  static void writeSequence(uint16_t *data, uint16_t count);
  static void writeMultiple(uint16_t color, uint32_t count);
>>>>>>> origin/release-2.1.3-beta2
};
