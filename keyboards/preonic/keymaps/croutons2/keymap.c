/* Copyright 2015-2021 Jack Humbert
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
#include muse.h
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
    _QWERTY,
    _FPAD,
    _FPADPLUS,
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
#define FPad     MO(_FPAD)
#define Quickbar MO(_FPADPLUS)

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

float caps_song[][2] = SONG(TERMINAL_SOUND);
float caps_on[][2] = SONG(NUM_LOCK_ON_SOUND);
float caps_off[][2] = SONG(NUM_LOCK_OFF_SOUND);
float lead_song[][2] = SONG(AUDIO_ON_SOUND);
static uint16_t caps_flag; // capslock flag for LED indicator

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* ColemakDHm - 1
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |  GUI |  Nav | Shift|   Quickbar  | Space| Sym  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_preonic_grid(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,  HOME_B,  HOME_J,  KC_L,     KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,  HOME_G,  HOME_M,  KC_N,     KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_D,  HOME_V,  HOME_K,  KC_H,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
  KC_LCTL, KC_LALT, KC_LGUI, Nav,     KC_LSFT,    Quickbar,    KC_SPACE, Sym,     KC_LGUI, KC_LALT, KC_LCTL
),
[_WINMODE] = LAYOUT_preonic_grid(
  _______, _______, _______,_______,_______,_______,   _______, _______, _______,_______,_______,_______,
  _______, _______, _______,_______,_______, wHOME_B,  wHOME_J, _______, _______,_______,_______,_______,
  _______, _______, _______,_______,_______, wHOME_G,  wHOME_M, _______, _______,_______,_______,_______,
  _______, _______, _______,_______,_______, wHOME_V,  wHOME_K, _______, _______,_______,_______,_______,
  _______, _______, _______,_______,_______,      _______,     _______,  _______, _______, _______, _______
),

/* Fastpad - 2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   7  |   8  |   9  |   -  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |   *  |   1  |   2  |   3  |   +  |  .   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |   =  |   4  |   5  |   6  |   ,  |  :   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |  GUI |  Nav | Shift|    Space    |   0  | Sym  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FPAD] = LAYOUT_preonic_grid(
  _______, _______, _______,_______,_______,_______,   KC_6,    KC_7,   KC_8, KC_9, KC_0,      KC_BSPC,
  _______, _______, _______,_______,_______,_______,   KC_SLSH, KC_7,   KC_8, KC_9, KC_MINS,   KC_DEL,
  _______, _______, _______,_______,_______,_______,   S(KC_8), KC_1,   KC_2, KC_3, S(KC_EQL), KC_DOT,
  _______, _______, _______,_______,_______,_______,   KC_EQL,  KC_4,   KC_5, KC_6, KC_COMM,   S(KC_SCLN),
  KC_LCTL, KC_LALT, KC_LGUI,    Nav,KC_LSFT,      KC_SPACE,     KC_0,   Sym, _______, _______, _______
),

/* Fastpad+ - 3
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  F12 |SpaceL|   Up |SpaceR| AltUp|   /  |   7  |   8  |   9  |   -  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |      | Left | Down | Right| AltDn|   *  |   1  |   2  |   3  |   +  |  .   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Lshift| Undo | TabL | Copy | TabR | Paste|   =  |   4  |   5  |   6  |   ,  |  :   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |  GUI |  Nav | Shift|   Quickbar  |   0  | Sym  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FPADPLUS] = LAYOUT_preonic_grid(
  KC_ESC,  KC_1,    KC_2,         KC_3,    KC_4,        KC_5,        KC_6,    KC_7, KC_8, KC_9,    KC_0,      KC_BSPC,
  KC_TAB,  KC_F12,  C(KC_LEFT),   KC_UP,   C(KC_RIGHT), A(KC_UP),    KC_SLSH, KC_7, KC_8, KC_9,    KC_MINS,   KC_DEL,
  KC_BSPC, XXXXXXX, KC_LEFT,      KC_DOWN, KC_RIGHT,    A(KC_DOWN),  S(KC_8), KC_1, KC_2, KC_3,    S(KC_EQL), KC_DOT,
  XXXXXXX, B_UNDO,  S(C(KC_TAB)), B_COPY,  C(KC_TAB),   B_PASTE,     KC_EQL,  KC_4, KC_5, KC_6,    KC_DOT,    S(KC_SCLN),
  KC_LCTL, KC_LALT, KC_LGUI,      Nav,     KC_LSFT,          Quickbar,        KC_0, Sym,  _______, _______,   _______
),

/* Navigation - 4
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  F12 |SpaceL| Home |SpaceR| AltUp|      | Home |  Up  |  End |ScrnSh| Del  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Bksp | Shift| Ctrl |  Alt |  Cmd | AltDn| Caps | Left | Down | Right| Bri+ |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      | TabL |  End | TabR | Play |Sptlgt| PgUp | NLine| PgDn | Bri- |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |  GUI |  Nav | Shift|    Enter    | Space| Sym  | Up   | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_preonic_grid(
  KC_ESC,  KC_1,    KC_2,         KC_3,    KC_4,        KC_5,       KC_6,     KC_7,     KC_8,      KC_9,     KC_0,    KC_BSPC,
  KC_TAB,  KC_F12,  C(KC_LEFT),   KC_HOME, C(KC_RIGHT), A(KC_UP),   _______,  KC_HOME,  KC_UP,     KC_END,   B_SCAP,  KC_DEL,
  KC_BSPC, KC_LSFT, KC_LCTL,      KC_LALT, KC_LGUI,     A(KC_DOWN), KC_CAPS,  KC_LEFT,  KC_DOWN,   KC_RIGHT, KC_BRIU, KC_DEL,
  XXXXXXX, XXXXXXX, S(C(KC_TAB)), KC_END,  C(KC_TAB),   KC_MPLY,    B_RUNAPP, KC_PGUP,  C(KC_ENT), KC_PGDN,  KC_BRID, KC_ENT,
  KC_LCTL, KC_LALT, KC_LGUI,      Nav,     KC_LSFT,           KC_ENT,         KC_SPACE, Sym,       _______, _______,   _______
),

/* Symbols - 5
 * ,-----------------------------------------------------------------------------------.
 * |  `   |  !   |  @   |   £  |  $   |  %   |  ^   |  &   |  *   |  (   |  )   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  !   |   [  |   {  |  (   |  ~   |  ^   |   )  |  }   |  ]   |  `   | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   @  |   *  |   =  |   -  |  $   | nUS# |  Cmd |  Alt | Ctrl | Shift|   "  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Mac# |   &  |   |  |   +  |   _  |  {   |   }  |   /  |   |  |  !   |   ?  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |  GUI |  NAV |Shift |    Enter    | Space| Sym  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYM] = LAYOUT_preonic_grid(
  KC_GRV,  S(KC_1), S(KC_2),    S(KC_3),    S(KC_4),    S(KC_5), S(KC_6),     S(KC_7),  S(KC_8),    S(KC_9), S(KC_0),    LALT(KC_BSPC),
  KC_TAB,  S(KC_1), KC_LBRC,    S(KC_LBRC), S(KC_9),    KC_TILD, S(KC_6),     S(KC_0),  S(KC_RBRC), KC_RBRC, KC_GRAVE,   KC_DEL,
  KC_BSPC, KC_AT,   S(KC_8),    KC_EQL,     KC_MINS,    S(KC_4), KC_NUHS,     KC_RGUI,  KC_RALT,    KC_RCTL, KC_RSFT,    KC_DQUO,
  A(KC_3), S(KC_7), S(KC_BSLS), S(KC_EQL),  S(KC_MINS), S(KC_5), S(KC_RBRC),  KC_SLSH,  S(KC_BSLS), S(KC_1), S(KC_SLSH), KC_ENT,
  KC_LCTL, KC_LALT, KC_LGUI,    Nav,        KC_LSFT,         KC_ENT,          KC_SPACE, Sym,        _______, _______,   _______
),

/* Adjust - 6
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|RGBy/n|      |      |      |  F7  |  F8  |  F9  |  F12 |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|      |      |  F1  |  F2  |  F3  |  F11 |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|      |      |  F4  |  F5  |  F6  |  F10 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |BabWin|      |      |  Num | Shift|    Enter    | Space|  Num |      |      |BabMac|
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_preonic_grid(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_BSPC,
  _______, RESET,   DEBUG,   RGB_TOG, _______, _______, _______, KC_F7,    KC_F8,   KC_F9,   KC_F12,  KC_DEL,
  _______, _______, _______, AU_ON,   AU_OFF,  _______, _______, KC_F1,    KC_F2,   KC_F3,   KC_F11,  _______,
  _______, _______, _______, _______, _______, _______, _______, KC_F4,    KC_F5,   KC_F6,   KC_F10,  _______,
  B_WIN,   _______, _______, Num,     KC_LSFT,      KC_ENT,      KC_SPACE, Num,     _______, _______, B_MAC
),

/* Gaming/QWERTY - 7
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |  Up  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   S  |   D  |   F  |   G  |   H  | Left | Down | Rght |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Lshift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Rshift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |  GUI |   V  | Space|    Space    | Space| Home |  GUI |  Alt | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_UP,    KC_O,     KC_P, KC_DEL,
  KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H, KC_LEFT, KC_DOWN, KC_RGHT,    KC_SCLN,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LALT, KC_LGUI, KC_V,     KC_SPACE,    KC_SPACE,     KC_SPACE, Home,  KC_LGUI, KC_LALT, KC_RCTL
)


};

const uint16_t PROGMEM wf_combo[] =        {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM xc_combo[] =        {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM commadot_combo[] =  {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM gm_combo[] =        {HOME_G, HOME_M, COMBO_END};
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
  [_FP] =        COMBO(fp_combo, S(KC_1)), // !
  [_HCOMMA] =    COMBO(hcomma_combo, S(KC_SLASH)), //?
  [_UY] =        COMBO(uy_combo, S(KC_QUOT)), // "

  //Layer combos
  [_CD] =        COMBO(cd_combo, FPad), // switch to right hand numpad
  [_DOTSLASH] =  COMBO(dotslash_combo, KC_LEAD), // Leader key alternative

  //Vertical command combos
  [_AZ] =        COMBO(az_combo, B_UNDO), // undo
  [_RX] =        COMBO(rx_combo, B_SAVE), // save
  [_SC] =        COMBO(sc_combo, B_COPY), // copy
  [_TD] =        COMBO(td_combo, B_CUT), // cut
  [_GV] =        COMBO(gv_combo, B_PASTE),  // paste
  [_wGV]=        COMBO(gv_win_combo, C(KC_V)), // paste for windows
  [_ZX] =        COMBO(zx_combo, B_DLW), // delete word

  //String combos
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
    switch(keycode) {
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
        case KC_CAPS:
            if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              tap_code(KC_CAPS);
              if (caps_flag==1){
              PLAY_SONG(caps_on);
              }
              else {
                PLAY_SONG(caps_off);
              }
        #endif //AUDIO_ENABLE
        }
          return false;
          break;
      }
    return true;
};

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
}

#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(12,233,255); // Warm white 12,233,255
}

void leader_start(void) {
  rgblight_sethsv_noeeprom(127,255,255);
  #ifdef AUDIO_ENABLE
    PLAY_SONG(lead_song);
#endif
}

void leader_end(void) {
  rgblight_sethsv_noeeprom(12,233,255);
  if (caps_flag == 1){
      //Catch leader during caps on edgecase
      //Caps case last to make sure it overrides
      rgblight_sethsv_noeeprom(0, 255, 255);
  }
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock){
        // if caps lock on, do this
        rgblight_sethsv_noeeprom(0, 255, 255);
        caps_flag = 1;
    }
    else{
        caps_flag = 0;
        rgblight_sethsv_noeeprom(12,233,255);
        }
return true;
}

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
        #ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case _BASE: //  for any other layers, or the default layer
        rgblight_sethsv_noeeprom(12,233,255);
        if (caps_flag == 1){
        // make sure caps light works between layer changes
        rgblight_sethsv_noeeprom(0, 255, 255);
        }
        break;
    }
    #endif
  return update_tri_layer_state(state, _SYM, _NAV, _FUNC);
}
