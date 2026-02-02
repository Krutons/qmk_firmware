// qmk compile -kb reviung/reviung41 -km croutons_no_babble
#include QMK_KEYBOARD_H
#include "users/secrets/secret.h"

#if defined(KEYMAP_SAFE_RANGE)
#    define USER_START KEYMAP_SAFE_RANGE
#else
#    define USER_START SAFE_RANGE
#endif

// clang-format off
enum keycodes {
    TO_MAC = SAFE_RANGE,
    TO_WIN,
    DblClik,
    Home,
    ZIN,
    ZOUT,
    UNDO,
    SAVE,
    COPY,
    CUT,
    PASTE,
    DLW,
    SCAP,
    RUNAPP,
    WHLU,
    WHLD
};

enum layer_names {
    _BASE = 0,
    _WINMODE,
    _FPAD,
    _FPADPLUS,
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
// clang-format on

// Layer macros
#define FPad MO(_FPAD)
#define Nav MO(_NAV)
#define Sym MO(_SYM)
#define Num MO(_FUNC)
#define Quickbar LT(_FPADPLUS, KC_TAB)

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
#define BASE_COL 12, 233, 255  // Warm white
#define WIN_COL 3, 220, 255    // Pink
#define PS_COL 155, 255, 255   // Blue
#define LEAD_COL 127, 255, 255 // Cyan
#define GAME_COL 190, 255, 255 // Purple
#define CAPS_COL 0, 255, 255   // Red

// LED addresses
#define LED_ALL 0, 11
#define LED_IND 10, 11 // Front-facing LED
#define LED_DOWN 0, 10 // Downlighting LED

// Flags
static bool win_mode = false; // flag to track windows mode across other layer moves

// Combo
const uint16_t PROGMEM wf_combo[]       = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM xc_combo[]       = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM commadot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM gm_combo[]       = {HOME_G, HOME_M, COMBO_END};
const uint16_t PROGMEM gm_win_combo[]   = {wHOME_G, wHOME_M, COMBO_END};
const uint16_t PROGMEM fp_combo[]       = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM cd_combo[]       = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM hcomma_combo[]   = {KC_H, KC_COMMA, COMBO_END};
const uint16_t PROGMEM az_combo[]       = {KC_A, KC_Z, COMBO_END};
const uint16_t PROGMEM rx_combo[]       = {KC_R, KC_X, COMBO_END};
const uint16_t PROGMEM sc_combo[]       = {KC_S, KC_C, COMBO_END};
const uint16_t PROGMEM td_combo[]       = {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM gv_combo[]       = {HOME_G, HOME_V, COMBO_END};
const uint16_t PROGMEM gv_win_combo[]   = {wHOME_G, wHOME_V, COMBO_END};
const uint16_t PROGMEM uy_combo[]       = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM rs_combo[]       = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM sf_combo[]       = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM aq_combo[]       = {KC_A, KC_Q, COMBO_END};
const uint16_t PROGMEM sd_combo[]       = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM zx_combo[]       = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM dotslash_combo[] = {KC_DOT, KC_SLSH, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [_WF]       = COMBO(wf_combo, KC_MINS),         // -
    [_XC]       = COMBO(xc_combo, S(KC_MINS)),      // _
    [_COMMADOT] = COMBO(commadot_combo, KC_TAB),    // Tab
    [_GM]       = COMBO(gm_combo, KC_CAPS),         // Caps
    [_wGM]      = COMBO(gm_win_combo, KC_CAPS),     // Caps in winmode
    [_FP]       = COMBO(fp_combo, S(KC_1)),         // !
    [_HCOMMA]   = COMBO(hcomma_combo, S(KC_SLASH)), //?
    [_UY]       = COMBO(uy_combo, S(KC_QUOT)),      // "
    [_RS]       = COMBO(rs_combo, KC_ENT),          // Enter

    // Layer combos
    [_CD]       = COMBO(cd_combo, FPad),          // switch to right hand numpad
    [_DOTSLASH] = COMBO(dotslash_combo, QK_LEAD), // Leader key alternative

    // Vertical command combos
    [_AZ]  = COMBO(az_combo, UNDO),      // undo
    [_RX]  = COMBO(rx_combo, SAVE),      // save
    [_SC]  = COMBO(sc_combo, COPY),      // copy
    [_TD]  = COMBO(td_combo, CUT),       // cut
    [_GV]  = COMBO(gv_combo, PASTE),     // paste
    [_wGV] = COMBO(gv_win_combo, PASTE), // paste for windows
    [_ZX]  = COMBO(zx_combo, DLW),       // delete word

    [_SD] = COMBO_ACTION(sd_combo), // d3
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case _SD:
            if (pressed) {
                SEND_STRING("d3");
            }
            break;
    }
}

// Startup
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(BASE_COL);
}

