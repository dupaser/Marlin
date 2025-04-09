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

#include "../../../inc/MarlinConfigPre.h"

#if HAS_DGUS_LCD_CLASSIC

#if HOTENDS > 2
  #warning "More than 2 hotends not implemented on DGUS Display UI."
#endif

#include "../ui_api.h"

#include "../../../MarlinCore.h"
#include "../../../module/motion.h"
#include "../../../gcode/queue.h"
#include "../../../module/planner.h"
#include "../../../libs/duration_t.h"
#include "../../../module/printcounter.h"
#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../../feature/powerloss.h"
#endif

#include <locale>
#include <codecvt>
#include <cstring>

#include "DGUSDisplay.h"
#include "DGUSVPVariable.h"
#include "DGUSDisplayDef.h"

DGUSDisplay dgus;

#ifdef DEBUG_DGUSLCD_COMM
  #define DEBUGLCDCOMM_ECHOPGM DEBUG_ECHOPGM
#else
  #define DEBUGLCDCOMM_ECHOPGM(...) NOOP
#endif

// Preamble... 2 Bytes, usually 0x5A 0xA5, but configurable
constexpr uint8_t DGUS_HEADER1 = 0x5A;
constexpr uint8_t DGUS_HEADER2 = 0xA5;

constexpr uint8_t DGUS_CMD_WRITEVAR = 0x82;
constexpr uint8_t DGUS_CMD_READVAR = 0x83;

#if ENABLED(DEBUG_DGUSLCD)
  bool dguslcd_local_debug; // = false;
#endif

void DGUSDisplay::initDisplay() {
  #ifndef LCD_BAUDRATE
    #define LCD_BAUDRATE 115200
  #endif
  LCD_SERIAL.begin(LCD_BAUDRATE);

  if (TERN1(POWER_LOSS_RECOVERY, !recovery.valid())) {  // If no Power-Loss Recovery is needed...
    TERN_(DGUS_LCD_UI_MKS, delay(LOGO_TIME_DELAY));     // Show the logo for a little while
  }
  //dgus.writeVariable(VP_ERROR_STATUS, (uint16_t)0); //Свое 
  RequestScreen(TERN(SHOW_BOOTSCREEN, DGUSLCD_SCREEN_BOOT, DGUSLCD_SCREEN_MAIN));
}

void DGUSDisplay::SetIcon(uint16_t vp, bool is_on){
  if(is_on) dgus.writeVariable(vp, (uint16_t)1); // свое uint16_t обязателен, чтобы было 00 01, а не 01 00(uint8_t).
  else dgus.writeVariable(vp, (uint16_t)0); // uint16_t обязателен, чтобы было 00 01, а не 01 00(uint8_t).

}

void DGUSDisplay::writeVariable(uint16_t adr, const void *values, uint8_t valueslen, bool isstr) {
  const char* myvalues = static_cast<const char*>(values);
  bool strend = !myvalues;
  WriteHeader(adr, DGUS_CMD_WRITEVAR, valueslen);
  while (valueslen--) {
    char x;
    if(!strend) x = *myvalues++;
    if ((isstr && !x) || strend) {
      strend = true;
      x = ' ';
    }
    LCD_SERIAL.write(x);
  }
}

void DGUSDisplay::WriteString(uint16_t adr, FSTR_P values, uint8_t valueslen) {
      const char * const pstr = FTOP(values);
      WriteString(adr, pstr, valueslen);
}

void DGUSDisplay::WriteString(uint16_t adr, const char *values, uint8_t valueslen) {
      char destination[valueslen] = ""; 
      memset(destination, 0, valueslen);
      strcpy(destination, values);
      // Преобразование из UTF-8 в UTF-16
      std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
      std::u16string utf16_string = converter.from_bytes(values);
      // Копирование данных UTF-16 в char массив
      int i = 0;
      // TODO: Сравнить размер utf16_string и tmpFilename.
      for (char16_t ch : utf16_string) {
          if(i >= VP_SD_FileName_LEN) break; 
          // Выводим каждый байт символа UTF-16
          uint8_t high_byte = (ch >> 8) & 0xFF; // Высокий байт
          uint8_t low_byte = ch & 0xFF; // Низкий байт
          destination[i++] = high_byte;
          destination[i++] = low_byte;
      }

      dgus.WriteUtf16String(adr, destination, valueslen);
}

