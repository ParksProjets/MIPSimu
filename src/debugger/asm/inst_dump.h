/*

Instruction dumper.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include <stdint.h>

namespace debugger {


// Instruction dumper.
class InstDump {
public:

    // Dump an instruction.
    void Dump(uint32_t code);


    // Instruction parameters.
    uint32_t opcode;
    uint32_t rs, rt, rd;
    uint32_t shamt, func;
    uint32_t immediate;
    uint32_t signedimm;
    uint32_t address;
};


} // namespace debugger
