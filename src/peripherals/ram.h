/*

The CPU RAM.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "core/bus.h"

#include <memory>

namespace peripherals {


// The CPU RAM.
class Ram : public core::Peripheral {
public:

    // Allocate the RAM memory.
    void Allocate(uint32_t bytes);


    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value) override;

    // Get a value from an address.
    uint32_t GetValue(uint32_t addr) override;


    // Get the RAM buffer.
    uint32_t *buffer() { return data_.get(); }

    // Get the RAM size.
    uint32_t size() { return size_; }


private:

    std::unique_ptr<uint32_t[]> data_;

    uint32_t size_;
};


} // namespace peripherals
