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
#include <stdio.h>
#include "features/capsword.h"

enum layer_names {
    _BASE,
    _NAV,
    _SYM,
    _NUM
};

enum combos {
  _WF,
  _XC,
  _COMMADOT,
  _GM
};

enum keycodes {
  OSM_SFT,
  OSM_CTL,
  OSM_ALT,
  OSM_GUI
};

#define Home MO(_BASE)
#define Nav  MO(_NAV)
#define Sym  MO(_SYM)
#define Num  MO(_NUM)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

     /* Base - Colemak 0
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Esc |   Q  |   W  |   F  |   P  |   B  |         |   J  |   L  |   U  |   Y  |  ;   | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   A  |   R  |   S  |   T  |   G  |         |   M  |   N  |   E  |   I  |  O   |  '   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |Lshift|   Z  |   X  |   C  |   D  |   V  |         |   K  |   H  |   ,  |   .  |  /   |Rshift|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|   IDK   | Space| Sym  |
    *                             +-------------/         \-------------+
    */

  [_BASE] = LAYOUT_reviung41(
    KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_B,     KC_J,  KC_L,  KC_U,     KC_Y,     KC_SCLN, KC_BSPC,
    KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_G,     KC_M,  KC_N,  KC_E,     KC_I,     KC_O,    KC_QUOT,
    KC_LSPO, KC_Z, KC_X, KC_C, KC_D, KC_V,     KC_K,  KC_H,  KC_COMM,  KC_DOT,   KC_SLSH, KC_RSPC,
                        Nav,   KC_LSFT,   Home,    KC_SPACE,    Sym
  ),

       /* Nav - 1
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Tab |      |SpaceL| Home |SpaceR| AltUp|         |Reset | Home |  Up  |  End |      | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp | Shift| Ctrl | Alt  | Cmd  |AltDow|         | Caps | Left | Down | Right|      |  Del |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      | Undo | TabL | End  | TabR | Play |         |Sptlgt| PgUp |      | PgDn |      | Enter|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Enter  | Space| Sym  |
    *                             +-------------/         \-------------+
    */
  [_NAV] = LAYOUT_reviung41(
    KC_TAB,  XXXXXXX,       C(KC_LEFT),    KC_HOME,       C(KC_RIGHT),   A(KC_UP),                 RESET,       KC_HOME, KC_UP,   KC_END,   XXXXXXX, KC_BSPC,
    KC_BSPC, OSM_SFT, OSM_CTL, OSM_ALT, OSM_GUI, A(KC_DOWN),               KC_LCAP,     KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, KC_DEL,
    XXXXXXX, G(KC_Z),       S(C(KC_TAB)),  KC_END,        C(KC_TAB),     KC_MEDIA_PLAY_PAUSE,      G(KC_SPACE), KC_PGUP, XXXXXXX, KC_PGDN,  XXXXXXX, KC_ENT,
                                                                           Nav,   KC_LSFT,   KC_ENT,    KC_SPACE,    Sym
  ),

       /* Sym - 2
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Tab |   !  |   [  |   {  |   (  |   ~  |         |   ^  |   )  |   }  |   ]  |  `   |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   @  |   *  |   =  |   -  |   $  |         |   #  |  Cmd |  Alt | Ctrl | Shift|   "  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Mac# |   &  |   |  |   +  |   _  |   %  |         |   £  |   \  |   ;  |   :  |  ?   |   \  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Enter  | Space| Sym  |
    *                             +-------------/         \-------------+
    */

  [_SYM] = LAYOUT_reviung41(
    KC_TAB, S(KC_1), KC_LBRC,    S(KC_LBRC), S(KC_9),    KC_TILD,    S(KC_6), S(KC_0),       S(KC_RBRC),    KC_RBRC,       KC_GRAVE,  XXXXXXX,
    KC_BSPC, KC_AT,   S(KC_8),    KC_EQL,     KC_MINS, S(KC_4),       KC_NUHS, OSM_GUI, OSM_ALT, OSM_CTL, OSM_SFT, KC_DQUO,
    A(KC_3), S(KC_7), S(KC_BSLS), S(KC_EQL),      S(KC_MINS),    S(KC_5),       S(KC_3), KC_NUBS,       KC_SCLN,       S(KC_SCLN),       S(KC_SLSH), KC_BSLS,
                                                    Nav,   KC_LSFT,   KC_ENT,    KC_SPACE,    Sym
  ),

       /* Num - 3
    * ,-----------------------------------------+         +-----------------------------------------.
    * |      |   1  |   2  |   3  |   4  |  5   |         |   6  |   7  |   8  |   9  |   0  | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      | Shift| Ctrl | Alt  | Cmd  |  F11 |         |  F12 |  Cmd |  Alt | Ctrl | Shift|  .   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      |  F1  |  F2  |  F3  |  F4  |  F5  |         |  F6  |  F7  |  F8  |  F9  |  F10 |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Enter  | Space| Sym  |
    *                             +-------------/         \-------------+
    */

  [_NUM] = LAYOUT_reviung41(
    XXXXXXX,   KC_1, KC_2,  KC_3,  KC_4,   KC_5,            KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_BSPC,
    XXXXXXX,   OSM_SFT, OSM_CTL, OSM_ALT, OSM_GUI,   KC_F11,            KC_F12,  OSM_GUI, OSM_ALT, OSM_CTL, OSM_SFT,  KC_DOT,
    XXXXXXX,   KC_F1, KC_F2,  KC_F3,  KC_F4,   KC_F5,            KC_F6,    KC_F7,  KC_F8,  KC_F9,  KC_F10,  XXXXXXX,
                                            Nav,   KC_LSFT,  KC_ENT,  KC_SPACE,  Sym
  ),
};

const uint16_t PROGMEM wf_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM gm_combo[] = {KC_G, KC_M, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [_WF] = COMBO(wf_combo, KC_MINS),
  [_XC] = COMBO(xc_combo, S(KC_MINS)),
  [_COMMADOT] = COMBO(commadot_combo, OSM(MOD_LSFT)),
  [_GM] = COMBO(gm_combo, KC_CAPS),
};

// Oneshot mods are handled like this so they can be rolled from the layers properly.
// Without this, the oneshot keystroke must be finished before leaving the layer... gross.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case OSM_SFT:
        if (record->event.pressed) {
            add_oneshot_mods(MOD_BIT(KC_LSFT));
        }
        break;
    case OSM_ALT:
        if (record->event.pressed) {
            add_oneshot_mods(MOD_BIT(KC_LALT));
        }
        break;
    case OSM_CTL:
        if (record->event.pressed) {
            add_oneshot_mods(MOD_BIT(KC_LCTL));
        }
        break;
    case OSM_GUI:
        if (record->event.pressed) {
            add_oneshot_mods(MOD_BIT(KC_LGUI));
        }
        break;
    }
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NAV, _SYM, _NUM);
  }
