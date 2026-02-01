#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keymap_steno.h"

//enum keycodes {
//    SFT_CAP = SAFE_RANGE,
//    WIN_MAC
//};

enum layer_names {
    _STEN
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_STEN] = LAYOUT_split_3x6_3(
        // Stenography - 7
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,                       STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL, STN_ST1,                      STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  STN_S2,  STN_KL,  STN_WL,  STN_RL, STN_ST2,                      STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             XXXXXXX,    STN_A,   STN_O,   STN_E,     STN_U,   XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(222,255,255);
}


#endif
