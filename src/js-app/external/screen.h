/*

The VGA screen.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "core/bus.h"

#include <memory>
#include <stdint.h>

namespace app {


// The VGA screen.
class Screen : public core::Peripheral {

public:

    // Attach the pixel buffer.
    void Attach(unsigned char *u8pixels);


    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value) override;

    // Get a value from an address.
    uint32_t GetValue(uint32_t addr) override;


private:

    unsigned char *u8pixels_;
};


} // namespace app
