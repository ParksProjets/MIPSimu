/*

The timer peripheral.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "core/bus.h"
#include "core/processor.h"

#include <memory>

namespace peripherals {


// The timer peripheral.
class Timer : public core::Peripheral {
public:

    // Set the processor component.
    void SetProcessor(core::Processor *processor);


    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value) override;

    // Get a value from an address.
    uint32_t GetValue(uint32_t addr) override;


private:

    // The CPU component.
    core::Processor *processor_;

    // Timer information.
    uint64_t start_count_;
    uint32_t period_;
    uint32_t thresold_;
};


} // namespace peripherals
