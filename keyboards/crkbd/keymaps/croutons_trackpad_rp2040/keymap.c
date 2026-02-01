//qmk compile -kb crkbd/rev1 -km croutons_trackpad_rp2040
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
    SCROLL_U,
    SCROLL_D,
    Home
};

enum layer_names {
    _BASE = 0,
    _WINMODE,
    _FPAD,
    _FPADPLUS,
    _FPADPLUSw,
    _FPADPLUSRIGHT,
    _NAV,
    _SYM,
    _FUNC
};

enum combos {
  _WF,
  _XC,
  _COMMADOT,
  _GM,
  _wGM,
  _FP,
  _HCOMMA,
  _UY,
  _EI,
  _AZ,
  _RX,
  _SC,
  _TD,
  _GV,
  _wGV,
  _RS,
  _AQ,
  _SD,
  _ZX,
  _CD,
  _DOTSLASH
};

// Layer macros
// #define Home    TO(_BASE)
#define FPad     MO(_FPAD)
#define Nav      MO(_NAV)
#define Sym      MO(_SYM)
#define Num      MO(_FUNC)
#define Quickbar MO(_FPADPLUS)
#define QuickbarW MO(_FPADPLUSw)
#define QuickbarR LT(_FPADPLUSRIGHT, KC_TAB)

// Home row mod macros - mac
#define HOME_G LGUI_T(KC_G)
#define HOME_B LCTL_T(KC_B)
#define HOME_V LALT_T(KC_V)
#define HOME_M RGUI_T(KC_M)
#define HOME_K LALT_T(KC_K)
#define HOME_J RCTL_T(KC_J)

// Home row mod macros - win
#define wHOME_G LCTL_T(KC_G)
#define wHOME_B LGUI_T(KC_B)
#define wHOME_V LALT_T(KC_V)
#define wHOME_M RCTL_T(KC_M)
#define wHOME_K LALT_T(KC_K)
#define wHOME_J RGUI_T(KC_J)

// Define custom colours
#define BASE_COL        12,233,255  // Warm white //rgb (255,239,232)
#define WIN_COL         3,220,255  // Pink
#define PS_COL          155,255,255 // Blue
#define LEAD_COL        127,255,255 // Cyan
#define GAME_COL        190,255,255 // Purple
#define CAPS_COL        0, 255, 255 // Red
#define OFF_COL         0, 0, 0 // Black

// LED Colour arrays
static const int base_col[] = {255,80,20};  // RGB_WHITE
static const int win_col[] =  {255, 40, 20};  // RGB_PINK
static const int ps_col[] =   {0x00, 0xFF, 0xFF};  // RGB_CYAN
static const int lead_col[] = {0x00, 0x80, 0x80};  // RGB_TEAL
static const int game_col[] = {0x7A, 0x00, 0xFF};  // RGB_PURPLE
static const int caps_col[] = {0xFF, 0x00, 0x00};  // RGB_RED
static const int nav_green[] = {0x00, 0xFF, 0x00}; // RGB_GREEN
static const int off_col[] = {0x00, 0x00, 0x00};  // RGB_BLACK

// LED addresses
static const char underglow_leds[] = {0,1,2,3,4,5,27,28,29,30,31,32};
static const char indicator_leds[] = {7,34};


// Flags
static uint8_t caps_flag = 0; // capslock flag for LED indicator
bool win_mode = false; // flag to track windows mode across other layer moves
bool is_leader = false; // flag to detect leader status


