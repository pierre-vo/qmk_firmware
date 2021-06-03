/* Copyright 2020 Torreip
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
    _VOL,
    _PO1,
    _PO2,
    _PAG,
    _COL,
};


#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM my_vol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}
);
const rgblight_segment_t PROGMEM my_po1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_po2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM my_pag_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_YELLOW}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_vol_layer,
    my_po1_layer,
    my_po2_layer,
    my_pag_layer
);
#endif // RGBLIGHT_LAYERS


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base KC_MPLY */
    [_VOL] = LAYOUT(
        RESET,   KC_MPLY, TO(_PO1), RESET, RESET, RESET
    ),
    [_PO1] = LAYOUT(
        RESET,   TO(_PO2), TO(_PAG), RESET, RESET, RESET
    ),
    [_PO2] = LAYOUT(
        RESET,   TO(_PO1), TO(_PAG), RESET, RESET, RESET
    ),
    [_PAG] = LAYOUT(
        RESET,   KC_HOME, TO(_COL), RESET, RESET, RESET
    ),
    [_COL] = LAYOUT(
        RESET,   RGB_MOD, TO(_VOL), RESET, RESET, RESET
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    switch(biton32(layer_state)){
      case _PO1:
        if (clockwise) {
          tap_code(KC_UP);
        } else {
          tap_code(KC_DOWN);
        }
        break;
      case _PO2:
        if (clockwise) {
          tap_code(KC_RGHT);
        } else {
          tap_code(KC_LEFT);
        }
        break;
      case _PAG:
        if (clockwise) {
          tap_code(KC_PGUP);
        } else {
          tap_code(KC_PGDN);
        }
        break;
      case _COL:
        if (clockwise) {
          rgblight_increase_hue_noeeprom();
        } else {
          rgblight_decrease_hue_noeeprom();
        }
        break;
      case _VOL:
      default:
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
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
  // rgblight_decrease_val_noeeprom();
  // rgblight_sethsv_noeeprom(0, 255, 130);
}

#ifdef RGBLIGHT_LAYERS
void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, _VOL));
    rgblight_set_layer_state(1, layer_state_cmp(state, _PO1));
    rgblight_set_layer_state(2, layer_state_cmp(state, _PO2));
    rgblight_set_layer_state(3, layer_state_cmp(state, _PAG));
    // rgblight_set_layer_state(4, layer_state_cmp(state, _COL));

    return state;
}

// bool led_update_user(led_t led_state) {
    // rgblight_set_layer_state(0, led_state.caps_lock);
    // return true;
// }

void suspend_power_down_user(void) {
    rgblight_disable();
}

void suspend_wakeup_init_user(void) {
    rgblight_enable();
}

#endif // RGBLIGHT_LAYERS

/*

void matrix_scan_user(void) {

}

*/
