/*
    This file include alias for type used in this project and basic structs
    Author: Michał
*/
#pragma once
#include <cstdint>

namespace PicoType{
// type alias 
using GPIO_type = int16_t;
using slice_number_type = int16_t;
using frequency_type = uint32_t;
using channel_type = uint16_t;

/*
    @details - this struct is used to define pwm pin
*/
struct gpio_pwm{
    GPIO_type gpio;
    slice_number_type slice_number;
    channel_type channel;
};

} // namespace PicoType