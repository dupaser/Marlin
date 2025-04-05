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

#include "DGUSDisplay.h"
#include "definition/DGUS_VP.h"

namespace DGUSRxHandler {

<<<<<<< HEAD
  void ScreenChange(DGUS_VP &, void *);

  #if ENABLED(SDSUPPORT)
    void Scroll(DGUS_VP &, void *);
    void SelectFile(DGUS_VP &, void *);
    void PrintFile(DGUS_VP &, void *);
  #endif

  void PrintAbort(DGUS_VP &, void *);
  void PrintPause(DGUS_VP &, void *);
  void PrintResume(DGUS_VP &, void *);

  void Feedrate(DGUS_VP &, void *);
  void Flowrate(DGUS_VP &, void *);
  void BabystepSet(DGUS_VP &, void *);
  void Babystep(DGUS_VP &, void *);

  void TempPreset(DGUS_VP &, void *);
  void TempTarget(DGUS_VP &, void *);
  void TempCool(DGUS_VP &, void *);

  void Steppers(DGUS_VP &, void *);

  void ZOffset(DGUS_VP &, void *);
  void ZOffsetStep(DGUS_VP &, void *);
  void ZOffsetSetStep(DGUS_VP &, void *);

  void MoveToPoint(DGUS_VP &, void *);

  void Probe(DGUS_VP &, void *);
  void DisableABL(DGUS_VP &, void *);

  void FilamentSelect(DGUS_VP &, void *);
  void FilamentLength(DGUS_VP &, void *);
  void FilamentMove(DGUS_VP &, void *);

  void Home(DGUS_VP &, void *);
  void Move(DGUS_VP &, void *);
  void MoveStep(DGUS_VP &, void *);
  void MoveSetStep(DGUS_VP &, void *);

  void GcodeClear(DGUS_VP &, void *);
  void GcodeExecute(DGUS_VP &, void *);

  void ResetEEPROM(DGUS_VP &, void *);

  void SettingsExtra(DGUS_VP &, void *);

  void PIDSelect(DGUS_VP &, void *);
  void PIDSetTemp(DGUS_VP &, void *);
  void PIDRun(DGUS_VP &, void *);

  #if ENABLED(POWER_LOSS_RECOVERY)
    void PowerLossAbort(DGUS_VP &, void *);
    void PowerLossResume(DGUS_VP &, void *);
  #endif

  void WaitAbort(DGUS_VP &, void *);
  void WaitContinue(DGUS_VP &, void *);

  void FanSpeed(DGUS_VP &, void *);

  void Volume(DGUS_VP &, void *);

  void Brightness(DGUS_VP &, void *);

  void Debug(DGUS_VP &, void *);

  void StringToExtra(DGUS_VP &, void *);

  template<typename T>
  void IntegerToExtra(DGUS_VP &vp, void *data_ptr) {
=======
  void screenChange(DGUS_VP &, void *);

  #if HAS_MEDIA
    void scroll(DGUS_VP &, void *);
    void selectFile(DGUS_VP &, void *);
    void printFile(DGUS_VP &, void *);
  #endif

  void printAbort(DGUS_VP &, void *);
  void printPause(DGUS_VP &, void *);
  void printResume(DGUS_VP &, void *);

  void feedrate(DGUS_VP &, void *);
  void flowrate(DGUS_VP &, void *);
  void babystepSet(DGUS_VP &, void *);
  void babystep(DGUS_VP &, void *);

  void tempPreset(DGUS_VP &, void *);
  void tempTarget(DGUS_VP &, void *);
  void tempCool(DGUS_VP &, void *);

  void steppers(DGUS_VP &, void *);

  void zOffset(DGUS_VP &, void *);
  void zOffsetStep(DGUS_VP &, void *);
  void zOffsetSetStep(DGUS_VP &, void *);

  void moveToPoint(DGUS_VP &, void *);

  void probe(DGUS_VP &, void *);
  void disableABL(DGUS_VP &, void *);

  void filamentSelect(DGUS_VP &, void *);
  void filamentLength(DGUS_VP &, void *);
  void filamentMove(DGUS_VP &, void *);

  void home(DGUS_VP &, void *);
  void move(DGUS_VP &, void *);
  void moveStep(DGUS_VP &, void *);
  void moveSetStep(DGUS_VP &, void *);

  void gcodeClear(DGUS_VP &, void *);
  void gcodeExecute(DGUS_VP &, void *);

  void resetEEPROM(DGUS_VP &, void *);

  void settingsExtra(DGUS_VP &, void *);

  void pidSelect(DGUS_VP &, void *);
  void pidSetTemp(DGUS_VP &, void *);
  void pidRun(DGUS_VP &, void *);

  #if ENABLED(POWER_LOSS_RECOVERY)
    void powerLossAbort(DGUS_VP &, void *);
    void powerLossResume(DGUS_VP &, void *);
  #endif

  void waitAbort(DGUS_VP &, void *);
  void waitContinue(DGUS_VP &, void *);

  void fanSpeed(DGUS_VP &, void *);

  void volume(DGUS_VP &, void *);

  void brightness(DGUS_VP &, void *);

  void debug(DGUS_VP &, void *);

  void stringToExtra(DGUS_VP &, void *);

  template<typename T>
  void integerToExtra(DGUS_VP &vp, void *data_ptr) {
>>>>>>> origin/release-2.1.3-beta2
    if (!vp.size || !vp.extra) return;
    switch (vp.size) {
      default: return;
      case 1: {
        const uint8_t data = *(uint8_t*)data_ptr;
        *(T*)vp.extra = (T)data;
        break;
      }
      case 2: {
<<<<<<< HEAD
        const uint16_t data = Swap16(*(uint16_t*)data_ptr);
=======
        const uint16_t data = BE16_P(data_ptr);
>>>>>>> origin/release-2.1.3-beta2
        *(T*)vp.extra = (T)data;
        break;
      }
      case 4: {
<<<<<<< HEAD
        const uint32_t data = dgus_display.SwapBytes(*(uint32_t*)data_ptr);
=======
        const uint32_t data = dgus.swapBytes(*(uint32_t*)data_ptr);
>>>>>>> origin/release-2.1.3-beta2
        *(T*)vp.extra = (T)data;
        break;
      }
    }
  }

}
