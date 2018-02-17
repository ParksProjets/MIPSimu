/*

The MIPS processor.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "core/disassembler.h"
#include "core/bus.h"

namespace core {


// The MIPS processor.
class Processor {
public:

    Processor(Bus &bus);


    // Reset the processor.
    void Reset();

    // Process the next instruction.
    void ProcessNext();


    // Get the CPU count.
    uint64_t cpucount() { return cpucount_; }


private:

    // Make test classes friends.
    friend class TestCoreProcessor;


    // Process a "normal" instruction.
    void ProcessNormalInst();

    // Process a special instruction.
    void ProcessSpecialInst();

    // Process a reg-imm instruction.
    void ProcessRegImmInst();


    // CPU information.
    uint64_t cpucount_;

    // The CPU bus.
    Bus &bus_;

    // Instruction disassembler.
    Disassembler d;

    // CPU registers.
    uint32_t pc;
    uint32_t regs[32];
};


} // namespace core
