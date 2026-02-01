#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

 #define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
// #define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

