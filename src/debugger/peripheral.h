/*

The debugger peripheral.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "core/bus.h"

namespace debugger {


// The debugger peripheral.
class Peripheral : public core::Peripheral {
public:

    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value) override;

    // Get the value the address given.
    uint32_t GetValue(uint32_t addr) override;


    // Must the debugger be paused?
    bool paused = false;
};


} // namespace debugger
