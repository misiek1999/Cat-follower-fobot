/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// include standard libraries
#include <cstdio>
// include the Pico SDK API header
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

// include local header files
#include "pinout.h"
#include "motor_driver.h"
#include "ultrasonic.h"

#include "main_controller.h"

// declare motor driver objects
Motor::MotorDriver motor1(kMotorPWM_1_A, kMotorPWM_1_B);
Motor::MotorDriver motor2(kMotorPWM_2_A, kMotorPWM_2_B);
Motor::MotorDriver motor3(kMotorPWM_3_A, kMotorPWM_3_B);
Motor::MotorDriver motor4(kMotorPWM_4_A, kMotorPWM_4_B);

// declare ultrasonic sensor objects
Ultrasonic::SR04 ultrasonic1(kUltrasonicTriggeSR04_1, kUltrasonicEchoSR04_1);
Ultrasonic::SR04 ultrasonic2(kUltrasonicTriggeSR04_2, kUltrasonicEchoSR04_2);

int main() {
    // setup stdio
    stdio_init_all();

    // send initial message over UART 
    printf("Initialization!\n");

    // setup each motor controller 
    motor1.setControl(500);


    while (true)
    {   
        // test ultrasonic sensor 1
        ultrasonic1.start_measurement();
        sleep_ms(200);
        // test ultrasonic sensor 1
        printf("Distance: %f\n", ultrasonic1.get_distance());
    }
    

    printf("Stop program\n");
    return 0;
}