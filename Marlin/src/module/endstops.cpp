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

/**
 * endstops.cpp - A singleton object to manage endstops
 */

#include "endstops.h"
#include "stepper.h"

<<<<<<< HEAD
#include "../sd/cardreader.h"
#include "temperature.h"
#include "../lcd/marlinui.h"

#define DEBUG_OUT BOTH(USE_SENSORLESS, DEBUG_LEVELING_FEATURE)
#include "../core/debug_out.h"

#if ENABLED(ENDSTOP_INTERRUPTS_FEATURE)
  #include HAL_PATH(../HAL, endstop_interrupts.h)
=======
#if ANY(HAS_STATUS_MESSAGE, VALIDATE_HOMING_ENDSTOPS)
  #include "../lcd/marlinui.h"
>>>>>>> origin/release-2.1.3-beta2
#endif

#if ENABLED(SOVOL_SV06_RTS)
  #include "../lcd/sovol_rts/sovol_rts.h"
#endif

#if ENABLED(FT_MOTION)
  #include "ft_motion.h"
#endif

#if ENABLED(ENDSTOP_INTERRUPTS_FEATURE)
  #include HAL_PATH(.., endstop_interrupts.h)
#endif

#if ENABLED(SD_ABORT_ON_ENDSTOP_HIT)
  #include "printcounter.h" // for print_job_timer
  #include "temperature.h"
  #include "../sd/cardreader.h"
#endif

#if ENABLED(BLTOUCH)
  #include "../feature/bltouch.h"
#endif

#if ENABLED(JOYSTICK)
  #include "../feature/joystick.h"
#endif

#if HAS_FILAMENT_SENSOR
  #include "../feature/runout.h"
#endif

#if HAS_BED_PROBE
  #include "probe.h"
#endif

<<<<<<< HEAD

#include "../lcd/extui/dgus/DGUSScreenHandler.h" //Свое
=======
#define DEBUG_OUT ALL(USE_SENSORLESS, DEBUG_LEVELING_FEATURE)
#include "../core/debug_out.h"
>>>>>>> origin/release-2.1.3-beta2

Endstops endstops;

// private:

<<<<<<< HEAD
bool Endstops::enabled, Endstops::enabled_globally; // Initialized by settings.load()

volatile Endstops::endstop_mask_t Endstops::hit_state;
Endstops::endstop_mask_t Endstops::live_state = 0;
=======
bool Endstops::enabled, Endstops::enabled_globally; // Initialized by settings.load

volatile Endstops::endstop_mask_t Endstops::hit_state;
Endstops::endstop_mask_t Endstops::live_state = 0;

#if ENABLED(BD_SENSOR)
  bool Endstops::bdp_state; // = false
  #if HOMING_Z_WITH_PROBE
    #define READ_ENDSTOP(P) ((P == TERN(Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN, Z_MIN_PIN, Z_MIN_PROBE_PIN)) ? bdp_state : READ(P))
  #else
    #define READ_ENDSTOP(P) READ(P)
  #endif
#else
  #define READ_ENDSTOP(P) READ(P)
#endif
>>>>>>> origin/release-2.1.3-beta2

#if ENDSTOP_NOISE_THRESHOLD
  Endstops::endstop_mask_t Endstops::validated_live_state;
  uint8_t Endstops::endstop_poll_count;
#endif

#if HAS_BED_PROBE
  volatile bool Endstops::z_probe_enabled = false;
#endif

#if ENABLED(CALIBRATION_GCODE)
  volatile bool Endstops::calibration_probe_enabled = false;
  volatile bool Endstops::calibration_stop_state;
#endif

// Initialized by settings.load
#if ENABLED(X_DUAL_ENDSTOPS)
  float Endstops::x2_endstop_adj;
#endif
#if ENABLED(Y_DUAL_ENDSTOPS)
  float Endstops::y2_endstop_adj;
#endif
#if ENABLED(Z_MULTI_ENDSTOPS)
  float Endstops::z2_endstop_adj;
  #if NUM_Z_STEPPERS >= 3
    float Endstops::z3_endstop_adj;
    #if NUM_Z_STEPPERS >= 4
      float Endstops::z4_endstop_adj;
    #endif
  #endif
#endif

#if ENABLED(SPI_ENDSTOPS)
  Endstops::tmc_spi_homing_t Endstops::tmc_spi_homing; // = 0
#endif
#if ENABLED(IMPROVE_HOMING_RELIABILITY)
  millis_t sg_guard_period; // = 0
#endif

/**
 * Class and Instance Methods
 */

void Endstops::init() {

  #define _INIT_ENDSTOP(T,A,N) TERN(ENDSTOPPULLUP_##A##T, SET_INPUT_PULLUP, TERN(ENDSTOPPULLDOWN_##A##T, SET_INPUT_PULLDOWN, SET_INPUT))(A##N##_##T##_PIN)
  #if USE_X_MIN
    _INIT_ENDSTOP(MIN,X,);
  #endif
  #if USE_X_MAX
    _INIT_ENDSTOP(MAX,X,);
  #endif
  #if USE_X2_MIN
    _INIT_ENDSTOP(MIN,X,2);
  #endif
  #if USE_X2_MAX
    _INIT_ENDSTOP(MAX,X,2);
  #endif
  #if USE_Y_MIN
    _INIT_ENDSTOP(MIN,Y,);
  #endif
  #if USE_Y_MAX
    _INIT_ENDSTOP(MAX,Y,);
  #endif
  #if USE_Y2_MIN
    _INIT_ENDSTOP(MIN,Y,2);
  #endif
  #if USE_Y2_MAX
    _INIT_ENDSTOP(MAX,Y,2);
  #endif
  #if USE_Z_MIN
    _INIT_ENDSTOP(MIN,Z,);
  #endif
  #if USE_Z_MAX
    _INIT_ENDSTOP(MAX,Z,);
  #endif
  #if USE_Z2_MIN
    _INIT_ENDSTOP(MIN,Z,2);
  #endif
  #if USE_Z2_MAX
    _INIT_ENDSTOP(MAX,Z,2);
  #endif
  #if USE_Z3_MIN
    _INIT_ENDSTOP(MIN,Z,3);
  #endif
  #if USE_Z3_MAX
    _INIT_ENDSTOP(MAX,Z,3);
  #endif
  #if USE_Z4_MIN
    _INIT_ENDSTOP(MIN,Z,4);
  #endif
  #if USE_Z4_MAX
    _INIT_ENDSTOP(MAX,Z,4);
  #endif
  #if USE_I_MIN
    _INIT_ENDSTOP(MIN,I,);
  #endif
  #if USE_I_MAX
    _INIT_ENDSTOP(MAX,I,);
  #endif
  #if USE_J_MIN
    _INIT_ENDSTOP(MIN,J,);
  #endif
  #if USE_J_MAX
    _INIT_ENDSTOP(MAX,J,);
  #endif
  #if USE_K_MIN
    _INIT_ENDSTOP(MIN,K,);
  #endif
  #if USE_K_MAX
    _INIT_ENDSTOP(MAX,K,);
  #endif
  #if USE_U_MIN
    _INIT_ENDSTOP(MIN,U,);
  #endif
  #if USE_U_MAX
    _INIT_ENDSTOP(MAX,U,);
  #endif
  #if USE_V_MIN
    _INIT_ENDSTOP(MIN,V,);
  #endif
  #if USE_V_MAX
    _INIT_ENDSTOP(MAX,V,);
  #endif
  #if USE_W_MIN
    _INIT_ENDSTOP(MIN,W,);
  #endif
  #if USE_W_MAX
    _INIT_ENDSTOP(MAX,W,);
  #endif

<<<<<<< HEAD
  #if HAS_X2_MIN
    #if ENABLED(ENDSTOPPULLUP_XMIN)
      SET_INPUT_PULLUP(X2_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_XMIN)
      SET_INPUT_PULLDOWN(X2_MIN_PIN);
    #else
      SET_INPUT(X2_MIN_PIN);
    #endif
  #endif

  #if HAS_Y_MIN
    #if ENABLED(ENDSTOPPULLUP_YMIN)
      SET_INPUT_PULLUP(Y_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_YMIN)
      SET_INPUT_PULLDOWN(Y_MIN_PIN);
    #else
      SET_INPUT(Y_MIN_PIN);
    #endif
  #endif

  #if HAS_Y2_MIN
    #if ENABLED(ENDSTOPPULLUP_YMIN)
      SET_INPUT_PULLUP(Y2_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_YMIN)
      SET_INPUT_PULLDOWN(Y2_MIN_PIN);
    #else
      SET_INPUT(Y2_MIN_PIN);
    #endif
  #endif

  #if HAS_Z_MIN
    #if ENABLED(ENDSTOPPULLUP_ZMIN)
      SET_INPUT_PULLUP(Z_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMIN)
      SET_INPUT_PULLDOWN(Z_MIN_PIN);
    #else
      SET_INPUT(Z_MIN_PIN);
    #endif
  #endif

  #if HAS_Z2_MIN
    #if ENABLED(ENDSTOPPULLUP_ZMIN)
      SET_INPUT_PULLUP(Z2_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMIN)
      SET_INPUT_PULLDOWN(Z2_MIN_PIN);
    #else
      SET_INPUT(Z2_MIN_PIN);
    #endif
  #endif

  #if HAS_Z3_MIN
    #if ENABLED(ENDSTOPPULLUP_ZMIN)
      SET_INPUT_PULLUP(Z3_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMIN)
      SET_INPUT_PULLDOWN(Z3_MIN_PIN);
    #else
      SET_INPUT(Z3_MIN_PIN);
    #endif
  #endif

  #if HAS_Z4_MIN
    #if ENABLED(ENDSTOPPULLUP_ZMIN)
      SET_INPUT_PULLUP(Z4_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMIN)
      SET_INPUT_PULLDOWN(Z4_MIN_PIN);
    #else
      SET_INPUT(Z4_MIN_PIN);
    #endif
  #endif

  #if HAS_X_MAX
    #if ENABLED(ENDSTOPPULLUP_XMAX)
      SET_INPUT_PULLUP(X_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_XMAX)
      SET_INPUT_PULLDOWN(X_MAX_PIN);
    #else
      SET_INPUT(X_MAX_PIN);
    #endif
  #endif

  #if HAS_X2_MAX
    #if ENABLED(ENDSTOPPULLUP_XMAX)
      SET_INPUT_PULLUP(X2_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_XMAX)
      SET_INPUT_PULLDOWN(X2_MAX_PIN);
    #else
      SET_INPUT(X2_MAX_PIN);
    #endif
  #endif

  #if HAS_Y_MAX
    #if ENABLED(ENDSTOPPULLUP_YMAX)
      SET_INPUT_PULLUP(Y_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_YMAX)
      SET_INPUT_PULLDOWN(Y_MAX_PIN);
    #else
      SET_INPUT(Y_MAX_PIN);
    #endif
  #endif

  #if HAS_Y2_MAX
    #if ENABLED(ENDSTOPPULLUP_YMAX)
      SET_INPUT_PULLUP(Y2_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_YMAX)
      SET_INPUT_PULLDOWN(Y2_MAX_PIN);
    #else
      SET_INPUT(Y2_MAX_PIN);
    #endif
  #endif

  #if HAS_Z_MAX
    #if ENABLED(ENDSTOPPULLUP_ZMAX)
      SET_INPUT_PULLUP(Z_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMAX)
      SET_INPUT_PULLDOWN(Z_MAX_PIN);
    #else
      SET_INPUT(Z_MAX_PIN);
    #endif
  #endif

  #if HAS_Z2_MAX
    #if ENABLED(ENDSTOPPULLUP_ZMAX)
      SET_INPUT_PULLUP(Z2_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMAX)
      SET_INPUT_PULLDOWN(Z2_MAX_PIN);
    #else
      SET_INPUT(Z2_MAX_PIN);
    #endif
  #endif

  #if HAS_Z3_MAX
    #if ENABLED(ENDSTOPPULLUP_ZMAX)
      SET_INPUT_PULLUP(Z3_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMAX)
      SET_INPUT_PULLDOWN(Z3_MAX_PIN);
    #else
      SET_INPUT(Z3_MAX_PIN);
    #endif
  #endif

  #if HAS_Z4_MAX
    #if ENABLED(ENDSTOPPULLUP_ZMAX)
      SET_INPUT_PULLUP(Z4_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMAX)
      SET_INPUT_PULLDOWN(Z4_MAX_PIN);
    #else
      SET_INPUT(Z4_MAX_PIN);
    #endif
  #endif

  #if HAS_I_MIN
    #if ENABLED(ENDSTOPPULLUP_IMIN)
      SET_INPUT_PULLUP(I_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_IMIN)
      SET_INPUT_PULLDOWN(I_MIN_PIN);
    #else
      SET_INPUT(I_MIN_PIN);
    #endif
  #endif

  #if HAS_I_MAX
    #if ENABLED(ENDSTOPPULLUP_IMAX)
      SET_INPUT_PULLUP(I_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_IMAX)
      SET_INPUT_PULLDOWN(I_MAX_PIN);
    #else
      SET_INPUT(I_MAX_PIN);
    #endif
  #endif

  #if HAS_J_MIN
    #if ENABLED(ENDSTOPPULLUP_JMIN)
      SET_INPUT_PULLUP(J_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_IMIN)
      SET_INPUT_PULLDOWN(J_MIN_PIN);
    #else
      SET_INPUT(J_MIN_PIN);
    #endif
  #endif

  #if HAS_J_MAX
    #if ENABLED(ENDSTOPPULLUP_JMAX)
      SET_INPUT_PULLUP(J_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_JMAX)
      SET_INPUT_PULLDOWN(J_MAX_PIN);
    #else
      SET_INPUT(J_MAX_PIN);
    #endif
  #endif

  #if HAS_K_MIN
    #if ENABLED(ENDSTOPPULLUP_KMIN)
      SET_INPUT_PULLUP(K_MIN_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_KMIN)
      SET_INPUT_PULLDOWN(K_MIN_PIN);
    #else
      SET_INPUT(K_MIN_PIN);
    #endif
  #endif

  #if HAS_K_MAX
    #if ENABLED(ENDSTOPPULLUP_KMAX)
      SET_INPUT_PULLUP(K_MAX_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_KMIN)
      SET_INPUT_PULLDOWN(K_MAX_PIN);
    #else
      SET_INPUT(K_MAX_PIN);
    #endif
  #endif

  #if PIN_EXISTS(CALIBRATION)
=======
  #if USE_CALIBRATION
>>>>>>> origin/release-2.1.3-beta2
    #if ENABLED(CALIBRATION_PIN_PULLUP)
      SET_INPUT_PULLUP(CALIBRATION_PIN);
    #elif ENABLED(CALIBRATION_PIN_PULLDOWN)
      SET_INPUT_PULLDOWN(CALIBRATION_PIN);
    #else
      SET_INPUT(CALIBRATION_PIN);
    #endif
  #endif

<<<<<<< HEAD
  #if USES_Z_MIN_PROBE_PIN
=======
  #if USE_Z_MIN_PROBE
>>>>>>> origin/release-2.1.3-beta2
    #if ENABLED(ENDSTOPPULLUP_ZMIN_PROBE)
      SET_INPUT_PULLUP(Z_MIN_PROBE_PIN);
    #elif ENABLED(ENDSTOPPULLDOWN_ZMIN_PROBE)
      SET_INPUT_PULLDOWN(Z_MIN_PROBE_PIN);
    #else
      SET_INPUT(Z_MIN_PROBE_PIN);
    #endif
  #endif

  #if ENABLED(PROBE_ACTIVATION_SWITCH)
    SET_INPUT(PROBE_ACTIVATION_SWITCH_PIN);
  #endif

  TERN_(PROBE_TARE, probe.tare());

  TERN_(ENDSTOP_INTERRUPTS_FEATURE, setup_endstop_interrupts());

  // Enable endstops
  enable_globally(ENABLED(ENDSTOPS_ALWAYS_ON_DEFAULT));

} // Endstops::init

