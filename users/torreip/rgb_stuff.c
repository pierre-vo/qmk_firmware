#include "torreip.h"
#include "rgb_stuff.h"
#include "eeprom.h"

#if defined(RGBLIGHT_ENABLE)
  extern rgblight_config_t rgblight_config;
  bool has_initialized;
#endif

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record)
{
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX)
    || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX))
  {
    keycode = keycode & 0xFF;
  }

  switch (keycode)
  {
    case KC_RGB_T:  // This allows me to use underglow as layer indication, or as normal
#ifdef RGBLIGHT_ENABLE
      if (record->event.pressed)
      {
        userspace_config.rgb_layer_change ^= 1;
        xprintf("rgblight layer change [EEPROM]: %u\n",
          userspace_config.rgb_layer_change);
        eeconfig_update_user(userspace_config.raw);

        if (userspace_config.rgb_layer_change)
        {
          layer_state_set(
            layer_state); // This is needed to immediately set the layer color (looks better)
        }
      }

#endif // RGBLIGHT_ENABLE
      return false;
      break;
#ifdef RGBLIGHT_ENABLE

    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // quantum_keycodes.h L400 for definitions
      if (record->event.pressed)   //This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
      {
        if (userspace_config.rgb_layer_change)
        {
          userspace_config.rgb_layer_change = false;
          xprintf("rgblight layer change [EEPROM]: %u\n",
            userspace_config.rgb_layer_change);
          eeconfig_update_user(userspace_config.raw);
        }
      }

      return true;
      break;

    case KC_RST:
      _delay_ms(250);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 5);
      _delay_ms(250);
      return false;
      break;
#endif // RGBLIGHT_ENABLE
  }

  return true;
}



void keyboard_post_init_rgb(void)
{
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_STARTUP_ANIMATION)

  if (userspace_config.rgb_layer_change)
  {
    rgblight_enable_noeeprom();
  }

  if (rgblight_config.enable)
  {
    layer_state_set_user(layer_state);
    uint16_t old_hue = rgblight_config.hue;
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

    for (uint16_t i = 255; i > 0; i--)
    {
      rgblight_sethsv_noeeprom((i + old_hue) % 255, 255, 255);
      matrix_scan();
      wait_ms(10);
    }
  }

#endif
  layer_state_set_user(layer_state);
  // rgblight_dim_noeeprom_blue();
}


layer_state_t layer_state_set_rgb(layer_state_t state)
{
#ifdef RGBLIGHT_ENABLE

  if (userspace_config.rgb_layer_change)
  {
    switch (biton32(state))
    {
/*
      case _MEDIA:
        rgblight_dim_noeeprom_chartreuse();
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 1);
        break;

      case _GAMEPAD:
        rgblight_dim_noeeprom_orange();
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 2);
        break;
*/

      case _FUNCTION:
#if defined(KEYBOARD_xd75)
        rgblight_dim_noeeprom_coral();
#else
        rgblight_dim_noeeprom_orange();
#endif /* KEYBOARDS */
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
        break;

      case _RAISE:
        rgblight_dim_noeeprom_red();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
        break;

      case _LOWER:
#if defined(KEYBOARD_xd75)
        rgblight_dim_noeeprom_blue();
#else
        rgblight_dim_noeeprom_cyan();
#endif /* KEYBOARDS */
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
        break;

      case _ADJUST:
        rgblight_dim_noeeprom_green();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
        break;

      case _QWERTY:
      default: //  for any other layers, or the default layer
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#if defined(KEYBOARD_lets_split_eh_eh)
        /* without delay the color would not go back */
        _delay_ms(1);
#endif /* KEYBOARD_lets_split_eh_eh */
#if defined(KEYBOARD_xd75)
        rgblight_dim_noeeprom_orange();
#else
        rgblight_dim_noeeprom_blue();
#endif /* KEYBOARDS */
        break;
    }
  }
#endif // RGBLIGHT_ENABLE
  return state;
}


