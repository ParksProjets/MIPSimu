/*

MIPSimu debugger.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "debugger/peripheral.h"
#include "debugger/asm/disassembler.h"

namespace debugger {


// MIPSimu debugger.
class Debugger {
public:


    // Getters
    Disassembler &disassembler() { return disassembler_; }
    Peripheral &peripheral() { return peripheral_; }


private:

    // Instruction disassembler.
    Disassembler disassembler_;

    // Debug peripheral.
    Peripheral peripheral_;
};


} // namespace debugger
