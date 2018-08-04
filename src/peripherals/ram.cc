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
    managed_data_.reset(new uint32_t[bytes >> 2]);
    data_ = managed_data_.get();

    size_ = bytes;
}


// Attach some data to the RAM.
void Ram::Attach(unsigned char *data, uint32_t size)
{
    data_ = reinterpret_cast<uint32_t *>(data);
    size_ = size;
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
