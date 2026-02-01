/* Copyright 2020 gtips
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "quantum.h"
#include <stdio.h>

#ifdef USE_BABBLEPASTE
#    include "babblePaste.h"
#endif

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
// #define Home     TO(_BASE)
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
#define LED_ALL         0, 11
#define LED_IND         10, 11 // Front-facing LED
#define LED_DOWN        0, 10 // Downlighting LED


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


     /* Fastpad - 2
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Esc |   Q  |   W  |   F  |   P  |   B  |         |   /  |   7  |   8  |   9  |  -   | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   A  |   R  |   S  |   T  |   G  |         |   *  |   1  |   2  |   3  |  +   |  .   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |Lshift|   Z  |   X  |   C  |   D  |   V  |         |   =  |   4  |   5  |   6  |  .   |  :   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Space  |   0  | Sym  |
    *                             +-------------/         \-------------+
    */

  [_FPAD] = LAYOUT_reviung41(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_SLSH, KC_7, KC_8, KC_9, KC_MINS,   KC_BSPC,
    KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     S(KC_8), KC_1, KC_2, KC_3, S(KC_EQL), KC_DOT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_EQL,  KC_4, KC_5, KC_6, KC_COMM,   S(KC_SCLN),
                            Nav,   KC_LSFT,   KC_SPACE,    KC_0,    Sym
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
    XXXXXXX, B_UNDO,  S(C(KC_TAB)), B_COPY,  C(KC_TAB),   B_PASTE,        KC_EQL,  KC_4, KC_5, KC_6, KC_COMM,    S(KC_SCLN),
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
    KC_TAB,  KC_F12,  C(KC_LEFT),   KC_HOME, C(KC_RIGHT), A(KC_UP),      QK_REBOOT,    KC_HOME, KC_UP,   KC_END,   B_SCAP,  KC_BSPC,
    KC_BSPC, KC_LSFT, KC_LCTL,      KC_LALT, KC_LGUI,     A(KC_DOWN),    B_FIND,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_BRIU, KC_DEL,
    XXXXXXX, A(KC_TAB), S(C(KC_TAB)), KC_END,  C(KC_TAB),   KC_MPLY,       B_RUNAPP, KC_PGUP, C(KC_ENT), KC_PGDN,  KC_BRID, XXXXXXX,
                                                  Nav,   KC_LSFT,   KC_ENT,    KC_SPACE,    Sym
  ),

       /* Sym - 5
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Tab |   !  |   [  |   {  |   (  |   ~  |         |   ^  |   )  |   }  |   ]  |  `   |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   @  |   *  |   =  |   -  |   $  |         | nUS# |  Cmd |  Alt | Ctrl | Shift|   "  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Mac# |   &  |   |  |   +  |   _  |   %  |         |   £  | nUS\ |   ~  |   :  |  ?   |   \  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Enter  | Space| Sym  |
    *                             +-------------/         \-------------+
    */

  [_SYM] = LAYOUT_reviung41(
    KC_TAB,  S(KC_1), KC_LBRC,    S(KC_LBRC), S(KC_9),    KC_TILD,      S(KC_6), S(KC_0), S(KC_RBRC), KC_RBRC,    KC_GRAVE,   XXXXXXX,
    KC_BSPC, KC_AT,   S(KC_8),    KC_EQL,     KC_MINS,    S(KC_4),      KC_NUHS, OSM(MOD_RGUI), OSM(MOD_RALT), OSM(MOD_RCTL), OSM(MOD_RSFT),    KC_DQUO,
    A(KC_3), S(KC_7), S(KC_BSLS), S(KC_EQL),  S(KC_MINS), S(KC_5),      S(KC_3), KC_NUBS, S(KC_NUBS),    S(KC_SCLN), S(KC_SLSH), KC_BSLS,
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
    Photosh,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,         XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12, Dest2,
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



         /* Photoshop layer 1 - 8
    * ,-----------------------------------------+         +-----------------------------------------.
    * |      |      |      |      |      |      |         | FlipH|  [   |   ]  |   V  |      |CMD(Z)|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      |      |      |      |      |      |         |ZoomIn|  R   |   B  |CMD(D)|   J  |   I  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Exit |      |      |      |      |      |         |ZoomOt|  `   |   L  | CMD  | Shift| Alt  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |      |      |         |Space |Layer2|
    *                             +-------------/         \-------------+
    */

  [_PS1] = LAYOUT_reviung41(
    Home,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       G(S(KC_DOT)), KC_LBRC, KC_RBRC, KC_V,    KC_BTN2, B_UNDO,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       G(S(KC_EQL)), KC_R,    KC_B,    G(KC_D), KC_J,    KC_I,
    Home,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       G(KC_MINS), KC_GRAVE,  KC_L,    KC_LGUI, KC_LSFT, KC_LALT,
                                    Home,   XXXXXXX,     Home,  KC_SPACE,   Ps2
  ),



         /* Photoshop layer 2 - 9
    * ,-----------------------------------------+         +-----------------------------------------.
    * |      |      |      |      |      |      |         |      |SpaceL|  Top |SpaceR|      | Redo |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      |      |      |      |      |      |         |Rightc| Left | Down | Right|DblClk|      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Exit |      |      |      |      |      |         |      | Enter| Save |BackSp|      |Scnsht|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |      |      |         |      |Layer2|
    *                             +-------------/         \-------------+
    */

  [_PS2] = LAYOUT_reviung41(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, C(KC_LEFT), KC_UP,   C(KC_RIGHT), XXXXXXX, G(S(KC_Z)),
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_LEFT,    KC_DOWN, KC_RIGHT,    DblClik, XXXXXXX,
    Home,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_ENT,     B_SAVE,  KC_BSPC,     XXXXXXX, B_SCAP,
                                    XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,   Ps2
  ),
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
  [_DOTSLASH] =  COMBO(dotslash_combo, KC_LEAD), // Leader key alternative

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
  [_JL] =        COMBO_ACTION(jl_combo), // ://3
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
                }
                else if (win_mode == false) {  // Move to mac mode
                    layer_move(_BASE);  // Toggle WINMODE off
                    set_babble_mode(BABL_MAC_MODE);
                    win_mode = false;
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
      rgblight_sethsv_range(CAPS_COL, LED_IND);
    }
    else if (caps_flag == 0){
        base_or_winmode_col();
    }
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(BASE_COL);
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
    else {
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
    //case _WINMODE:
    //    caps_light_set();
    //    rgblight_sethsv_noeeprom(WIN_COL);
    //    break;
    //case _BASE:
    //    caps_light_set();
    //    rgblight_sethsv_noeeprom(BASE_COL);
    //    break;
    default:
        base_or_winmode_col();
        caps_light_set();
        break;
    }
    #endif
  return update_tri_layer_state(state, _NAV, _SYM, _FUNC);
  }
