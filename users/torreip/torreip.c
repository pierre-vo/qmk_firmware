#include "torreip.h"
#include "version.h"
#include "eeprom.h"
#include "rgb_stuff.h"

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300
#define LAYER_SKIP_DELAY 1000

userspace_config_t userspace_config;

bool mod_key_press_timer(uint16_t code, uint16_t mod_code, bool pressed)
{
  static uint16_t this_timer;

  if (pressed)
  {
    this_timer= timer_read();
  }
  else
  {
    if (timer_elapsed(this_timer) < TAPPING_TERM)
    {
      register_code(code);
      unregister_code(code);
    }
    else
    {
      register_code(mod_code);
      register_code(code);
      unregister_code(code);
      unregister_code(mod_code);
    }
  }

  return false;
}

bool mod_key_press(uint16_t code, uint16_t mod_code, bool pressed,
  uint16_t this_timer)
{
  if (pressed)
  {
    this_timer= timer_read();
  }
  else
  {
    if (timer_elapsed(this_timer) < TAPPING_TERM)
    {
      register_code(code);
      unregister_code(code);
    }
    else
    {
      register_code(mod_code);
      register_code(code);
      unregister_code(code);
      unregister_code(mod_code);
    }
  }

  return false;
}

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__((weak))
void matrix_init_keymap(void) {}

__attribute__((weak))
void startup_keymap(void) {}

__attribute__((weak))
void shutdown_keymap(void) {}

__attribute__((weak))
void suspend_power_down_keymap(void) {}

__attribute__((weak))
void suspend_wakeup_init_keymap(void) {}

__attribute__((weak))
void matrix_scan_keymap(void) {}

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record)
{
  return true;
}

__attribute__((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record)
{
  return true;
}


__attribute__((weak))
uint32_t layer_state_set_keymap(uint32_t state)
{
  return state;
}

__attribute__((weak))
uint32_t default_layer_state_set_keymap(uint32_t state)
{
  return state;
}

__attribute__((weak))
void led_set_keymap(uint8_t usb_led) {}

__attribute__((weak))
void eeconfig_init_keymap(void) {}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void)
{
  userspace_config.raw = eeconfig_read_user();
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))

  if (eeprom_read_byte(EECONFIG_UNICODEMODE) != UC_WIN)
  {
    set_unicode_input_mode(UC_WIN);
  }

#endif //UNICODE_ENABLE
  matrix_init_keymap();
}

void startup_user(void)
{
#ifdef RGBLIGHT_ENABLE
  matrix_init_rgb();
#endif //RGBLIGHT_ENABLE
  startup_keymap();
}

void shutdown_user(void)
{
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(1);
  rgblight_setrgb_red();
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
  rgb_led led;

  for (int i = 0; i < DRIVER_LED_TOTAL; i++)
  {
    led = g_rgb_leds[i];

    if (led.matrix_co.raw < 0xFF)
    {
      rgb_matrix_set_color(i, 0xFF, 0x00, 0x00);
    }
  }

#endif //RGB_MATRIX_ENABLE
  shutdown_keymap();
}

void suspend_power_down_user(void)
{
  suspend_power_down_keymap();
}

void suspend_wakeup_init_user(void)
{
  suspend_wakeup_init_keymap();
}


// No global matrix scan code, so just run keymap's matrix
// scan function
void matrix_scan_user(void)
{
  static bool has_ran_yet;

  if (!has_ran_yet)
  {
    has_ran_yet = true;
    startup_user();
  }

#ifdef RGBLIGHT_ENABLE
  matrix_scan_rgb();
#endif // RGBLIGHT_ENABLE
  matrix_scan_keymap();
}



static uint16_t key_timer;
static bool singular_key = false;
//static uint8_t skip = false;  /* if true: we do not restore the RGB state */

// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
#if defined(KEYBOARD_ergodox_ez) || defined(KEYBOARD_iris_rev2)
  xprintf("KL: col: %u, row: %u, pressed: %u\n", record->event.key.row,
    record->event.key.col, record->event.pressed);
#else
  xprintf("KL: col: %u, row: %u, pressed: %u\n", record->event.key.col,
    record->event.key.row, record->event.pressed);
