/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

#define PRODUCT_ID      0x3537
#define DEVICE_VER      0x0001
#define PRODUCT         Dactyl-Manuform (5x7)

//#define DEBUG_MATRIX_SCAN_RATE

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define USE_I2C
#define F_SCL 400000L
//#define SPLIT_USB_DETECT

// wiring of each half
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
//#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5 }

#define DIODE_DIRECTION COL2ROW

// WS2812 RGB LED strip input and number of LEDs
#define RGB_DI_PIN F4
#ifdef RGB_DI_PIN
  #define RGBLIGHT_LAYERS
  #define RGB_DISABLE_WHEN_USB_SUSPENDED true

  #define RGBLED_NUM 2
  #define RGBLED_SPLIT {1, 1}
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 100 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== or choose animations ==*/
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
  #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
  /*==== use exp() and sin() ====*/
  #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
  #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D2 }

// Bootloader
#define QMK_ESC_OUTPUT F5 //D2 //F5 // usually COL
#define QMK_ESC_INPUT  B5 //D3 //C6 // usually ROW
#define QMK_LED B0
