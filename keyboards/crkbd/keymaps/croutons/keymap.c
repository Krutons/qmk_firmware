#include QMK_KEYBOARD_H
#include "quantum.h"
#include <stdio.h>

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"
#endif

//enum keycodes {
//    SFT_CAP = SAFE_RANGE,
//    WIN_MAC
//};

#if defined(BABBLE_END_RANGE)
#    define USER_START BABBLE_END_RANGE
#else
#    if defined(KEYMAP_SAFE_RANGE)
#        define USER_START KEYMAP_SAFE_RANGE
#    else
#        define USER_START SAFE_RANGE
#    endif
#endif

enum keycodes {
    TO_MAC = BABBLE_END_RANGE,
    TO_WIN,
    DblClik,
    Home
};

enum layer_names {
    _BASE = 0,
    _WINMODE,
    _FPAD,
    _FPADPLUS,
    _NAV,
    _SYM,
    _FUNC,
    _D2,
    _PS1,
    _PS2
};

enum combos {
  _WF,
  _XC,
  _COMMADOT,
  _GM,
  _FP,
  _HCOMMA,
  _UY,
  _EI,
  _AZ,
  _RX,
  _SC,
  _TD,
  _GV,
  _RS,
  _CD,
  _AQ,
  _SD,
  _PB,
  _TG,
  _DV,
  _JL,
  _MN,
  _KH,
  _ZX,
  _DOTSLASH
};

// Layer macros
// #define Home    TO(_BASE)
#define FPad     MO(_FPAD)
#define Nav      MO(_NAV)
#define Sym      MO(_SYM)
#define Num      MO(_FUNC)
#define Dest2    TO(_D2)
#define Quickbar MO(_FPADPLUS)
#define Ps2      MO(_PS2)
#define Photosh  TO(_PS1)

// Home row mod macros
#define HOME_A LSFT_T(KC_A)
#define HOME_R LCTL_T(KC_R)
#define HOME_S LALT_T(KC_S)
#define HOME_T LGUI_T(KC_T)
#define HOME_D LCTL_T(KC_D)
#define HOME_G LGUI_T(KC_G)
#define HOME_B LCTL_T(KC_B)
#define HOME_V LALT_T(KC_V)

#define HOME_N RGUI_T(KC_N)
#define HOME_E LALT_T(KC_E)
#define HOME_I RCTL_T(KC_I)
#define HOME_O RSFT_T(KC_O)
#define HOME_H RCTL_T(KC_H)
#define HOME_M RGUI_T(KC_M)
#define HOME_K LALT_T(KC_K)
#define HOME_J RCTL_T(KC_J)

// Define custom colours
#define BASE_COL        12,233,255  // Warm white
#define WIN_COL         3,220,255  // Pink
#define PS_COL          155,255,255 // Blue
#define LEAD_COL        127,255,255 // Cyan
#define GAME_COL        190,255,255 // Purple
#define CAPS_COL        0, 255, 255 // Red

// LED addresses
// TODO: LED addresses


static uint16_t caps_flag; // capslock flag for LED indicator
bool win_mode = false; // flag to track windows mode across other layer moves

#ifdef RGBLIGHT_ENABLE

void base_or_winmode_col(void) {
    if (layer_state_is(_BASE)) {
        rgblight_sethsv_noeeprom(BASE_COL);
    }
    else if (layer_state_is(_WINMODE)) {
        rgblight_sethsv_noeeprom(WIN_COL);
    }
}

