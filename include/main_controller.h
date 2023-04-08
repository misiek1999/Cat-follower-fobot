/*
    Author:     Michał
    Date:       2023-04-08
    Description:    This file consist main function of the program.
*/
#pragma once

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
#include "encoder_driver.h"
#include "gpio_irq_controller.h"


namespace controller{
/*
    @brief time between each call of main function [ms]
*/
constexpr uint32_t kMainControllerCallTime = 10; 

/*
    @brief flag to check if main function is ended before next call
*/
static bool main_function_overrun_flag = false;

/*
    @brief main function of the program called by timer each kMainControllerCallTime
*/
void main_controller();


} // end namespace controller