/*

The MIPS processor.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "core/processor.h"

#include <QtCore/QtGlobal>

#include <string.h>

namespace core {


// Constructor
Processor::Processor(Bus &bus)
    : bus_(bus)
{
    Reset();
}



// Reset the processor.
void Processor::Reset()
{
    cpucount_ = 0;

    pc = 0;
    memset(regs, 0, sizeof(regs));
}



// Process the next instruction.
void Processor::ProcessNext()
{
    d.Disassemble(bus_.GetValue(pc));
    regs[0] = 0;

    pc += 4;
    cpucount_ += 3;

    switch(d.opcode) {
        case 0b000000: ProcessSpecialInst(); break;
        case 0b000001: ProcessRegImmInst(); break;
        default:       ProcessNormalInst(); break;  
    }
}



// Process a "normal" instruction.
void Processor::ProcessNormalInst()
{
    switch(d.opcode) {
        case 0b000010: // j
            pc = (pc & 0x1E000000) | (d.address << 2);
            cpucount_ += 1; break;

        case 0b000011: // jal
            regs[31] = pc;
            pc = (pc & 0x1E000000) | (d.address << 2);
            cpucount_ += 2; break;

        case 0b000100: // beq
            if (regs[d.rs] == regs[d.rt]) pc += d.signedimm << 2;
            cpucount_ += 2; break;

        case 0b000101: // bne
            if (regs[d.rt] != regs[d.rs]) pc += d.signedimm << 2;
            cpucount_ += 2; break;

        case 0b000110: // blez
            if ((int32_t)regs[d.rs] <= 0) pc += d.signedimm << 2;
            cpucount_ += 2; break;

        case 0b000111: // bgtz
            if ((int32_t)regs[d.rs] > 0) pc += d.signedimm << 2;
            cpucount_ += 2; break;

        case 0b001000: // addi
        case 0b001001: // addiu
            regs[d.rt] = regs[d.rs] + d.signedimm; break;

        case 0b001010: // slti
            regs[d.rt] = (int32_t)regs[d.rs] < d.signedimm ? 1 : 0;
            cpucount_ += 1; break;

        case 0b001011: // sltiu
            regs[d.rt] = regs[d.rs] < d.signedimm ? 1 : 0;
            cpucount_ += 1; break;

        case 0b001100: // andi
            regs[d.rt] = regs[d.rs] & d.immediate; break;

        case 0b001101: // ori
            regs[d.rt] = regs[d.rs] | d.immediate; break;

        case 0b001110: // xori
            regs[d.rt] = regs[d.rs] ^ d.immediate; break;

        case 0b001111: // lui
            regs[d.rt] = d.signedimm << 16; break;

        case 0b100011: // lw
            regs[d.rt] = bus_.GetValue(regs[d.rs] + d.signedimm);
            cpucount_ += 3; break;

        case 0b101011: // sw
            bus_.SetValue(regs[d.rs] + d.signedimm, regs[d.rt]);
            cpucount_ += 3; break;

        default:
            qWarning("Unknown instruction with OPCODE = %#01X at PC = %#04X.", d.opcode, pc-4);
    }
}



// Process a special instruction.
void Processor::ProcessSpecialInst()
{
    switch(d.func) {
        case 0b000000: // sll
            regs[d.rd] = regs[d.rt] << d.shamt; break;

        case 0b000010: // srl
            regs[d.rd] = regs[d.rt] >> d.shamt; break;

        case 0b000011: // sra
            regs[d.rd] = (uint32_t)((int32_t)regs[d.rt] >> d.shamt); break;

        case 0b000100: // sllv
            regs[d.rd] = regs[d.rt] << regs[d.rs]; break;

        case 0b000110: // srlv
            regs[d.rd] = regs[d.rt] >> regs[d.rs]; break;

        case 0b000111: // srav
            regs[d.rd] = (uint32_t)((int32_t)regs[d.rt] >> regs[d.rs]); break;

        case 0b001000: // jr
            pc = regs[d.rs];
            cpucount_ += 1; break;

        case 0b001001: // jalr
            regs[31] = pc;
            pc = regs[d.rs];
            cpucount_ += 2; break;

        case 0b100000: // add
        case 0b100001: // addu
            regs[d.rd] = regs[d.rs] + regs[d.rt]; break;

        case 0b100010: // sub
        case 0b100011: // subu
            regs[d.rd] = regs[d.rs] - regs[d.rt]; break;

        case 0b100100: // and
            regs[d.rd] = regs[d.rs] & regs[d.rt]; break;

        case 0b100101: // or
            regs[d.rd] = regs[d.rs] | regs[d.rt]; break;

        case 0b100110: // xor
            regs[d.rd] = regs[d.rs] ^ regs[d.rt]; break;

        case 0b100111: // nor
            regs[d.rd] = ~(regs[d.rs] | regs[d.rt]); break;

        case 0b101010: // slt
            regs[d.rd] = ((int32_t)regs[d.rs] - (int32_t)regs[d.rt]) < 0 ? 1 : 0;
            cpucount_ += 1; break;

        case 0b101011: // sltu
            regs[d.rd] = (int32_t)(regs[d.rs] - regs[d.rt]) < 0 ? 1 : 0;
            cpucount_ += 1; break;

        default:
            qWarning("Unknown 'special' instruction with FUNC = %#01X at PC = %#04X.", d.func, pc-4);
    }
}



// Process a reg-imm instruction.
void Processor::ProcessRegImmInst()
{
    switch(d.rt) {
        case 0b10000: // bltzal
            regs[31] = pc;
            cpucount_ += 1;
            // Use BLTZ instruction.

        case 0b00000: // bltz
            if ((int32_t)regs[d.rs] < 0) pc += d.signedimm << 2;
            cpucount_ += 2; break;

        case 0b10001: // bgezal
            regs[31] = pc;
            cpucount_ += 1;
            // Use BGEZ instruction.

        case 0b00001: // bgez
            if ((int32_t)regs[d.rs] >= 0) pc += d.signedimm << 2;
            cpucount_ += 2; break;

        default:
            qWarning("Unknown 'regimm' instruction with RT = %#01X at PC = %#04X.", d.rt, pc-4);
    }
}


} // namespace core
