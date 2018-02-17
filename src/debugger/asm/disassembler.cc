/*

Instruction disassembler.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "debugger/asm/disassembler.h"

#include <stdio.h>
#include <memory>

namespace debugger {

namespace {


// Named registers.
const char *kNamedRegisters[] = {
    "$zero", "$at", "$v0", "$v1",
    "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1",
    "$gp", "$sp", "$fp", "$ra"
};


// Unamed registers.
const char *kUnamedRegisters[] = {
    "$0",  "$1",  "$2",  "$3",  "$4",  "$5",  "$6",  "$7",
    "$8",  "$9",  "$10", "$11", "$12", "$13", "$14", "$15",
    "$16", "$17", "$18", "$19", "$20", "$21", "$22", "$23",
    "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31"
};


// 'Normal' instructions.
const char *kNormalInstrs[64] = {
    NULL,   NULL,    "j",    "jal",   "beq",  "bne", "blez", "bgtz",
	"addi", "addiu", "slti", "sltiu", "andi", "ori", "xori", "lui",
    NULL,   NULL,    NULL,   NULL,    NULL,   NULL,  NULL,   NULL,
    NULL,   NULL,    NULL,   NULL,    NULL,   NULL,  NULL,   NULL,
	"lb",   "lh",    NULL,   "lw",    "lbu",  "lhu", NULL,   NULL,
	"sb",   "sh",    NULL,   "sw",    NULL,   NULL,  NULL,   NULL,
};


// 'Special' instructions.
const char *kSpecialInstrs[64] = {
    "sll",  NULL,    "srl",  "sra", "sllv",    NULL,    "srlv", "srav",
    "jr",   "jalr",  NULL,   NULL,  "syscall", "break", NULL,   NULL,
    "mfhi", "mthi",  "mflo", "mtlo", NULL,     NULL,    NULL,   NULL,
    "mult", "multu", "div",  "divu", NULL,     NULL,    NULL,   NULL,
    "add",  "addu",  "sub",  "subu", "and",    "or",    "xor",  "nor",
    NULL,   NULL,    "slt",  "sltu", NULL,     NULL,    NULL,   NULL,
};


// 'RegImm' instructions.
const char *kRegImmInstrs[32] = {
    "bltz",   "bgez",   NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
    "bltzal", "bgezal", NULL,  NULL,  NULL,  NULL,  NULL,  NULL,
};



// Format a string.
template<typename ...Args>
std::string Format(const std::string &msg, Args ...args)
{
    size_t size = snprintf(nullptr, 0, msg.c_str(), args...) + 1;
    auto buffer = std::make_unique<char[]>(size);

    snprintf(buffer.get(), size, msg.c_str(), args...);
    return std::string(buffer.get(), buffer.get() + size - 1);
}


} // anonymous namespace



// Constructor.
Disassembler::Disassembler(bool named_register)
{
    registers_ = named_register ? kNamedRegisters : kUnamedRegisters;
}



// Disassemble an instruction.
std::string Disassembler::Disassemble(uint32_t code)
{
    d.Disassemble(code);

    if (d.opcode == 0)
        return DisassembleSpecial();
    else
        return DisassembleNormal();
}



// Disassemble a 'normal' instruction.
std::string Disassembler::DisassembleNormal()
{
    const char *name = (d.opcode == 1) ? kRegImmInstrs[d.rt] : kNormalInstrs[d.opcode];
    if (name == nullptr)
        return Format("Unknown instruction with OPCODE = %#01X", d.opcode);

    const char *rs = registers_[d.rs];
    const char *rt = registers_[d.rt];

    switch (d.opcode) {
        case 0b000001: // bltz, bgez, bltzal, bgezal
        case 0b000110: // blez
        case 0b000111: // bgtz
            return Format("%s %s, %#X", name, rs, d.immediate);

        case 0b000010: // j
        case 0b000011: // jal
            return Format("%s %#X", name, d.address << 2);

        case 0b001111: // lui
            return Format("%s %s, %#X", name, rt, d.immediate);

        case 0b100000: // lb
        case 0b100001: // lh
        case 0b100011: // lw
        case 0b100100: // lbu
        case 0b100101: // lhu
        case 0b101000: // sb
        case 0b101001: // sh
        case 0b101011: // sb
            return Format("%s %s %#X(%s)", name, rt, d.signedimm, rs);

        case 0b000100: // beq
        case 0b000101: // sh
            return Format("%s %s, %s, %#X", name, rt, rs, d.immediate);

        default:
           return Format("%s %s, %s, %#X", name, rt, rs, d.immediate); 
    }
}



// Disassemble a 'special' instruction.
std::string Disassembler::DisassembleSpecial()
{
    const char *name = kSpecialInstrs[d.func];
    if (name == nullptr)
        return Format("Unknown special instruction with FUNC = %#01X", d.func);

    const char *rs = registers_[d.rs];
    const char *rt = registers_[d.rt];
    const char *rd = registers_[d.rd];

    switch (d.func) {
        case 0b000000: // sll
        case 0b000010: // srl
        case 0b000011: // sra
            return Format("%s %s, %s, %d", name, rd, rt, d.shamt);

        case 0b001000: // jr
        case 0b001001: // jalr
            return Format("%s %s", name, rs);

        case 0b001100: // syscall
        case 0b001101: // break
            return name;

        case 0b010000: // mfhi
        case 0b010001: // mthi
        case 0b010010: // mflo
        case 0b010011: // mtlo
            return Format("%s %s", name, rd);

        case 0b011000: // mult
        case 0b011001: // multu
        case 0b011010: // div
        case 0b011011: // divu
            return Format("%s %s, %s", name, rs, rt);

        default:
            return Format("%s %s, %s, %s", name, rd, rs, rt);
    }
}


} // namespace debugger