// Called at ~1kHz from Temperature ISR: Poll endstop state if required
void Endstops::poll() {

  TERN_(PINS_DEBUGGING, run_monitor()); // Report changes in endstop status

  #if DISABLED(ENDSTOP_INTERRUPTS_FEATURE)
    update();
  #elif ENDSTOP_NOISE_THRESHOLD
    if (endstop_poll_count) update();
  #endif
}

void Endstops::enable_globally(const bool onoff) {
  enabled_globally = enabled = onoff;
  resync();
}

// Enable / disable endstop checking
void Endstops::enable(const bool onoff) {
  enabled = onoff;
  resync();
}

// Disable / Enable endstops based on ENSTOPS_ONLY_FOR_HOMING and global enable
void Endstops::not_homing() {
  enabled = enabled_globally;
}

#if ENABLED(VALIDATE_HOMING_ENDSTOPS)
  // If the last move failed to trigger an endstop, call kill
  void Endstops::validate_homing_move() {
<<<<<<< HEAD
    if (trigger_state()) hit_on_purpose();
    else {
    DGUSScreenHandlerMKS::Error(GET_TEXT_F(MSG_KILL_HOMING_FAILED), 0); //свое
    kill(GET_TEXT_F(MSG_KILL_HOMING_FAILED));
=======
    if (trigger_state())
      hit_on_purpose();
    else {
      TERN_(SOVOL_SV06_RTS, rts.gotoPageBeep(ID_KillHome_L, ID_KillHome_D));
      kill(GET_TEXT_F(MSG_KILL_HOMING_FAILED));
>>>>>>> origin/release-2.1.3-beta2
    }
  }
#endif

// Enable / disable endstop z-probe checking
#if HAS_BED_PROBE
  void Endstops::enable_z_probe(const bool onoff) {
    z_probe_enabled = onoff;
    #if PIN_EXISTS(PROBE_ENABLE)
      WRITE(PROBE_ENABLE_PIN, onoff);
    #endif
<<<<<<< HEAD
=======
    resync();
  }
#endif

// Enable / disable calibration probe checking
#if ENABLED(CALIBRATION_GCODE)
  void Endstops::enable_calibration_probe(const bool onoff, const bool stop_state) {
    // Avoid race condition by setting stop state first
    if (onoff) calibration_stop_state = stop_state;
    calibration_probe_enabled = onoff;

>>>>>>> origin/release-2.1.3-beta2
    resync();
  }
#endif

// Get the stable endstop states when enabled
void Endstops::resync() {
  if (!abort_enabled()) return;     // If endstops/probes are disabled the loop below can hang

  // Wait for Temperature ISR to run at least once (runs at 1kHz)
  TERN(ENDSTOP_INTERRUPTS_FEATURE, update(), safe_delay(2));
  while (TERN0(ENDSTOP_NOISE_THRESHOLD, endstop_poll_count)) safe_delay(1);
}

#if ENABLED(PINS_DEBUGGING)
  void Endstops::run_monitor() {
    if (!monitor_flag) return;
    static uint8_t monitor_count = 16;  // offset this check from the others
    monitor_count += _BV(1);            //  15 Hz
    monitor_count &= 0x7F;
    if (!monitor_count) monitor();      // report changes in endstop status
  }
#endif

void Endstops::event_handler() {
  static endstop_mask_t prev_hit_state; // = 0
  if (hit_state == prev_hit_state) return;
  prev_hit_state = hit_state;
  if (hit_state) {
    #if HAS_STATUS_MESSAGE
<<<<<<< HEAD
      char NUM_AXIS_LIST(chrX = ' ', chrY = ' ', chrZ = ' ', chrI = ' ', chrJ = ' ', chrK = ' '),
=======
      char NUM_AXIS_LIST_(chrX = ' ', chrY = ' ', chrZ = ' ', chrI = ' ', chrJ = ' ', chrK = ' ', chrU = ' ', chrV = ' ', chrW = ' ')
>>>>>>> origin/release-2.1.3-beta2
           chrP = ' ';
      #define _SET_STOP_CHAR(A,C) (chr## A = C)
    #else
      #define _SET_STOP_CHAR(A,C) NOOP
    #endif

    #define _ENDSTOP_HIT_ECHO(A,C) do{ \
      SERIAL_ECHOPGM(" " STRINGIFY(A) ":", planner.triggered_position_mm(_AXIS(A))); _SET_STOP_CHAR(A,C); }while(0)

    #define _ENDSTOP_HIT_TEST(A,C) \
<<<<<<< HEAD
      if (TERN0(HAS_##A##_MIN, TEST(hit_state, A##_MIN)) || TERN0(HAS_##A##_MAX, TEST(hit_state, A##_MAX))) \
=======
      if (TERN0(HAS_##A##_MIN_STATE, TEST(hit_state, ES_ENUM(A,MIN))) || TERN0(HAS_##A##_MAX_STATE, TEST(hit_state, ES_ENUM(A,MAX)))) \
>>>>>>> origin/release-2.1.3-beta2
        _ENDSTOP_HIT_ECHO(A,C)

    #define ENDSTOP_HIT_TEST_X() _ENDSTOP_HIT_TEST(X,'X')
    #define ENDSTOP_HIT_TEST_Y() _ENDSTOP_HIT_TEST(Y,'Y')
    #define ENDSTOP_HIT_TEST_Z() _ENDSTOP_HIT_TEST(Z,'Z')
    #define ENDSTOP_HIT_TEST_I() _ENDSTOP_HIT_TEST(I,'I')
    #define ENDSTOP_HIT_TEST_J() _ENDSTOP_HIT_TEST(J,'J')
    #define ENDSTOP_HIT_TEST_K() _ENDSTOP_HIT_TEST(K,'K')
<<<<<<< HEAD
=======
    #define ENDSTOP_HIT_TEST_U() _ENDSTOP_HIT_TEST(U,'U')
    #define ENDSTOP_HIT_TEST_V() _ENDSTOP_HIT_TEST(V,'V')
    #define ENDSTOP_HIT_TEST_W() _ENDSTOP_HIT_TEST(W,'W')
>>>>>>> origin/release-2.1.3-beta2

    SERIAL_ECHO_START();
    SERIAL_ECHOPGM(STR_ENDSTOPS_HIT);
    NUM_AXIS_CODE(
       ENDSTOP_HIT_TEST_X(),
       ENDSTOP_HIT_TEST_Y(),
       ENDSTOP_HIT_TEST_Z(),
      _ENDSTOP_HIT_TEST(I,'I'),
      _ENDSTOP_HIT_TEST(J,'J'),
<<<<<<< HEAD
      _ENDSTOP_HIT_TEST(K,'K')
    );

    #if USES_Z_MIN_PROBE_PIN
=======
      _ENDSTOP_HIT_TEST(K,'K'),
      _ENDSTOP_HIT_TEST(U,'U'),
      _ENDSTOP_HIT_TEST(V,'V'),
      _ENDSTOP_HIT_TEST(W,'W')
    );

    #if USE_Z_MIN_PROBE
>>>>>>> origin/release-2.1.3-beta2
      #define P_AXIS Z_AXIS
      if (TEST(hit_state, Z_MIN_PROBE)) _ENDSTOP_HIT_ECHO(P, 'P');
    #endif
    SERIAL_EOL();

<<<<<<< HEAD
    TERN_(HAS_STATUS_MESSAGE,
      ui.status_printf(0,
        F(S_FMT GANG_N_1(NUM_AXES, " %c") " %c"),
        GET_TEXT(MSG_LCD_ENDSTOPS),
        NUM_AXIS_LIST(chrX, chrY, chrZ, chrI, chrJ, chrK), chrP
      )
    );
=======
    #if HAS_STATUS_MESSAGE
      ui.status_printf(0,
        F(S_FMT GANG_N_1(NUM_AXES, " %c") " %c"),
        GET_TEXT_F(MSG_LCD_ENDSTOPS),
        NUM_AXIS_LIST_(chrX, chrY, chrZ, chrI, chrJ, chrK, chrU, chrV, chrW) chrP
      );
    #endif
>>>>>>> origin/release-2.1.3-beta2

    #if ENABLED(SD_ABORT_ON_ENDSTOP_HIT)
      if (planner.abort_on_endstop_hit) {
        card.abortFilePrintNow();
        quickstop_stepper();
        thermalManager.disable_all_heaters();
        #ifdef SD_ABORT_ON_ENDSTOP_HIT_GCODE
          queue.clear();
          queue.inject(F(SD_ABORT_ON_ENDSTOP_HIT_GCODE));
        #endif
        print_job_timer.stop();
      }
    #endif
  }
}

<<<<<<< HEAD
#pragma GCC diagnostic push
#if GCC_VERSION <= 50000
  #pragma GCC diagnostic ignored "-Wunused-function"
#endif

static void print_es_state(const bool is_hit, FSTR_P const flabel=nullptr) {
  if (flabel) SERIAL_ECHOF(flabel);
  SERIAL_ECHOPGM(": ");
  SERIAL_ECHOLNF(is_hit ? F(STR_ENDSTOP_HIT) : F(STR_ENDSTOP_OPEN));
}

#pragma GCC diagnostic pop
=======
#if NUM_AXES

  #pragma GCC diagnostic push
  #if GCC_VERSION <= 50000
    #pragma GCC diagnostic ignored "-Wunused-function"
  #endif

  static void print_es_state(const bool is_hit, FSTR_P const flabel=nullptr) {
    if (flabel) SERIAL_ECHO(flabel);
    SERIAL_ECHOLN(F(": "), is_hit ? F(STR_ENDSTOP_HIT) : F(STR_ENDSTOP_OPEN));
  }

  #pragma GCC diagnostic pop

#endif
>>>>>>> origin/release-2.1.3-beta2

void __O2 Endstops::report_states() {
  TERN_(BLTOUCH, bltouch._set_SW_mode());
  SERIAL_ECHOLNPGM(STR_M119_REPORT);
<<<<<<< HEAD
  #define ES_REPORT(S) print_es_state(READ(S##_PIN) != S##_ENDSTOP_INVERTING, F(STR_##S))
  #if HAS_X_MIN
=======
  #define ES_REPORT(S) print_es_state(READ_ENDSTOP(S##_PIN) == S##_ENDSTOP_HIT_STATE, F(STR_##S))
  #if USE_X_MIN
>>>>>>> origin/release-2.1.3-beta2
    ES_REPORT(X_MIN);
  #endif
  #if USE_X2_MIN
    ES_REPORT(X2_MIN);
  #endif
  #if USE_X_MAX
    ES_REPORT(X_MAX);
  #endif
  #if USE_X2_MAX
    ES_REPORT(X2_MAX);
  #endif
  #if USE_Y_MIN
    ES_REPORT(Y_MIN);
  #endif
  #if USE_Y2_MIN
    ES_REPORT(Y2_MIN);
  #endif
  #if USE_Y_MAX
    ES_REPORT(Y_MAX);
  #endif
  #if USE_Y2_MAX
    ES_REPORT(Y2_MAX);
  #endif
  #if USE_Z_MIN
    ES_REPORT(Z_MIN);
  #endif
  #if USE_Z2_MIN
    ES_REPORT(Z2_MIN);
  #endif
  #if USE_Z3_MIN
    ES_REPORT(Z3_MIN);
  #endif
  #if USE_Z4_MIN
    ES_REPORT(Z4_MIN);
  #endif
  #if USE_Z_MAX
    ES_REPORT(Z_MAX);
  #endif
  #if USE_Z2_MAX
    ES_REPORT(Z2_MAX);
  #endif
  #if USE_Z3_MAX
    ES_REPORT(Z3_MAX);
  #endif
  #if USE_Z4_MAX
    ES_REPORT(Z4_MAX);
  #endif
<<<<<<< HEAD
  #if HAS_I_MIN
    ES_REPORT(I_MIN);
  #endif
  #if HAS_I_MAX
    ES_REPORT(I_MAX);
  #endif
  #if HAS_J_MIN
    ES_REPORT(J_MIN);
  #endif
  #if HAS_J_MAX
    ES_REPORT(J_MAX);
  #endif
  #if HAS_K_MIN
    ES_REPORT(K_MIN);
  #endif
  #if HAS_K_MAX
    ES_REPORT(K_MAX);
  #endif
  #if ENABLED(PROBE_ACTIVATION_SWITCH)
    print_es_state(probe_switch_activated(), F(STR_PROBE_EN));
  #endif
  #if USES_Z_MIN_PROBE_PIN
    print_es_state(PROBE_TRIGGERED(), F(STR_Z_PROBE));
  #endif
  #if MULTI_FILAMENT_SENSOR
    #define _CASE_RUNOUT(N) case N: pin = FIL_RUNOUT##N##_PIN; state = FIL_RUNOUT##N##_STATE; break;
    LOOP_S_LE_N(i, 1, NUM_RUNOUT_SENSORS) {
      pin_t pin;
      uint8_t state;
      switch (i) {
        default: continue;
        REPEAT_1(NUM_RUNOUT_SENSORS, _CASE_RUNOUT)
      }
      SERIAL_ECHOPGM(STR_FILAMENT);
      if (i > 1) SERIAL_CHAR(' ', '0' + i);
      print_es_state(extDigitalRead(pin) != state);
    }
    #undef _CASE_RUNOUT
  #elif HAS_FILAMENT_SENSOR
    print_es_state(READ(FIL_RUNOUT1_PIN) != FIL_RUNOUT1_STATE, F(STR_FILAMENT));
=======
  #if USE_I_MIN
    ES_REPORT(I_MIN);
  #endif
  #if USE_I_MAX
    ES_REPORT(I_MAX);
  #endif
  #if USE_J_MIN
    ES_REPORT(J_MIN);
  #endif
  #if USE_J_MAX
    ES_REPORT(J_MAX);
  #endif
  #if USE_K_MIN
    ES_REPORT(K_MIN);
  #endif
  #if USE_K_MAX
    ES_REPORT(K_MAX);
  #endif
  #if USE_U_MIN
    ES_REPORT(U_MIN);
  #endif
  #if USE_U_MAX
    ES_REPORT(U_MAX);
  #endif
  #if USE_V_MIN
    ES_REPORT(V_MIN);
  #endif
  #if USE_V_MAX
    ES_REPORT(V_MAX);
  #endif
  #if USE_W_MIN
    ES_REPORT(W_MIN);
  #endif
  #if USE_W_MAX
    ES_REPORT(W_MAX);
  #endif
  #if ENABLED(PROBE_ACTIVATION_SWITCH)
    print_es_state(probe_switch_activated(), F(STR_PROBE_EN));
  #endif
  #if USE_Z_MIN_PROBE
    print_es_state(PROBE_TRIGGERED(), F(STR_Z_PROBE));
  #endif
  #if USE_CALIBRATION
    print_es_state(READ(CALIBRATION_PIN) != CALIBRATION_PIN_INVERTING, F(STR_CALIBRATION));
  #endif
  #if MULTI_FILAMENT_SENSOR
    #define _CASE_RUNOUT(N) do{ \
      SERIAL_ECHO(F(STR_FILAMENT)); \
      if ((N) > 1) SERIAL_CHAR(' ', '0' + char(N)); \
      print_es_state(!FILAMENT_IS_OUT(N)); \
    }while(0);
    REPEAT_1(NUM_RUNOUT_SENSORS, _CASE_RUNOUT)
    #undef _CASE_RUNOUT
  #elif HAS_FILAMENT_SENSOR
    print_es_state(!FILAMENT_IS_OUT(), F(STR_FILAMENT));
>>>>>>> origin/release-2.1.3-beta2
  #endif

  TERN_(BLTOUCH, bltouch._reset_SW_mode());
  TERN_(JOYSTICK_DEBUG, joystick.report());

} // Endstops::report_states

<<<<<<< HEAD
#if HAS_DELTA_SENSORLESS_PROBING
  #define __ENDSTOP(AXIS, ...) AXIS ##_MAX
  #define _ENDSTOP_PIN(AXIS, ...) AXIS ##_MAX_PIN
  #define _ENDSTOP_INVERTING(AXIS, ...) AXIS ##_MAX_ENDSTOP_INVERTING
#else
  #define __ENDSTOP(AXIS, MINMAX) AXIS ##_## MINMAX
  #define _ENDSTOP_PIN(AXIS, MINMAX) AXIS ##_## MINMAX ##_PIN
  #define _ENDSTOP_INVERTING(AXIS, MINMAX) AXIS ##_## MINMAX ##_ENDSTOP_INVERTING
#endif
#define _ENDSTOP(AXIS, MINMAX) __ENDSTOP(AXIS, MINMAX)

=======
>>>>>>> origin/release-2.1.3-beta2
/**
 * Called from interrupt context by the Endstop ISR or Stepper ISR!
 * Read endstops to get their current states, register hits for all
 * axes moving in the direction of their endstops, and abort moves.
 */
void Endstops::update() {

  #if !ENDSTOP_NOISE_THRESHOLD      // If not debouncing...
    if (!abort_enabled()) return;   // ...and not enabled, exit.
  #endif

  // Macros to update / copy the live_state
<<<<<<< HEAD
  #define UPDATE_ENDSTOP_BIT(AXIS, MINMAX) SET_BIT_TO(live_state, _ENDSTOP(AXIS, MINMAX), (READ(_ENDSTOP_PIN(AXIS, MINMAX)) != _ENDSTOP_INVERTING(AXIS, MINMAX)))
  #define COPY_LIVE_STATE(SRC_BIT, DST_BIT) SET_BIT_TO(live_state, DST_BIT, TEST(live_state, SRC_BIT))

  #if ENABLED(G38_PROBE_TARGET) && NONE(CORE_IS_XY, CORE_IS_XZ, MARKFORGED_XY, MARKFORGED_YX)
    #define HAS_G38_PROBE 1
    // For G38 moves check the probe's pin for ALL movement
    if (G38_move) UPDATE_ENDSTOP_BIT(Z, TERN(USES_Z_MIN_PROBE_PIN, MIN_PROBE, MIN));
  #endif

  // With Dual X, endstops are only checked in the homing direction for the active extruder
  #define X_MIN_TEST() TERN1(DUAL_X_CARRIAGE, TERN0(X_HOME_TO_MIN, stepper.last_moved_extruder == 0) || TERN0(X2_HOME_TO_MIN, stepper.last_moved_extruder != 0))
  #define X_MAX_TEST() TERN1(DUAL_X_CARRIAGE, TERN0(X_HOME_TO_MAX, stepper.last_moved_extruder == 0) || TERN0(X2_HOME_TO_MAX, stepper.last_moved_extruder != 0))
=======
  #define _ES_PIN(A,M) A##_##M##_PIN
  #define _ES_HIT(A,M) A##_##M##_ENDSTOP_HIT_STATE
  #define UPDATE_LIVE_STATE(AXIS, MINMAX) SET_BIT_TO(live_state, ES_ENUM(AXIS, MINMAX), (READ_ENDSTOP(_ES_PIN(AXIS, MINMAX)) == _ES_HIT(AXIS, MINMAX)))
  #define COPY_LIVE_STATE(SRC_BIT, DST_BIT) SET_BIT_TO(live_state, DST_BIT, TEST(live_state, SRC_BIT))

  #if ENABLED(G38_PROBE_TARGET)
    // For G38 moves check the probe's pin for ALL movement
    if (G38_move) UPDATE_LIVE_STATE(Z, TERN(USE_Z_MIN_PROBE, MIN_PROBE, MIN));
  #endif

  #if ENABLED(CALIBRATION_GCODE)
    if (calibration_probe_enabled) {
      #if HAS_CALIBRATION_STATE
        SET_BIT_TO(live_state, CALIBRATION, READ(CALIBRATION_PIN) != CALIBRATION_PIN_INVERTING);
      #else
        UPDATE_LIVE_STATE(Z, TERN(USE_Z_MIN_PROBE, MIN_PROBE, MIN));
      #endif
    }
  #endif

  // With Dual X, endstops are only checked in the homing direction for the active extruder
  #define X_MIN_TEST() TERN1(DUAL_X_CARRIAGE, stepper.last_moved_extruder == 0) // Check min for the left carriage
  #define X_MAX_TEST() TERN1(DUAL_X_CARRIAGE, stepper.last_moved_extruder != 0) // Check max for the right carriage
>>>>>>> origin/release-2.1.3-beta2

  // Use HEAD for core axes, AXIS for others
  #if ANY(CORE_IS_XY, CORE_IS_XZ, MARKFORGED_XY, MARKFORGED_YX)
    #define X_AXIS_HEAD X_HEAD
  #else
    #define X_AXIS_HEAD X_AXIS
  #endif
  #if ANY(CORE_IS_XY, CORE_IS_YZ, MARKFORGED_XY, MARKFORGED_YX)
    #define Y_AXIS_HEAD Y_HEAD
  #else
    #define Y_AXIS_HEAD Y_AXIS
  #endif
  #if CORE_IS_XZ || CORE_IS_YZ
    #define Z_AXIS_HEAD Z_HEAD
  #else
    #define Z_AXIS_HEAD Z_AXIS
  #endif

  #define I_AXIS_HEAD I_AXIS
  #define J_AXIS_HEAD J_AXIS
  #define K_AXIS_HEAD K_AXIS
<<<<<<< HEAD
=======
  #define U_AXIS_HEAD U_AXIS
  #define V_AXIS_HEAD V_AXIS
  #define W_AXIS_HEAD W_AXIS
>>>>>>> origin/release-2.1.3-beta2

  /**
   * Check and update endstops
   */
  #if USE_X_MIN
    UPDATE_LIVE_STATE(X, MIN);
    #if ENABLED(X_DUAL_ENDSTOPS)
      #if USE_X2_MIN
        UPDATE_LIVE_STATE(X2, MIN);
      #else
        COPY_LIVE_STATE(X_MIN, X2_MIN);
      #endif
    #endif
  #endif

  #if USE_X_MAX
    UPDATE_LIVE_STATE(X, MAX);
    #if ENABLED(X_DUAL_ENDSTOPS)
      #if USE_X2_MAX
        UPDATE_LIVE_STATE(X2, MAX);
      #else
        COPY_LIVE_STATE(X_MAX, X2_MAX);
      #endif
    #endif
  #endif

  #if USE_Y_MIN
    UPDATE_LIVE_STATE(Y, MIN);
    #if ENABLED(Y_DUAL_ENDSTOPS)
      #if USE_Y2_MIN
        UPDATE_LIVE_STATE(Y2, MIN);
      #else
        COPY_LIVE_STATE(Y_MIN, Y2_MIN);
      #endif
    #endif
  #endif

  #if USE_Y_MAX
    UPDATE_LIVE_STATE(Y, MAX);
    #if ENABLED(Y_DUAL_ENDSTOPS)
      #if USE_Y2_MAX
        UPDATE_LIVE_STATE(Y2, MAX);
      #else
        COPY_LIVE_STATE(Y_MAX, Y2_MAX);
      #endif
    #endif
  #endif

<<<<<<< HEAD
  #if HAS_Z_MIN && NONE(Z_SPI_SENSORLESS, Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN)
    UPDATE_ENDSTOP_BIT(Z, MIN);
    #if ENABLED(Z_MULTI_ENDSTOPS)
      #if HAS_Z2_MIN
        UPDATE_ENDSTOP_BIT(Z2, MIN);
      #else
        COPY_LIVE_STATE(Z_MIN, Z2_MIN);
      #endif
      #if NUM_Z_STEPPERS >= 3
        #if HAS_Z3_MIN
          UPDATE_ENDSTOP_BIT(Z3, MIN);
        #else
          COPY_LIVE_STATE(Z_MIN, Z3_MIN);
        #endif
      #endif
      #if NUM_Z_STEPPERS >= 4
        #if HAS_Z4_MIN
          UPDATE_ENDSTOP_BIT(Z4, MIN);
        #else
          COPY_LIVE_STATE(Z_MIN, Z4_MIN);
        #endif
      #endif
    #endif
=======
  #if USE_Z_MIN && NONE(Z_SPI_SENSORLESS, Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN)
    UPDATE_LIVE_STATE(Z, MIN);
  #endif
  #if USE_Z2_MIN
    UPDATE_LIVE_STATE(Z2, MIN);
  #elif HAS_Z2_MIN_STATE
    COPY_LIVE_STATE(Z_MIN, Z2_MIN);
  #endif
  #if USE_Z3_MIN
    UPDATE_LIVE_STATE(Z3, MIN);
  #elif HAS_Z3_MIN_STATE
    COPY_LIVE_STATE(Z_MIN, Z3_MIN);
  #endif
  #if USE_Z4_MIN
    UPDATE_LIVE_STATE(Z4, MIN);
  #elif HAS_Z4_MIN_STATE
    COPY_LIVE_STATE(Z_MIN, Z4_MIN);
>>>>>>> origin/release-2.1.3-beta2
  #endif

  #if HAS_REAL_BED_PROBE
    // When closing the gap check the enabled probe
    if (probe_switch_activated())
<<<<<<< HEAD
      UPDATE_ENDSTOP_BIT(Z, TERN(USES_Z_MIN_PROBE_PIN, MIN_PROBE, MIN));
  #endif

  #if HAS_Z_MAX && !Z_SPI_SENSORLESS
    // Check both Z dual endstops
    #if ENABLED(Z_MULTI_ENDSTOPS)
      UPDATE_ENDSTOP_BIT(Z, MAX);
      #if HAS_Z2_MAX
        UPDATE_ENDSTOP_BIT(Z2, MAX);
      #else
        COPY_LIVE_STATE(Z_MAX, Z2_MAX);
      #endif
      #if NUM_Z_STEPPERS >= 3
        #if HAS_Z3_MAX
          UPDATE_ENDSTOP_BIT(Z3, MAX);
        #else
          COPY_LIVE_STATE(Z_MAX, Z3_MAX);
        #endif
      #endif
      #if NUM_Z_STEPPERS >= 4
        #if HAS_Z4_MAX
          UPDATE_ENDSTOP_BIT(Z4, MAX);
        #else
          COPY_LIVE_STATE(Z_MAX, Z4_MAX);
        #endif
      #endif
    #elif TERN1(USES_Z_MIN_PROBE_PIN, Z_MAX_PIN != Z_MIN_PROBE_PIN)
      // If this pin isn't the bed probe it's the Z endstop
      UPDATE_ENDSTOP_BIT(Z, MAX);
    #endif
=======
      UPDATE_LIVE_STATE(Z, TERN(USE_Z_MIN_PROBE, MIN_PROBE, MIN));
  #endif

  #if USE_Z_MAX
    UPDATE_LIVE_STATE(Z, MAX);
  #endif
  #if USE_Z2_MAX
    UPDATE_LIVE_STATE(Z2, MAX);
  #elif HAS_Z2_MAX_STATE
    COPY_LIVE_STATE(Z_MAX, Z2_MAX);
  #endif
  #if USE_Z3_MAX
    UPDATE_LIVE_STATE(Z3, MAX);
  #elif HAS_Z3_MAX_STATE
    COPY_LIVE_STATE(Z_MAX, Z3_MAX);
  #endif
  #if USE_Z4_MAX
    UPDATE_LIVE_STATE(Z4, MAX);
  #elif HAS_Z4_MAX_STATE
    COPY_LIVE_STATE(Z_MAX, Z4_MAX);
  #endif

  #if USE_I_MIN
    UPDATE_LIVE_STATE(I, MIN);
  #endif
  #if USE_I_MAX
    UPDATE_LIVE_STATE(I, MAX);
  #endif
  #if USE_J_MIN
    UPDATE_LIVE_STATE(J, MIN);
  #endif
  #if USE_J_MAX
    UPDATE_LIVE_STATE(J, MAX);
  #endif
  #if USE_K_MIN
    UPDATE_LIVE_STATE(K, MIN);
  #endif
  #if USE_K_MAX
    UPDATE_LIVE_STATE(K, MAX);
  #endif
  #if USE_U_MIN
    UPDATE_LIVE_STATE(U, MIN);
  #endif
  #if USE_U_MAX
    UPDATE_LIVE_STATE(U, MAX);
  #endif
  #if USE_V_MIN
    UPDATE_LIVE_STATE(V, MIN);
  #endif
  #if USE_V_MAX
    UPDATE_LIVE_STATE(V, MAX);
  #endif
  #if USE_W_MIN
    UPDATE_LIVE_STATE(W, MIN);
  #endif
  #if USE_W_MAX
    UPDATE_LIVE_STATE(W, MAX);
>>>>>>> origin/release-2.1.3-beta2
  #endif

  #if HAS_I_MIN && !I_SPI_SENSORLESS
    #if ENABLED(I_DUAL_ENDSTOPS)
      UPDATE_ENDSTOP_BIT(I, MIN);
      #if HAS_I2_MIN
        UPDATE_ENDSTOP_BIT(I2, MAX);
      #else
        COPY_LIVE_STATE(I_MIN, I2_MIN);
      #endif
    #else
      UPDATE_ENDSTOP_BIT(I, MIN);
    #endif
  #endif

  #if HAS_I_MAX && !I_SPI_SENSORLESS
    #if ENABLED(I_DUAL_ENDSTOPS)
      UPDATE_ENDSTOP_BIT(I, MAX);
      #if HAS_I2_MAX
        UPDATE_ENDSTOP_BIT(I2, MAX);
      #else
        COPY_LIVE_STATE(I_MAX, I2_MAX);
      #endif
    #else
      UPDATE_ENDSTOP_BIT(I, MAX);
    #endif
  #endif

  #if HAS_J_MIN && !J_SPI_SENSORLESS
    #if ENABLED(J_DUAL_ENDSTOPS)
      UPDATE_ENDSTOP_BIT(J, MIN);
      #if HAS_J2_MIN
        UPDATE_ENDSTOP_BIT(J2, MIN);
      #else
        COPY_LIVE_STATE(J_MIN, J2_MIN);
      #endif
    #else
      UPDATE_ENDSTOP_BIT(J, MIN);
    #endif
  #endif

  #if HAS_J_MAX && !J_SPI_SENSORLESS
    #if ENABLED(J_DUAL_ENDSTOPS)
      UPDATE_ENDSTOP_BIT(J, MAX);
      #if HAS_J2_MAX
        UPDATE_ENDSTOP_BIT(J2, MAX);
      #else
        COPY_LIVE_STATE(J_MAX, J2_MAX);
      #endif
    #else
      UPDATE_ENDSTOP_BIT(J, MAX);
    #endif
  #endif

  #if HAS_K_MIN && !K_SPI_SENSORLESS
    #if ENABLED(K_DUAL_ENDSTOPS)
      UPDATE_ENDSTOP_BIT(K, MIN);
      #if HAS_K2_MIN
        UPDATE_ENDSTOP_BIT(K2, MIN);
      #else
        COPY_LIVE_STATE(K_MIN, K2_MIN);
      #endif
    #else
      UPDATE_ENDSTOP_BIT(K, MIN);
    #endif
  #endif

  #if HAS_K_MAX && !K_SPI_SENSORLESS
    #if ENABLED(K_DUAL_ENDSTOPS)
      UPDATE_ENDSTOP_BIT(K, MAX);
      #if HAS_K2_MAX
        UPDATE_ENDSTOP_BIT(K2, MAX);
      #else
        COPY_LIVE_STATE(K_MAX, K2_MAX);
      #endif
    #else
      UPDATE_ENDSTOP_BIT(K, MAX);
    #endif
  #endif

  #if ENDSTOP_NOISE_THRESHOLD

    /**
     * Filtering out noise on endstops requires a delayed decision. Let's assume, due to noise,
     * that 50% of endstop signal samples are good and 50% are bad (assuming normal distribution
     * of random noise). Then the first sample has a 50% chance to be good or bad. The 2nd sample
     * also has a 50% chance to be good or bad. The chances of 2 samples both being bad becomes
     * 50% of 50%, or 25%. That was the previous implementation of Marlin endstop handling. It
     * reduces chances of bad readings in half, at the cost of 1 extra sample period, but chances
     * still exist. The only way to reduce them further is to increase the number of samples.
     * To reduce the chance to 1% (1/128th) requires 7 samples (adding 7ms of delay).
     */
    static endstop_mask_t old_live_state;
    if (old_live_state != live_state) {
      endstop_poll_count = ENDSTOP_NOISE_THRESHOLD;
      old_live_state = live_state;
    }
    else if (endstop_poll_count && !--endstop_poll_count)
      validated_live_state = live_state;

    if (!abort_enabled()) return;

  #endif

  // Test the current status of an endstop
  #define TEST_ENDSTOP(ENDSTOP) (TEST(state(), ENDSTOP))

  // Record endstop was hit
  #define _ENDSTOP_HIT(AXIS, MINMAX) SBI(hit_state, ES_ENUM(AXIS, MINMAX))

  // Call the endstop triggered routine for single endstops
  #define PROCESS_ENDSTOP(AXIS, MINMAX) do { \
    if (TEST_ENDSTOP(ES_ENUM(AXIS, MINMAX))) { \
      _ENDSTOP_HIT(AXIS, MINMAX); \
      planner.endstop_triggered(_AXIS(AXIS)); \
    } \
  }while(0)

  // Core Sensorless Homing needs to test an Extra Pin
  #define CORE_DIAG(QQ,A,MM) (CORE_IS_##QQ && A##_SENSORLESS && !A##_SPI_SENSORLESS && USE_##A##_##MM)
  #define PROCESS_CORE_ENDSTOP(A1,M1,A2,M2) do { \
    if (TEST_ENDSTOP(ES_ENUM(A1,M1))) { \
      _ENDSTOP_HIT(A2,M2); \
      planner.endstop_triggered(_AXIS(A2)); \
    } \
  }while(0)

  // Call the endstop triggered routine for dual endstops
  #define PROCESS_DUAL_ENDSTOP(A, MINMAX) do { \
    const byte dual_hit = TEST_ENDSTOP(ES_ENUM(A, MINMAX)) | (TEST_ENDSTOP(ES_ENUM(A##2, MINMAX)) << 1); \
    if (dual_hit) { \
      _ENDSTOP_HIT(A, MINMAX); \
      /* if not performing home or if both endstops were triggered during homing... */ \
      if (!stepper.separate_multi_axis || dual_hit == 0b11) \
        planner.endstop_triggered(_AXIS(A)); \
    } \
  }while(0)

  #define PROCESS_TRIPLE_ENDSTOP(A, MINMAX) do { \
    const byte triple_hit = TEST_ENDSTOP(ES_ENUM(A, MINMAX)) | (TEST_ENDSTOP(ES_ENUM(A##2, MINMAX)) << 1) | (TEST_ENDSTOP(ES_ENUM(A##3, MINMAX)) << 2); \
    if (triple_hit) { \
      _ENDSTOP_HIT(A, MINMAX); \
      /* if not performing home or if both endstops were triggered during homing... */ \
      if (!stepper.separate_multi_axis || triple_hit == 0b111) \
        planner.endstop_triggered(_AXIS(A)); \
    } \
  }while(0)

  #define PROCESS_QUAD_ENDSTOP(A, MINMAX) do { \
    const byte quad_hit = TEST_ENDSTOP(ES_ENUM(A, MINMAX)) | (TEST_ENDSTOP(ES_ENUM(A##2, MINMAX)) << 1) | (TEST_ENDSTOP(ES_ENUM(A##3, MINMAX)) << 2) | (TEST_ENDSTOP(ES_ENUM(A##4, MINMAX)) << 3); \
    if (quad_hit) { \
      _ENDSTOP_HIT(A, MINMAX); \
      /* if not performing home or if both endstops were triggered during homing... */ \
      if (!stepper.separate_multi_axis || quad_hit == 0b1111) \
        planner.endstop_triggered(_AXIS(A)); \
    } \
  }while(0)

  #if ENABLED(X_DUAL_ENDSTOPS)
    #define PROCESS_ENDSTOP_X(MINMAX) PROCESS_DUAL_ENDSTOP(X, MINMAX)
  #else
    #define PROCESS_ENDSTOP_X(MINMAX) if (X_##MINMAX##_TEST()) PROCESS_ENDSTOP(X, MINMAX)
  #endif

  #if ENABLED(Y_DUAL_ENDSTOPS)
    #define PROCESS_ENDSTOP_Y(MINMAX) PROCESS_DUAL_ENDSTOP(Y, MINMAX)
  #else
    #define PROCESS_ENDSTOP_Y(MINMAX) PROCESS_ENDSTOP(Y, MINMAX)
  #endif

  #if DISABLED(Z_MULTI_ENDSTOPS)
    #define PROCESS_ENDSTOP_Z(MINMAX) PROCESS_ENDSTOP(Z, MINMAX)
  #elif NUM_Z_STEPPERS == 4
    #define PROCESS_ENDSTOP_Z(MINMAX) PROCESS_QUAD_ENDSTOP(Z, MINMAX)
  #elif NUM_Z_STEPPERS == 3
    #define PROCESS_ENDSTOP_Z(MINMAX) PROCESS_TRIPLE_ENDSTOP(Z, MINMAX)
  #else
    #define PROCESS_ENDSTOP_Z(MINMAX) PROCESS_DUAL_ENDSTOP(Z, MINMAX)
  #endif

<<<<<<< HEAD
  #if HAS_G38_PROBE
    #define _G38_OPEN_STATE TERN(G38_PROBE_AWAY, (G38_move >= 4), LOW)
    // For G38 moves check the probe's pin for ALL movement
    if (G38_move && TEST_ENDSTOP(_ENDSTOP(Z, TERN(USES_Z_MIN_PROBE_PIN, MIN_PROBE, MIN))) != _G38_OPEN_STATE) {
             if (stepper.axis_is_moving(X_AXIS)) { _ENDSTOP_HIT(X, TERN(X_HOME_TO_MIN, MIN, MAX)); planner.endstop_triggered(X_AXIS); }
      #if HAS_Y_AXIS
        else if (stepper.axis_is_moving(Y_AXIS)) { _ENDSTOP_HIT(Y, TERN(Y_HOME_TO_MIN, MIN, MAX)); planner.endstop_triggered(Y_AXIS); }
      #endif
      #if HAS_Z_AXIS
        else if (stepper.axis_is_moving(Z_AXIS)) { _ENDSTOP_HIT(Z, TERN(Z_HOME_TO_MIN, MIN, MAX)); planner.endstop_triggered(Z_AXIS); }
      #endif
=======
  #if ENABLED(G38_PROBE_TARGET)
    // For G38 moves check the probe's pin for ALL movement
    if (G38_move && TEST_ENDSTOP(Z_MIN_PROBE) == TERN1(G38_PROBE_AWAY, (G38_move < 4))) {
>>>>>>> origin/release-2.1.3-beta2
      G38_did_trigger = true;
      #define _G38_SET(Q) | (stepper.axis_is_moving(_AXIS(Q)) << _AXIS(Q))
      #define _G38_RESP(Q) if (moving[_AXIS(Q)]) { _ENDSTOP_HIT(Q, ENDSTOP); planner.endstop_triggered(_AXIS(Q)); }
      const Flags<NUM_AXES> moving = { uvalue_t(NUM_AXES)(0 MAIN_AXIS_MAP(_G38_SET)) };
      MAIN_AXIS_MAP(_G38_RESP);
    }
  #endif

  #if ENABLED(CALIBRATION_GCODE)
    if (calibration_probe_enabled
        && calibration_stop_state == TEST(live_state, TERN(HAS_CALIBRATION_STATE, CALIBRATION, Z_MIN_PROBE)))
      stepper.quick_stop();
  #endif

  // Signal, after validation, if an endstop limit is pressed or not

<<<<<<< HEAD
  if (stepper.axis_is_moving(X_AXIS)) {
    if (stepper.motor_direction(X_AXIS_HEAD)) { // -direction
      #if HAS_X_MIN || (X_SPI_SENSORLESS && X_HOME_TO_MIN)
        PROCESS_ENDSTOP_X(MIN);
        #if   CORE_DIAG(XY, Y, MIN)
          PROCESS_CORE_ENDSTOP(Y,MIN,X,MIN);
        #elif CORE_DIAG(XY, Y, MAX)
          PROCESS_CORE_ENDSTOP(Y,MAX,X,MIN);
        #elif CORE_DIAG(XZ, Z, MIN)
          PROCESS_CORE_ENDSTOP(Z,MIN,X,MIN);
        #elif CORE_DIAG(XZ, Z, MAX)
          PROCESS_CORE_ENDSTOP(Z,MAX,X,MIN);
        #endif
      #endif
    }
    else { // +direction
      #if HAS_X_MAX || (X_SPI_SENSORLESS && X_HOME_TO_MAX)
        PROCESS_ENDSTOP_X(MAX);
        #if   CORE_DIAG(XY, Y, MIN)
          PROCESS_CORE_ENDSTOP(Y,MIN,X,MAX);
        #elif CORE_DIAG(XY, Y, MAX)
          PROCESS_CORE_ENDSTOP(Y,MAX,X,MAX);
        #elif CORE_DIAG(XZ, Z, MIN)
          PROCESS_CORE_ENDSTOP(Z,MIN,X,MAX);
        #elif CORE_DIAG(XZ, Z, MAX)
          PROCESS_CORE_ENDSTOP(Z,MAX,X,MAX);
        #endif
      #endif
    }
  }

  #if HAS_Y_AXIS
    if (stepper.axis_is_moving(Y_AXIS)) {
      if (stepper.motor_direction(Y_AXIS_HEAD)) { // -direction
        #if HAS_Y_MIN || (Y_SPI_SENSORLESS && Y_HOME_TO_MIN)
          PROCESS_ENDSTOP_Y(MIN);
          #if   CORE_DIAG(XY, X, MIN)
            PROCESS_CORE_ENDSTOP(X,MIN,Y,MIN);
          #elif CORE_DIAG(XY, X, MAX)
            PROCESS_CORE_ENDSTOP(X,MAX,Y,MIN);
          #elif CORE_DIAG(YZ, Z, MIN)
            PROCESS_CORE_ENDSTOP(Z,MIN,Y,MIN);
          #elif CORE_DIAG(YZ, Z, MAX)
            PROCESS_CORE_ENDSTOP(Z,MAX,Y,MIN);
          #endif
        #endif
      }
      else { // +direction
        #if HAS_Y_MAX || (Y_SPI_SENSORLESS && Y_HOME_TO_MAX)
          PROCESS_ENDSTOP_Y(MAX);
          #if   CORE_DIAG(XY, X, MIN)
            PROCESS_CORE_ENDSTOP(X,MIN,Y,MAX);
          #elif CORE_DIAG(XY, X, MAX)
            PROCESS_CORE_ENDSTOP(X,MAX,Y,MAX);
          #elif CORE_DIAG(YZ, Z, MIN)
            PROCESS_CORE_ENDSTOP(Z,MIN,Y,MAX);
          #elif CORE_DIAG(YZ, Z, MAX)
            PROCESS_CORE_ENDSTOP(Z,MAX,Y,MAX);
=======
  #define AXIS_IS_MOVING(A) TERN(FT_MOTION, ftMotion, stepper).axis_is_moving(_AXIS(A))
  #define AXIS_DIR_REV(A)  !TERN(FT_MOTION, ftMotion, stepper).motor_direction(A)

  #if HAS_X_AXIS
    if (AXIS_IS_MOVING(X)) {
      const AxisEnum x_head = TERN0(FT_MOTION, ftMotion.cfg.active) ? X_AXIS : X_AXIS_HEAD;
      if (AXIS_DIR_REV(x_head)) {
        #if HAS_X_MIN_STATE
          PROCESS_ENDSTOP_X(MIN);
          #if   CORE_DIAG(XY, Y, MIN)
            PROCESS_CORE_ENDSTOP(Y,MIN,X,MIN);
          #elif CORE_DIAG(XY, Y, MAX)
            PROCESS_CORE_ENDSTOP(Y,MAX,X,MIN);
          #elif CORE_DIAG(XZ, Z, MIN)
            PROCESS_CORE_ENDSTOP(Z,MIN,X,MIN);
          #elif CORE_DIAG(XZ, Z, MAX)
            PROCESS_CORE_ENDSTOP(Z,MAX,X,MIN);
          #endif
        #endif
      }
      else {
        #if HAS_X_MAX_STATE
          PROCESS_ENDSTOP_X(MAX);
          #if   CORE_DIAG(XY, Y, MIN)
            PROCESS_CORE_ENDSTOP(Y,MIN,X,MAX);
          #elif CORE_DIAG(XY, Y, MAX)
            PROCESS_CORE_ENDSTOP(Y,MAX,X,MAX);
          #elif CORE_DIAG(XZ, Z, MIN)
            PROCESS_CORE_ENDSTOP(Z,MIN,X,MAX);
          #elif CORE_DIAG(XZ, Z, MAX)
            PROCESS_CORE_ENDSTOP(Z,MAX,X,MAX);
>>>>>>> origin/release-2.1.3-beta2
          #endif
        #endif
      }
    }
<<<<<<< HEAD
  #endif

  #if HAS_Z_AXIS
    if (stepper.axis_is_moving(Z_AXIS)) {
      if (stepper.motor_direction(Z_AXIS_HEAD)) { // Z -direction. Gantry down, bed up.

        #if HAS_Z_MIN || (Z_SPI_SENSORLESS && Z_HOME_TO_MIN)
          if ( TERN1(Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN, z_probe_enabled)
            && TERN1(USES_Z_MIN_PROBE_PIN, !z_probe_enabled)
          ) PROCESS_ENDSTOP_Z(MIN);
          #if   CORE_DIAG(XZ, X, MIN)
            PROCESS_CORE_ENDSTOP(X,MIN,Z,MIN);
          #elif CORE_DIAG(XZ, X, MAX)
            PROCESS_CORE_ENDSTOP(X,MAX,Z,MIN);
          #elif CORE_DIAG(YZ, Y, MIN)
            PROCESS_CORE_ENDSTOP(Y,MIN,Z,MIN);
          #elif CORE_DIAG(YZ, Y, MAX)
            PROCESS_CORE_ENDSTOP(Y,MAX,Z,MIN);
          #endif
        #endif

        // When closing the gap check the enabled probe
        #if USES_Z_MIN_PROBE_PIN
          if (z_probe_enabled) PROCESS_ENDSTOP(Z, MIN_PROBE);
        #endif
      }
      else { // Z +direction. Gantry up, bed down.
        #if HAS_Z_MAX || (Z_SPI_SENSORLESS && Z_HOME_TO_MAX)
          #if ENABLED(Z_MULTI_ENDSTOPS)
            PROCESS_ENDSTOP_Z(MAX);
          #elif TERN1(USES_Z_MIN_PROBE_PIN, Z_MAX_PIN != Z_MIN_PROBE_PIN)  // No probe or probe is Z_MIN || Probe is not Z_MAX
            PROCESS_ENDSTOP(Z, MAX);
          #endif
          #if   CORE_DIAG(XZ, X, MIN)
            PROCESS_CORE_ENDSTOP(X,MIN,Z,MAX);
          #elif CORE_DIAG(XZ, X, MAX)
            PROCESS_CORE_ENDSTOP(X,MAX,Z,MAX);
          #elif CORE_DIAG(YZ, Y, MIN)
            PROCESS_CORE_ENDSTOP(Y,MIN,Z,MAX);
          #elif CORE_DIAG(YZ, Y, MAX)
            PROCESS_CORE_ENDSTOP(Y,MAX,Z,MAX);
          #endif
        #endif
      }
    }
  #endif

  #if HAS_I_AXIS
    if (stepper.axis_is_moving(I_AXIS)) {
      if (stepper.motor_direction(I_AXIS_HEAD)) { // -direction
        #if HAS_I_MIN || (I_SPI_SENSORLESS && I_HOME_TO_MIN)
          PROCESS_ENDSTOP(I, MIN);
        #endif
      }
      else { // +direction
        #if HAS_I_MAX || (I_SPI_SENSORLESS && I_HOME_TO_MAX)
=======
  #endif // HAS_X_AXIS

  #if HAS_Y_AXIS
    if (AXIS_IS_MOVING(Y)) {
      const AxisEnum y_head = TERN0(FT_MOTION, ftMotion.cfg.active) ? Y_AXIS : Y_AXIS_HEAD;
      if (AXIS_DIR_REV(y_head)) {
        #if HAS_Y_MIN_STATE
          PROCESS_ENDSTOP_Y(MIN);
          #if   CORE_DIAG(XY, X, MIN)
            PROCESS_CORE_ENDSTOP(X,MIN,Y,MIN);
          #elif CORE_DIAG(XY, X, MAX)
            PROCESS_CORE_ENDSTOP(X,MAX,Y,MIN);
          #elif CORE_DIAG(YZ, Z, MIN)
            PROCESS_CORE_ENDSTOP(Z,MIN,Y,MIN);
          #elif CORE_DIAG(YZ, Z, MAX)
            PROCESS_CORE_ENDSTOP(Z,MAX,Y,MIN);
          #endif
        #endif
      }
      else {
        #if HAS_Y_MAX_STATE
          PROCESS_ENDSTOP_Y(MAX);
          #if   CORE_DIAG(XY, X, MIN)
            PROCESS_CORE_ENDSTOP(X,MIN,Y,MAX);
          #elif CORE_DIAG(XY, X, MAX)
            PROCESS_CORE_ENDSTOP(X,MAX,Y,MAX);
          #elif CORE_DIAG(YZ, Z, MIN)
            PROCESS_CORE_ENDSTOP(Z,MIN,Y,MAX);
          #elif CORE_DIAG(YZ, Z, MAX)
            PROCESS_CORE_ENDSTOP(Z,MAX,Y,MAX);
          #endif
        #endif
      }
    }
  #endif // HAS_Y_AXIS

  #if HAS_Z_AXIS
    if (AXIS_IS_MOVING(Z)) {
      const AxisEnum z_head = TERN0(FT_MOTION, ftMotion.cfg.active) ? Z_AXIS : Z_AXIS_HEAD;
      if (AXIS_DIR_REV(z_head)) {
        // Z- : Gantry down, bed up
        #if HAS_Z_MIN_STATE
          // If the Z_MIN_PIN is being used for the probe there's no
          // separate Z_MIN endstop. But a Z endstop could be wired
          // in series, so someone might find this useful.
          if ( TERN1(Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN, z_probe_enabled) // When Z_MIN is the probe, the probe must be enabled
            && TERN1(USE_Z_MIN_PROBE, !z_probe_enabled)                   // When Z_MIN isn't the probe, Z MIN is ignored while probing
          ) {
            PROCESS_ENDSTOP_Z(MIN);
            #if   CORE_DIAG(XZ, X, MIN)
              PROCESS_CORE_ENDSTOP(X,MIN,Z,MIN);
            #elif CORE_DIAG(XZ, X, MAX)
              PROCESS_CORE_ENDSTOP(X,MAX,Z,MIN);
            #elif CORE_DIAG(YZ, Y, MIN)
              PROCESS_CORE_ENDSTOP(Y,MIN,Z,MIN);
            #elif CORE_DIAG(YZ, Y, MAX)
              PROCESS_CORE_ENDSTOP(Y,MAX,Z,MIN);
            #endif
          }
        #endif

        // When closing the gap use the probe trigger state
        #if USE_Z_MIN_PROBE
          if (z_probe_enabled) PROCESS_ENDSTOP(Z, MIN_PROBE);
        #endif
      }
      else {
        // Z+ : Gantry up, bed down
        #if HAS_Z_MAX_STATE
          PROCESS_ENDSTOP_Z(MAX);
          #if   CORE_DIAG(XZ, X, MIN)
            PROCESS_CORE_ENDSTOP(X,MIN,Z,MAX);
          #elif CORE_DIAG(XZ, X, MAX)
            PROCESS_CORE_ENDSTOP(X,MAX,Z,MAX);
          #elif CORE_DIAG(YZ, Y, MIN)
            PROCESS_CORE_ENDSTOP(Y,MIN,Z,MAX);
          #elif CORE_DIAG(YZ, Y, MAX)
            PROCESS_CORE_ENDSTOP(Y,MAX,Z,MAX);
          #endif
        #endif
      }
    }
  #endif // HAS_Z_AXIS

  #if HAS_I_AXIS && HAS_I_STATE
    if (AXIS_IS_MOVING(I)) {
      if (AXIS_DIR_REV(I_AXIS_HEAD)) {
        #if HAS_I_MIN_STATE
          PROCESS_ENDSTOP(I, MIN);
        #endif
      }
      else {
        #if HAS_I_MAX_STATE
>>>>>>> origin/release-2.1.3-beta2
          PROCESS_ENDSTOP(I, MAX);
        #endif
      }
    }
<<<<<<< HEAD
  #endif

  #if HAS_J_AXIS
    if (stepper.axis_is_moving(J_AXIS)) {
      if (stepper.motor_direction(J_AXIS_HEAD)) { // -direction
        #if HAS_J_MIN || (J_SPI_SENSORLESS && J_HOME_TO_MIN)
          PROCESS_ENDSTOP(J, MIN);
        #endif
      }
      else { // +direction
        #if HAS_J_MAX || (J_SPI_SENSORLESS && J_HOME_TO_MAX)
=======
  #endif // HAS_I_AXIS

  #if HAS_J_AXIS && HAS_J_STATE
    if (AXIS_IS_MOVING(J)) {
      if (AXIS_DIR_REV(J_AXIS_HEAD)) {
        #if HAS_J_MIN_STATE
          PROCESS_ENDSTOP(J, MIN);
        #endif
      }
      else {
        #if HAS_J_MAX_STATE
>>>>>>> origin/release-2.1.3-beta2
          PROCESS_ENDSTOP(J, MAX);
        #endif
      }
    }
<<<<<<< HEAD
  #endif

  #if HAS_K_AXIS
    if (stepper.axis_is_moving(K_AXIS)) {
      if (stepper.motor_direction(K_AXIS_HEAD)) { // -direction
        #if HAS_K_MIN || (K_SPI_SENSORLESS && K_HOME_TO_MIN)
          PROCESS_ENDSTOP(K, MIN);
        #endif
      }
      else { // +direction
        #if HAS_K_MAX || (K_SPI_SENSORLESS && K_HOME_TO_MAX)
=======
  #endif // HAS_J_AXIS

  #if HAS_K_AXIS && HAS_K_STATE
    if (AXIS_IS_MOVING(K)) {
      if (AXIS_DIR_REV(K_AXIS_HEAD)) {
        #if HAS_K_MIN_STATE
          PROCESS_ENDSTOP(K, MIN);
        #endif
      }
      else {
        #if HAS_K_MAX_STATE
>>>>>>> origin/release-2.1.3-beta2
          PROCESS_ENDSTOP(K, MAX);
        #endif
      }
    }
<<<<<<< HEAD
  #endif
=======
  #endif // HAS_K_AXIS

  #if HAS_U_AXIS && HAS_U_STATE
    if (AXIS_IS_MOVING(U)) {
      if (AXIS_DIR_REV(U_AXIS_HEAD)) {
        #if HAS_U_MIN_STATE
          PROCESS_ENDSTOP(U, MIN);
        #endif
      }
      else {
        #if HAS_U_MAX_STATE
          PROCESS_ENDSTOP(U, MAX);
        #endif
      }
    }
  #endif // HAS_U_AXIS

  #if HAS_V_AXIS && HAS_V_STATE
    if (AXIS_IS_MOVING(V)) {
      if (AXIS_DIR_REV(V_AXIS_HEAD)) {
        #if HAS_V_MIN_STATE
          PROCESS_ENDSTOP(V, MIN);
        #endif
      }
      else {
        #if HAS_V_MAX_STATE
          PROCESS_ENDSTOP(V, MAX);
        #endif
      }
    }
  #endif // HAS_V_AXIS

  #if HAS_W_AXIS && HAS_W_STATE
    if (AXIS_IS_MOVING(W)) {
      if (AXIS_DIR_REV(W_AXIS_HEAD)) {
        #if HAS_W_MIN_STATE
          PROCESS_ENDSTOP(W, MIN);
        #endif
      }
      else {
        #if HAS_W_MAX_STATE
          PROCESS_ENDSTOP(W, MAX);
        #endif
      }
    }
  #endif // HAS_W_AXIS

>>>>>>> origin/release-2.1.3-beta2
} // Endstops::update()

#if ENABLED(SPI_ENDSTOPS)

  // Called from idle() to read Trinamic stall states
  bool Endstops::tmc_spi_homing_check() {
    bool hit = false;

    #if X_SPI_SENSORLESS
<<<<<<< HEAD
      if (tmc_spi_homing.x && (stepperX.test_stall_status()
        #if ANY(CORE_IS_XY, MARKFORGED_XY, MARKFORGED_YX) && Y_SPI_SENSORLESS
          || stepperY.test_stall_status()
        #elif CORE_IS_XZ && Z_SPI_SENSORLESS
          || stepperZ.test_stall_status()
=======
      if (tmc_spi_homing.x) {
        #if ENABLED(DUAL_X_CARRIAGE)
          const bool ismin = X_MIN_TEST();
        #endif
        const bool xhit = (
          #if ENABLED(DUAL_X_CARRIAGE)
            ismin ? stepperX.test_stall_status() : stepperX2.test_stall_status()
          #else
            stepperX.test_stall_status()
            #if Y_SPI_SENSORLESS && ANY(CORE_IS_XY, MARKFORGED_XY, MARKFORGED_YX)
              || stepperY.test_stall_status()
            #elif Z_SPI_SENSORLESS && CORE_IS_XZ
              || stepperZ.test_stall_status()
            #endif
          #endif
        );
        if (xhit) { SBI(live_state, TERN(DUAL_X_CARRIAGE, ismin ? X_MIN : X_MAX, X_ENDSTOP)); hit = true; }
        #if ENABLED(X_DUAL_ENDSTOPS)
          if (stepperX2.test_stall_status()) { SBI(live_state, X2_ENDSTOP); hit = true; }
>>>>>>> origin/release-2.1.3-beta2
        #endif
      }
    #endif

    #if Y_SPI_SENSORLESS
<<<<<<< HEAD
      if (tmc_spi_homing.y && (stepperY.test_stall_status()
        #if ANY(CORE_IS_XY, MARKFORGED_XY, MARKFORGED_YX) && X_SPI_SENSORLESS
          || stepperX.test_stall_status()
        #elif CORE_IS_YZ && Z_SPI_SENSORLESS
          || stepperZ.test_stall_status()
=======
      if (tmc_spi_homing.y) {
        if (stepperY.test_stall_status()
          #if X_SPI_SENSORLESS && ANY(CORE_IS_XY, MARKFORGED_XY, MARKFORGED_YX)
            || stepperX.test_stall_status()
          #elif Z_SPI_SENSORLESS && CORE_IS_YZ
            || stepperZ.test_stall_status()
          #endif
        ) { SBI(live_state, Y_ENDSTOP); hit = true; }
        #if ENABLED(Y_DUAL_ENDSTOPS)
          if (stepperY2.test_stall_status()) { SBI(live_state, Y2_ENDSTOP); hit = true; }
>>>>>>> origin/release-2.1.3-beta2
        #endif
      }
    #endif

    #if Z_SPI_SENSORLESS
      if (tmc_spi_homing.z) {
        if (stepperZ.test_stall_status()
          #if X_SPI_SENSORLESS && CORE_IS_XZ
            || stepperX.test_stall_status()
          #elif Y_SPI_SENSORLESS && CORE_IS_YZ
            || stepperY.test_stall_status()
          #endif
        ) { SBI(live_state, Z_ENDSTOP); hit = true; }
        #if ENABLED(Z_MULTI_ENDSTOPS)
          if (stepperZ2.test_stall_status()) { SBI(live_state, Z2_ENDSTOP); hit = true; }
          #if NUM_Z_STEPPERS >= 3
            if (stepperZ3.test_stall_status()) { SBI(live_state, Z3_ENDSTOP); hit = true; }
            #if NUM_Z_STEPPERS >= 4
              if (stepperZ4.test_stall_status()) { SBI(live_state, Z4_ENDSTOP); hit = true; }
            #endif
          #endif
        #endif
      }
    #endif
    #if I_SPI_SENSORLESS
      if (tmc_spi_homing.i && stepperI.test_stall_status()) {
        SBI(live_state, I_ENDSTOP);
        hit = true;
      }
    #endif
    #if J_SPI_SENSORLESS
      if (tmc_spi_homing.j && stepperJ.test_stall_status()) {
        SBI(live_state, J_ENDSTOP);
        hit = true;
      }
    #endif
    #if K_SPI_SENSORLESS
      if (tmc_spi_homing.k && stepperK.test_stall_status()) {
        SBI(live_state, K_ENDSTOP);
        hit = true;
      }
    #endif

    #if I_SPI_SENSORLESS
      if (tmc_spi_homing.i && stepperI.test_stall_status()) { SBI(live_state, I_ENDSTOP); hit = true; }
    #endif
    #if J_SPI_SENSORLESS
      if (tmc_spi_homing.j && stepperJ.test_stall_status()) { SBI(live_state, J_ENDSTOP); hit = true; }
    #endif
    #if K_SPI_SENSORLESS
      if (tmc_spi_homing.k && stepperK.test_stall_status()) { SBI(live_state, K_ENDSTOP); hit = true; }
    #endif
    #if U_SPI_SENSORLESS
      if (tmc_spi_homing.u && stepperU.test_stall_status()) { SBI(live_state, U_ENDSTOP); hit = true; }
    #endif
    #if V_SPI_SENSORLESS
      if (tmc_spi_homing.v && stepperV.test_stall_status()) { SBI(live_state, V_ENDSTOP); hit = true; }
    #endif
    #if W_SPI_SENSORLESS
      if (tmc_spi_homing.w && stepperW.test_stall_status()) { SBI(live_state, W_ENDSTOP); hit = true; }
    #endif

    if (TERN0(ENDSTOP_INTERRUPTS_FEATURE, hit)) update();

    return hit;
  }

  void Endstops::clear_endstop_state() {
    TERN_(X_SPI_SENSORLESS, CBI(live_state, X_ENDSTOP));
    #if ALL(X_SPI_SENSORLESS, X_DUAL_ENDSTOPS)
      CBI(live_state, X2_ENDSTOP);
    #endif
    TERN_(Y_SPI_SENSORLESS, CBI(live_state, Y_ENDSTOP));
    #if ALL(Y_SPI_SENSORLESS, Y_DUAL_ENDSTOPS)
      CBI(live_state, Y2_ENDSTOP);
    #endif
    TERN_(Z_SPI_SENSORLESS, CBI(live_state, Z_ENDSTOP));
<<<<<<< HEAD
    TERN_(I_SPI_SENSORLESS, CBI(live_state, I_ENDSTOP));
    TERN_(J_SPI_SENSORLESS, CBI(live_state, J_ENDSTOP));
    TERN_(K_SPI_SENSORLESS, CBI(live_state, K_ENDSTOP));
=======
    #if ALL(Z_SPI_SENSORLESS, Z_MULTI_ENDSTOPS)
      CBI(live_state, Z2_ENDSTOP);
      #if NUM_Z_STEPPERS >= 3
        CBI(live_state, Z3_ENDSTOP);
        #if NUM_Z_STEPPERS >= 4
          CBI(live_state, Z4_ENDSTOP);
        #endif
      #endif
    #endif
    TERN_(I_SPI_SENSORLESS, CBI(live_state, I_ENDSTOP));
    TERN_(J_SPI_SENSORLESS, CBI(live_state, J_ENDSTOP));
    TERN_(K_SPI_SENSORLESS, CBI(live_state, K_ENDSTOP));
    TERN_(U_SPI_SENSORLESS, CBI(live_state, U_ENDSTOP));
    TERN_(V_SPI_SENSORLESS, CBI(live_state, V_ENDSTOP));
    TERN_(W_SPI_SENSORLESS, CBI(live_state, W_ENDSTOP));
>>>>>>> origin/release-2.1.3-beta2
  }

#endif // SPI_ENDSTOPS

#if ENABLED(PINS_DEBUGGING)

  bool Endstops::monitor_flag = false;

  /**
   * Monitor Endstops and Z Probe for changes
   *
   * If a change is detected then the LED is toggled and
   * a message is sent out the serial port.
   *
   * Yes, we could miss a rapid back & forth change but
   * that won't matter because this is all manual.
   */
  void Endstops::monitor() {

    static uint16_t old_live_state_local = 0;
    static uint8_t local_LED_status = 0;
    uint16_t live_state_local = 0;

    #define ES_GET_STATE(S) if (READ_ENDSTOP(S##_PIN)) SBI(live_state_local, S)

    #if USE_X_MIN
      ES_GET_STATE(X_MIN);
    #endif
    #if USE_X_MAX
      ES_GET_STATE(X_MAX);
    #endif
    #if USE_Y_MIN
      ES_GET_STATE(Y_MIN);
    #endif
    #if USE_Y_MAX
      ES_GET_STATE(Y_MAX);
    #endif
    #if USE_Z_MIN
      ES_GET_STATE(Z_MIN);
    #endif
    #if USE_Z_MAX
      ES_GET_STATE(Z_MAX);
    #endif
    #if USE_Z_MIN_PROBE
      ES_GET_STATE(Z_MIN_PROBE);
    #endif
    #if USE_CALIBRATION
      ES_GET_STATE(CALIBRATION);
    #endif
    #if USE_X2_MIN
      ES_GET_STATE(X2_MIN);
    #endif
    #if USE_X2_MAX
      ES_GET_STATE(X2_MAX);
    #endif
    #if USE_Y2_MIN
      ES_GET_STATE(Y2_MIN);
    #endif
    #if USE_Y2_MAX
      ES_GET_STATE(Y2_MAX);
    #endif
    #if USE_Z2_MIN
      ES_GET_STATE(Z2_MIN);
    #endif
    #if USE_Z2_MAX
      ES_GET_STATE(Z2_MAX);
    #endif
    #if USE_Z3_MIN
      ES_GET_STATE(Z3_MIN);
    #endif
    #if USE_Z3_MAX
      ES_GET_STATE(Z3_MAX);
    #endif
    #if USE_Z4_MIN
      ES_GET_STATE(Z4_MIN);
    #endif
    #if USE_Z4_MAX
      ES_GET_STATE(Z4_MAX);
    #endif
<<<<<<< HEAD
    #if HAS_I_MAX
      ES_GET_STATE(I_MAX);
    #endif
    #if HAS_I_MIN
      ES_GET_STATE(I_MIN);
    #endif
    #if HAS_J_MAX
      ES_GET_STATE(J_MAX);
    #endif
    #if HAS_J_MIN
      ES_GET_STATE(J_MIN);
    #endif
    #if HAS_K_MAX
      ES_GET_STATE(K_MAX);
    #endif
    #if HAS_K_MIN
      ES_GET_STATE(K_MIN);
    #endif

    uint16_t endstop_change = live_state_local ^ old_live_state_local;
=======
    #if USE_I_MAX
      ES_GET_STATE(I_MAX);
    #endif
    #if USE_I_MIN
      ES_GET_STATE(I_MIN);
    #endif
    #if USE_J_MAX
      ES_GET_STATE(J_MAX);
    #endif
    #if USE_J_MIN
      ES_GET_STATE(J_MIN);
    #endif
    #if USE_K_MAX
      ES_GET_STATE(K_MAX);
    #endif
    #if USE_K_MIN
      ES_GET_STATE(K_MIN);
    #endif
    #if USE_U_MAX
      ES_GET_STATE(U_MAX);
    #endif
    #if USE_U_MIN
      ES_GET_STATE(U_MIN);
    #endif
    #if USE_V_MAX
      ES_GET_STATE(V_MAX);
    #endif
    #if USE_V_MIN
      ES_GET_STATE(V_MIN);
    #endif
    #if USE_W_MAX
      ES_GET_STATE(W_MAX);
    #endif
    #if USE_W_MIN
      ES_GET_STATE(W_MIN);
    #endif

    const uint16_t endstop_change = live_state_local ^ old_live_state_local;
>>>>>>> origin/release-2.1.3-beta2
    #define ES_REPORT_CHANGE(S) if (TEST(endstop_change, S)) SERIAL_ECHOPGM("  " STRINGIFY(S) ":", TEST(live_state_local, S))

    if (endstop_change) {
      #if USE_X_MIN
        ES_REPORT_CHANGE(X_MIN);
      #endif
      #if USE_X_MAX
        ES_REPORT_CHANGE(X_MAX);
      #endif
      #if USE_Y_MIN
        ES_REPORT_CHANGE(Y_MIN);
      #endif
      #if USE_Y_MAX
        ES_REPORT_CHANGE(Y_MAX);
      #endif
      #if USE_Z_MIN
        ES_REPORT_CHANGE(Z_MIN);
      #endif
      #if USE_Z_MAX
        ES_REPORT_CHANGE(Z_MAX);
      #endif
      #if USE_Z_MIN_PROBE
        ES_REPORT_CHANGE(Z_MIN_PROBE);
      #endif
      #if USE_CALIBRATION
        ES_REPORT_CHANGE(CALIBRATION);
      #endif
      #if USE_X2_MIN
        ES_REPORT_CHANGE(X2_MIN);
      #endif
      #if USE_X2_MAX
        ES_REPORT_CHANGE(X2_MAX);
      #endif
      #if USE_Y2_MIN
        ES_REPORT_CHANGE(Y2_MIN);
      #endif
      #if USE_Y2_MAX
        ES_REPORT_CHANGE(Y2_MAX);
      #endif
      #if USE_Z2_MIN
        ES_REPORT_CHANGE(Z2_MIN);
      #endif
      #if USE_Z2_MAX
        ES_REPORT_CHANGE(Z2_MAX);
      #endif
      #if USE_Z3_MIN
        ES_REPORT_CHANGE(Z3_MIN);
      #endif
      #if USE_Z3_MAX
        ES_REPORT_CHANGE(Z3_MAX);
      #endif
      #if USE_Z4_MIN
        ES_REPORT_CHANGE(Z4_MIN);
      #endif
      #if USE_Z4_MAX
        ES_REPORT_CHANGE(Z4_MAX);
      #endif
<<<<<<< HEAD
      #if HAS_I_MIN
        ES_REPORT_CHANGE(I_MIN);
      #endif
      #if HAS_I_MAX
        ES_REPORT_CHANGE(I_MAX);
      #endif
      #if HAS_J_MIN
        ES_REPORT_CHANGE(J_MIN);
      #endif
      #if HAS_J_MAX
        ES_REPORT_CHANGE(J_MAX);
      #endif
      #if HAS_K_MIN
        ES_REPORT_CHANGE(K_MIN);
      #endif
      #if HAS_K_MAX
        ES_REPORT_CHANGE(K_MAX);
      #endif
=======
      #if USE_I_MIN
        ES_REPORT_CHANGE(I_MIN);
      #endif
      #if USE_I_MAX
        ES_REPORT_CHANGE(I_MAX);
      #endif
      #if USE_J_MIN
        ES_REPORT_CHANGE(J_MIN);
      #endif
      #if USE_J_MAX
        ES_REPORT_CHANGE(J_MAX);
      #endif
      #if USE_K_MIN
        ES_REPORT_CHANGE(K_MIN);
      #endif
      #if USE_K_MAX
        ES_REPORT_CHANGE(K_MAX);
      #endif
      #if USE_U_MIN
        ES_REPORT_CHANGE(U_MIN);
      #endif
      #if USE_U_MAX
        ES_REPORT_CHANGE(U_MAX);
      #endif
      #if USE_V_MIN
        ES_REPORT_CHANGE(V_MIN);
      #endif
      #if USE_V_MAX
        ES_REPORT_CHANGE(V_MAX);
      #endif
      #if USE_W_MIN
        ES_REPORT_CHANGE(W_MIN);
      #endif
      #if USE_W_MAX
        ES_REPORT_CHANGE(W_MAX);
      #endif

>>>>>>> origin/release-2.1.3-beta2
      SERIAL_ECHOLNPGM("\n");
      hal.set_pwm_duty(pin_t(LED_PIN), local_LED_status);
      local_LED_status ^= 255;
      old_live_state_local = live_state_local;
    }
  }

#endif // PINS_DEBUGGING

#if USE_SENSORLESS
  /**
   * Change TMC driver currents to N##_CURRENT_HOME, saving the current configuration of each.
   */
  void Endstops::set_homing_current(const bool onoff) {
    #define HAS_CURRENT_HOME(N) (defined(N##_CURRENT_HOME) && N##_CURRENT_HOME != N##_CURRENT)
    #define HAS_DELTA_X_CURRENT (ENABLED(DELTA) && HAS_CURRENT_HOME(X))
    #define HAS_DELTA_Y_CURRENT (ENABLED(DELTA) && HAS_CURRENT_HOME(Y))
    #if HAS_DELTA_X_CURRENT || HAS_DELTA_Y_CURRENT || HAS_CURRENT_HOME(Z)
      #if HAS_DELTA_X_CURRENT
        static int16_t saved_current_x;
      #endif
      #if HAS_DELTA_Y_CURRENT
        static int16_t saved_current_y;
      #endif
      #if HAS_CURRENT_HOME(Z)
        static int16_t saved_current_z;
      #endif
      auto debug_current_on = [](PGM_P const s, const int16_t a, const int16_t b) {
        if (DEBUGGING(LEVELING)) { DEBUG_ECHOPGM_P(s); DEBUG_ECHOLNPGM(" current: ", a, " -> ", b); }
      };
      if (onoff) {
        #if HAS_DELTA_X_CURRENT
          saved_current_x = stepperX.getMilliamps();
          stepperX.rms_current(X_CURRENT_HOME);
          debug_current_on(PSTR("X"), saved_current_x, X_CURRENT_HOME);
        #endif
        #if HAS_DELTA_Y_CURRENT
          saved_current_y = stepperY.getMilliamps();
          stepperY.rms_current(Y_CURRENT_HOME);
          debug_current_on(PSTR("Y"), saved_current_y, Y_CURRENT_HOME);
        #endif
        #if HAS_CURRENT_HOME(Z)
          saved_current_z = stepperZ.getMilliamps();
          stepperZ.rms_current(Z_CURRENT_HOME);
          debug_current_on(PSTR("Z"), saved_current_z, Z_CURRENT_HOME);
        #endif
      }
      else {
        #if HAS_DELTA_X_CURRENT
          stepperX.rms_current(saved_current_x);
          debug_current_on(PSTR("X"), X_CURRENT_HOME, saved_current_x);
        #endif
        #if HAS_DELTA_Y_CURRENT
          stepperY.rms_current(saved_current_y);
          debug_current_on(PSTR("Y"), Y_CURRENT_HOME, saved_current_y);
        #endif
        #if HAS_CURRENT_HOME(Z)
          stepperZ.rms_current(saved_current_z);
          debug_current_on(PSTR("Z"), Z_CURRENT_HOME, saved_current_z);
        #endif
      }

      TERN_(IMPROVE_HOMING_RELIABILITY, planner.enable_stall_prevention(onoff));

      #if SENSORLESS_STALLGUARD_DELAY
        safe_delay(SENSORLESS_STALLGUARD_DELAY); // Short delay needed to settle
      #endif

    #endif // XYZ
  }
#endif
