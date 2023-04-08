/*
    Author:     Michał
    Date:       2023-04-08
*/
#pragma once
// include
#include <cstdint>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

namespace Encoder{
// alias for gpio type
using GPIO_type = uint16_t;

/*
    @brief virtual class with interface for encoder driver
*/
class EncoderDriver{
    // disable default constructor and copy/move constructors
    EncoderDriver() = delete;
    EncoderDriver(const EncoderDriver&) = delete;
    EncoderDriver& operator=(const EncoderDriver&) = delete;
    EncoderDriver(EncoderDriver&&) = delete;
    EncoderDriver& operator=(EncoderDriver&&) = delete;
    // constructor
    EncoderDriver(GPIO_type encoder_a, GPIO_type encoder_b);


    private:
        GPIO_type encoder_a_;
        GPIO_type encoder_b_;
        uint32_t encoder_count_;


};



} // end namespace Encoder