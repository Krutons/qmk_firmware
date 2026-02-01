#pragma once
#include "quantum.h"

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
    TO_WIN
}

enum layer_names {
    _BASE = 0,
    _WINMODE,
    _FPADPLUS,
    _NAV,
    _SYM,
    _FUNC,
    _D2
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
#define Home     TO(_BASE)
#define Nav      MO(_NAV)
#define Sym      MO(_SYM)
#define Num      MO(_FUNC)
#define Dest2    TO(_D2)
#define Quickbar MO(_FPADPLUS)

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


static uint16_t caps_flag; // capslock flag for LED indicator

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

     /* Base - Colemak 0
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Esc |   Q  |   W  |   F  |   P  |   B  |         |   J  |   L  |   U  |   Y  |  ;   | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   A  |   R  |   S  |   T  |   G  |         |   M  |   N  |   E  |   I  |  O   |  '   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |CMD/( |   Z  |   X  |   C  |   D  |   V  |         |   K  |   H  |   ,  |   .  |  /   |Alt/) |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift| Quickbar| Space| Sym  |
    *                             +-------------/         \-------------+
    */

  [_BASE] = LAYOUT_reviung41(
    KC_ESC,  KC_Q, KC_W,   KC_F,   KC_P,   HOME_B,        HOME_J,  KC_L,  KC_U,    KC_Y,   KC_SCLN, KC_BSPC,
    KC_BSPC,   KC_A, KC_R, KC_S,   KC_T,   HOME_G,        HOME_M,  KC_N,  KC_E,  KC_I, KC_O,    KC_QUOT,
    KC_LSPO, KC_Z, KC_X,   KC_C,   KC_D,   HOME_V,        HOME_K,  KC_H,  KC_COMM, KC_DOT, KC_SLSH, KC_RAPC,
                            Nav,   KC_LSFT,       Quickbar,    KC_SPACE,    Sym
  ),

     /* Alt - Handsdown Neu 1
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Esc |   W  |   F  |   M  |   P  |   V  |         |   /  |   .  |   Q  |   "  |  '   |  Z   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   R  |   S  |   N  |   T  |   B  |         |   ,  |   A  |   E  |   I  |  H   |  J   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |Lshift|   X  |   C  |   L  |   D  |   G  |         |   -  |   U  |   O  |   Y  |  K   |Rshift|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift| Quickbar| Space| Sym  |
    *                             +-------------/         \-------------+
    */

//  [_HDN] = LAYOUT_reviung41(
//    KC_ESC,   KC_W,  KC_F,  KC_M,   KC_P,   KC_V,        KC_SLASH,  KC_DOT,  KC_Q,  S(KC_QUOT),  KC_QUOT, KC_Z,
//    KC_BSPC,  KC_R,  KC_S,  KC_N,   KC_T,   KC_B,        KC_COMM,   KC_A,    KC_E,  KC_I,        KC_H,    KC_J,
//    KC_LSPO,  KC_X,  KC_C,  KC_L,   KC_D,   KC_G,        KC_MINS,   KC_U,    KC_O,  KC_Y,        KC_K,    KC_RSPC,
//                            Nav,   KC_LSFT,       Quickbar,    KC_SPACE,    Sym
//  ),

     /* Windows mode overlay - 2
    * ,-----------------------------------------+         +-----------------------------------------.
    * |      |      |      |      |      |      |         |      |      |      |      |      |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      |      |      |      |      |      |         |      |      |      |      |      |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |Ctrl/(|      |      |      |      |      |         |      |      |      |      |      |Alt/ )|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |      |      |         |      |      |
    *                             +-------------/         \-------------+
    */

  [_WINMODE] = LAYOUT_reviung41(
    _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
    KC_LCPO, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
                                 _______,   _______,   _______,    _______,    _______
  ),

       /* Fastpad+ - 3
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Esc |  F12 |SpaceL|  Up  |SpaceR| AltUp|         |   /  |   7  |   8  |   9  |  -   | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |      | Left | Down |Right | AltDn|         |   *  |   1  |   2  |   3  |  +   |  .   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      | Undo | TabL | Copy | TabR |Paste |         |   =  |   4  |   5  |   6  |  .   |  :   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift| Quickbar|   0  | Sym  |
    *                             +-------------/         \-------------+
    */

  [_FPADPLUS] = LAYOUT_reviung41(
    KC_ESC,   KC_F12, C(KC_LEFT),   KC_UP,   C(KC_RIGHT), A(KC_UP),       KC_SLSH, KC_7, KC_8, KC_9, KC_MINS,   KC_BSPC,
    KC_BSPC, XXXXXXX, KC_LEFT,      KC_DOWN, KC_RIGHT,    A(KC_DOWN),     S(KC_8), KC_1, KC_2, KC_3, S(KC_EQL), KC_DOT,
    XXXXXXX, B_UNDO,  S(C(KC_TAB)), B_COPY,  C(KC_TAB),   B_PASTE,        KC_EQL,  KC_4, KC_5, KC_6, KC_DOT,    S(KC_SCLN),
                                                Nav,   KC_LSFT,   Quickbar,    KC_0,    Sym
  ),


