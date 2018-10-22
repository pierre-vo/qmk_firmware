#include "quantum.h"

typedef struct {
    bool enabled;
    uint8_t hue;
    uint16_t timer;
    uint8_t life;
} rgblight_fadeout;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
void scan_rgblight_fadeout(void);
void matrix_init_rgb(void);
void matrix_scan_rgb(void);
uint32_t layer_state_set_rgb(uint32_t state);

#define rgblight_dim_noeeprom_white()       rgblight_sethsv_noeeprom (  0,   0, 100)
#define rgblight_dim_noeeprom_red()         rgblight_sethsv_noeeprom (  0, 255, 100)
#define rgblight_dim_noeeprom_coral()       rgblight_sethsv_noeeprom ( 16, 176, 100)
#define rgblight_dim_noeeprom_orange()      rgblight_sethsv_noeeprom ( 39, 255, 100)
#define rgblight_dim_noeeprom_goldenrod()   rgblight_sethsv_noeeprom ( 43, 218,  80)
#define rgblight_dim_noeeprom_gold()        rgblight_sethsv_noeeprom ( 51, 255, 100)
#define rgblight_dim_noeeprom_yellow()      rgblight_sethsv_noeeprom ( 60, 255, 100)
#define rgblight_dim_noeeprom_chartreuse()  rgblight_sethsv_noeeprom ( 90, 255, 100)
#define rgblight_dim_noeeprom_green()       rgblight_sethsv_noeeprom (120, 255, 100)
#define rgblight_dim_noeeprom_springgreen() rgblight_sethsv_noeeprom (150, 255, 100)
#define rgblight_dim_noeeprom_turquoise()   rgblight_sethsv_noeeprom (174,  90,  50)
#define rgblight_dim_noeeprom_teal()        rgblight_sethsv_noeeprom (180, 255,  50)
#define rgblight_dim_noeeprom_cyan()        rgblight_sethsv_noeeprom (180, 255, 100)
#define rgblight_dim_noeeprom_azure()       rgblight_sethsv_noeeprom (186, 102, 100)
#define rgblight_dim_noeeprom_blue()        rgblight_sethsv_noeeprom (240, 255, 100)
#define rgblight_dim_noeeprom_purple()      rgblight_sethsv_noeeprom (270, 255, 100)
#define rgblight_dim_noeeprom_magenta()     rgblight_sethsv_noeeprom (300, 255, 100)
#define rgblight_dim_noeeprom_pink()        rgblight_sethsv_noeeprom (330, 128, 100)