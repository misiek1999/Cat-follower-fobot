/*
    Author:     Michał
    Date:       2023-04-08
    Descripcion:    file include gpio irq callback functions using in project
*/

#pragma once

#include "pico/stdlib.h"
#include "hardware/gpio.h"
// load pinout layout
#include "pico_type.h"
#include "pinout.h"
#include "global_object_declaration.h"

namespace gpio_irq{
/*
    @description:    function for gpio irq callback 
    @param gpio:     gpio number
    @param events:   event type
*/
void gpio_callback(uint gpio, uint32_t events);

void gpio_irq_init();


}   // end namespace gpio_irq





