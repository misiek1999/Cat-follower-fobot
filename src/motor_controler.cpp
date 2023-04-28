#include "motor_controler.h"

// local function to covert time_us_64() to ms
unsigned long getTimeMs()
{
    unsigned long time_ms = 0;
    time_ms = time_us_64() / 1000;    
    return time_ms;
}


Motor::MotorControl::MotorControl(const GPIO_type motor_pin_A, 
                                  const GPIO_type motor_pin_B,
                                  Encoder::SingleEncoderDriver *encoder_ptr):
                                  motor_driver_(MotorDriver(motor_pin_A, motor_pin_B)),
                                  encoder_ptr_(encoder_ptr),
                                  pid_controller_(PIDController<float>(
                                    Motor::kMotorPID_P, Motor::kMotorPID_I, Motor::kMotorPID_D,
                                    std::bind(&Motor::MotorControl::setControllerFeedback, this),
                                    std::bind(&Motor::MotorControl::getControllerOutput, this, std::placeholders::_1)))
{
    // set PID controller output limits
    this->pid_controller_.setOutputBounds(Motor::kMotorControlMin, Motor::kMotorControlMax);
    // set PID timer function
    this->pid_controller_.registerTimeFunction(getTimeMs);
}

void Motor::MotorControl::setSpeed(const float speed)
{
    this->setpoint_speed_ = speed;
}

float Motor::MotorControl::getSpeed() const
{
    return this->current_speed_;
}

void Motor::MotorControl::perdiodicUpdate() noexcept
{
    // read encoder speed
    this->current_speed_ = this->encoder_ptr_->getRotationSpeed();
    // calculate motor speed
    float speed_error = this->setpoint_speed_ - this->current_speed_;
    // calculate motor control
    this->pid_controller_.tick();
    // check pid is properly update setpoint and current speed
    assert(this->pid_controller_.getFeedback() == this->current_speed_);
    // set motor control
    this->motor_driver_.setControl(this->control_);
}

float Motor::MotorControl::setControllerFeedback()
{
    return this->current_speed_;
}

void Motor::MotorControl::getControllerOutput(float output)
{
    this->control_ = output;
}

void Motor::MotorControl::setRawControl(const int control)
{
    this->motor_driver_.setControl(control);
}