/*

The VGA peripheral.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "core/bus.h"

#include <memory>

namespace peripherals {


// The VGA peripheral.
class Vga : public core::Peripheral {
public:

    // Allocate the video RAM memory.
    void Allocate(int width, int height);


    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value) override;

    // Get a value from an address.
    uint32_t GetValue(uint32_t addr) override;


    // Get the video buffer.
    uint32_t *buffer() { return (uint32_t *)data_.get(); }


private:

    std::unique_ptr<uint16_t[]> data_;
};


} // namespace peripherals
