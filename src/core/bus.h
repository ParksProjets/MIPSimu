/*

The processor bus.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "utils/range.h"

#include <vector>
#include <utility>
#include <stdint.h>

namespace core {


// A peripheral on the CPU bus.
class Peripheral {
public:

    // Set a value at the address given.
    virtual void SetValue(uint32_t addr, uint32_t value) = 0;

    // Get the value the address given.
    virtual uint32_t GetValue(uint32_t addr) = 0;
};



// The processor bus.
class Bus {
public:

    using Plugged = std::pair<utils::range<uint32_t>, Peripheral *>;


    // Add a another peripheral in the bus.
    void Add(Peripheral *peripheral, utils::range<uint32_t> range);

    // Get the peripheral mapped at the address given.
    Plugged *Get(uint32_t addr);


    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value);

    // Get the value the address given.
    uint32_t GetValue(uint32_t addr);


private:

    std::vector<Plugged> peripherals_;
};


} // namespace core
