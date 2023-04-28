#pragma once

#include <cstdint>


namespace Motor{

// type alias 
using GPIO_type = int16_t;
using slice_number_type = int16_t;
using frequency_type = uint32_t;
using channel_type = uint16_t;

class MotorDriver{

public:
    MotorDriver() = delete;
    MotorDriver(const MotorDriver&) = delete;
    MotorDriver& operator=(const MotorDriver&) = delete;
    MotorDriver(MotorDriver&&) = delete;
    MotorDriver& operator=(MotorDriver&&) = delete;
    MotorDriver(GPIO_type pwm_a, GPIO_type pwm_b, frequency_type frequency_ = 1000);

    void setControl(const float pwm_level);
    float getControl()const;

private:
    struct gpio_pwm{
        GPIO_type gpio;
        slice_number_type slice_number;
        channel_type channel;
    };
    gpio_pwm gpio_a;
    gpio_pwm gpio_b;
    float clock_divider_;

    float pwm_level_;
    float kMaxPWM_ = 1000;
    
};
}  // end namespace