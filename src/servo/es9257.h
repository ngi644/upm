/*
 * Author: Yevgeniy Kiveisha <yevgeniy.kiveisha@intel.com>
 *         Abhishek Malik <abhishek.malik@intel.com>
 * Copyright (c) 2016 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef ES9257_H_
#define ES9257_H_

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "upm.h"
#include "mraa/pwm.h"

/**
 * @library servo
 * @sensor es9257
 * @comname ES9257 Servo
 * @altname Grove Servo
 * @type servos
 * @man emax
 * @web http://www.seeedstudio.com/wiki/Grove_-_Servo
 * @con pwm
 * @kit gsk
 *
 * @brief API for the ES9257 Servo
 *
 * This module defines the ES9257 interface for ES9257 servos.
 * Like other servos, the ES9257 servo has a shaft that can be controlled
 * by setting the desired angle. There are also routines for setting
 * and getting the minimum and maximum pulse width as well as the
 * maximum period.
 *
 * @image html es9257.jpg
 * @snippet es9257.c Interesting
 */

#define ES9257_MIN_PULSE_WIDTH             600
#define ES9257_MAX_PULSE_WIDTH             2200
#define ES9257_PERIOD                      20000
#define ES9257_MAX_ANGLE                   180.0

/*
 * device context
 */
typedef struct _es9257_context {
    mraa_pwm_context    pwm;
    uint16_t            servo_pin;
    uint32_t            max_pulse_width;
    uint32_t            min_pulse_width;
} *es9257_context;

/**
 * Instantiates a the servo at the given pin
 *
 * @param pin Servo pin number
 * @param minPulseWidth Minimum pulse width, in microseconds
 * @param maxPulseWidth Maximum pulse width, in microseconds
 * @param waitAndDisablePwm If 1, PWM is enabled only during the
 * setAngle() execution for a period of 1 second, and then turned back
 * off. If 0, PWM remains on afterward.
 */


es9257_context es9257_init(int32_t pin, int32_t min_pulse_width,
                         int32_t max_pulse_width);

/**
 * Halts PWM for this servo and allows it to move freely.
 */
void es9257_halt(es9257_context dev);

/**
 * Sets the angle of the servo engine.
 *
 * @param angle Number between 0 and 180
 * @return 0 if successful, non-zero otherwise
 */
upm_result_t es9257_set_angle(es9257_context dev, int32_t angle);

/*
 * Calculating relative pulse time to the value.
 * */
upm_result_t es9257_calc_pulse_travelling(const es9257_context dev,
                                         int32_t* ret_val,
                                         int32_t value);

/**
 * Sets the minimum pulse width
 *
 * @param width Minimum HIGH signal width
 */
void es9257_set_min_pulse_width (es9257_context dev, int width);

/**
 * Sets the maximum pulse width
 *
 * @param width Maximum HIGH signal width
 */
void es9257_set_max_pulse_width (es9257_context dev, int width);

/**
 * Returns the minimum pulse width
 *
 * @return Minimum pulse width
 */
int es9257_get_min_pulse_width (es9257_context dev);

/**
 * Returns the maximum pulse width
 *
 * @return Maximum pulse width
 */
int es9257_get_max_pulse_width (es9257_context dev);

#endif /* ES9257_H_ */