#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(
      // Colemak DHm - 0
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,  HOME_B,                       HOME_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,  HOME_G,                       HOME_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSPO,    KC_Z,    KC_X,    KC_C,    KC_D,  HOME_V,                       HOME_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_RAPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,Quickbar,  Quickbar,  KC_SPC,  Sym
                                      //`--------------------------'  `--------------------------'

  ),

  [_WINMODE] = LAYOUT_split_3x6_3(
        // Windows mode overlay - 1
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCPO, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______, _______,_______,      _______, _______,   _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_FPAD] = LAYOUT_split_3x6_3(
      // Fastpad - 2
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      S(KC_8),    KC_1,    KC_2,    KC_3,S(KC_EQL), KC_DOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_EQL,    KC_4,    KC_5,    KC_6,KC_DOT,S(KC_SCLN),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,KC_SPACE,   KC_SPACE,    KC_0,   Sym
                                      //`--------------------------'  `--------------------------'
  ),

  [_FPADPLUS] = LAYOUT_split_3x6_3(
      // Fastpad+ - 3
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,  KC_F12,C(KC_LEFT), KC_UP,C(KC_RIGHT),A(KC_UP),                      KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, XXXXXXX, KC_LEFT,KC_DOWN, KC_RIGHT,A(KC_DOWN),                      S(KC_8),    KC_1,    KC_2,    KC_3,S(KC_EQL), KC_DOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, B_UNDO,S(C(KC_TAB)),B_COPY,C(KC_TAB),B_PASTE,                       KC_EQL,    KC_4,    KC_5,    KC_6,KC_DOT,S(KC_SCLN),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,Quickbar,  Quickbar,    KC_0,   Sym
                                      //`--------------------------'  `--------------------------'
  ),


  [_NAV] = LAYOUT_split_3x6_3(
      // Navigation - 4
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,KC_F12,C(KC_LEFT),KC_HOME,C(KC_RGHT),A(KC_UP),                    QK_REBOOT, KC_HOME,   KC_UP,  KC_END,  B_SCAP, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, KC_LSFT, KC_LCTL,KC_LALT,KC_LGUI,A(KC_DOWN),                      B_FIND, KC_LEFT, KC_DOWN, KC_RGHT, KC_BRIU,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX,A(KC_TAB),S(C(KC_TAB)),KC_END,C(KC_TAB),KC_MPLY,                     B_RUNAPP, KC_PGUP,C(KC_ENT),KC_PGDN, KC_BRID,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,  KC_ENT,     KC_ENT,KC_SPACE,   Sym
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYM] = LAYOUT_split_3x6_3(
        // Symbols - 5
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, S(KC_1), KC_LBRC,S(KC_LBRC),S(KC_9),KC_TILD,                     S(KC_6),S(KC_0),S(KC_RBRC), KC_RBRC,KC_GRAVE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,   KC_AT, S(KC_8),  KC_EQL, KC_MINS, S(KC_4),                      KC_NUHS, KC_RGUI, KC_LALT, KC_RCTL, KC_RSFT, KC_DQUO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     A(KC_3),S(KC_7),S(KC_BSLS),S(KC_EQL),S(KC_MINS),S(KC_5),                   S(KC_3),KC_NUBS,KC_SCLN,S(KC_SCLN),S(KC_SLSH),KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,  KC_ENT,     KC_ENT,KC_SPACE,   Sym
                                      //`--------------------------'  `--------------------------'
  ),

    [_FUNC] = LAYOUT_split_3x6_3(
        // Function and modes - 6
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      Photosh, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,  Dest2,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,                      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F11, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       TO_WIN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F10,  TO_MAC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Num, KC_LSFT,  KC_ENT,     KC_ENT,KC_SPACE,   Num
                                      //`--------------------------'  `--------------------------'
  ),

    [_D2] = LAYOUT_split_3x6_3(
        // Destiny 2 - 7
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_J,    KC_L,   KC_UP,    KC_Y, KC_SCLN,    Home,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_H, KC_LEFT, KC_DOWN,KC_RIGHT,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_I,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,KC_SPACE,    KC_C,     KC_ENT,   KC_F1,   Home
                                      //`--------------------------'  `--------------------------'
  ),

    [_PS1] = LAYOUT_split_3x6_3(
        // Photoshop layer 1 - 8
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         Home, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 G(S(KC_DOT)), KC_LBRC, KC_RBRC,    KC_V, KC_BTN2,  B_UNDO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 G(S(KC_EQL)),    KC_R,    KC_B, G(KC_D),    KC_J,    KC_I,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         Home, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   G(KC_MINS),KC_GRAVE,    KC_L, KC_LGUI, KC_LSFT, KC_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          Home,  XXXXXXX,  XXXXXXX,        Home, KC_SPACE,   Ps2
                                      //`--------------------------'  `--------------------------'
  ),

   [_PS2] = LAYOUT_split_3x6_3(
        // Photoshop layer 2 - 9
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,C(KC_LEFT), KC_UP,C(KC_RIGHT),XXXXXXX,G(S(KC_Z)),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, DblClik, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_ENT,   B_SAVE, KC_BSPC, XXXXXXX,  B_SCAP,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,   Ps2
                                      //`--------------------------'  `--------------------------'
  )
};

