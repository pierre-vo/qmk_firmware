/*
This is the c configuration file for the keymap

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

#include "../../config.h"

/* Use I2C or Serial, not both */
#undef USE_SERIAL
#define USE_I2C

/* Select hand configuration */
// #define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define TAPPING_TERM 200

#ifdef RGBLIGHT_ENABLE
//#  undef RGBLED_NUM
#  define RGBLIGHT_ANIMATIONS
#  define RGBLIGHT_HUE_STEP 12
#  define RGBLIGHT_SAT_STEP 12
#  define RGBLIGHT_VAL_STEP 12
#  define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#  define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#  define RGBLIGHT_EFFECT_BREATHE_CENTER 1

#  define RGBLIGHT_LIMIT_VAL 225
#endif // RGBLIGHT_ENABLE


