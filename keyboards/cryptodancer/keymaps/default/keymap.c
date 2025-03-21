// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


// enum special_keycodes {
//     // LOWER = SAFE_RANGE,
// };

// KC_GRV
// KC_QUOT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 KC_1,   KC_2,   KC_3,  KC_4,    KC_5,                           KC_6,    KC_7,  KC_8,    KC_9,    KC_0,
        KC_TAB,  KC_Q,   KC_W,   KC_E,  KC_R,    KC_T,                           KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,   KC_S,   KC_D,  KC_F,    KC_G,                           KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, KC_RCTL,
        KC_LSFT, KC_Z,   KC_X,   KC_C,  KC_V,    KC_B,                           KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_ESC, KC_GRV, KC_NO, KC_LALT, KC_LGUI, MO(1), KC_SPC, KC_ENT, MO(2),   KC_RALT, KC_NO,   KC_QUOT, KC_BSLS,
    ),

    [1] = LAYOUT(
               KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                               KC_F6, KC_F7,   KC_F8,   KC_F9,  KC_F10,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                               KC_NO, KC_NO,   KC_NO,   KC_F11, KC_F12,  KC_DEL,
        KC_NO, KC_PGUP, KC_HOME, KC_LBRC, KC_MINS, KC_NO,                               KC_NO, KC_EQL,  KC_RBRC, KC_END, KC_PGDN, KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                               KC_NO, KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,
               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,
    ),

    [2] = LAYOUT(
                 KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,                               KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,                               KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, MS_BTN2, MS_BTN3,                             MS_BTN3, MS_BTN1, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,                               KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO,   KC_NO,   KC_NO, KC_NO,
    ),
};


const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_UP, KC_DOWN),   ENCODER_CCW_CW(KC_LEFT, KC_RGHT), },
    [2] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLL, MS_WHLR), },
    [1] = { ENCODER_CCW_CW(MS_UP, MS_DOWN),   ENCODER_CCW_CW(MS_LEFT, MS_RGHT), },
};


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // return true;
// }


#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}
#endif
