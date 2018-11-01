#include "torreip.h"
#include "rgb_stuff.h"
#include "eeprom.h"

extern rgblight_config_t rgblight_config;
extern userspace_config_t userspace_config;

#ifdef RGBLIGHT_ENABLE
void rgblight_sethsv_default_helper(uint8_t index)
{
  rgblight_sethsv_at(rgblight_config.hue, rgblight_config.sat,
    rgblight_config.val, index);
}
#endif // RGBLIGHT_ENABLE

#ifdef INDICATOR_LIGHTS
uint8_t last_mod;
uint8_t last_led;
uint8_t last_osm;
uint8_t current_mod;
uint8_t current_led;
uint8_t current_osm;


void set_rgb_indicators(uint8_t this_mod, uint8_t this_led, uint8_t this_osm)
{
  if (userspace_config.rgb_layer_change && biton32(layer_state) == 0)
  {
    if (this_mod & MODS_SHIFT_MASK || this_led & (1<<USB_LED_CAPS_LOCK)
      || this_osm & MODS_SHIFT_MASK)
    {
#ifdef SHFT_LED1
      rgblight_sethsv_at(120, 255, 255, SHFT_LED1);
#endif // SHFT_LED1
#ifdef SHFT_LED2
      rgblight_sethsv_at(120, 255, 255, SHFT_LED2);
#endif // SHFT_LED2
    }
    else
    {
#ifdef SHFT_LED1
      rgblight_sethsv_default_helper(SHFT_LED1);
#endif // SHFT_LED1
#ifdef SHFT_LED2
      rgblight_sethsv_default_helper(SHFT_LED2);
#endif // SHFT_LED2
    }

    if (this_mod & MODS_CTRL_MASK || this_osm & MODS_CTRL_MASK)
    {
#ifdef CTRL_LED1
      rgblight_sethsv_at(0, 255, 255, CTRL_LED1);
#endif // CTRL_LED1
#ifdef CTRL_LED2
      rgblight_sethsv_at(0, 255, 255, CTRL_LED2);
#endif // CTRL_LED2
    }
    else
    {
#ifdef CTRL_LED1
      rgblight_sethsv_default_helper(CTRL_LED1);
#endif // CTRL_LED1
#ifdef CTRL_LED2
      rgblight_sethsv_default_helper(CTRL_LED2);
#endif // CTRL_LED2
    }

    if (this_mod & MODS_GUI_MASK || this_osm & MODS_GUI_MASK)
    {
#ifdef GUI_LED1
      rgblight_sethsv_at(51, 255, 255, GUI_LED1);
#endif // GUI_LED1
#ifdef GUI_LED2
      rgblight_sethsv_at(51, 255, 255, GUI_LED2);
#endif // GUI_LED2
    }
    else
    {
#ifdef GUI_LED1
      rgblight_sethsv_default_helper(GUI_LED1);
#endif // GUI_LED1
#ifdef GUI_LED2
      rgblight_sethsv_default_helper(GUI_LED2);
#endif // GUI_LED2
    }

    if (this_mod & MODS_ALT_MASK || this_osm & MODS_ALT_MASK)
    {
#ifdef ALT_LED1
      rgblight_sethsv_at(240, 255, 255, ALT_LED1);
#endif // ALT_LED1
#ifdef GUI_LED2
      rgblight_sethsv_at(240, 255, 255, ALT_LED2);
#endif // GUI_LED2
    }
    else
    {
#ifdef GUI_LED1
      rgblight_sethsv_default_helper(ALT_LED1);
#endif // GUI_LED1
#ifdef GUI_LED2
      rgblight_sethsv_default_helper(ALT_LED2);
#endif // GUI_LED2
    }
  }
}

void matrix_scan_indicator(void)
{
  current_mod = get_mods();
  current_led = host_keyboard_leds();
  current_osm = get_oneshot_mods();
  set_rgb_indicators(current_mod, current_led, current_osm);
  last_mod = current_mod;
  last_led = current_led;
  last_osm = current_osm;
}
#endif //INDICATOR_LIGHTS


bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record)
{
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
      rgblight_dim_noeeprom_red();
      rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
      return false;
      break;
#endif // RGBLIGHT_ENABLE
  }

  return true;
}


void matrix_init_rgb(void)
{
#ifdef INDICATOR_LIGHTS
  current_mod = last_mod = get_mods();
  current_led = last_led = host_keyboard_leds();
  current_osm = last_osm = get_oneshot_mods();
#endif

  if (userspace_config.rgb_layer_change)
  {
    rgblight_enable_noeeprom();

    switch (biton32(eeconfig_read_default_layer()))
    {
      default:
        rgblight_dim_noeeprom_blue();
        break;
    }

    rgblight_mode_noeeprom(1);
  }
}

void matrix_scan_rgb(void)
{
#ifdef INDICATOR_LIGHTS
  matrix_scan_indicator();
#endif
}


uint32_t layer_state_set_rgb(uint32_t state)
{
#ifdef RGBLIGHT_ENABLE

  if (userspace_config.rgb_layer_change)
  {
    switch (biton32(state))
    {
      case _MEDIA:
        rgblight_dim_noeeprom_chartreuse();
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 1);
        break;

      case _GAMEPAD:
        rgblight_dim_noeeprom_orange();
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 2);
        break;

      case _FUNCTION:
        rgblight_dim_noeeprom_orange();
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;

      case _RAISE:
        rgblight_dim_noeeprom_red();
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;

      case _LOWER:
        rgblight_dim_noeeprom_cyan();
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;

      case _ADJUST:
        rgblight_dim_noeeprom_green();
        // rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT + 2);
        break;

      default: //  for any other layers, or the default layer
        switch (biton32(default_layer_state))
        {
          default:
#if defined(KEYBOARD_xd75)
            rgblight_dim_noeeprom_goldenrod();
#else
            rgblight_dim_noeeprom_blue();
#endif /* KEYBOARDS */
            break;
        }

        biton32(state) == _MODS ? rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING) :
        rgblight_mode_noeeprom(
          RGBLIGHT_MODE_STATIC_LIGHT); // if _MODS layer is on, then breath to denote it
        break;
    }

    //    layer_state_set_indicator(); // Runs every scan, so need to call this here .... since I can't get it working "right" anyhow
  }

#endif // RGBLIGHT_ENABLE
  return state;
}


