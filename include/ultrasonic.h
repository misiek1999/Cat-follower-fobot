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
#include <vector>

namespace Ultrasonic {

// using name alias to gpio pin type
using Pin_type = uint16_t;

/*
    @details - this is virtual class, used to measure distance using ultrasonic sensor
*/
class UltraSonicSensor{
    public:
        UltraSonicSensor() = delete;
        UltraSonicSensor(const Pin_type trigger_pin, const  Pin_type echo_pin): 
            trigger_pin_(trigger_pin), echo_pin_(echo_pin){};
        virtual ~UltraSonicSensor(){};
        // start measurement
        virtual void start_measurement();

        // virtual method to get distance in cm
        virtual float get_distance() = 0;

        // set temperature in celsius
        static void set_temperature(const float temperature);

    protected:
        Pin_type trigger_pin_;  // trigger pin to generate initial pulse 
        Pin_type echo_pin_; // echo pin attached to interrupt
        clock_t start_time_; // time when measurement was started uint64_t
        clock_t end_time_; // time when measurement was ended uint64_t

        static float temperature_;  // temperature in celsius

        // echo pin callback function
        virtual void echo_callback();
};


/*
    @details - this class is used to measure distance using ultrasonic sensor SR04
*/
class SR04 : public UltraSonicSensor{
    public:
        SR04() = delete;
        /*
        * @param trigger_pin - trigger pin to generate initial pulse
        * @param echo_pin - echo pin attached to interrupt
        */
        SR04(const Pin_type trigger_pin, const Pin_type echo_pin): 
            UltraSonicSensor(trigger_pin, echo_pin){};
        ~SR04(){};
        // start meas   urement
        void start_measurement();
        virtual float get_distance();
    private:
};

// /*
//     @details - this class is used to measure distance using multiple ultrasonic sensors connected to the same trigger pin
// */
// class MultiSonar {
//     public:
//         MultiSonar() = delete;
//         /*
//         * @param sensors - vector of ultrasonic sensors
//           @attention - all sensors must be connected to the same trigger pin
//         */
//         MultiSonar(std::vector<UltraSonicSensor> sensors): sensors_(sensors){};

//         // start measurement
//         void start_measurements();

//         // get distance from all sensors
//         float get_distance(size_t sensor_number) const;
//     private:
//     std::vector<UltraSonicSensor> sensors_;
 
// };

}   // namespace Ultrasonic