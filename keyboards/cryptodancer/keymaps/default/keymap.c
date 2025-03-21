// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


enum LAYERS {
    _QWERT = 0,
    _RAISE,
    _MOUSE,
};

#define L_QWERT TO(_QWERT)
#define L_RAISE MO(_RAISE)
#define L_MOUSE TO(_MOUSE)

enum KEYCODES {
    // Direction keys
    UD_UP = SAFE_RANGE,
    UD_RGHT,
    UD_DOWN,
    UD_LEFT,

    // Mouse movement keys
    UM_UP,
    UM_RGHT,
    UM_DOWN,
    UM_LEFT,
};


#ifdef AUDIO_ENABLE
float CAPS_SONG[][2] = SONG(CAPS_SOUND);
float DIRS_X1_SONG[][2] = SONG(DIRS_X1_SOUND);
float DIRS_X2_SONG[][2] = SONG(DIRS_X2_SOUND);
float DIRS_X4_SONG[][2] = SONG(DIRS_X4_SOUND);
#endif /* AUDIO_ENABLE */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERT] = LAYOUT(
                 KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RCTL,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_HOME, KC_PGUP, XXXXXXX, KC_LALT, KC_LGUI, KC_SPC,  KC_CAPS, L_MOUSE, KC_ENT,  L_RAISE, KC_RALT, XXXXXXX, KC_PGDN, KC_END
    ),

    [_RAISE] = LAYOUT(
                 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  KC_DEL,
        _______, KC_ESC,  XXXXXXX, KC_LBRC, KC_MINS, KC_GRV,                                      KC_QUOT, KC_EQL,  KC_RBRC, KC_BSLS, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                 XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_MOUSE] = LAYOUT(
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX,                                     XXXXXXX, MS_BTN1, MS_BTN3, MS_BTN2, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                 XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, L_QWERT, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
};


const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERT] = { ENCODER_CCW_CW(UD_UP,   UD_DOWN), ENCODER_CCW_CW(UD_LEFT, UD_RGHT), },
    [_RAISE] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
    [_MOUSE] = { ENCODER_CCW_CW(UM_UP,   UM_DOWN), ENCODER_CCW_CW(UM_LEFT, UM_RGHT), },
};


layer_state_t layer_state_set_user(layer_state_t state) {
    if (_MOUSE == get_highest_layer(state)) {
        gpio_write_pin_low(LED_USER);
    } else {
        gpio_write_pin_high(LED_USER);
    }
    return state;
}

const uint16_t keyncoder_map[] = {
    KC_UP,
    KC_RGHT,
    KC_DOWN,
    KC_LEFT,
    MS_UP,
    MS_RGHT,
    MS_DOWN,
    MS_LEFT,
};

uint16_t keyncoder_times[8] = { 0 };

bool process_record_keyncoder(uint16_t keycode, keyrecord_t *record) {
    // Ignore release events
    if (!record->event.pressed) {
        return true;
    }

    size_t index = keycode - SAFE_RANGE;

    uint16_t time_last = keyncoder_times[index];
    uint16_t time_now = record->event.time;
    keyncoder_times[index] = time_now;

    uint16_t target_keycode = keyncoder_map[index];

    // Calculate delta between repeated keypresses.
    // This makes sure that integer overflow does not happen.
    // This may still cause the wrong number of keystrokes to be sent in rare circumstances (as this is `mod 65 seconds`).
    uint16_t delta = UINT16_MAX;
    if (time_now >= time_last) {
        delta = time_now - time_last;
    }

    if (delta < KEYNCODER_THRESHOLD_X4) {
        tap_code16(target_keycode);
        tap_code16(target_keycode);
        tap_code16(target_keycode);
        tap_code16(target_keycode);

#ifdef AUDIO_ENABLE
        PLAY_SONG(DIRS_X4_SONG);
#endif /* AUDIO_ENABLE */
    } else if (delta < KEYNCODER_THRESHOLD_X2) {
        tap_code16(target_keycode);
        tap_code16(target_keycode);

#ifdef AUDIO_ENABLE
        PLAY_SONG(DIRS_X2_SONG);
#endif /* AUDIO_ENABLE */
    } else {
        tap_code16(target_keycode);

#ifdef AUDIO_ENABLE
        PLAY_SONG(DIRS_X1_SONG);
#endif /* AUDIO_ENABLE */
    }

    return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UD_UP:
        case UD_RGHT:
        case UD_DOWN:
        case UD_LEFT:
        case UM_UP:
        case UM_RGHT:
        case UM_DOWN:
        case UM_LEFT:
            return process_record_keyncoder(keycode, record);

        default:
            break;
    }

#ifdef AUDIO_ENABLE
    if (KC_CAPS == keycode && record->event.pressed) {
        PLAY_SONG(CAPS_SONG);
    }
#endif /* AUDIO_ENABLE */

    return true;
}


void keyboard_post_init_user(void) {
    gpio_set_pin_output(LED_USER);

#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = true;
#endif /* CONSOLE_ENABLE */
}