// Combo
const uint16_t PROGMEM wf_combo[] =        {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM xc_combo[] =        {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM commadot_combo[] =  {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM gm_combo[] =        {HOME_G, HOME_M, COMBO_END};
const uint16_t PROGMEM gm_win_combo[] =    {wHOME_G, wHOME_M, COMBO_END};
const uint16_t PROGMEM fp_combo[] =        {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM cd_combo[] =        {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM hcomma_combo[] =    {KC_H, KC_COMMA, COMBO_END};
const uint16_t PROGMEM az_combo[] =        {KC_A, KC_Z, COMBO_END};
const uint16_t PROGMEM rx_combo[] =        {KC_R, KC_X, COMBO_END};
const uint16_t PROGMEM sc_combo[] =        {KC_S, KC_C, COMBO_END};
const uint16_t PROGMEM td_combo[] =        {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM gv_combo[] =        {HOME_G, HOME_V, COMBO_END};
const uint16_t PROGMEM gv_win_combo[] =    {wHOME_G, wHOME_V, COMBO_END};
const uint16_t PROGMEM uy_combo[] =        {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM rs_combo[] =        {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM sf_combo[] =        {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM aq_combo[] =        {KC_A, KC_Q, COMBO_END};
const uint16_t PROGMEM sd_combo[] =        {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM zx_combo[] =        {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM dotslash_combo[] =  {KC_DOT, KC_SLSH, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [_WF] =        COMBO(wf_combo, KC_MINS), // -
  [_XC] =        COMBO(xc_combo, S(KC_MINS)), // _
  [_COMMADOT] =  COMBO(commadot_combo, KC_TAB), // Tab
  [_GM] =        COMBO(gm_combo, KC_CAPS), // Caps
  [_wGM] =       COMBO(gm_win_combo, KC_CAPS), // Caps in winmode
  [_FP] =        COMBO(fp_combo, S(KC_1)), // !
  [_HCOMMA] =    COMBO(hcomma_combo, S(KC_SLASH)), //?
  [_UY] =        COMBO(uy_combo, S(KC_QUOT)), // "
  [_RS] =        COMBO(rs_combo, KC_ENT), // Enter

  //Layer combos
  [_CD] =        COMBO(cd_combo, FPad), // switch to right hand numpad
  [_DOTSLASH] =  COMBO(dotslash_combo, QK_LEAD),  // Leader key alternative

  //Vertical command combos
  [_AZ] =        COMBO(az_combo, B_UNDO), // undo
  [_RX] =        COMBO(rx_combo, B_SAVE), // save
  [_SC] =        COMBO(sc_combo, B_COPY), // copy
  [_TD] =        COMBO(td_combo, B_CUT), // cut
  [_GV] =        COMBO(gv_combo, G(KC_V)),  // paste
  [_wGV]=        COMBO(gv_win_combo, C(KC_V)), // paste for windows
  [_ZX] =        COMBO(zx_combo, B_DLW), // delete word

  //String combos - maybe not a great idea until accuracy is better
  [_SD] =        COMBO_ACTION(sd_combo), // d3
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case _SD:
      if (pressed) {
        SEND_STRING("d3");
      }
      break;
  }
}

// LED Setters
void set_underglow_col(const int *rgb) {
    for (uint8_t i = 0; i < 12; i++) {
    rgb_matrix_set_color(underglow_leds[i], rgb[0], rgb[1], rgb[2]);
    }
}

void set_indicators(const int *rgb) {
    rgb_matrix_set_color(indicator_leds[0], rgb[0], rgb[1], rgb[2]);
    rgb_matrix_set_color(indicator_leds[1], rgb[0], rgb[1], rgb[2]);
}

void base_or_winmode_col(void) {
    if (layer_state_is(_BASE)) {
        set_underglow_col(base_col);
    }
    else if (layer_state_is(_WINMODE)) {
        set_underglow_col(win_col);
    }
}

void caps_light_set(void) {
    if ((caps_flag == 1) & (!is_leader)){
      //Catch leader during caps on edgecase
      //Caps case last to make sure it overrides
      //Also check for leader since they share LEDs
        set_indicators(caps_col);
    }
    else if ((caps_flag == 0) & (!is_leader)){
        set_indicators(off_col);
        base_or_winmode_col();
    }
}


// Startup
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
    base_or_winmode_col();
    layer_move(_BASE);
}

// LED Update loop
bool led_update_user(led_t led_state) {
    if (led_state.caps_lock){
        caps_flag = 1;
        caps_light_set();
    }
    else {
        caps_flag = 0;
        caps_light_set();
        base_or_winmode_col();
    }
return true;
}

// RGB Matrix update loop
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_leader) {
        set_indicators(lead_col);
        }

    if (host_keyboard_led_state().caps_lock|is_leader) {
        caps_light_set();
    }

    switch(get_highest_layer(layer_state|default_layer_state)) {
    case _BASE:
    case _WINMODE:
    case _NAV:
    case _SYM:
    case _FUNC:
    case _FPAD:
    case _FPADPLUS:
    case _FPADPLUSRIGHT:
        //base_or_winmode_col();
        //caps_light_set();
        //break;
    default:
        base_or_winmode_col();
        caps_light_set();
        break;
    }
    return false;
}

// Layer state behaviour
layer_state_t layer_state_set_user(layer_state_t state) {
    //switch (get_highest_layer(state)) {
    //case _D2:
    //    set_underglow_col(game_col);
    //    break;
    //case _PS1:
    //    set_underglow_col(ps_col);
    //    break;
    //case _PS2:
    //    set_underglow_col(ps_col);
    //    break;
    //default:
    //    base_or_winmode_col();
    //    caps_light_set();
    //    break;
    //}
  return update_tri_layer_state(state, _NAV, _SYM, _FUNC);
  }


// Custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef USE_BABBLEPASTE
    if (keycode > BABBLE_START && keycode < BABBLE_END_RANGE) {
        if (record->event.pressed) {
            babblePaste(keycode, 1);
        } else {
            babblePaste(keycode, 0);
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
            return false;
        break;
      }
    return true;
}

// Leader key
void leader_start_user(void) {
    is_leader = true;
    rgb_matrix_set_color(indicator_leds[0], RGB_TEAL);
    rgb_matrix_set_color(indicator_leds[1], RGB_TEAL);
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_LSFT)) {
        tap_code(KC_CAPS);
    }
    else if (leader_sequence_one_key(KC_Q))
    {
        SEND_STRING("");
    }
    else if (leader_sequence_two_keys(KC_D, KC_F))
    {
        SEND_STRING("");
    }
    else if (leader_sequence_two_keys(KC_C, KC_G))
    {
        SEND_STRING("");
    }
    else if (leader_sequence_three_keys(KC_G, KC_U, KC_Y))
    {
        SEND_STRING("");
    }
    else if (leader_sequence_three_keys(KC_S, KC_A, KC_T))
    {
        SEND_STRING("");
    }
    is_leader = false;
}

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(
      // Colemak DHm - 0
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,  HOME_B,                       HOME_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,  HOME_G,                       HOME_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_D,  HOME_V,                       HOME_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,Quickbar,   QuickbarR,  KC_SPC,  Sym
                                      //`--------------------------'  `--------------------------'

  ),

  [_WINMODE] = LAYOUT_split_3x6_3(
        // Windows mode overlay - 1
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, wHOME_B,                      wHOME_J, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, wHOME_G,                      wHOME_M, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, wHOME_V,                      wHOME_K, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______, _______,QuickbarW,       _______, _______,  _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_FPAD] = LAYOUT_split_3x6_3(
      // Fastpad on cd combo - 2
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      S(KC_8),    KC_1,    KC_2,    KC_3,S(KC_EQL), KC_DOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_EQL,    KC_4,    KC_5,    KC_6,KC_COMM,S(KC_SCLN),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,KC_SPACE,   KC_SPACE,    KC_0,   Sym
                                      //`--------------------------'  `--------------------------'
  ),

  [_FPADPLUS] = LAYOUT_split_3x6_3(
      // Fastpad+ - 3
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,KC_F12,C(KC_LEFT), KC_UP,C(KC_RIGHT),MS_WHLD,                    KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DblClik, KC_LEFT,KC_DOWN, KC_RIGHT, MS_WHLU,                    S(KC_8),    KC_1,    KC_2,    KC_3,S(KC_EQL), KC_DOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MS_BTN1, B_UNDO,LCS(KC_TAB),B_COPY,C(KC_TAB),B_PASTE,                      KC_EQL,    KC_4,    KC_5,    KC_6,KC_COMM,S(KC_SCLN),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,Quickbar,   KC_SPACE,    KC_0,   Sym
                                      //`--------------------------'  `--------------------------'
  ),

  [_FPADPLUSw] = LAYOUT_split_3x6_3(
        // Fastpad+ windows specific stuff
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,KC_F12,C(KC_LEFT), KC_UP,C(KC_RIGHT),MS_WHLU,                    KC_SLSH,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DblClik, KC_LEFT,KC_DOWN, KC_RIGHT, MS_WHLD,                    S(KC_8),    KC_1,    KC_2,    KC_3,S(KC_EQL), KC_DOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MS_BTN1, B_UNDO,LCS(KC_TAB),B_COPY,C(KC_TAB),B_PASTE,                      KC_EQL,    KC_4,    KC_5,    KC_6,KC_COMM,S(KC_SCLN),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,Quickbar,   KC_SPACE,    KC_0,   Sym
                                      //`--------------------------'  `--------------------------'
  ),

    [_FPADPLUSRIGHT] = LAYOUT_split_3x6_3(
      // Fastpad+ on the right hotkey - 4
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,  KC_F12,C(KC_LEFT), KC_UP,C(KC_RIGHT),A(KC_UP),                  _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DblClik, KC_LEFT,KC_DOWN, KC_RIGHT,A(KC_DOWN),                  S(KC_SCLN),S(KC_9),KC_LBRC,S(KC_LBRC), _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MS_BTN1, B_UNDO,LCS(KC_TAB),B_COPY,C(KC_TAB),B_PASTE,                    KC_SCLN,  S(KC_0), KC_RBRC, S(KC_RBRC), _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,Quickbar,   QuickbarR, _______,   Sym
                                      //`--------------------------'  `--------------------------'
  ),


  [_NAV] = LAYOUT_split_3x6_3(
      // Navigation - 5
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,KC_F12,C(KC_LEFT),KC_HOME,C(KC_RGHT),A(KC_UP),                     _______, KC_HOME,   KC_UP,  KC_END,  B_SCAP, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LSFT, KC_LCTL,KC_LALT,KC_LGUI,A(KC_DOWN),                      B_FIND, KC_LEFT, KC_DOWN, KC_RGHT, KC_BRIU,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     MS_BTN1,A(KC_TAB),LCS(KC_TAB),KC_END,C(KC_TAB),KC_MPLY,                   B_RUNAPP, KC_PGUP,C(KC_ENT),KC_PGDN, KC_BRID, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,  KC_ENT,     KC_ENT,KC_SPACE,   Sym
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYM] = LAYOUT_split_3x6_3(
        // Symbols - 6
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, S(KC_1),S(KC_LBRC),KC_LBRC,S(KC_9),KC_TILD,                      S(KC_6),S(KC_0),KC_RBRC, S(KC_RBRC),KC_GRAVE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_AT, S(KC_8),  KC_EQL, S(KC_9), S(KC_4),                      KC_NUHS, KC_RGUI, KC_LALT, KC_RCTL, KC_RSFT, KC_DQUO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     A(KC_3),S(KC_7),S(KC_BSLS),S(KC_EQL),S(KC_0),S(KC_5),                      S(KC_3),KC_NUBS,S(KC_NUBS),S(KC_SCLN),KC_NUBS,KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Nav, KC_LSFT,  KC_ENT,     KC_ENT,KC_SPACE,   Sym
                                      //`--------------------------'  `--------------------------'
  ),

    [_FUNC] = LAYOUT_split_3x6_3(
        // Function and modes - 7
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    XXXXXXX,XXXXXXX,MEH(KC_LEFT),XXXXXXX,MEH(KC_RIGHT),QK_BOOT,                  QK_BOOT,   KC_F7,   KC_F8,   KC_F9,  KC_F12, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,  XXXXXXX,                 LCS(KC_EQL),   KC_F1,   KC_F2,   KC_F3,  KC_F11, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       TO_WIN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   C(KC_MINS),   KC_F4,   KC_F5,   KC_F6,  KC_F10,  TO_MAC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              Num, KC_LSFT,  KC_ENT,     KC_ENT,KC_SPACE,   Num
                                      //`--------------------------'  `--------------------------'
  )
};