// LED Update loop
bool led_update_user(led_t led_state) {
    if (layer_state_is(_BASE)) {
        rgblight_sethsv_noeeprom(BASE_COL);
    } else if (layer_state_is(_WINMODE)) {
        rgblight_sethsv_noeeprom(WIN_COL);
    }
    if (host_keyboard_led_state().caps_lock == true) {
        rgblight_sethsv_range(CAPS_COL, LED_IND);
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE:
            win_mode = false;
            break;
        case _WINMODE:
            win_mode = true;
            break;
        case _NAV:
        case _SYM:
        case _FUNC:
        case _FPAD:
        case _FPADPLUS:
        default:
            break;
    }
    return update_tri_layer_state(state, _NAV, _SYM, _FUNC);
}

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TO_MAC:
            if (record->event.pressed) {
                layer_move(_BASE); // Toggle WINMODE off
            }
            return false;
        case TO_WIN:
            if (record->event.pressed) {
                layer_move(_WINMODE); // Toggle WINMODE on
            }
            return false;
        case DblClik:
            if (record->event.pressed) {
                tap_code16(MS_BTN1);
                tap_code16(MS_BTN1);
            }
            break;
        case ZIN: // Zoom in
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING(SS_LCTL("="));
                } else {
                    SEND_STRING(SS_LGUI("="));
                }
            }
            break;
        case ZOUT: // Zoom out
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING(SS_LCTL("-"));
                } else {
                    SEND_STRING(SS_LGUI("-"));
                }
            }
            break;
        case UNDO: // Undo
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING(SS_LCTL("z"));
                } else {
                    SEND_STRING(SS_LGUI("z"));
                }
            }
            break;
        case SAVE: // Save
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING(SS_LCTL("s"));
                } else {
                    SEND_STRING(SS_LGUI("s"));
                }
            }
            break;
        case COPY: // Copy
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING(SS_LCTL("c"));
                } else {
                    SEND_STRING(SS_LGUI("c"));
                }
            }
            break;
        case CUT: // Cut
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING(SS_LCTL("x"));
                } else {
                    SEND_STRING(SS_LGUI("x"));
                }
            }
            break;
        case PASTE: // Paste
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING(SS_LCTL("v"));
                } else {
                    SEND_STRING(SS_LGUI("v"));
                }
            }
            break;
        case DLW: // Delete previous word
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING("" SS_LCTL(SS_TAP(X_BSPC)));
                } else {
                    SEND_STRING("" SS_LGUI(SS_TAP(X_BSPC)));
                }
            }
            break;
        case SCAP: // Screencap
            if (record->event.pressed) {
                if (win_mode == true) {
                    register_code16(KC_LSFT);
                    SEND_STRING(SS_LGUI("s"));
                    unregister_code16(KC_LSFT);
                } else {
                    register_code16(KC_LSFT);
                    SEND_STRING(SS_LGUI("4"));
                    unregister_code16(KC_LSFT);
                }
            }
            break;
        case RUNAPP: // App launcher: spotlight etc
            if (record->event.pressed) {
                if (win_mode == true) {
                    SEND_STRING(SS_LALT(SS_TAP(X_SPC)));
                } else {
                    SEND_STRING(SS_LGUI(SS_TAP(X_SPC)));
                }
            }
            break;
        case WHLU:                        // Mouse wheel "up"
            if (record->tap.count == 0) { // Key is being held.
                if (record->event.pressed) {
                    if (win_mode == true) {
                        register_code16(MS_WHLU);
                    } else {
                        register_code16(MS_WHLD);
                    }
                } else {
                    if (win_mode == true) {
                        unregister_code16(MS_WHLU);
                    } else {
                        unregister_code16(MS_WHLD);
                    }
                }
                return false;
            }
            break;
        case WHLD:                        // Mouse wheel "down"
            if (record->tap.count == 0) { // Key is being held.
                if (record->event.pressed) {
                    if (win_mode == true) {
                        register_code16(MS_WHLD);
                    } else {
                        register_code16(MS_WHLU);
                    }
                } else {
                    if (win_mode == true) {
                        unregister_code16(MS_WHLD);
                    } else {
                        unregister_code16(MS_WHLU);
                    }
                }
                return false;
            }
            break;
        case Home:
            if (record->event.pressed) {
                if (win_mode == true) {         // Move to window mode
                    layer_move(_WINMODE);       // Toggle WINMODE on
                } else if (win_mode == false) { // Move to mac mode
                    layer_move(_BASE);          // Toggle WINMODE off
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
    rgblight_sethsv_range(RGB_TEAL, LED_IND);
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_LSFT)) {
        tap_code(KC_CAPS);
    } else if (leader_sequence_one_key(KC_Q)) {
        SEND_STRING(SECRET_5);
    } else if (leader_sequence_two_keys(KC_D, KC_F)) {
        SEND_STRING(SECRET_4);
    } else if (leader_sequence_two_keys(KC_C, KC_G)) {
        SEND_STRING(SECRET_3);
    } else if (leader_sequence_three_keys(KC_G, KC_U, KC_Y)) {
        SEND_STRING(SECRET_2);
    } else if (leader_sequence_three_keys(KC_S, KC_A, KC_T)) {
        SEND_STRING(SECRET_1);
    }
    led_update_user(host_keyboard_led_state());
}

