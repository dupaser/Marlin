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

#include "../../inc/MarlinConfig.h"

#if HAS_SPI_TFT
  #include HAL_PATH(../.., tft/tft_spi.h)
#elif HAS_FSMC_TFT
  #include HAL_PATH(../.., tft/tft_fsmc.h)
#elif HAS_LTDC_TFT
  #include HAL_PATH(../.., tft/tft_ltdc.h)
#else
  #error "TFT IO only supports SPI, FSMC or LTDC interface."
#endif

<<<<<<< HEAD
#define TFT_EXCHANGE_XY _BV32(1)
#define TFT_INVERT_X    _BV32(2)
#define TFT_INVERT_Y    _BV32(3)

#define TFT_NO_ROTATION           (0x00)
#define TFT_ROTATE_90             (TFT_EXCHANGE_XY | TFT_INVERT_X)
#define TFT_ROTATE_180            (TFT_INVERT_X    | TFT_INVERT_Y)
#define TFT_ROTATE_270            (TFT_EXCHANGE_XY | TFT_INVERT_Y)

#define TFT_MIRROR_X              (TFT_INVERT_Y)
#define TFT_MIRROR_Y              (TFT_INVERT_X)

#define TFT_ROTATE_90_MIRROR_X    (TFT_ROTATE_90 ^ TFT_INVERT_Y)
#define TFT_ROTATE_90_MIRROR_Y    (TFT_ROTATE_90 ^ TFT_INVERT_X)

#define TFT_ROTATE_180_MIRROR_X   (TFT_ROTATE_180 ^ TFT_INVERT_Y)
#define TFT_ROTATE_180_MIRROR_Y   (TFT_ROTATE_180 ^ TFT_INVERT_X)

#define TFT_ROTATE_270_MIRROR_X   (TFT_ROTATE_270 ^ TFT_INVERT_Y)
#define TFT_ROTATE_270_MIRROR_Y   (TFT_ROTATE_270 ^ TFT_INVERT_X)

// TFT_ROTATION is user configurable
#ifndef TFT_ROTATION
  #define TFT_ROTATION TFT_NO_ROTATION
#endif

// TFT_ORIENTATION is the "sum" of TFT_DEFAULT_ORIENTATION plus user TFT_ROTATION
#define TFT_ORIENTATION ((TFT_DEFAULT_ORIENTATION) ^ (TFT_ROTATION))

#define TFT_COLOR_RGB   _BV32(3)
#define TFT_COLOR_BGR   _BV32(4)

// Each TFT Driver is responsible for its default color mode.
// #ifndef TFT_COLOR
//   #define TFT_COLOR   TFT_COLOR_RGB
// #endif

#define TOUCH_ORIENTATION_NONE  0
#define TOUCH_LANDSCAPE         1
#define TOUCH_PORTRAIT          2

#ifndef TOUCH_CALIBRATION_X
  #define TOUCH_CALIBRATION_X   0
#endif
#ifndef TOUCH_CALIBRATION_Y
  #define TOUCH_CALIBRATION_Y   0
#endif
#ifndef TOUCH_OFFSET_X
  #define TOUCH_OFFSET_X        0
#endif
#ifndef TOUCH_OFFSET_Y
  #define TOUCH_OFFSET_Y        0
#endif
#ifndef TOUCH_ORIENTATION
  #define TOUCH_ORIENTATION     TOUCH_LANDSCAPE
#endif

=======
#ifndef DMA_MAX_WORDS
  #error "DMA_MAX_WORDS is not configured for this platform."
#endif

>>>>>>> origin/release-2.1.3-beta2
#ifndef TFT_DRIVER
  #define TFT_DRIVER AUTO
#endif

#define ESC_REG(x)   0xFFFF, 0x00FF & (uint16_t)x
#define ESC_DELAY(x) 0xFFFF, 0x8000 | (x & 0x7FFF)
#define ESC_END      0xFFFF, 0x7FFF
#define ESC_FFFF     0xFFFF, 0xFFFF

class TFT_IO {
public:
  static TFT_IO_DRIVER io;

  static void initTFT();
  static void set_window(uint16_t xMin, uint16_t yMin, uint16_t xMax, uint16_t yMax);
  static void write_esc_sequence(const uint16_t *sequence);

  // Deletaged methods
  inline static void init() { io.init(); }
  inline static bool isBusy() { return io.isBusy(); }
  inline static void abort() { io.abort(); }
  inline static uint32_t getID() { return io.getID(); }

  inline static void dataTransferBegin(uint16_t dataWidth=DATASIZE_16BIT) { io.dataTransferBegin(dataWidth); }
  inline static void dataTransferEnd() { io.dataTransferEnd(); }

  inline static void writeData(uint16_t data) { io.writeData(data); }
  inline static void writeReg(const uint16_t inReg) { io.writeReg(inReg); }

<<<<<<< HEAD
  inline static void WriteSequence(uint16_t *Data, uint16_t Count) { io.WriteSequence(Data, Count); };

  #if ENABLED(USE_SPI_DMA_TC)
    inline static void WriteSequenceIT(uint16_t *Data, uint16_t Count) { io.WriteSequenceIT(Data, Count); };
  #endif

  // static void WriteMultiple(uint16_t Color, uint16_t Count) { static uint16_t Data; Data = Color; TransmitDMA(DMA_MINC_DISABLE, &Data, Count); }
  inline static void WriteMultiple(uint16_t Color, uint32_t Count) { io.WriteMultiple(Color, Count); };
=======
  // Blocking IO used by TFT_CLASSIC_UI and TFT_LVGL_UI
  // These functions start data transfer and WAIT for data transfer completion
  inline static void writeSequence(uint16_t *data, uint16_t count) { io.writeSequence(data, count); }
  inline static void writeMultiple(uint16_t color, uint32_t count) { io.writeMultiple(color, count); }

  // Non-blocking DMA-based IO used by TFT_COLOR_UI only
  // These functions start data transfer using DMA and do NOT wait for data transfer completion
  inline static void writeSequenceDMA(uint16_t *data, uint16_t count) { io.writeSequence_DMA(data, count); }
  inline static void WriteMultipleDMA(uint16_t color, uint16_t count) { io.writeMultiple_DMA(color, count); }

  // Non-blocking DMA-based IO with IRQ callback used by TFT_LVGL_UI only
  // This function starts data transfer using DMA and does NOT wait for data transfer completion
  #if ENABLED(USE_SPI_DMA_TC)
    inline static void writeSequenceIT(uint16_t *data, uint16_t count) { io.writeSequenceIT(data, count); }
  #endif
>>>>>>> origin/release-2.1.3-beta2

protected:
  static uint32_t lcd_id;
};
