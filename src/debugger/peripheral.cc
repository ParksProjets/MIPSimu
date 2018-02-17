/*

The debugger peripheral.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "debugger/peripheral.h"

#include <stdio.h>

namespace debugger {

namespace {


// Address of the 'new-line' port
constexpr uint32_t kNewLineAddress = 30 * 4;


} // anonymous namespace



// Set a value at the address given.
void Peripheral::SetValue(uint32_t addr, uint32_t value)
{
    if (addr < kNewLineAddress)
        printf("0x%02X = %d\n", addr, value);

    else if (addr == kNewLineAddress)
        printf("\n");

    else
        paused = true;
}



// Get the value the address given.
uint32_t Peripheral::GetValue(uint32_t addr)
{
    return 0;
}


} // namespace debugger
