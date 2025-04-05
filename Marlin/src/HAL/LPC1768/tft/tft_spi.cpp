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

#ifdef TARGET_LPC1768

#include "../../../inc/MarlinConfig.h"

#if HAS_SPI_TFT

#include "tft_spi.h"

<<<<<<< HEAD
SPIClass TFT_SPI::SPIx(1);

void TFT_SPI::Init() {
=======
SPIClass TFT_SPI::SPIx(TFT_SPI_DEVICE);

void TFT_SPI::init() {
>>>>>>> origin/release-2.1.3-beta2
  #if PIN_EXISTS(TFT_RESET)
    OUT_WRITE(TFT_RESET_PIN, HIGH);
    delay(100);
  #endif

  #if PIN_EXISTS(TFT_BACKLIGHT)
    OUT_WRITE(TFT_BACKLIGHT_PIN, HIGH);
  #endif

<<<<<<< HEAD
  SET_OUTPUT(TFT_DC_PIN);
  SET_OUTPUT(TFT_CS_PIN);
  WRITE(TFT_DC_PIN, HIGH);
  WRITE(TFT_CS_PIN, HIGH);

  /**
   * STM32F1 APB2 = 72MHz, APB1 = 36MHz, max SPI speed of this MCU if 18Mhz
   * STM32F1 has 3 SPI ports, SPI1 in APB2, SPI2/SPI3 in APB1
   * so the minimum prescale of SPI1 is DIV4, SPI2/SPI3 is DIV2
   */
  #if 0
    #if SPI_DEVICE == 1
     #define SPI_CLOCK_MAX SPI_CLOCK_DIV4
    #else
     #define SPI_CLOCK_MAX SPI_CLOCK_DIV2
    #endif
    uint8_t  clock;
    uint8_t spiRate = SPI_FULL_SPEED;
    switch (spiRate) {
     case SPI_FULL_SPEED:    clock = SPI_CLOCK_MAX ;  break;
     case SPI_HALF_SPEED:    clock = SPI_CLOCK_DIV4 ; break;
     case SPI_QUARTER_SPEED: clock = SPI_CLOCK_DIV8 ; break;
     case SPI_EIGHTH_SPEED:  clock = SPI_CLOCK_DIV16; break;
     case SPI_SPEED_5:       clock = SPI_CLOCK_DIV32; break;
     case SPI_SPEED_6:       clock = SPI_CLOCK_DIV64; break;
     default:                clock = SPI_CLOCK_DIV2;  // Default from the SPI library
    }
  #endif

  #if TFT_MISO_PIN == BOARD_SPI1_MISO_PIN
    SPIx.setModule(1);
  #elif TFT_MISO_PIN == BOARD_SPI2_MISO_PIN
    SPIx.setModule(2);
  #endif
=======
  OUT_WRITE(TFT_DC_PIN, HIGH);
  OUT_WRITE(TFT_CS_PIN, HIGH);

  SPIx.setModule(TFT_SPI_DEVICE);
>>>>>>> origin/release-2.1.3-beta2
  SPIx.setClock(SPI_CLOCK_MAX_TFT);
  SPIx.setBitOrder(MSBFIRST);
  SPIx.setDataMode(SPI_MODE0);
}

void TFT_SPI::dataTransferBegin(uint16_t dataSize) {
  SPIx.setDataSize(dataSize);
  SPIx.begin();
  WRITE(TFT_CS_PIN, LOW);
}

#ifdef TFT_DEFAULT_DRIVER
  #include "../../../lcd/tft_io/tft_ids.h"
#endif

uint32_t TFT_SPI::getID() {
  uint32_t id;
  id = readID(LCD_READ_ID);
  if ((id & 0xFFFF) == 0 || (id & 0xFFFF) == 0xFFFF)
    id = readID(LCD_READ_ID4);
    #ifdef TFT_DEFAULT_DRIVER
      if ((id & 0xFFFF) == 0 || (id & 0xFFFF) == 0xFFFF)
        id = TFT_DEFAULT_DRIVER;
    #endif
  return id;
}

uint32_t TFT_SPI::readID(const uint16_t inReg) {
  uint32_t data = 0;

  #if PIN_EXISTS(TFT_MISO)
    uint8_t d = 0;
    SPIx.setDataSize(DATASIZE_8BIT);
    SPIx.setClock(SPI_CLOCK_DIV64);
    SPIx.begin();
    WRITE(TFT_CS_PIN, LOW);
<<<<<<< HEAD
    WriteReg(Reg);
=======
    writeReg(inReg);
>>>>>>> origin/release-2.1.3-beta2

    for (uint8_t i = 0; i < 4; ++i) {
      SPIx.read((uint8_t*)&d, 1);
      data = (data << 8) | d;
    }

    dataTransferEnd();
    SPIx.setClock(SPI_CLOCK_MAX_TFT);
  #endif

  return data >> 7;
}

<<<<<<< HEAD
bool TFT_SPI::isBusy() { return false; }

void TFT_SPI::Abort() { DataTransferEnd(); }

void TFT_SPI::Transmit(uint16_t Data) { SPIx.transfer(Data); }

void TFT_SPI::TransmitDMA(uint32_t MemoryIncrease, uint16_t *Data, uint16_t Count) {
  DataTransferBegin(DATASIZE_16BIT);
  WRITE(TFT_DC_PIN, HIGH);
  SPIx.dmaSend(Data, Count, MemoryIncrease);
  DataTransferEnd();
=======
bool TFT_SPI::isBusy() {
  #define __IS_DMA_CONFIGURED(__HANDLE__)   ((__HANDLE__)->DMACCSrcAddr != 0)

  // DMA Channel 0 is hardcoded in dmaSendAsync() and dmaSend()
  if (!__IS_DMA_CONFIGURED(LPC_GPDMACH0)) return false;

  if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, 0)) {
    // You should not be here - DMA transfer error flag is set
    // Abort DMA transfer and release SPI
  }
  else {
    // Check if DMA transfer completed flag is set
    if (!GPDMA_IntGetStatus(GPDMA_STAT_INTTC, 0)) return true;
    // Check if SPI TX butter is empty and SPI is idle
    if ((SSP_GetStatus(LPC_SSPx, SSP_STAT_TXFIFO_EMPTY) == RESET) || (SSP_GetStatus(LPC_SSPx, SSP_STAT_BUSY) == SET)) return true;
  }

  abort();
  return false;
}

