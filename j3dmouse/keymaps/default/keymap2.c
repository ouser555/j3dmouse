/*
 * Copyright 2023 Kevin Gee <info@controller.works>
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

enum layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_vertical_3x4(
  //,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,
  //|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C
  //|--------+--------+--------+--------+--------+--------|
  //|--------+--------+--------+--------+--------+--------|
  ),

  [1] = LAYOUT_vertical_3x4(
  //,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,
  //|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C
  //|--------+--------+--------+--------+--------+--------|
  //|--------+--------+--------+--------+--------+--------|
  ),

  [2] = LAYOUT_vertical_3x4(
  //,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,
  //|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C
  //|--------+--------+--------+--------+--------+--------|
  //|--------+--------+--------+--------+--------+--------|
  ),

  [3] = LAYOUT_vertical_3x4(
  //,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,
  //|--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,
  //|--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C
  //|--------+--------+--------+--------+--------+--------|
  //|--------+--------+--------+--------+--------+--------|
  )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise)
{
    if(clockwise){
      tap_code(KC_AUDIO_VOL_UP);
    }else{
      tap_code(KC_AUDIO_VOL_DOWN);
    }
    return true;
}
#endif

//joystick config
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    //JOYSTICK_AXIS_VIRTUAL,
    //JOYSTICK_AXIS_VIRTUAL
    JOYSTICK_AXIS_IN(JSH, _MAX, _CENTER, _MIN),
    JOYSTICK_AXIS_IN(JSV, _MIN, _CENTER, _MAX)  
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJUS\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    return false;
}
#endif