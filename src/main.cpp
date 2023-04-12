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
Motor::MotorDriver motor1(GPIO::kMotorPWM_1_A, GPIO::kMotorPWM_1_B);
Motor::MotorDriver motor2(GPIO::kMotorPWM_2_A, GPIO::kMotorPWM_2_B);
Motor::MotorDriver motor3(GPIO::kMotorPWM_3_A, GPIO::kMotorPWM_3_B);
Motor::MotorDriver motor4(GPIO::kMotorPWM_4_A, GPIO::kMotorPWM_4_B);

// declare ultrasonic sensor objects
Ultrasonic::SR04 ultrasonic1(GPIO::kUltrasonicTriggeSR04_1, GPIO::kUltrasonicEchoSR04_1);
Ultrasonic::SR04 ultrasonic2(GPIO::kUltrasonicTriggeSR04_2, GPIO::kUltrasonicEchoSR04_2);



int main() {
    // setup stdio
    stdio_init_all();

    // send initial message over UART 
    printf("Initialization!\n");

    // setup each motor controller 
    motor1.setControl(900);
    motor2.setControl(100);
    motor3.setControl(900);
    motor4.setControl(100);

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