/*
* This file include class to control single motor instance 
*/
#pragma once 
#include <cstdint>
#include <functional>
#include <cassert>
// include external lib
#include "PID.h"    

#include "pico_type.h"
#include "motor_driver.h"
#include "encoder_driver.h"


namespace Motor{
using GPIO_type = PicoType::GPIO_type;

// maximum motor speed in rad/s 
constexpr float kMotorMaxSpeed = 8.377580409572781f; // rad/s
// minimum motor control value
constexpr float kMotorControlMin = -1000.0f;
// maximum motor control value
constexpr float kMotorControlMax = 1000.0f;
// basic PID controller parameters
constexpr float kMotorPID_P = 0.0f;
constexpr float kMotorPID_I = 0.0f;
constexpr float kMotorPID_D = 0.0f;
/*
* Class to control a single motor instance
* This class is not copyable or movable
* This class use basic arduino motor with 2 pwm pins to change motor speed and
* encoder with 1 pin
*/
class MotorControl{
public:
    MotorControl() = delete;
    MotorControl(const MotorControl&) = delete;
    MotorControl& operator=(const MotorControl&) = delete;
    MotorControl(MotorControl&&) = delete;
    MotorControl& operator=(MotorControl&&) = delete;
    /*
    * @brief constructor of MotorControl class
    * @param motor_pin_A pin number of motor driver pin A
    * @param motor_pin_B pin number of motor driver pin B
    * @param pointer to encoder object
    */
    MotorControl(const GPIO_type motor_pin_A, const GPIO_type motor_pin_B, 
                 Encoder::SingleEncoderDriver *encoder_ptr);
    
    /*
    * @brief Set setpoint motor speed in rad/s
    * @param speed setpoint motor speed in rad/s
    */
    void setSpeed(const float speed);
    /*
    * @brief Get current motor speed in rad/s
    * @return current motor speed in rad/s
    */
    float getSpeed()const;

    /*
    * @brief Function to update encoder speed and calculate motor control
    */
   void perdiodicUpdate() noexcept;

   void setRawControl(const int control);

private:
    // Motor driver object
    MotorDriver motor_driver_;

    // handler to endoder object
    Encoder::SingleEncoderDriver *encoder_ptr_;
    
    // Motor speed controll object
    float setpoint_speed_;
    float current_speed_;

    // Motor maximum speed
    float max_speed_;

    // PID controller object 
    PIDController<float> pid_controller_;
    // private methods to update and read data from PID controller 
    float setControllerFeedback();
    void getControllerOutput(float output);
    // control singal to motor driver
    float control_;
};

}  // namespace Motor