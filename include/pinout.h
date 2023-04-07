#pragma once 
// pinout for the raspberry pi pico board
// see https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf   

/*
    Defines go here 
*/ 
#include "cstdlib"
// using alias to define gpio type
using GPIO_type = uint16_t;

// motor pwm defines 
// motor 1 gpio pin group
inline constexpr GPIO_type kMotorPWM_1_A = 0;
inline constexpr GPIO_type kMotorPWM_1_B = 1;
// motor 2 gpio pin group
inline constexpr GPIO_type kMotorPWM_2_A = 2;
inline constexpr GPIO_type kMotorPWM_2_B = 3;
// motor 3 gpio pin group
inline constexpr GPIO_type kMotorPWM_3_A = 4;
inline constexpr GPIO_type kMotorPWM_3_B = 5;
// motor 4 gpio pin group
inline constexpr GPIO_type kMotorPWM_4_A = 6;
inline constexpr GPIO_type kMotorPWM_4_B = 7;

// ultrasonic sensor defines
// ultrasonic sensor SR04_1
constexpr GPIO_type kUltrasonicTriggeSR04_1 = 8;
constexpr GPIO_type kUltrasonicEchoSR04_1 = 9;
