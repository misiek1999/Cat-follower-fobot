#include "ultrasonic.h"
#include <unistd.h>
#include <cassert>
#include "hardware/pwm.h"

//TODO: add temperature compensation
float Ultrasonic::SR04::get_distance()
{
    Ultrasonic::Ultrasonic_time_us_type echo_time = this->meas_echo_pwm_.get_echo_time();
    float distance = (float(echo_time) * 0.034f)/2;
    if (distance > 400.0f)
    {
        distance = -1.0f;   // return -1 if distance is greater than 400 cm
    }
    return distance;
}

// TODO: replace usleep method with non-blocking function 
void Ultrasonic::UltraSonicSensor::start_measurement()
{
    this -> meas_echo_pwm_.start_measurement();
}

void Ultrasonic::SR04::start_measurement()
{
    //set trigger pin to high
    gpio_put(this->trigger_pin_, 1);
    sleep_us(10); // the worst ever method to generate impulse for certain amount of time 
    gpio_put(this->trigger_pin_, 0);
    // call parent method to start measurement
    UltraSonicSensor::start_measurement();
}
void Ultrasonic::UltraSonicSensor::set_temperature(const float temperature)
{
    UltraSonicSensor::temperature_ = temperature;
}

Ultrasonic::MeasureEchoPWM::MeasureEchoPWM(const Pin_type echo_pin)
{
    // covnvert pin number to pwm slice and channel 
    echo_pwm_.gpio = echo_pin;
    echo_pwm_.slice_number = pwm_gpio_to_slice_num(echo_pin);
    echo_pwm_.channel = pwm_gpio_to_channel(echo_pin);
    // Only the PWM B pins can be used as inputs.
    assert(echo_pwm_.channel == PWM_CHAN_B);
    // read current pwm configuration
    pwm_config cfg = pwm_get_default_config();
    // set pwm clock divider to 125 and clock divider mode to high
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_HIGH);
    pwm_config_set_clkdiv(&cfg, 125);   //TODO: change this value to parameter
    // pwm initializtion 
    pwm_init(echo_pwm_.slice_number, &cfg, false);
    gpio_set_function(echo_pwm_.gpio, GPIO_FUNC_PWM);
}

void Ultrasonic::MeasureEchoPWM::start_measurement()
{
    // set pwm counter to 0
    pwm_set_counter(echo_pwm_.slice_number, 0);
    // start timer counter
    pwm_set_enabled(echo_pwm_.slice_number, true);
}

Ultrasonic::Ultrasonic_time_us_type Ultrasonic::MeasureEchoPWM::get_echo_time()
{
    // stop timer counter
    pwm_set_enabled(echo_pwm_.slice_number, false);
    // read pwm counter value
    uint32_t counter_value = 0;
    counter_value = (uint32_t)pwm_get_counter(echo_pwm_.slice_number);
    return counter_value;
}