// Свое метод отправки сиволов в формате UTF-16
void DGUSDisplay::WriteUtf16String(uint16_t adr, const char *values, uint8_t valueslen) {
  std::string str = values;
  bool strend = !values + !(values + 1);
  WriteHeader(adr, DGUS_CMD_WRITEVAR, valueslen);
  uint8_t low_byte = 0;
  uint8_t high_byte = 0;
  bool space_print_inversion = false;
  while (valueslen--) {
    char x;
    if(!strend) {
      low_byte = *values;
      x = *values++;
      high_byte = *values;
    }
    if ((!low_byte && !high_byte) || strend) {
      strend = true;
      if(space_print_inversion) x = ' ';
      else x = 0x00;
      space_print_inversion = !space_print_inversion;
    }
    LCD_SERIAL.write(x);
    // if(x == 0x00){
    //   LCD_SERIAL.write(' ');
    // }
  }
}

void DGUSDisplay::writeVariable(uint16_t adr, uint16_t value) {
  value = (value & 0xFFU) << 8U | (value >> 8U);
  writeVariable(adr, static_cast<const void*>(&value), sizeof(uint16_t));
}

void DGUSDisplay::writeVariable(uint16_t adr, int16_t value) {
  value = (value & 0xFFU) << 8U | (value >> 8U);
  writeVariable(adr, static_cast<const void*>(&value), sizeof(uint16_t));
}

void DGUSDisplay::writeVariable(uint16_t adr, uint8_t value) {
  writeVariable(adr, static_cast<const void*>(&value), sizeof(uint8_t));
}

void DGUSDisplay::writeVariable(uint16_t adr, int8_t value) {
  writeVariable(adr, static_cast<const void*>(&value), sizeof(int8_t));
}

void DGUSDisplay::writeVariable(uint16_t adr, long value) {
  union { long l; char lb[4]; } endian;
  char tmp[4];
  endian.l = value;
  tmp[0] = endian.lb[3];
  tmp[1] = endian.lb[2];
  tmp[2] = endian.lb[1];
  tmp[3] = endian.lb[0];
  writeVariable(adr, static_cast<const void*>(&tmp), sizeof(long));
}

void DGUSDisplay::WriteVariablePGM(uint16_t adr, const void *values, uint8_t valueslen, bool isstr) {
  const char* myvalues = static_cast<const char*>(values);
  bool strend = !myvalues;
  WriteHeader(adr, DGUS_CMD_WRITEVAR, valueslen);
  while (valueslen--) {
    char x;
    if (!strend) x = pgm_read_byte(myvalues++);
    if ((isstr && !x) || strend) {
      strend = true;
      x = ' ';
    }
    LCD_SERIAL.write(x);
  }
}

