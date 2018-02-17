/*

External peripherals, i.e. LEDs, switches and push buttons.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "core/bus.h"

namespace peripherals {


// External peripherals, i.e. LEDs, switches and push buttons.
class External : public core::Peripheral {
public:

    // Set the value of the buttons.
    void SetButtonValue(uint32_t value);


    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value) override;

    // Get a value from an address.
    uint32_t GetValue(uint32_t addr) override;


private:

    uint8_t leds_ = 0b1010;
    uint32_t buttons_ = 0;
};


} // namespace peripherals
