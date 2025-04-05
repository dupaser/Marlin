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

/**
 * Pins Debugging for LPC1768/9
 *
 *   - NUMBER_PINS_TOTAL
 *   - MULTI_NAME_PAD
 *   - getPinByIndex(index)
 *   - printPinNameByIndex(index)
 *   - getPinIsDigitalByIndex(index)
 *   - digitalPinToAnalogIndex(pin)
 *   - getValidPinMode(pin)
 *   - isValidPin(pin)
 *   - isAnalogPin(pin)
 *   - digitalRead_mod(pin)
 *   - pwm_status(pin)
 *   - printPinPWM(pin)
 *   - printPinPort(pin)
 *   - printPinNumber(pin)
 *   - printPinAnalog(pin)
 */

#define NUMBER_PINS_TOTAL NUM_DIGITAL_PINS
<<<<<<< HEAD
#define pwm_details(pin) pin = pin    // do nothing  // print PWM details
#define pwm_status(pin) false //Print a pin's PWM status. Return true if it's currently a PWM pin.
#define IS_ANALOG(P) (DIGITAL_PIN_TO_ANALOG_PIN(P) >= 0 ? 1 : 0)
#define digitalRead_mod(p) extDigitalRead(p)
#define PRINT_PORT(p)
#define GET_ARRAY_PIN(p) pin_array[p].pin
#define PRINT_ARRAY_NAME(x) do{ sprintf_P(buffer, PSTR("%-" STRINGIFY(MAX_NAME_LENGTH) "s"), pin_array[x].name); SERIAL_ECHO(buffer); }while(0)
#define PRINT_PIN(p) do{ sprintf_P(buffer, PSTR("P%d_%02d"), LPC176x::pin_port(p), LPC176x::pin_bit(p)); SERIAL_ECHO(buffer); }while(0)
#define PRINT_PIN_ANALOG(p) do{ sprintf_P(buffer, PSTR("_A%d     "), LPC176x::pin_get_adc_channel(pin)); SERIAL_ECHO(buffer); }while(0)
=======
#define isAnalogPin(P) (digitalPinToAnalogIndex(P) >= 0)
#define digitalRead_mod(P) extDigitalRead(P)
#define getPinByIndex(x) pin_array[x].pin
#define printPinNameByIndex(x) do{ sprintf_P(buffer, PSTR("%-" STRINGIFY(MAX_NAME_LENGTH) "s"), pin_array[x].name); SERIAL_ECHO(buffer); }while(0)
#define printPinNumber(P) do{ sprintf_P(buffer, PSTR("P%d_%02d"), LPC176x::pin_port(P), LPC176x::pin_bit(P)); SERIAL_ECHO(buffer); }while(0)
#define printPinAnalog(P) do{ sprintf_P(buffer, PSTR("_A%d     "), LPC176x::pin_get_adc_channel(P)); SERIAL_ECHO(buffer); }while(0)
>>>>>>> origin/release-2.1.3-beta2
#define MULTI_NAME_PAD 17 // space needed to be pretty if not first name assigned to a pin

// pins that will cause hang/reset/disconnect in M43 Toggle and Watch utilities
#ifndef M43_NEVER_TOUCH
  #define M43_NEVER_TOUCH(Q) ((Q) == P0_29 || (Q) == P0_30 || (Q) == P2_09)  // USB pins
#endif

bool getValidPinMode(const pin_t pin) {
  if (!LPC176x::pin_is_valid(pin) || LPC176x::pin_adc_enabled(pin)) // Invalid pin or active analog pin
    return false;

  return LPC176x::gpio_direction(pin);
}

<<<<<<< HEAD
#define GET_ARRAY_IS_DIGITAL(x) ((bool) pin_array[x].is_digital)
=======
#define getPinIsDigitalByIndex(x) ((bool) pin_array[x].is_digital)

void printPinPort(const pin_t) {}
void printPinPWM(const pin_t) {}
bool pwm_status(const pin_t) { return false; }
>>>>>>> origin/release-2.1.3-beta2
