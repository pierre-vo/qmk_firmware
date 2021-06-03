/* Copyright 2020 torreip
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base KC_MPLY */
    [_BASE] = LAYOUT(
        RESET,    _FN, _FN
    ),
    [_FN] = LAYOUT(
        RESET,   _BASE, _BASE
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}


void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    switch(biton32(layer_state)){
      case _FN:
        if (clockwise) {
          tap_code(KC_UP);
          // rgblight_increase_hue_noeeprom();
        } else {
          tap_code(KC_DOWN);
          // rgblight_decrease_hue_noeeprom();
        }
        break;
      case _BASE:
      default:
        if (clockwise) {
          tap_code(KC_VOLU);
          // rgblight_increase_hue_noeeprom();
        } else {
          tap_code(KC_VOLD);
          // rgblight_decrease_hue_noeeprom();
        }
        break;
    }
  }
}

void matrix_init_user(void) {
  // rgblight_enable();
  // rgblight_sethsv(HSV_RED);
  // rgblight_decrease_val_noeeprom();
  // rgblight_decrease_val_noeeprom();
  // rgblight_decrease_val_noeeprom();
}

/*

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
