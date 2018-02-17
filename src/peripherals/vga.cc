/*

The VGA peripheral.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "peripherals/vga.h"

#include <string.h>

namespace peripherals {


// Allocate the RAM memory.
void Vga::Allocate(int width, int height)
{
    data_.reset(new uint16_t[width * height]);
    memset(data_.get(), 0, width * height * 2);
}


// Set a value at the address given.
void Vga::SetValue(uint32_t addr, uint32_t value)
{
    data_[addr >> 2] = (value & 0xFFFF);
}


// Get a value from an address.
uint32_t Vga::GetValue(uint32_t addr)
{
    return data_[addr >> 2];
}


} // namespace core
