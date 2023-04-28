#include "gpio_irq_controller.h"

// enable namespace GPIO in this file
using namespace GPIO;

void gpio_irq::gpio_callback(uint gpio, uint32_t events)
{
    
    // switch between allocated gpio 
    switch (gpio)
    {
    case GPIO::kEncoder_1:  // call encoder 1 object irq handler
        encoder1.encoderIRQ();
        break;
    case GPIO::kEncoder_2:  // call encoder 2 object irq handler
        encoder2.encoderIRQ();
        break;
    case GPIO::kEncoder_3:  // call encoder 3 object irq handler
        encoder3.encoderIRQ();
        break;
    case GPIO::kEncoder_4:  // call encoder 4 object irq handler
        encoder4.encoderIRQ();
        break;
    default:
        // do nothing 
        break;
    }
}

void gpio_irq::gpio_irq_init()
{
    // setup gpio irq callback function and enable kEncoder_1 pin
    gpio_set_irq_enabled_with_callback(kEncoder_1, GPIO_IRQ_EDGE_RISE, true, &gpio_irq::gpio_callback);
    // add other encoder pins to irq callback function
    gpio_set_irq_enabled(kEncoder_2, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(kEncoder_3, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(kEncoder_4, GPIO_IRQ_EDGE_RISE, true);

}
