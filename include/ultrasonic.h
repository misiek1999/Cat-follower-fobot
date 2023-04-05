/*
    * Ultrasonic.h
    *
    *  Created on: 2017-11-20
    *     Author: Michał Dydo
    * 
    * This file consist of functions that are used to measure distance using ultrasonic sensor.
    * 
*/
#pragma once

#include <cstdint>
#include <time.h>

namespace Ultrasonic {

// using name alias 
using Pin_type = uint16_t;

class UltraSonicSensor{
    public:
        UltraSonicSensor() = delete;
        UltraSonicSensor(Pin_type trigger_pin, Pin_type echo_pin);

        // start measurement
        virtual void start_measurement();

        // virtual method to get distance in cm
        virtual float get_distance() = 0;

    private:
        Pin_type trigger_pin_;
        Pin_type echo_pin_;

        clock_t start_time_; // time when measurement was started uint64_t

};

// class with functions that are used to measure distance using ultrasonic sensor SR04
class SR04 : public UltraSonicSensor{
    public:
        SR04() = delete;
        SR04(Pin_type trigger_pin, Pin_type echo_pin);

        // start measurement
        void start_measurement();

    private:

};

}   // namespace Ultrasonic