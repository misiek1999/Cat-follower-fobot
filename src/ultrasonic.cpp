#include "ultrasonic.h"
#include <unistd.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


//TODO: add temperature compensation
float Ultrasonic::SR04::get_distance()
{
    // calculate distance in cm
    float distance = difftime(this->end_time_, this->start_time_) * 0.0343f / 2.0f;
    if (distance > 400.0f)
    {
        distance = -1.0f;   // return -1 if distance is greater than 400 cm
    }
    return distance;
}

// TODO: replace usleep method with non-blocking function 
void Ultrasonic::UltraSonicSensor::start_measurement()
{
    //read start time 
    this->start_time_ = clock();
}
void Ultrasonic::SR04::start_measurement()
{
    //set trigger pin to high
    gpio_put(this->trigger_pin_, 1);
    sleep_us(10); // the worst ever method to generate impulse for certain amount of time 
    gpio_put(this->trigger_pin_, 1);

    this->start_time_ = clock();
}
void Ultrasonic::UltraSonicSensor::set_temperature(const float temperature)
{
    UltraSonicSensor::temperature_ = temperature;
}

void Ultrasonic::UltraSonicSensor::echo_callback()
{
    this->end_time_ = clock();
}

// void Ultrasonic::MultiSonar::start_measurements()
// {
//     // start measurement for each sensor using parent method
//     for (auto &sensor : this->sensors_)
//     {
//         sensor.start_measurement();
//     }
// }

// float Ultrasonic::MultiSonar::get_distance(size_t sensor_number) const
// {
//     return sensors_[sensor_number].get_distance();
// }
