#pragma once 
// pinout for the raspberry pi pico board
// see https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf   

/*
    Defines go here 
*/ 
#include "cstdlib"
#include "pico_type.h"

namespace GPIO
{
    // using alias to define gpio type
using GPIO_type = PicoType::GPIO_type;

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

// servo defines
inline constexpr GPIO_type kServo_1 = 14;   // servo 1
inline constexpr GPIO_type kServo_2 = 15;   // servo 2

// limit sensor defines
inline constexpr GPIO_type kLimitSensorFront = 22;
inline constexpr GPIO_type kLimitSensor_Back = 26;

// UART defines
inline constexpr GPIO_type kUART_TX = 0;
inline constexpr GPIO_type kUART_RX = 1;

// I2C defines
inline constexpr GPIO_type kI2C_SDA = 20;
inline constexpr GPIO_type kI2C_SCL = 21; 

// Tensometric sensor defines
inline constexpr GPIO_type kTensometricSensorData = 27;
inline constexpr GPIO_type kTensometricSensorClk = 28;
} // namespace GPIO



