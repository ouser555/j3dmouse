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

#pragma once

//#define WS2812_PIO_USE_PIO1
//#define RGB_MATRIX_LED_COUNT 1
//#define ADNS5050_SCLK_PIN   GP10 
//#define ADNS5050_SDIO_PIN   GP9
//#define ADNS5050_CS_PIN     GP11
//#define POINTING_DEVICE_INVERT_Y

//#define ENCODERS_PAD_A { GP12 }
//#define ENCODERS_PAD_B { GP13 }
//#define ENCODER_TESTS

//#define I2C_DRIVER I2CD0
//#define I2C1_SDA_PIN GP6
//#define I2C1_SCL_PIN GP7

//#define I2C_DRIVER I2CD1
//#define I2C1_SDA_PIN GP6
//#define I2C1_SCL_PIN GP7

// Min 0, max 32
#define JOYSTICK_BUTTON_COUNT 16
// Min 0, max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXIS_COUNT 6
// Min 8, max 16
//#define JOYSTICK_AXIS_RESOLUTION 10 // for AVR
#define JOYSTICK_AXIS_RESOLUTION 12 // 12-bit for most STM32

#define ANALOG_JOYSTICK_X_AXIS_PIN GP26
#define ANALOG_JOYSTICK_Y_AXIS_PIN GP27

#define JSV ANALOG_JOYSTICK_Y_AXIS_PIN
#define JSH ANALOG_JOYSTICK_X_AXIS_PIN

#define JSV2 GP29
#define JSH2 GP28

#define ANALOG_JOYSTICK_AXIS_MAX 800
#define ANALOG_JOYSTICK_AXIS_MIN 200

#define _MIN 190
#define _MAX 820
#define _J_REP_MAX 2047
#define _CENTER 550
#define _J_DEADZONE 10
//#define _MAX 1023
//#define _CENTER 512
#define _DEAD 100
#define _SHIFT 15 // last 15 steps upwards

#define _DOWN_TRESHOLD (_CENTER+_DEAD)
#define _UP_TRESHOLD (_CENTER-_DEAD)

#define _TRESHOLD 40

#ifdef OLED_ENABLE
#define OLED_DISPLAY_128X32
//#define I2C1_SCL_PIN        B9
//#define I2C1_SDA_PIN        B8
#define OLED_BRIGHTNESS 128
//#define OLED_FONT_H "keyboards/mlego/m65/lib/glcdfont.c"
#endif