#endif
#endif //KEYLOGGER_ENABLE

  switch (keycode)
  {
    case KC_QWERTY:
      if (record->event.pressed)
      {
        set_single_persistent_default_layer(_QWERTY);
      }

      return false;
      break;

    case LOWER:
      if (record->event.pressed)
      {
        key_timer = timer_read();
        singular_key = true;
        layer_on(_LOWER);
      }
      else if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY
        || timer_elapsed(key_timer) > LAYER_SKIP_DELAY
        || !singular_key)
      {
        layer_off(_LOWER);
      }

      return false;
      break;

    case RAISE:
      if (record->event.pressed)
      {
        key_timer = timer_read();
        singular_key = true;
        layer_on(_RAISE);
      }
      else if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY
        || timer_elapsed(key_timer) > LAYER_SKIP_DELAY
        || !singular_key)
      {
        layer_off(_RAISE);
      }

      return false;
      break;

    case FUNCTION:
      if (record->event.pressed)
      {
        key_timer = timer_read();
        singular_key = true;
        layer_on(_FUNCTION);
      }
      else if (timer_elapsed(key_timer) < LAYER_TOGGLE_DELAY
        || timer_elapsed(key_timer) > LAYER_SKIP_DELAY
        || !singular_key)
      {
        layer_off(_FUNCTION);
      }

      return false;
      break;

    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
      if (!record->event.pressed)
      {
        uint8_t temp_mod = get_mods();
        clear_mods();
        send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), 10);

        if (temp_mod & MODS_SHIFT_MASK)
        {
          send_string_with_delay_P(PSTR(
#if defined(__ARM__)
              ":dfu-util"
#elif (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
              ":dfu"
#elif defined(BOOTLOADER_HALFKAY)
              ":teensy"
#elif defined(BOOTLOADER_CATERINA)
              ":avrdude"
#else
              ":missing_define"
#endif // bootloader options
            ), 10);
        }

        if (temp_mod & MODS_CTRL_MASK)
        {
          send_string_with_delay_P(PSTR(" -j8 --output-sync"), 10);
        }

        send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);
        set_mods(temp_mod);
      }

      return false;
      break;

    case KC_RESET: // Custom RESET code that sets RGBLights to RED
      if (!record->event.pressed)
      {
#ifdef RGBLIGHT_ENABLE
        rgblight_enable_noeeprom();
        rgblight_mode_noeeprom(1);
        rgblight_setrgb_red();
        _delay_ms(250);
        rgblight_sethsv_noeeprom(0x3C, 0xFF, 0xFF);
        _delay_ms(250);
        rgblight_setrgb_red();
        _delay_ms(250);
#endif // RGBLIGHT_ENABLE
        reset_keyboard();
      }

      return false;
      break;

    case EPRM: // Resets EEPROM
      if (record->event.pressed)
      {
        eeconfig_init();
      }

      return false;
      break;

    case VRSN: // Prints firmware version
      if (record->event.pressed)
      {
        send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION
            ", Built on: " QMK_BUILDDATE), MACRO_TIMER);
      }

      return false;
      break;

    case KMAP:
      if (record->event.pressed)
      {
#if defined(KEYBOARD_lets_split_eh_eh)
        send_string_with_delay("http://www.keyboard-layout-editor.com/#/gists/7cdd2e5ef3b328117a56f3edff59906b",
          10);
#elif defined(KEYBOARD_ergodox_infinity)
        send_string_with_delay("http://www.keyboard-layout-editor.com/#/gists/9dd2c2bd6f1120685ee810303563c7f5",
          10);
#elif defined(KEYBOARD_xd75)
        send_string_with_delay("http://www.keyboard-layout-editor.com/#/gists/0e924c013c75d1dc4bbf51806b5500ee",
          10);
#else
        send_string_with_delay("http://www.keyboard-layout-editor.com/", 10);
#endif /* KEYBOARD */
      }

      return false;
      break;

    /* Skip restoring the old RGB if we changed the current manually */
    case RGB_TOG:
    case RGB_MOD:
    case RGB_HUI:
    case RGB_HUD:
    case RGB_SAI:
    case RGB_SAD:
    case RGB_VAI:
    case RGB_VAD:
      //skip = true;
      singular_key = false;
      return true;
      break;

    /* If any other key was pressed during the layer mod hold period,
     * then the layer mod was used momentarily, and should block latching */
    default:
      singular_key = false;
      break;
  }

  return process_record_keymap(keycode, record) &&
#ifdef RGBLIGHT_ENABLE
    process_record_user_rgb(keycode, record) &&
#endif // RGBLIGHT_ENABLE
    process_record_secrets(keycode, record);
}



// Runs state check and changes underglow color and animation
// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
uint32_t layer_state_set_user(uint32_t state)
{
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
  state = layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
  return layer_state_set_keymap(state);
}


uint32_t default_layer_state_set_user(uint32_t state)
{
  return default_layer_state_set_keymap(state);
}


// Any custom LED code goes here.
// So far, I only have keyboard specific code,
// So nothing goes here.
void led_set_user(uint8_t usb_led)
{
  led_set_keymap(usb_led);
}

#ifdef TAP_DANCE_ENABLE
/* Tap Dance Definitions */
qk_tap_dance_action_t tap_dance_actions[] =
{
  /* Shifting for double quote and semicolon */
  [SCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
  [QUO] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),

  /* complex tap dance function (to specify what happens when key is
   * pressed 3+ times, for example). See
   * https://docs.qmk.fm/tap_dance.html for how to define
  [YOUR_TAPDANCE_2] = ACTION_TAP_DANCE_FUNCTION(your_function_name),0
  */
};
#endif /* TAP_DANCE_ENABLE */
