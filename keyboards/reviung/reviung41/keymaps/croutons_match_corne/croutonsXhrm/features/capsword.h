// This library implements "Caps Word", which is like conventional Caps Lock,
// but automatically disables itself at the end of the word. This is useful for
// typing all-caps identifiers like `MOD_MASK_ALT`.
//
// Caps Word is activated by pressing the left and right shift keys at the same
// time. This way you don't need a dedicated key for using Caps Word. I've
// tested that this works as expected with one-shot mods and Space Cadet Shift.
// If your shift keys are mod-taps, activate Caps Word by holding both shift
// mod-tap keys until the tapping term, release them, then begin typing.
//
// For full documentation, see
// https://getreuer.info/posts/keyboards/caps-word

#pragma once

#include QMK_KEYBOARD_H

bool process_caps_word(uint16_t keycode, keyrecord_t* record);