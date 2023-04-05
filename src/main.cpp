/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// include the Pico SDK API header
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "FreeRTOS.h"
#include "task.h"     /* RTOS task related API prototypes. */
#include "queue.h"    /* RTOS queue related API prototypes. */
#include "timers.h"   /* Software timer related API prototypes. */
#include "semphr.h"   /* Semaphore related API prototypes. */

// include local header files
#include "pinout.h"
#include "motor_driver.h"

// declare motor driver objects for each motor
Motor::MotorDriver motor1(kMotorPWM_1_A, kMotorPWM_1_B);
Motor::MotorDriver motor2(kMotorPWM_2_A, kMotorPWM_2_B);
Motor::MotorDriver motor3(kMotorPWM_3_A, kMotorPWM_3_B);
Motor::MotorDriver motor4(kMotorPWM_4_A, kMotorPWM_4_B);

// main function
int main() {

    // init console communication with PC
    stdio_init_all();
    // print init message
    printf("Initialization robot controller");

    // setup each motor controller 
    motor1.setControl(500);
    while (true)
    {
    }

}