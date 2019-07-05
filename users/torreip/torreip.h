#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "wrappers.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
//  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  #include "rgb_stuff.h"
#endif

/* Fillers to make layering more clear */
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO


/* Define layer names */
enum userspace_layers
{
  _QWERTY = 0,
  _NUMLOCK = 0,
  _MODS,
  _GAMEPAD,
  _MACROS,
  _MEDIA,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FUNCTION,
};

/*
define modifiers here, since MOD_* doesn't seem to work for these
 */
#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK  (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))


/*
RGB color codes are no longer located here anymore.  Instead, you will want to
head to https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h
*/

#ifdef RGBLIGHT_ENABLE
  void rgblight_sethsv_default_helper(uint8_t index);
#endif // RGBLIGHT_ENABLE

bool mod_key_press_timer(uint16_t code, uint16_t mod_code, bool pressed);
bool mod_key_press(uint16_t code, uint16_t mod_code, bool pressed,
  uint16_t this_timer);
void matrix_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
void led_set_keymap(uint8_t usb_led);
void eeconfig_init_keymap(void);

typedef union
{
  uint32_t raw;
  struct
  {
    bool     rgb_layer_change :1;
    bool     nuke_switch      :1;
    uint8_t  unicode_mod      :4;
  };
} userspace_config_t;

extern userspace_config_t userspace_config;


#if defined(KEYMAP_SAFE_RANGE)
  #define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
  #define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define FUNCTION MO(_FUNCTION)
//#define TG_MODS TG(_MODS)
//#define TG_GAME TG(_GAMEPAD)

#define KC_SEC1 KC_SECRET_1
#define KC_SEC2 KC_SECRET_2
#define KC_SEC3 KC_SECRET_3
#define KC_SEC4 KC_SECRET_4
#define KC_SEC5 KC_SECRET_5

#define QWERTY KC_QWERTY

//#define KC_RESET RESET
#define KC_RST KC_RESET

#ifdef SWAP_HANDS_ENABLE
  #define KC_C1R3 SH_TT
#else // SWAP_HANDS_ENABLE
  #define KC_C1R3 KC_BSPC
#endif // SWAP_HANDS_ENABLE

#define BK_LWER LT(_LOWER, KC_BSPC)
#define SP_LWER LT(_LOWER, KC_SPC)
#define DL_RAIS LT(_RAISE, KC_DEL)
#define ET_RAIS LT(_RAISE, KC_ENTER)

/* OSM keycodes, to keep things clean and easy to change */
#define KC_MLSF OSM(MOD_LSFT)
#define KC_MRSF OSM(MOD_RSFT)

#define OS_LGUI OSM(MOD_LGUI)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_LALT OSM(MOD_LALT)
#define OS_RALT OSM(MOD_RALT)
#define ALT_APP ALT_T(KC_APP)

#define MG_NKRO MAGIC_TOGGLE_NKRO


//#define M_LOWER M(MACRO_LOWER)
//#define M_UPPER M(MACRO_UPPER)
#define ROT_LED M(M_LED)   /* Rotate LED */
#define CTLENTER MT(MOD_RCTL, KC_ENT)
#define SHIFTQUOTE MT(MOD_RAISEFT, KC_QUOT)
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


#ifdef TAP_DANCE_ENABLE
/* Tap Dance Declarations */
enum
{
  SCL = 0,
  QUO,
};
#endif /* TAP_DANCE_ENABLE */

