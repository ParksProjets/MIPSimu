/*

Instruction disassembler.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "core/disassembler.h"

namespace core {


// Instruction masks.
static constexpr uint32_t mask6 = 0b111111;
static constexpr uint32_t mask5 = 0b11111;


// Disassemble an instruction.
void Disassembler::Disassemble(uint32_t code)
{
    func = code & mask6;
    shamt = (code >> 6) & mask5;
    rd = (code >> 11) & mask5;
    rt = (code >> 16) & mask5;
    rs = (code >> 21) & mask5;
    opcode = (code >> 26) & mask6;

    immediate = code & 0xffff;
    signedimm = (immediate & 0x8000) == 0 ? immediate : immediate | 0xffff0000;

    address = code & 0x3ffffff;
}


} // namespace core
