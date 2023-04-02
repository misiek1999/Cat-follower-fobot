/*
* This file include class to control single motor instance 
*/
#pragma once 
#include <cstdint>

#include "motor_driver.h"

namespace Motor{
/*
* Enum class to define the type of encoder used
*/
enum class EncoderType{
    kNone,
    kSingle,
    kDouble
};

/*
* Class to control a single motor instance
* This class is not copyable or movable
* Use 
*/
using GPIO_type = int16_t;
class MotorControl{
    MotorControl() = delete;
    MotorControl(const MotorControl&) = delete;
    MotorControl& operator=(const MotorControl&) = delete;
    MotorControl(MotorControl&&) = delete;
    MotorControl& operator=(MotorControl&&) = delete;

    /*
    * Constructor for 2 encoder pin
    */
    MotorControl(GPIO_type pwm_a, GPIO_type pwm_b, GPIO_type encoder_a, GPIO_type encoder_b = 0):
        motor_driver_(pwm_a, pwm_b), encoder_a_(encoder_a), encoder_b_(encoder_b), encoder_type_(EncoderType::kDouble) {};  
    /*
    * Constructor for 1 encoder pin
    */
    MotorControl(GPIO_type pwm_a, GPIO_type pwm_b, GPIO_type encoder_a, EncoderType encoder_type):
        motor_driver_(pwm_a, pwm_b), encoder_a_(encoder_a), encoder_b_(-1), encoder_type_(EncoderType::kSingle) {};  
    /*
    * Constructor for only motor pin, encoder is disabled
    */
    MotorControl(GPIO_type pwm_a, GPIO_type pwm_b):
        motor_driver_(pwm_a, pwm_b), encoder_a_(-1), encoder_b_(-1), encoder_type_(EncoderType::kNone) {};
    
    void setSpeed(const float speed);
    float getSpeed()const;

  private:
    // Motor driver object
    MotorDriver motor_driver_;

    // Encoder object
    GPIO_type encoder_a_;
    GPIO_type encoder_b_;
    EncoderType encoder_type_;
    
    // Motor speed controll object
    float setpoint_speed_;
    float current_speed_;
};

}  // namespace Motor