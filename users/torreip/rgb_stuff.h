#include "quantum.h"

#ifndef __RGB_STUFF__
#define __RGB_STUFF__

typedef struct
{
  bool enabled;
  uint8_t hue;
  uint16_t timer;
  uint8_t life;
} rgblight_fadeout;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void scan_rgblight_fadeout(void);
void keyboard_post_init_rgb(void);
layer_state_t layer_state_set_rgb(layer_state_t state);
void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void rgb_matrix_layer_helper(uint8_t red, uint8_t green, uint8_t blue,
  uint8_t led_type);

#define rgblight_dim_noeeprom_white()       rgblight_sethsv_noeeprom (HSV_WHITE / 2.5)
#define rgblight_dim_noeeprom_red()         rgblight_sethsv_noeeprom (  0, 255, 100)
#define rgblight_dim_noeeprom_coral()       rgblight_sethsv_noeeprom ( 11, 176, 100)
#define rgblight_dim_noeeprom_orange()      rgblight_sethsv_noeeprom ( 28, 255, 100)
#define rgblight_dim_noeeprom_goldenrod()   rgblight_sethsv_noeeprom ( 30, 218,  80)
#define rgblight_dim_noeeprom_gold()        rgblight_sethsv_noeeprom ( 36, 255, 100)
#define rgblight_dim_noeeprom_yellow()      rgblight_sethsv_noeeprom ( 43, 255, 100)
#define rgblight_dim_noeeprom_chartreuse()  rgblight_sethsv_noeeprom ( 64, 255, 100)
#define rgblight_dim_noeeprom_green()       rgblight_sethsv_noeeprom ( 85, 255, 100)
#define rgblight_dim_noeeprom_springgreen() rgblight_sethsv_noeeprom (106, 255, 100)
#define rgblight_dim_noeeprom_turquoise()   rgblight_sethsv_noeeprom (123,  90,  50)
#define rgblight_dim_noeeprom_teal()        rgblight_sethsv_noeeprom (128, 255,  50)
#define rgblight_dim_noeeprom_cyan()        rgblight_sethsv_noeeprom (128, 255, 100)
#define rgblight_dim_noeeprom_azure()       rgblight_sethsv_noeeprom (132, 102, 100)
#define rgblight_dim_noeeprom_blue()        rgblight_sethsv_noeeprom (HSV_BLUE / 2.5)
#define rgblight_dim_noeeprom_purple()      rgblight_sethsv_noeeprom (191, 255, 100)
#define rgblight_dim_noeeprom_magenta()     rgblight_sethsv_noeeprom (213, 255, 100)
#define rgblight_dim_noeeprom_pink()        rgblight_sethsv_noeeprom (234, 128, 100)

#endif //__RGB_STUFF__