void TFT_SPI::abort() {
  // DMA Channel 0 is hardcoded in dmaSendAsync() and dmaSend()

  // Disable DMA
  GPDMA_ChannelCmd(0, DISABLE);

  // Clear ERR and TC
  GPDMA_ClearIntPending(GPDMA_STATCLR_INTTC, 0);
  GPDMA_ClearIntPending(GPDMA_STATCLR_INTERR, 0);

  // Disable DMA on SPI
  SSP_DMACmd(LPC_SSPx, SSP_DMA_TX, DISABLE);

  // Deconfigure DMA Channel 0
  LPC_GPDMACH0->DMACCControl  = 0U;
  LPC_GPDMACH0->DMACCConfig   = 0U;
  LPC_GPDMACH0->DMACCSrcAddr  = 0U;
  LPC_GPDMACH0->DMACCDestAddr = 0U;

  dataTransferEnd();
}

void TFT_SPI::transmit(uint16_t data) { SPIx.transfer(data); }

void TFT_SPI::transmit(uint32_t memoryIncrease, uint16_t *data, uint16_t count) {
  dataTransferBegin(DATASIZE_16BIT);
  SPIx.dmaSend(data, count, memoryIncrease);
  abort();
}

void TFT_SPI::transmitDMA(uint32_t memoryIncrease, uint16_t *data, uint16_t count) {
  dataTransferBegin(DATASIZE_16BIT);
  SPIx.dmaSendAsync(data, count, memoryIncrease);

  TERN_(TFT_SHARED_IO, while (isBusy()));
>>>>>>> origin/release-2.1.3-beta2
}

#endif // HAS_SPI_TFT
#endif // TARGET_LPC1768
