
/* A QWERTY 3 Layer layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define TASK    LCTL(LSFT(KC_ESC))
#define TAB_R   LCTL(KC_TAB)
#define TAB_L   LCTL(LSFT(KC_TAB))
#define TAB_RO  LCTL(LSFT(KC_T))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = LAYOUT_5x7(
  // left hand
   KC_ESC,    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,
   KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_LBRC,
   KC_LCTL,   KC_A,    KC_S,    KC_D,   RESET,   KC_G,   TAB_RO,
   MOD_LSFT,  KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
                       TAB_L,   TAB_R,
                               TT(_LOWER), KC_SPC,
                               KC_END, KC_HOME,
                               KC_PSCR, TASK,
        // right hand
                     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,
                     KC_RBRC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
                 TG(_RAISE),  KC_H,    RESET,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
                              KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT),
                                                KC_LEFT, KC_UP,
        KC_BSPC, KC_ENT,
        KC_PGUP, KC_PGDN,
        KC_LCTL, KC_LALT),

[_LOWER] = LAYOUT_5x7(
  // left hand
   _______,   KC_F1,     KC_F2,      KC_F3,    KC_F4,     KC_F5,    KC_F6,
   _______,   _______,   _______,    KC_UP,    _______,   _______,  _______,
   _______,   _______,   KC_LEFT,    KC_DOWN,  KC_RGHT,   _______,  RESET,
   _______,   _______,   _______,   _______,   _______,   _______,
                         KC_MPRV,   KC_MNXT,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    _______,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                                _______,   _______,   _______,   _______,   _______,   _______,
                                                      _______,   _______,
        KC_DEL, _______,
        _______, _______,
        _______, _______),

[_RAISE] = LAYOUT_5x7(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,
                         _______,   _______,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,   _______,
                     _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
                     _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
                                _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
                                                      KC_P0,     KC_PDOT,
        _______, KC_PENT,
        _______, _______,
        _______, _______),

};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