       /* Nav - 4
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Tab |  F12 |SpaceL| Home |SpaceR| AltUp|         |Reset | Home |  Up  |  End |ScrnSh| Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp | Shift| Ctrl | Alt  | Cmd  | AltDn|         | Find | Left | Down | Right| BrUp |  Del |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      |AltTab| TabL | End  | TabR | Play |         |Sptlgt| PgUp | NLine| PgDn | BrDn | Enter|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Enter  | Space| Sym  |
    *                             +-------------/         \-------------+
    */
  [_NAV] = LAYOUT_reviung41(
    KC_TAB,  KC_F12,  C(KC_LEFT),   KC_HOME, C(KC_RIGHT), A(KC_UP),      RESET,    KC_HOME, KC_UP,   KC_END,   B_SCAP,  KC_BSPC,
    KC_BSPC, KC_LSFT, KC_LCTL,      KC_LALT, KC_LGUI,     A(KC_DOWN),    B_FIND,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_BRIU, KC_DEL,
    XXXXXXX, A(KC_TAB), S(C(KC_TAB)), KC_END,  C(KC_TAB),   KC_MPLY,       B_RUNAPP, KC_PGUP, C(KC_ENT), KC_PGDN,  KC_BRID, KC_ENT,
                                                  Nav,   KC_LSFT,   KC_ENT,    KC_SPACE,    Sym
  ),

       /* Sym - 5
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Tab |   !  |   [  |   {  |   (  |   ~  |         |   ^  |   )  |   }  |   ]  |  `   |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   @  |   *  |   =  |   -  |   $  |         | nUS# |  Cmd |  Alt | Ctrl | Shift|   "  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Mac# |   &  |   |  |   +  |   _  |   %  |         |   £  | nUS\ |   ;  |   :  |  ?   |   \  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Enter  | Space| Sym  |
    *                             +-------------/         \-------------+
    */

  [_SYM] = LAYOUT_reviung41(
    KC_TAB,  S(KC_1), KC_LBRC,    S(KC_LBRC), S(KC_9),    KC_TILD,      S(KC_6), S(KC_0), S(KC_RBRC), KC_RBRC,    KC_GRAVE,   XXXXXXX,
    KC_BSPC, KC_AT,   S(KC_8),    KC_EQL,     KC_MINS,    S(KC_4),      KC_NUHS, OSM(MOD_RGUI), OSM(MOD_RALT), OSM(MOD_RCTL), OSM(MOD_RSFT),    KC_DQUO,
    A(KC_3), S(KC_7), S(KC_BSLS), S(KC_EQL),  S(KC_MINS), S(KC_5),      S(KC_3), KC_NUBS, KC_SCLN,    S(KC_SCLN), S(KC_SLSH), KC_BSLS,
                                                Nav,   KC_LSFT,   KC_ENT,    KC_SPACE,    Sym
  ),

       /* Functions - 6
    * ,-----------------------------------------+         +-----------------------------------------.
    * |      |      |      |      |      |      |         |      |  F7  |  F8  |  F9  |  F12 |Desti2|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      | Shift| Ctrl | Alt  | Cmd  |      |         |      |  F1  |  F2  |  F3  |  F11 |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |To Win|     |      |      |      |      |         |      |  F4  |  F5  |  F6  |  F10  |To Mac|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Num | Shift|  Enter  | Space|  Num |
    *                             +-------------/         \-------------+
    */

  [_FUNC] = LAYOUT_reviung41(
    XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,         XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12, Dest2,
    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,       XXXXXXX, KC_F1,   KC_F2,   KC_F3,  KC_F11, XXXXXXX,
    TO_WIN,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_F4,   KC_F5,   KC_F6,  KC_F10, TO_MAC,
                                        Num,   KC_LSFT,  KC_ENT,  KC_SPACE,   Num
  ),



     /* Destiny 2 - 7
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Esc |   1  |   2  |   3  |   4  |   5  |         |   J  |   L  |  Up  |   Y  |  ;   | Home |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |  Tab |   Q  |   W  |   E  |   R  |   T  |         |   H  | Left | Down |Right |  O   |  '   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |Lshift|   A  |   S  |   D  |   F  |   G  |         |   I  |   M  |   ,  |   .  |  /   |Rshift|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             | Ctrl | Space|    C    |  F1  | Home |
    *                             +-------------/         \-------------+
    */

  [_D2] = LAYOUT_reviung41(
    KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5,     KC_J,  KC_L,    KC_UP,    KC_Y,     KC_SCLN, Home,
    KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,     KC_H,  KC_LEFT, KC_DOWN,  KC_RIGHT, KC_O,    KC_QUOT,
    KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,     KC_I,  KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, KC_RSPC,
                  KC_LCTL,   KC_SPACE,   KC_C,    KC_F1,    Home
  ),

};
