/*
    Author:     Michał
    Date:       2023-04-08
*/
#pragma once
// include
#include <cstdint>
#include <ctime>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "pico_type.h"
#include "pinout.h"
//TODO: Implement double encoder decoding
//Separate this class into two children class: kSingle and KDouble decode mode 
namespace Encoder{
// default time between next function call 
constexpr unsigned long kTimeBetweenNextCall = 20000UL;    // 20 000[us]
constexpr unsigned int kImpulsePerFullRotation = 20; // 20 impulses per full rotation
constexpr float kMaxRotationSpeed = 1000.0f; // 1000[rev/min]
constexpr unsigned long kEncoderTimeout = 5000000UL; // 5 000 000[us]
/*
* Enum class to define the type of encoder used
*/
enum class EncoderType{
    kNone,
    kSingle,
    kDouble
};

enum class EncoderDirection{
    kForward = 1,
    kBackward = -1,
};

/*
* @brief enum class to define the mode of encoder used
*/
enum class EncoderDecodeMode{
    kNone,  /*!< None decoding mode selected */
    kCountImpulse,  /*!< Count number of impulse in specific period pf time */
    kCountTime, /*!< Count time between next impulse and calculate rotation speed */
};

/*
    @brief virtual class with interface for encoder driver
*/
class EncoderDriver{
public:
    EncoderDriver(); // empty constructor
    // disable default constructor and copy/move constructors
    EncoderDriver(const EncoderDriver&) = delete;
    EncoderDriver& operator=(const EncoderDriver&) = delete;
    EncoderDriver(EncoderDriver&&) = delete;
    EncoderDriver& operator=(EncoderDriver&&) = delete;
    // change direction of encoder methods
    EncoderDirection getDirection()const;
    // method to get encoder rotation speed
    virtual float getRotationSpeed() =0;
    // methods to change and get encoder decode mode
    void changeDecodeMode(const EncoderDecodeMode decode_mode);
    EncoderDecodeMode getDecodeMode()const;
    // change and get impulse per full rotation
    virtual void changeImpulsePerFullRotation(const unsigned int impulse_per_full_rotation);
    unsigned int getImpulsePerFullRotation()const;
    // change and get time between compute
    void changeTimeBetweenCompute(const time_t time_between_compute);
    time_t getTimeBetweenCompute()const;
    /*
        @brief virtual method called during irq call
    */
    virtual void encoderIRQ() = 0;
    protected:
        PicoType::GPIO_type encoder_a_; // used for both single and double encoder
        PicoType::GPIO_type encoder_b_; // used only for double encoder
        long long encoder_count_;    // used only for count impulse
        long long encoder_count_last_;    // last value of encoder_count_ 
        EncoderType encoder_type_;  // type of encoder used
        EncoderDecodeMode decode_mode_; // mode of encoder used
        EncoderDirection direction_;    // direction of encoder rotation
        time_t last_time_;  // used for store last irq call time
        time_t prev_last_time; // used for store  penultimate irq call time
        uint32_t time_between_compute_; // time between next call method getRotationSpeed 
        float time_between_compute_s_;  // time between next call method getRotationSpeed in [s]
        unsigned int impulse_per_full_rotation_; // used only for count impulse
};

/*
    @brief class to handle single encoder like LM393
*/
class SingleEncoderDriver : public EncoderDriver{
    public:
        /*
            @brief default constructor
            @param encoder_a - gpio pin used for encoder with single output (A)
        */
        SingleEncoderDriver(const PicoType::GPIO_type encoder_a);
        // public methods
        void encoderIRQ() override;
        float getRotationSpeed() override;
        /*
            @brief method to change direction of encoder with only one output
            @param direction - new direction of encoder
        */
        void changeDirection(EncoderDirection direction);
    private:
        // function to calculate rotation speed using diffrent methods
        float calculateRotationSpeedMeasureTime();
        float calculateRotationSpeedMeasureImpulse();
};  // end class SingleEncoderDriver

} // end namespace Encoder