const uint16_t PROGMEM wf_combo[] =        {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM xc_combo[] =        {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM commadot_combo[] =  {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM gm_combo[] =        {HOME_G, HOME_M, COMBO_END};
const uint16_t PROGMEM fp_combo[] =        {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM cd_combo[] =        {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM ne_combo[] =        {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM hcomma_combo[] =    {KC_H, KC_COMMA, COMBO_END};
const uint16_t PROGMEM az_combo[] =        {KC_A, KC_Z, COMBO_END};
const uint16_t PROGMEM rx_combo[] =        {KC_R, KC_X, COMBO_END};
const uint16_t PROGMEM sc_combo[] =        {KC_S, KC_C, COMBO_END};
const uint16_t PROGMEM td_combo[] =        {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM gv_combo[] =        {HOME_G, HOME_V, COMBO_END};
const uint16_t PROGMEM escq_combo[] =      {KC_ESC, KC_Q, COMBO_END};
const uint16_t PROGMEM uy_combo[] =        {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM ei_combo[] =        {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM rs_combo[] =        {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM sf_combo[] =        {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM aq_combo[] =        {KC_A, KC_Q, COMBO_END};
const uint16_t PROGMEM sd_combo[] =        {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM pb_combo[] =        {KC_P, HOME_B, COMBO_END};
const uint16_t PROGMEM tg_combo[] =        {KC_T, HOME_G, COMBO_END};
const uint16_t PROGMEM dv_combo[] =        {KC_D, HOME_V, COMBO_END};
const uint16_t PROGMEM jl_combo[] =        {HOME_J, KC_L, COMBO_END};
const uint16_t PROGMEM mn_combo[] =        {HOME_M, KC_N, COMBO_END};
const uint16_t PROGMEM kh_combo[] =        {HOME_K, KC_H, COMBO_END};
const uint16_t PROGMEM zx_combo[] =        {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM dotslash_combo[] =  {KC_DOT, KC_SLSH, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [_WF] =        COMBO(wf_combo, KC_MINS), // -
  [_XC] =        COMBO(xc_combo, S(KC_MINS)), // _
  [_COMMADOT] =  COMBO(commadot_combo, KC_TAB), // Tab
  [_GM] =        COMBO(gm_combo, KC_CAPS), // Caps
  [_FP] =        COMBO(fp_combo, S(KC_1)), // !
  [_HCOMMA] =    COMBO(hcomma_combo, S(KC_SLASH)), //?
  [_UY] =        COMBO(uy_combo, S(KC_QUOT)), // "
  [_EI] =        COMBO(ei_combo, KC_DOT), //.
  [_RS] =        COMBO(rs_combo, KC_ENT), // Enter

  //Layer combos
  [_CD] =        COMBO(cd_combo, FPad), // switch to right hand numpad
  [_DOTSLASH] =  COMBO(dotslash_combo, KC_LEAD),  // Leader key alternative

  //Vertical command combos
  [_AZ] =        COMBO(az_combo, B_UNDO), // undo
  [_RX] =        COMBO(rx_combo, B_SAVE), // save
  [_SC] =        COMBO(sc_combo, B_COPY), // copy
  [_TD] =        COMBO(td_combo, B_CUT), // cut
  [_GV] =        COMBO(gv_combo, B_PASTE),  // paste
  [_AQ] =        COMBO(aq_combo, B_REDO),  // redo
  [_ZX] =        COMBO(zx_combo, B_DLW), // delete word

  //String combos - maybe not a great idea until accuracy is better
  [_SD] =        COMBO_ACTION(sd_combo), // d3
  [_PB] =        COMBO_ACTION(pb_combo), //
  [_TG] =        COMBO_ACTION(tg_combo), //
  [_DV] =        COMBO_ACTION(dv_combo), //
  [_JL] =        COMBO_ACTION(jl_combo), //
  [_MN] =        COMBO_ACTION(mn_combo), // :3
  [_KH] =        COMBO_ACTION(kh_combo) //
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case _SD:
      if (pressed) {
        SEND_STRING("d3");
      }
      break;
    case _PB:
      if (pressed) {
        SEND_STRING("");
      }
      break;
    case _TG:
      if (pressed) {
        SEND_STRING("");
      }
      break;
    case _DV:
      if (pressed) {
        SEND_STRING("");
      }
      break;
    case _JL:
      if (pressed) {
        SEND_STRING("://3");
      }
      break;
    case _MN:
      if (pressed) {
        SEND_STRING(":3");
      }
      break;
    case _KH:
      if (pressed) {
        SEND_STRING("");
      }
      break;
  }
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_270;
    }
}

//void render_crkbd_logo(void) {
//    static const char PROGMEM crkbd_logo[] = {
//        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
//        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
//        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
//        0};
//    oled_write_P(crkbd_logo, false);
//}

#    define KEYLOG_LEN 5
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("Keys:"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("OS:  "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("MacOS"), false);
            break;
        case _WINMODE:
            oled_write_P(PSTR("Win  "), false);
            break;
        default:
            if (win_mode) {
                oled_write_P(PSTR("Win  "), false);
            }
            else {
                oled_write_P(PSTR("MacOS"), false);
            }
    }
}

//void render_layer_state(void) {
//
//    oled_write_P(PSTR("LAYER"), false);
//    oled_write_P(PSTR("MacOS"), layer_state_is(_BASE));
//    oled_write_P(PSTR("Win  "), layer_state_is(_WINMODE));
//    oled_write_P(PSTR("Nav  "), layer_state_is(_NAV));
//    oled_write_P(PSTR("Sym  "), layer_state_is(_SYM));
//    oled_write_P(PSTR("FKeys"), layer_state_is(_FUNC));
//    oled_write_P(PSTR("Game "), layer_state_is(_D2));
//    oled_write_P(PSTR("Num  "), layer_state_is(_FPAD));
//    oled_write_P(PSTR("Num+ "), layer_state_is(_FPADPLUS));
//    oled_write_P(PSTR("Ps   "), layer_state_is(_PS1));
//    //oled_write_P(PSTR("Ps2  "), layer_state_is(_PS2));
//}


void render_layer_state(void) {

        oled_write_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("MacOS"), false);
            break;
        case _WINMODE:
            oled_write_P(PSTR("Win  "), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Nav  "), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Sym  "), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("Fkeys"), false);
            break;
        case _D2:
            oled_write_P(PSTR("Game "), false);
            break;
        case _FPAD:
            oled_write_P(PSTR("Num  "), false);
            break;
        case _FPADPLUS:
            oled_write_P(PSTR("Num+ "), false);
            break;
        case _PS1:
            oled_write_P(PSTR("PsL1 "), false);
            break;
        case _PS2:
            oled_write_P(PSTR("PsL2 "), false);
            break;
}
}

void render_keylock_status(uint8_t led_usb_state) {
    //oled_write_P(PSTR("Lock:"), false);
    //oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("Caps"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_P(PSTR(" "), false);
    //oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR("Shift"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("Ctrl "), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("Alt  "), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("GUI  "), (modifiers & MOD_MASK_GUI));
}

//void render_bootmagic_status(void) {
//    /* Show Ctrl-Gui Swap options */
//    static const char PROGMEM logo[][2][3] = {
//        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
//        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
//    };
//    oled_write_P(PSTR("BTMGK"), false);
//    oled_write_P(PSTR(" "), false);
//    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
//    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
//    oled_write_P(PSTR(" "), false);
//    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
//    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
//    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
//}

void render_blank_line(void) {
    oled_write_P(PSTR("     "), false);
}

void render_uvu(void) {
    oled_write_P(PSTR(" uvu "), false);
    //oled_write_P(PSTR("unvnu"), false);
    //oled_write_P(PSTR(" unu "), false);
    //oled_write_P(PSTR(" uou "), false);
    oled_write_P(PSTR("u v u"), false);
}

void render_status_main(void) {
    render_default_layer_state();
    render_blank_line();
    render_layer_state();
    render_blank_line();
    render_keylock_status(host_keyboard_leds());
    render_blank_line();
    render_mod_status(get_mods());
    render_blank_line();
    render_keylogger_status();
}

bool oled_task_user(void) {
    update_log();
    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        //render_layer_state();
        //render_status_main();
        //render_crkbd_logo();
        render_uvu();
        render_uvu();
        render_uvu();
        render_uvu();
        render_uvu();
        render_uvu();
        render_uvu();
        render_uvu();
        render_uvu();
        render_uvu();
        render_uvu();
        //oled_scroll_left();  // Turns on scrolling
    }
    return false;
}
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef USE_BABBLEPASTE
    if (keycode > BABBLE_START && keycode < BABBLE_END_RANGE) {
        if (record->event.pressed) {
            babblePaste(keycode, 1);
            #ifdef OLED_ENABLE
            add_keylog(keycode);
            #endif
        } else {
            babblePaste(keycode, 0);
            #ifdef OLED_ENABLE
            add_keylog(keycode);
            #endif
        }
    }
    #endif
    switch (keycode) {
        case TO_MAC:
            if (record->event.pressed) {
            layer_move(_BASE);  // Toggle WINMODE off
            set_babble_mode(BABL_MAC_MODE);
            win_mode = false;
            base_or_winmode_col();
            } else {
            }
            break;
        case TO_WIN:
            if (record->event.pressed) {
            layer_move(_WINMODE);  // Toggle WINMODE on
            set_babble_mode(BABL_WINDOWS_MODE);
            win_mode = true;
            base_or_winmode_col();
            } else {
            }
            break;
        case DblClik:
            if (record->event.pressed) {
            tap_code16(KC_BTN1);
            tap_code16(KC_BTN1);
            } else {
            }
            break;
        case Home:
            if (record->event.pressed) {
                if (win_mode == true) {  // Move to window mode
                    layer_move(_WINMODE);  // Toggle WINMODE on
                    set_babble_mode(BABL_WINDOWS_MODE);
                    win_mode = true;
                    base_or_winmode_col();
                }
                else if (win_mode == false) {  // Move to mac mode
                    layer_move(_BASE);  // Toggle WINMODE off
                    set_babble_mode(BABL_MAC_MODE);
                    win_mode = false;
                    base_or_winmode_col();
                }
                 else {
                }
                break;
            }
//    case SFT_CAP:
//        if (record->event.pressed) {
//            if (caps_flag) {
//                tap_code(KC_CAPS); // Disable capslock
//            }
//            else {
//                if (get_oneshot_mods() & MOD_MASK_SHIFT || get_oneshot_locked_mods() & MOD_MASK_SHIFT) {
//                    del_oneshot_mods(MOD_BIT(KC_LSFT));
//                    unregister_mods(MOD_BIT(KC_LSFT));
//                    tap_code(KC_CAPS); // Enable capslock
//                }
//                else {
//                    set_oneshot_mods(MOD_BIT(KC_LSFT));
//                }
//            }
//        }
            return false;
        break;
      }
    #ifdef OLED_ENABLE
    if (record->event.pressed) {
        add_keylog(keycode);
    }
    return true;
    #endif
    return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
//Leader stuff
  LEADER_DICTIONARY() {
      leading = false;
      leader_end();
    // Caps
    SEQ_ONE_KEY(KC_LSFT){
    tap_code(KC_CAPS);
    }
    // lq
    SEQ_ONE_KEY(KC_Q){
    SEND_STRING("");
    }
    // d3
    SEQ_TWO_KEYS(KC_D, KC_F){
    SEND_STRING("");
    }
    // cg
    SEQ_TWO_KEYS(KC_C, KC_G){
    SEND_STRING("");
    }
    // >:)
    SEQ_TWO_KEYS(KC_DOT, KC_SCLN){
    SEND_STRING("");
    }
    // :<
    SEQ_TWO_KEYS(KC_COMM, KC_SCLN){
    SEND_STRING("");
    }
    // Destiny 2 layer
    SEQ_THREE_KEYS(KC_G, KC_U, KC_N){
    layer_invert(_D2);
    }
    // Email Address
    SEQ_THREE_KEYS(KC_G, KC_U, KC_Y){
        SEND_STRING("");
    }
  }
}

#ifdef RGBLIGHT_ENABLE

void caps_light_set(void) {
    if (caps_flag == 1){
      //Catch leader during caps on edgecase
      //Caps case last to make sure it overrides
      //rgblight_sethsv_range(CAPS_COL, LED_IND);
      //TODO: Caps lighting addressing
    }
    else if (caps_flag == 0){
        base_or_winmode_col();
    }
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(BASE_COL); // Warm white 12,233,255
}

void leader_start(void) {
  rgblight_sethsv_noeeprom(LEAD_COL);
}

void leader_end(void) {
  base_or_winmode_col();
  caps_light_set();
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock){
        caps_flag = 1;
        caps_light_set();
    }
    else{
        caps_flag = 0;
        base_or_winmode_col();
        }
return true;
}

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _D2:
        rgblight_sethsv_noeeprom(GAME_COL);
        break;
    case _PS1:
        rgblight_sethsv_noeeprom(PS_COL);
        break;
    case _PS2:
        rgblight_sethsv_noeeprom(PS_COL);
        break;
    default:
        base_or_winmode_col();
        caps_light_set();
        break;
    }
    #endif
  return update_tri_layer_state(state, _NAV, _SYM, _FUNC);
  }

