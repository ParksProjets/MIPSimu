/*

Instruction disassembler.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "core/disassembler.h"

#include <string>
#include <stdint.h>

namespace debugger {


// Instruction disassembler.
class Disassembler {
public:

    Disassembler(bool named_register = false);


    // Get a string representation of an instruction.
    std::string Disassemble(uint32_t code);


private:

    // Disassemble a 'normal' instruction.
    std::string DisassembleNormal();

    // Disassemble a 'special' instruction.
    std::string DisassembleSpecial();


    const char **registers_;
    core::Disassembler d;
};


} // namespace debugger