void DGUSDisplay::ProcessRx() {

  #if ENABLED(SERIAL_STATS_RX_BUFFER_OVERRUNS)
    if (!LCD_SERIAL.available() && LCD_SERIAL.buffer_overruns()) {
      // Overrun, but reset the flag only when the buffer is empty
      // We want to extract as many as valid datagrams possible...
      DEBUG_ECHOPGM("OVFL");
      rx_datagram_state = DGUS_IDLE;
      //LCD_SERIAL.reset_rx_overun();
      LCD_SERIAL.flush();
    }
  #endif

  uint8_t receivedbyte;
  while (LCD_SERIAL.available()) {
    switch (rx_datagram_state) {

      case DGUS_IDLE: // Waiting for the first header byte
        receivedbyte = LCD_SERIAL.read();
        //DEBUGLCDCOMM_ECHOPGM("< ", receivedbyte);
        if (DGUS_HEADER1 == receivedbyte) rx_datagram_state = DGUS_HEADER1_SEEN;
        break;

      case DGUS_HEADER1_SEEN: // Waiting for the second header byte
        receivedbyte = LCD_SERIAL.read();
        //DEBUGLCDCOMM_ECHOPGM(" ", receivedbyte);
        rx_datagram_state = (DGUS_HEADER2 == receivedbyte) ? DGUS_HEADER2_SEEN : DGUS_IDLE;
        break;

      case DGUS_HEADER2_SEEN: // Waiting for the length byte
        rx_datagram_len = LCD_SERIAL.read();
        //DEBUGLCDCOMM_ECHOPGM(" (", rx_datagram_len, ") ");

        // Telegram min len is 3 (command and one word of payload)
        rx_datagram_state = WITHIN(rx_datagram_len, 3, DGUS_RX_BUFFER_SIZE) ? DGUS_WAIT_TELEGRAM : DGUS_IDLE;
        break;

      case DGUS_WAIT_TELEGRAM: // wait for complete datagram to arrive.
        if (LCD_SERIAL.available() < rx_datagram_len) return;

        Initialized = true; // We've talked to it, so we defined it as initialized.
        uint8_t command = LCD_SERIAL.read();

        //DEBUGLCDCOMM_ECHOPGM("# ", command);

        uint8_t readlen = rx_datagram_len - 1;  // command is part of len.
        unsigned char tmp[rx_datagram_len - 1];
        unsigned char *ptmp = tmp;
        while (readlen--) {
          receivedbyte = LCD_SERIAL.read();
          //DEBUGLCDCOMM_ECHOPGM(" ", receivedbyte);
          *ptmp++ = receivedbyte;
        }
        //DEBUGLCDCOMM_ECHOPGM(" # ");
        // mostly we'll get this: 5A A5 03 82 4F 4B -- ACK on 0x82, so discard it.
        if (command == DGUS_CMD_WRITEVAR && 'O' == tmp[0] && 'K' == tmp[1]) {
          //DEBUGLCDCOMM_ECHOPGM(">");
          rx_datagram_state = DGUS_IDLE;
          break;
        }

        /* AutoUpload, (and answer to) Command 0x83 :
        |      tmp[0  1  2  3  4 ... ]
        | Example 5A A5 06 83 20 01 01 78 01 ……
        |          / /  |  |   \ /   |  \     \
        |        Header |  |    |    |   \_____\_ DATA (Words!)
        |     DatagramLen  /  VPAdr  |
        |           Command          DataLen (in Words) */
        if (command == DGUS_CMD_READVAR) {
          const uint16_t vp = tmp[0] << 8 | tmp[1];
          //const uint8_t dlen = tmp[2] << 1;  // Convert to Bytes. (Display works with words)
          //DEBUG_ECHOPGM(" vp=", vp, " dlen=", dlen);
          DGUS_VP_Variable ramcopy;
          if (populate_VPVar(vp, &ramcopy)) {
            if (ramcopy.set_by_display_handler)
              ramcopy.set_by_display_handler(ramcopy, &tmp[3]);
            else
              DEBUG_ECHOLNPGM(" VPVar found, no handler.");
          }
          else
            DEBUG_ECHOLNPGM(" VPVar not found:", vp);

          rx_datagram_state = DGUS_IDLE;
          break;
        }

      // discard anything else
      rx_datagram_state = DGUS_IDLE;
    }
  }
}

size_t DGUSDisplay::GetFreeTxBuffer() { return SERIAL_GET_TX_BUFFER_FREE(); }

void DGUSDisplay::WriteHeader(uint16_t adr, uint8_t cmd, uint8_t payloadlen) {
  LCD_SERIAL.write(DGUS_HEADER1);
  LCD_SERIAL.write(DGUS_HEADER2);
  LCD_SERIAL.write(payloadlen + 3);
  LCD_SERIAL.write(cmd);
  LCD_SERIAL.write(adr >> 8);
  LCD_SERIAL.write(adr & 0xFF);
}

void DGUSDisplay::WritePGM(const char str[], uint8_t len) {
  while (len--) LCD_SERIAL.write(pgm_read_byte(str++));
}

void DGUSDisplay::loop() {
  // Protect against recursion. ProcessRx() may indirectly call idle() when injecting G-code commands.
  if (!no_reentrance) {
    no_reentrance = true;
    ProcessRx();
    no_reentrance = false;
  }
}

rx_datagram_state_t DGUSDisplay::rx_datagram_state = DGUS_IDLE;
uint8_t DGUSDisplay::rx_datagram_len = 0;
bool DGUSDisplay::Initialized = false,
     DGUSDisplay::no_reentrance = false;

// A SW memory barrier, to ensure GCC does not overoptimize loops
#define sw_barrier() asm volatile("": : :"memory");

bool populate_VPVar(const uint16_t VP, DGUS_VP_Variable * const ramcopy) {
  //DEBUG_ECHOPGM("populate_VPVar ", VP);
  const DGUS_VP_Variable *pvp = DGUSLCD_FindVPVar(VP);
  //DEBUG_ECHOLNPGM(" pvp ", (uint16_t )pvp);
  if (!pvp) return false;
  memcpy_P(ramcopy, pvp, sizeof(DGUS_VP_Variable));
  return true;
}

#endif // HAS_DGUS_LCD_CLASSIC
