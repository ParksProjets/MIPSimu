/*

The CPU RAM.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "peripherals/ram.h"

namespace peripherals {


// Allocate the RAM memory.
void Ram::Allocate(uint32_t bytes)
{
    data_.reset(new uint32_t[bytes >> 2]);
    size_ = bytes;
}


// Set a value at the address given.
void Ram::SetValue(uint32_t addr, uint32_t value)
{
    data_[addr >> 2] = value;
}


// Get a value from an address.
uint32_t Ram::GetValue(uint32_t addr)
{
    return data_[addr >> 2];   
}


} // namespace core
