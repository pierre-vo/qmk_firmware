#include "torreip.h"

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

// Defines actions for my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
//  static uint16_t key_timer;
//  static bool singular_key = false;

  switch (keycode)
  {
    case KC_RST:
      reset_keyboard();
      return false;
      break;

    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
      if (!record->event.pressed)
      {
        uint8_t temp_mod = get_mods();
        uint8_t temp_osm = get_oneshot_mods();
        clear_mods();
        clear_oneshot_mods();
        send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP),
          TAP_CODE_DELAY);
#ifndef MAKE_BOOTLOADER

        if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#endif
        {
#if defined(__arm__)
          send_string_with_delay_P(PSTR(":dfu-util"), TAP_CODE_DELAY);
#elif defined(BOOTLOADER_DFU)
          send_string_with_delay_P(PSTR(":dfu"), TAP_CODE_DELAY);
#elif defined(BOOTLOADER_HALFKAY)
          send_string_with_delay_P(PSTR(":teensy"), TAP_CODE_DELAY);
#elif defined(BOOTLOADER_CATERINA)
          send_string_with_delay_P(PSTR(":avrdude"), TAP_CODE_DELAY);
#endif // bootloader options
        }

        if ((temp_mod | temp_osm) & MOD_MASK_CTRL)
        {
          send_string_with_delay_P(PSTR(" -j8 --output-sync"), TAP_CODE_DELAY);
        }

#ifdef RGB_MATRIX_SPLIT_RIGHT
        send_string_with_delay_P(
          PSTR(" MASTER=right"), TAP_CODE_DELAY);
#endif
        send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), TAP_CODE_DELAY);
      }

      break;

    case VRSN: // Prints firmware version
      if (record->event.pressed)
      {
        send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION
            ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
      }
      break;

    case KMAP:
      if (record->event.pressed) {
    	  send_string_with_delay_P(PSTR("http://www.keyboard-layout-editor.com/#/gists/0231894ce189eddf2dfdc902c19307cf"), TAP_CODE_DELAY);
      }
      break;

    /* If any other key was pressed during the layer mod hold period,
     * then the layer mod was used momentarily, and should block latching */
    default:
//      singular_key = false;
    	break;
  }

  return process_record_keymap(keycode, record) &&
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    process_record_user_rgb(keycode, record) &&
#endif // RGBLIGHT_ENABLE
    process_record_secrets(keycode, record);
}
