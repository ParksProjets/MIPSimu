/*

The MIPS processor.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "core/processor.h"
#include "core/debug.h"

#include <string.h>

namespace core {


// Get information from the instruction code.
#define GET_OPCODE(code) (((code) >> 26) & 0b111111)
#define GET_FUNC(code) ((code) & 0b111111)
#define GET_SHAMT(code) (((code) >> 6) & 0b11111)

#define GET_RD(code) (((code) >> 11) & 0b11111)
#define GET_RT(code) (((code) >> 16) & 0b11111)
#define GET_RS(code) (((code) >> 21) & 0b11111)

#define GET_IMM(code) ((code) & 0xffff)
#define GET_SIMM(code) (((code) & 0x8000) == 0 ? ((code) & 0xffff) : \
    ((code) & 0xffff) | 0xffff0000)
#define GET_ADDR(code) ((code) & 0x3ffffff)



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
    uint32_t c = bus_.GetValue(pc);
    pc += 4;

    uint32_t opcode = GET_OPCODE(c);


    switch(opcode) {

        // Special instruction.
        case 0b000000: switch(GET_FUNC(c)) {
            case 0b000000: // sll
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RT(c)] << GET_SHAMT(c); break;

            case 0b000010: // srl
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RT(c)] >> GET_SHAMT(c); break;

            case 0b000011: // sra
                cpucount_ += 3;
                regs[GET_RD(c)] = (uint32_t)((int32_t)regs[GET_RT(c)] >> GET_SHAMT(c)); break;

            case 0b000100: // sllv
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RT(c)] << regs[GET_RS(c)]; break;

            case 0b000110: // srlv
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RT(c)] >> regs[GET_RS(c)]; break;

            case 0b000111: // srav
                cpucount_ += 3;
                regs[GET_RD(c)] = (uint32_t)((int32_t)regs[GET_RT(c)] >> regs[GET_RS(c)]); break;

            case 0b001000: // jr
                cpucount_ += 4;
                pc = regs[GET_RS(c)]; break;

            case 0b001001: // jalr
                cpucount_ += 5;
                regs[31] = pc;
                pc = regs[GET_RS(c)]; break;

            case 0b100000: // add
            case 0b100001: // addu
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RS(c)] + regs[GET_RT(c)]; break;

            case 0b100010: // sub
            case 0b100011: // subu
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RS(c)] - regs[GET_RT(c)]; break;

            case 0b100100: // and
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RS(c)] & regs[GET_RT(c)]; break;

            case 0b100101: // or
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RS(c)] | regs[GET_RT(c)]; break;

            case 0b100110: // xor
                cpucount_ += 3;
                regs[GET_RD(c)] = regs[GET_RS(c)] ^ regs[GET_RT(c)]; break;

            case 0b100111: // nor
                cpucount_ += 3;
                regs[GET_RD(c)] = ~(regs[GET_RS(c)] | regs[GET_RT(c)]); break;

            case 0b101010: // slt
                regs[GET_RD(c)] = ((int32_t)regs[GET_RS(c)] - (int32_t)regs[GET_RT(c)]) < 0 ? 1 : 0;
                cpucount_ += 4; break;

            case 0b101011: // sltu
                regs[GET_RD(c)] = (int32_t)(regs[GET_RS(c)] - regs[GET_RT(c)]) < 0 ? 1 : 0;
                cpucount_ += 4; break;

            default:
                warn("Unknown 'special' instruction with FUNC = %#01X at PC = %#04X.",
                    GET_FUNC(c), pc-4);
                warn("Word: %#08X.", bus_.GetValue(pc - 4));
        } break;


        // Reg-imm instruction.
        case 0b000001: switch(GET_RT(c)) {
            case 0b10000: // bltzal
                regs[31] = pc;
                cpucount_ += 1;
                // Use BLTZ instruction.

            case 0b00000: // bltz
                if ((int32_t)regs[GET_RS(c)] < 0) pc += GET_SIMM(c) << 2;
                cpucount_ += 5; break;

            case 0b10001: // bgezal
                regs[31] = pc;
                cpucount_ += 1;
                // Use BGEZ instruction.

            case 0b00001: // bgez
                if ((int32_t)regs[GET_RS(c)] >= 0) pc += GET_SIMM(c) << 2;
                cpucount_ += 5; break;

            default:
                warn("Unknown 'regimm' instruction with RT = %#01X at PC = %#04X.",
                    GET_RT(c), pc-4);
                warn("Word: %#08X.", bus_.GetValue(pc - 4));
        } break;


        // Normal instruction.
        default: switch(opcode) {
            case 0b000010: // j
                pc = (pc & 0x1E000000) | (GET_ADDR(c) << 2);
                cpucount_ += 4; break;

            case 0b000011: // jal
                regs[31] = pc;
                pc = (pc & 0x1E000000) | (GET_ADDR(c) << 2);
                cpucount_ += 5; break;

            case 0b000100: // beq
                if (regs[GET_RS(c)] == regs[GET_RT(c)]) pc += GET_SIMM(c) << 2;
                cpucount_ += 5; break;

            case 0b000101: // bne
                if (regs[GET_RT(c)] != regs[GET_RS(c)]) pc += GET_SIMM(c) << 2;
                cpucount_ += 5; break;

            case 0b000110: // blez
                if ((int32_t)regs[GET_RS(c)] <= 0) pc += GET_SIMM(c) << 2;
                cpucount_ += 5; break;

            case 0b000111: // bgtz
                if ((int32_t)regs[GET_RS(c)] > 0) pc += GET_SIMM(c) << 2;
                cpucount_ += 5; break;

            case 0b001000: // addi
            case 0b001001: // addiu
                regs[GET_RT(c)] = regs[GET_RS(c)] + GET_SIMM(c); break;

            case 0b001010: // slti
                regs[GET_RT(c)] = (int32_t)regs[GET_RS(c)] < GET_SIMM(c) ? 1 : 0;
                cpucount_ += 4; break;

            case 0b001011: // sltiu
                regs[GET_RT(c)] = regs[GET_RS(c)] < GET_SIMM(c) ? 1 : 0;
                cpucount_ += 4; break;

            case 0b001100: // andi
                regs[GET_RT(c)] = regs[GET_RS(c)] & GET_IMM(c);
                cpucount_ += 3; break;

            case 0b001101: // ori
                regs[GET_RT(c)] = regs[GET_RS(c)] | GET_IMM(c);
                cpucount_ += 3; break;

            case 0b001110: // xori
                regs[GET_RT(c)] = regs[GET_RS(c)] ^ GET_IMM(c);
                cpucount_ += 3; break;

            case 0b001111: // lui
                regs[GET_RT(c)] = GET_SIMM(c) << 16;
                cpucount_ += 3; break;

            case 0b100011: // lw
                regs[GET_RT(c)] = bus_.GetValue(regs[GET_RS(c)] + GET_SIMM(c));
                cpucount_ += 6; break;

            case 0b101011: // sw
                bus_.SetValue(regs[GET_RS(c)] + GET_SIMM(c), regs[GET_RT(c)]);
                cpucount_ += 6; break;

            default:
                warn("Unknown instruction with OPCODE = %#01X at PC = %#04X.", opcode, pc-4);
                warn("Word: %#08X.", bus_.GetValue(pc - 4));
        } break;
    }
}


} // namespace core
