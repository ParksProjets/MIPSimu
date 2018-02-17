/*

Instruction disassembler.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include <stdint.h>

namespace core {


// Instruction disassembler.
class Disassembler {
public:

    // Disassemble an instruction.
    void Disassemble(uint32_t code);


    // Instruction parameters.
    uint32_t opcode;
    uint32_t rs, rt, rd;
    uint32_t shamt, func;
    uint32_t immediate;
    uint32_t signedimm;
    uint32_t address;
};


} // namespace core
