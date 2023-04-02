#include "motor_driver.h"

#include "hardware/gpio.h"
#include "hardware/pwm.h"

namespace Motor {

MotorDriver::MotorDriver(GPIO_type pwm_a, GPIO_type pwm_b, frequency_type frequency_):
    pwm_level_(frequency_) {
    // set gpio 
    gpio_a.gpio = pwm_a;
    gpio_b.gpio = pwm_b;
    // setup gpio for motor pwm
    gpio_set_function(pwm_a, GPIO_FUNC_PWM);
    gpio_set_function(pwm_b, GPIO_FUNC_PWM);
    // get slice for each gpio
    gpio_a.slice_number = pwm_gpio_to_slice_num(gpio_a.gpio);
    gpio_b.slice_number = pwm_gpio_to_slice_num(gpio_b.gpio);
    // get channel number for each pwm gpio
    gpio_a.channel = pwm_gpio_to_channel(gpio_a.gpio);
    gpio_b.channel = pwm_gpio_to_channel(gpio_b.gpio);
    // default clock diveder 
    clock_divider_ = 24;
    // set pwm clock divider
    pwm_set_clkdiv(gpio_a.slice_number, clock_divider_);
    pwm_set_clkdiv(gpio_b.slice_number, clock_divider_);
    // set pwm warp 
    pwm_set_wrap(gpio_a.slice_number, frequency_);
    pwm_set_wrap(gpio_b.slice_number, frequency_);
    // set pwm chan level to zero
    pwm_set_chan_level(gpio_a.slice_number, gpio_a.channel, 0);
    pwm_set_chan_level(gpio_b.slice_number, gpio_b.channel, 0);
    // enable each slice for each pwm output 
    pwm_set_enabled(gpio_a.slice_number, true);
    pwm_set_enabled(gpio_b.slice_number, true);
};


void MotorDriver::setControl(const float pwm_level){
    // limit pwm level to 0.0 to kMaxPWM_
    if(pwm_level < 0.0f)
        this->pwm_level_ = 0.0f;
    else if(pwm_level >= kMaxPWM_)
        this->pwm_level_ = kMaxPWM_;
    else
        // set pwm level to pwm_level (0.0 to kMaxPWM_
        this->pwm_level_ = pwm_level;
    
    // set pwm level to each pwm channel 
    pwm_set_chan_level(gpio_a.slice_number, gpio_a.channel, this->pwm_level_);
    pwm_set_chan_level(gpio_b.slice_number, gpio_b.channel, this->pwm_level_);
}

float MotorDriver::getControl()const{
    return this->pwm_level_;
}
}