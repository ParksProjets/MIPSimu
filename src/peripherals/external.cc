/*

The timer peripheral.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "peripherals/external.h"

namespace peripherals {


// Set the value of the buttons.
void External::SetButtonValue(uint32_t value)
{
    buttons_ = value;
}



// Set a value at the address given.
void External::SetValue(uint32_t addr, uint32_t value)
{
    if (addr == 0)
        leds_ = value;
}



// Get a value from an address.
uint32_t External::GetValue(uint32_t addr)
{
    return (addr == 0) ? leds_ : buttons_;
}


} // namespace peripherals
