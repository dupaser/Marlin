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
#pragma once

#ifdef STM32F1xx
  #include "stm32f1xx_hal.h"
#elif defined(STM32F4xx)
  #include "stm32f4xx_hal.h"
#elif defined(STM32H7xx)
  #include "stm32h7xx_hal.h"
#else
  #error SPI TFT is currently only supported on STM32F1, STM32F4 and STM32H7 hardware.
#endif

#ifndef LCD_READ_ID
  #define LCD_READ_ID 0x04   // Read display identification information (0xD3 on ILI9341)
#endif
#ifndef LCD_READ_ID4
  #define LCD_READ_ID4 0xD3   // Read display identification information (0xD3 on ILI9341)
#endif

#define DATASIZE_8BIT  SPI_DATASIZE_8BIT
#define DATASIZE_16BIT SPI_DATASIZE_16BIT
<<<<<<< HEAD
#define TFT_IO_DRIVER  TFT_SPI
=======
#define DATASIZE_32BIT SPI_DATASIZE_32BIT
#define TFT_IO_DRIVER  TFT_SPI
#define DMA_MAX_WORDS  0xFFFF
>>>>>>> origin/release-2.1.3-beta2

class TFT_SPI {
private:
  static SPI_HandleTypeDef SPIx;


<<<<<<< HEAD
  static uint32_t ReadID(uint16_t Reg);
  static void Transmit(uint16_t Data);
  static void TransmitDMA(uint32_t MemoryIncrease, uint16_t *Data, uint16_t Count);
  #if ENABLED(USE_SPI_DMA_TC)
    static void TransmitDMA_IT(uint32_t MemoryIncrease, uint16_t *Data, uint16_t Count);
  #endif

public:
  static DMA_HandleTypeDef DMAtx;

  static void Init();
  static uint32_t GetID();
=======
  static uint32_t readID(const uint16_t inReg);
  static void transmit(uint16_t data);
  static void transmit(uint32_t memoryIncrease, uint16_t *data, uint16_t count);
  static void transmitDMA(uint32_t memoryIncrease, uint16_t *data, uint16_t count);
  #if ENABLED(USE_SPI_DMA_TC)
    static void transmitDMA_IT(uint32_t memoryIncrease, uint16_t *data, uint16_t count);
  #endif

public:
  static void init();
  static uint32_t getID();
>>>>>>> origin/release-2.1.3-beta2
  static bool isBusy();
  static void abort();

  static void dataTransferBegin(uint16_t dataWidth=DATASIZE_16BIT);
  static void dataTransferEnd() { WRITE(TFT_CS_PIN, HIGH); __HAL_SPI_DISABLE(&SPIx); };
  static void dataTransferAbort();

  static void writeData(uint16_t data) { transmit(data); }
  static void writeReg(const uint16_t inReg) { WRITE(TFT_A0_PIN, LOW); transmit(inReg); WRITE(TFT_A0_PIN, HIGH); }

<<<<<<< HEAD
  static void WriteSequence(uint16_t *Data, uint16_t Count) { TransmitDMA(DMA_MINC_ENABLE, Data, Count); }

  #if ENABLED(USE_SPI_DMA_TC)
    static void WriteSequenceIT(uint16_t *Data, uint16_t Count) { TransmitDMA_IT(DMA_MINC_ENABLE, Data, Count); }
  #endif

  static void WriteMultiple(uint16_t Color, uint16_t Count) { static uint16_t Data; Data = Color; TransmitDMA(DMA_MINC_DISABLE, &Data, Count); }
  static void WriteMultiple(uint16_t Color, uint32_t Count) {
    static uint16_t Data; Data = Color;
    while (Count > 0) {
      TransmitDMA(DMA_MINC_DISABLE, &Data, Count > 0xFFFF ? 0xFFFF : Count);
      Count = Count > 0xFFFF ? Count - 0xFFFF : 0;
=======
  static void writeSequence_DMA(uint16_t *data, uint16_t count) { transmitDMA(DMA_MINC_ENABLE, data, count); }
  static void writeMultiple_DMA(uint16_t color, uint16_t count) { static uint16_t data; data = color; transmitDMA(DMA_MINC_DISABLE, &data, count); }

  #if ENABLED(USE_SPI_DMA_TC)
    static void writeSequenceIT(uint16_t *data, uint16_t count) { transmitDMA_IT(DMA_MINC_ENABLE, data, count); }
    inline static void DMA_IRQHandler() { HAL_DMA_IRQHandler(&TFT_SPI::DMAtx); }
  #endif

  static void writeSequence(uint16_t *data, uint16_t count) { transmit(DMA_MINC_ENABLE, data, count); }
  static void writeMultiple(uint16_t color, uint32_t count) {
    while (count > 0) {
      transmit(DMA_MINC_DISABLE, &color, count > DMA_MAX_WORDS ? DMA_MAX_WORDS : count);
      count = count > DMA_MAX_WORDS ? count - DMA_MAX_WORDS : 0;
>>>>>>> origin/release-2.1.3-beta2
    }
  }
};
