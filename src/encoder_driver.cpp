#include "encoder_driver.h"
#include "cassert"
#include "cmath"

Encoder::SingleEncoderDriver::SingleEncoderDriver(const PicoType::GPIO_type encoder_a) {
    encoder_a_=encoder_a;
}

Encoder::EncoderDriver::EncoderDriver():
    direction_(EncoderDirection::kForward),
    encoder_type_(EncoderType::kSingle),
    decode_mode_(EncoderDecodeMode::kCountTime),
    encoder_count_(0),
    encoder_count_last_(0),
    last_time_(0),
    prev_last_time(0),
    time_between_compute_(Encoder::kTimeBetweenNextCall),
    impulse_per_full_rotation_(Encoder::kImpulsePerFullRotation)
{
    // convert time between compute to [s]
    time_between_compute_s_ = static_cast<float>(time_between_compute_) / 1000000.0f;
}

void Encoder::SingleEncoderDriver::changeDirection(EncoderDirection direction)
{
    this->direction_ = direction;
}

Encoder::EncoderDirection Encoder::EncoderDriver::getDirection() const
{
    return this->direction_;
}

void Encoder::EncoderDriver::changeDecodeMode(const EncoderDecodeMode decode_mode)
{
    this->decode_mode_ = decode_mode;
}

Encoder::EncoderDecodeMode Encoder::EncoderDriver::getDecodeMode() const
{
    return this->decode_mode_;
}

void Encoder::EncoderDriver::changeImpulsePerFullRotation(const unsigned int impulse_per_full_rotation)
{
    this->impulse_per_full_rotation_ = impulse_per_full_rotation;
}

unsigned int Encoder::EncoderDriver::getImpulsePerFullRotation() const
{
    return this -> impulse_per_full_rotation_;
}

// TODO: implement this method
float Encoder::SingleEncoderDriver::getRotationSpeed()
{
    float rotation_speed = 0.0f;
    if (this->decode_mode_ == EncoderDecodeMode::kCountImpulse)
    {
        rotation_speed = this->calculateRotationSpeedMeasureImpulse();
    }
    else if (this->decode_mode_ == EncoderDecodeMode::kCountTime)
    {
        rotation_speed = this->calculateRotationSpeedMeasureTime();
    }
    else
    {
        // TODO: add error handling
    }

    return rotation_speed;
}

void Encoder::EncoderDriver::changeTimeBetweenCompute(const time_t time_between_compute)
{ 
    this->time_between_compute_ = time_between_compute;
}

time_t Encoder::EncoderDriver::getTimeBetweenCompute() const
{
    return this->time_between_compute_;
}

void Encoder::SingleEncoderDriver::encoderIRQ()
{ 
    // save call time into member variables
    this->prev_last_time = this->last_time_;
    this->last_time_ = time_us_64();    // get time in microseconds
    // increment encoder count
    if(this->direction_ == EncoderDirection::kForward)  
        ++(*this).encoder_count_;   // in single mode use rotation estimate
    else
        --(*this).encoder_count_;
}

float Encoder::SingleEncoderDriver::calculateRotationSpeedMeasureTime()
{
    float rotation_speed = 0.0f;
    // calculate time between last two calls
    time_t time_between_calls = this->last_time_ - this->prev_last_time;
    // if time between calls is 0, then return 0
    if (time_between_calls != 0) {
        // check timeout between irq calls
        if (time_between_calls > Encoder::kEncoderTimeout) {
            rotation_speed = 0;
        } else {
            // convert time to seconds
            float time_between_calls_sec = time_between_calls / 1000000.0f;
            // calculate rotation speed
            rotation_speed = 2 * M_PI / (this->impulse_per_full_rotation_ * time_between_calls_sec);
        }
    }
    // limit rotation speed to kMaxRotationSpeed    
    if (rotation_speed > Encoder::kMaxRotationSpeed) {
        rotation_speed = Encoder::kMaxRotationSpeed;
    }
    return rotation_speed;
}


float Encoder::SingleEncoderDriver::calculateRotationSpeedMeasureImpulse()
{
    float estimated_rotation_speed = 0.0f;
    // calculate diffrence between current and last encoder count
    int encoder_diff = (this->encoder_count_ - this->encoder_count_last_);
    // calculate rotation speed 
    estimated_rotation_speed = 2 * M_PI * encoder_diff /
                                (this->impulse_per_full_rotation_*
                                 this->time_between_compute_s_);
    // save current value to memory
    this->encoder_count_last_ = this->encoder_count_;
    // return calculated rotation speed
    return estimated_rotation_speed;
}
