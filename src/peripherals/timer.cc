/*

The timer peripheral.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "peripherals/timer.h"

namespace peripherals {


// Set the processor component.
void Timer::SetProcessor(core::Processor *processor)
{
    processor_ = processor;
    start_count_ = processor->cpucount();
}



// Set a value at the address given.
void Timer::SetValue(uint32_t addr, uint32_t value)
{
    switch (addr) {
        case 0:
            period_ = value;
            start_count_ = processor_->cpucount();
            break;

        case 4:
            thresold_ = value;
            break;
    }
}



// Get a value from an address.
uint32_t Timer::GetValue(uint32_t addr)
{
    uint64_t count = processor_->cpucount();
    return (count - start_count_) % period_ >= thresold_;
}


} // namespace core
