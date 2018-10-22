#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"
#include "version.h"

extern keymap_config_t keymap_config;

// #define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped this number of times again. */
// #define ONESHOT_TIMEOUT 2000  /* Time (in ms) before the one shot key is released */
#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300
#define LAYER_SKIP_DELAY 1000

/* Layer shorthand */
enum layers {
  _QW = 0, /* Base layer, QWERTY */
  _LW,     /* LOWER */
  _RS,     /* RAISE */
  _FN,     /* FUNCTION */
  _AD,     /* ADJUST */
};

#define _QWERTY _QW
#define _LOWER _LW // 3
#define _RAISE _RS // 4
#define _FUNCTION _FN // 15
#define _ADJUST _AD // 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  FUNC,
  VRSN,
  KMAP,
  RST,
};

/* Tap Dance Declarations */
enum {
  SCL = 0,
  QUO,
};

/* Fillers to make layering more clear */
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define ___T___ KC_TRNS

/* Short forms for keycodes so that they fit into limited-width cells */
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define M_LOWER M(MACRO_LOWER)
#define M_UPPER M(MACRO_UPPER)
#define ROT_LED M(M_LED)   /* Rotate LED */
#define CTLENTER MT(MOD_RCTL, KC_ENT)
#define SHIFTQUOTE MT(MOD_RSFT, KC_QUOT)
#define ALTRIGHT MT(MOD_LALT, KC_RGHT)
#define MVERSION M(M_VERSION)
#define ALTSLASH LALT(KC_SLSH)
#define ALTSHFT LALT(KC_LSFT)
#define ALTBSP ALT_T(KC_BSPC)
#define ALTSLSH ALGR_T(KC_SLSH)
#define SFTBSLS MT(MOD_RSFT, KC_BSLS)
#define MLSHIFT OSM(KC_LSFT)
#define MLCTL OSM(KC_LCTL)
#define CTRLB LCTL(KC_B)

#ifdef RGBLIGHT_ENABLE
  int RGB_current_mode;
#endif /* RGBLIGHT_ENABLE */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Func |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  `   | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_TAB,        KC_Q,   KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC, \
  MO(_FUNCTION), KC_A,   KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
  OSM(MOD_LSFT), KC_Z,   KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT, \
  KC_LCTL,       KC_GRV, KC_LGUI, KC_LALT, LOWER, KC_SPC, KC_ENT, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Mute |      |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower | Bksp | Bksp |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_ESC,  KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  _______, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, \
  _______, KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_MUTE, _______, KC_PIPE, \
  _______, _______,  _______, _______, _______, KC_BSPC, KC_BSPC, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   4  |   5  |   6  |   +  |  F5  |  F6  |   -  |   =  |   [  |   ]  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Enter |   7  |   8  |   9  |   -  |  F11 |  F12 |ISO # |ISO / | Mute |      |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ,  |   0  |  .   |Lower | Bksp | Bksp |Raise | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_ESC,  KC_1,    KC_2,  KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  _______, KC_4,    KC_5,  KC_6,   KC_PLUS, KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
  KC_ENT,  KC_7,    KC_8,  KC_9,   KC_MINS, KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_MUTE, _______, KC_BSLS, \
  _______, KC_COMM, KC_0,  KC_DOT, _______, KC_BSPC, KC_BSPC, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Taskmg|      |      |      |      |      |      |      |RGBVAI|RGBSAI|RGBHUI|caltde|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Qwerty|RGBVAD|RGBSAD|RGBHUD|RGBTOG|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |BLSTEP|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | RESET|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT( \
  TSKMGR,  _______, _______, _______, _______, _______, _______, _______, RGB_VAI, RGB_SAI, RGB_HUI, CALTDEL, \
  _______, _______, _______, _______, _______, _______, _______, QWERTY,  RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_STEP, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET    \
),

/* Function
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |  Up  |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  KC_CAPS,  DEBUG , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    RST  ,  KMAP  ,  VRSN  , _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


//static uint16_t key_timer;
//static bool singular_key = false;
static uint8_t skip = false;  /* if true: we do not restore the RGB state */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;

    case VRSN:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;

    case KMAP:
      if (record->event.pressed) {
        SEND_STRING("http://www.keyboard-layout-editor.com/#/gists/0e924c013c75d1dc4bbf51806b5500ee");
      }
      return false;
      break;

    case RST:
      rgblight_enable_noeeprom();
      rgblight_mode_noeeprom(1);

      rgblight_sethsv_noeeprom(0x00, 0xFF, 0xFF);
      _delay_ms(250);
      rgblight_sethsv_noeeprom(0x3C, 0xFF, 0xFF);
      _delay_ms(250);
      rgblight_sethsv_noeeprom(0x00, 0xFF, 0xFF);
      _delay_ms(250);

      reset_keyboard();
      return false;
      break;

  }
  return true;
}

/* Tap Dance Definitions */
qk_tap_dance_action_t tap_dance_actions[] = {
  /* Shifting for double quote and semicolon */
  [SCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
  [QUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),

  /* complex tap dance function (to specify what happens when key is 
   * pressed 3+ times, for example). See 
   * https://docs.qmk.fm/tap_dance.html for how to define
  [YOUR_TAPDANCE_2] = ACTION_TAP_DANCE_FN(your_function_name),0
  */
};

/* Runs whenever there is a layer state change. */
uint32_t layer_state_set_user(uint32_t state) {

#ifdef RGBLIGHT_ENABLE
  switch (biton32(state)) {
    case _QW:
      if (skip) {
        RGB_current_mode = rgblight_get_mode();
        skip = false;
      } else {
        rgblight_mode_noeeprom(RGB_current_mode);
      }
      break;

    case _LW:
      RGB_current_mode = rgblight_get_mode();
      rgblight_mode_noeeprom(1);
      rgblight_setrgb(0x00, 0xA0, 0xFF);
      break;

    case _RS:
      RGB_current_mode = rgblight_get_mode();
      rgblight_mode_noeeprom(1);
      rgblight_setrgb(0xFF, 0x00, 0x00);
      break;

    case _FN:
      RGB_current_mode = rgblight_get_mode();
      rgblight_mode_noeeprom(1);
      rgblight_setrgb(0xFF, 0x20, 0x00);
      break;

    case _AD:
      RGB_current_mode = rgblight_get_mode();
      rgblight_mode_noeeprom(1);
      rgblight_setrgb(0x00, 0xFF, 0x00);
      break;

    default:
      break;
  }
#endif /* RGBLIGHT_ENABLE */

  return state;
}

/* Called at startup */
void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_init();

  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(1);
  RGB_current_mode = rgblight_get_mode();
  rgblight_sethsv(240, 255, 100);

#endif /* RGBLIGHT_ENABLE */
}

/* Called all the time */
void matrix_scan_user(void) {

}
