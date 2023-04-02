#pragma once 
// pinout for the raspberry pi pico board
// see https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf   

/*
    Defines go here 
*/ 
#include "cstdlib"
// motor pwm defines 
// motor 1 gpio pin group
inline constexpr uint8_t kMotorPWM_1_A = 0;
inline constexpr uint8_t kMotorPWM_1_B = 1;
// motor 2 gpio pin group
inline constexpr uint8_t kMotorPWM_2_A = 2;
inline constexpr uint8_t kMotorPWM_2_B = 3;
// motor 3 gpio pin group
inline constexpr uint8_t kMotorPWM_3_A = 4;
inline constexpr uint8_t kMotorPWM_3_B = 5;
// motor 4 gpio pin group
inline constexpr uint8_t kMotorPWM_4_A = 6;
inline constexpr uint8_t kMotorPWM_4_B = 7;