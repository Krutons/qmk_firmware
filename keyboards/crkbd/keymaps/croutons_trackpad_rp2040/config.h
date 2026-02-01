#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

 #define MASTER_LEFT
 #define SPLIT_LAYER_STATE_ENABLE
 #define SPLIT_LED_STATE_ENABLE
 #define SPLIT_TRANSPORT_MIRROR
 #define SPLIT_ACTIVITY_ENABLE
 #define SPLIT_MODS_ENABLE
 #define SPLIT_POINTING_ENABLE
 #define POINTING_DEVICE_RIGHT
 #define POINTING_DEVICE_INVERT_X
 #define POINTING_DEVICE_INVERT_Y
 //#define SPLIT_OLED_ENABLE
// #define MASTER_RIGHT
// #define EE_HANDS
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL

#ifndef NO_DEBUG
    #define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
    #define NO_PRINT
#endif // !NO_PRINT

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
//#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#define AZOTEQ_IQS5XX_TPS43
#define AZOTEQ_IQS5XX_SCROLL_ENABLE false

#define USE_BABBLEPASTE
#define BABL_WINDOWS
#define BABL_MAC

#define BABL_OSKEYS
#define BABL_APP
#define BABL_MOVE

#define COMBO_COUNT 22
#define TAPPING_TERM 200
#define TAPPING_FORCE_HOLD
#define ONESHOT_TIMEOUT 3000

#define LEADER_TIMEOUT 450
#define LEADER_PER_KEY_TIMING
