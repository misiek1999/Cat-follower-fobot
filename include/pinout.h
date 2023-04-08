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
inline constexpr GPIO_type kMotorPWM_1_A = 2;
inline constexpr GPIO_type kMotorPWM_1_B = 3;
// motor 2 gpio pin group
inline constexpr GPIO_type kMotorPWM_2_A = 4;
inline constexpr GPIO_type kMotorPWM_2_B = 5;
// motor 3 gpio pin group
inline constexpr GPIO_type kMotorPWM_3_A = 6;
inline constexpr GPIO_type kMotorPWM_3_B = 7;
// motor 4 gpio pin group
inline constexpr GPIO_type kMotorPWM_4_A = 8;
inline constexpr GPIO_type kMotorPWM_4_B = 9;

// encoer defines
// encoder 1 gpio pin group
inline constexpr GPIO_type kEncoder_1 = 16;
inline constexpr GPIO_type kEncoder_2 = 17;
inline constexpr GPIO_type kEncoder_3 = 18;
inline constexpr GPIO_type kEncoder_4 = 19;

// ultrasonic sensor defines
// ultrasonic sensor SR04_1
inline constexpr GPIO_type kUltrasonicTriggeSR04_1 = 10;
inline constexpr GPIO_type kUltrasonicEchoSR04_1 = 11;
// ultrasonic sensor SR04_2
inline constexpr GPIO_type kUltrasonicTriggeSR04_2 = 10;
inline constexpr GPIO_type kUltrasonicEchoSR04_2 = 13;