// clang-format off
// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /* Base - Colemak 0
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Esc |   Q  |   W  |   F  |   P  |   B  |         |   J  |   L  |   U  |   Y  |  ;   | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   A  |   R  |   S  |   T  |   G  |         |   M  |   N  |   E  |   I  |  O   |  '   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Ctrl |   Z  |   X  |   C  |   D  |   V  |         |   K  |   H  |   ,  |   .  |  /   |Enter |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift| Quickbar| Space| Sym  |
    *                             +-------------/         \-------------+
    */

  [_BASE] = LAYOUT_reviung41(
    KC_ESC,  KC_Q, KC_W,   KC_F,   KC_P,   HOME_B,        HOME_J,  KC_L,  KC_U,    KC_Y,   KC_SCLN, KC_BSPC,
    KC_BSPC,   KC_A, KC_R, KC_S,   KC_T,   HOME_G,        HOME_M,  KC_N,  KC_E,  KC_I, KC_O,    KC_QUOT,
    KC_LCTL, KC_Z, KC_X,   KC_C,   KC_D,   HOME_V,        HOME_K,  KC_H,  KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
                            Nav,   KC_LSFT,       Quickbar,    KC_SPACE,    Sym
  ),
  [_WINMODE] = LAYOUT_reviung41(
    _______, _______, _______, _______, _______, wHOME_B,     wHOME_J, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, wHOME_G,     wHOME_M, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, wHOME_V,     wHOME_K, _______, _______, _______, _______, _______,
                                 _______,   _______,   _______,    _______,    _______
  ),


     /* Fastpad on cd combo - 2
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
    * |  Esc |  F12 |SpaceL|  Up  |SpaceR|ScrolU|         |   /  |   7  |   8  |   9  |  -   | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |DClick| Left | Down |Right |ScrolD|         |   *  |   1  |   2  |   3  |  +   |  .   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |Mouse1|      | TabL | Hyper| TabR |      |         |   =  |   4  |   5  |   6  |  .   |  :   |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift| Quickbar|   0  | Sym  |
    *                             +-------------/         \-------------+
    */

  [_FPADPLUS] = LAYOUT_reviung41(
    KC_ESC,   KC_F12, C(KC_LEFT), KC_UP,   C(KC_RIGHT), WHLU,      KC_SLSH, KC_7, KC_8, KC_9, KC_MINS,   KC_BSPC,
    KC_BSPC, DblClik, KC_LEFT,    KC_DOWN, KC_RIGHT,    WHLD,      S(KC_8), KC_1, KC_2, KC_3, S(KC_EQL), KC_DOT,
    MS_BTN1, XXXXXXX, LCS(KC_TAB), KC_HYPR,  C(KC_TAB), XXXXXXX,      KC_EQL,  KC_4, KC_5, KC_6, KC_COMM,   S(KC_SCLN),
                                                Nav,   KC_LSFT,   Quickbar,    KC_0,    Sym
  ),

       /* Nav - 4
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Tab |  F12 |SpaceL| Home |SpaceR| AltUp|         |VolUp | Home |  Up  |  End |ScrnSh|  Del |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp | Shift| Ctrl | Alt  | Cmd  | AltDn|         |VolDn | Left | Down | Right| BrUp |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |Mouse1|AltTab| TabL | End  | TabR | Play |         |Sptlgt| PgUp | NLine| PgDn | BrDn |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Enter  | Space| Sym  |
    *                             +-------------/         \-------------+
    */
  [_NAV] = LAYOUT_reviung41(
    KC_TAB,  KC_F12,  C(KC_LEFT),   KC_HOME, C(KC_RIGHT), A(KC_UP),       KC_VOLU,  KC_HOME, KC_UP,     KC_END,   SCAP,  KC_DEL,
    KC_BSPC, KC_LSFT, KC_LCTL,      KC_LALT, KC_LGUI,     A(KC_DOWN),     KC_VOLD,  KC_LEFT, KC_DOWN,   KC_RIGHT, KC_BRIU, XXXXXXX,
    MS_BTN1, A(KC_TAB), LCS(KC_TAB), KC_END,  C(KC_TAB),   KC_MPLY,       RUNAPP, KC_PGUP, C(KC_ENT), KC_PGDN,  KC_BRID, XXXXXXX,
                                                  Nav,   KC_LSFT,   KC_ENT,    KC_SPACE,    Sym
  ),

       /* Sym - 5
    * ,-----------------------------------------+         +-----------------------------------------.
    * |  Tab |   !  |   [  |   {  |   (  |      |         |   ^  |   )  |   }  |   ]  |  `   |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Bksp |   @  |   *  |   =  |   $  |   ~  |         | nUS# |  Cmd |  Alt | Ctrl | Shift|   "  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Mac# |   &  |   |  |   +  |   %  |      |         |   £  | nUS\ |   ~  |   :  |  `   |   \  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Nav | Shift|  Enter  | Space| Sym  |
    *                             +-------------/         \-------------+
    */

  [_SYM] = LAYOUT_reviung41(
    KC_TAB,  S(KC_1), KC_LBRC,    S(KC_LBRC), S(KC_9),    XXXXXXX,      S(KC_6), S(KC_0), S(KC_RBRC), KC_RBRC,    KC_GRAVE,   XXXXXXX,
    KC_BSPC, KC_AT,   S(KC_8),    KC_EQL,     S(KC_4),    KC_TILD,      KC_NUHS, KC_RGUI, KC_LALT, KC_RCTL, KC_RSFT,    KC_DQUO,
    A(KC_3), S(KC_7), S(KC_BSLS), S(KC_EQL),  S(KC_5),    XXXXXXX,      S(KC_3), KC_NUBS, S(KC_NUBS),    S(KC_SCLN), KC_NUBS, KC_BSLS,
                                                Nav,   KC_LSFT,   KC_ENT,    KC_SPACE,    Sym
  ),

       /* Functions - 6
    * ,-----------------------------------------+         +-----------------------------------------.
    * |      |Meh+L |Hyper |Meh+R |      |      |         |      |  F7  |  F8  |  F9  |  F12 |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      | Shift| Ctrl | Alt  | Cmd  |      |         |      |  F1  |  F2  |  F3  |  F11 |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |To Win|      |      |      |      |      |         |      |  F4  |  F5  |  F6  |  F10 |      |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             |  Num | Shift|  Enter  | Space|  Num |
    *                             +-------------/         \-------------+
    */

  [_FUNC] = LAYOUT_reviung41(
    XXXXXXX,XXXXXXX,MEH(KC_LEFT),KC_HYPR,MEH(KC_RIGHT),QK_BOOT,         QK_BOOT,   KC_F7,   KC_F8,   KC_F9,  KC_F12, XXXXXXX,
    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,               C(KC_EQL), KC_F1,   KC_F2,   KC_F3,  KC_F11, XXXXXXX,
    TO_WIN,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              C(KC_MINS), KC_F4,   KC_F5,   KC_F6,  KC_F10, TO_MAC,
                                        Num,   KC_LSFT,  KC_ENT,  KC_SPACE,   Num
  ),
};

// clang-format on
