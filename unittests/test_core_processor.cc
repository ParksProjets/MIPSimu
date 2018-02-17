/*

Test the processor from core module.

Useful ressources:
  http://shell-storm.org/online/Online-Assembler-and-Disassembler/
  https://www.eg.bucknell.edu/~csci320/mips_web/

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include <QtTest/QtTest>

#include "core/processor.h"
#include "core/bus.h"
#include "utils/range.h"

namespace core {


// Test class.
class TestCoreProcessor : public QObject {
    Q_OBJECT

private slots:
    void SimpleProgram();
    void Fibonacci();
};



// Mock the RAM.
class MockRam : public core::Peripheral {
public:

    MockRam(uint32_t *memory) : memory_{memory} {}

    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value) override {
        memory_[addr >> 2] = value; }

    // Get a value from an address.
    uint32_t GetValue(uint32_t addr) override {
        return memory_[addr >> 2]; }

private:
    uint32_t *memory_;
};



// Test a simple program.
void TestCoreProcessor::SimpleProgram()
{
    core::Bus bus;
    core::Processor processor(bus);

    uint32_t memory[128] = {
        0x01AD6826, // xor $13, $13, $13
        0x240D0002, // li $13, 2  =  addiu $13 $0 0x2
        0x21AD0004, // addi $13, $13, 4
        0xADAD00FE, // sw $13, 254($13)
        0x08000002, // j 0x01
    };

    MockRam ram(memory);
    bus.Add(&ram, utils::range<uint32_t>(0, 511));

    for (int i = 0; i < 2 + 3*3; i++)
        processor.ProcessNext();

    QCOMPARE((int)processor.cpucount(), 3 + 3 + 3 * (3 + 6 + 4));
    QCOMPARE(processor.pc, (uint32_t)8);
    QCOMPARE(processor.regs[13], (uint32_t)14);
    QCOMPARE(bus.GetValue(260), (uint32_t)6);
    QCOMPARE(bus.GetValue(268), (uint32_t)14);

    for (int i = 0; i < 20*3 + 1; i++)
        processor.ProcessNext();

    QCOMPARE((int)processor.cpucount(), 3 + 3 + 23 * (3 + 6 + 4) + 3);
    QCOMPARE(processor.pc, (uint32_t)12);
    QCOMPARE(processor.regs[13], (uint32_t)98);
    QCOMPARE(bus.GetValue(312), (uint32_t)58);
    QCOMPARE(bus.GetValue(344), (uint32_t)90);
}



// Calaculate Fibonacci terms.
void TestCoreProcessor::Fibonacci()
{
    core::Bus bus;
    core::Processor processor(bus);

    uint32_t memory[256] = {
        0x02805025, // fibo: move $10, $20
        0x240B0001, //       li $11, 1
        0x240C0001, //       li $12, 1
        0x016C6820, // loop: add $13, $11, $12
        0x01805825, //       move $11, $12
        0x01A06025, //       move $12, $13
        0x214AFFFF, //       addi $10, $10, -1
        0x1540FFFB, //       bne $10, $0, loop
        0xAC0D0200, // save: sw $13, 512($0)
        0x08000009, // wait: j wait
    };

    MockRam ram(memory);
    bus.Add(&ram, utils::range<uint32_t>(0, 1023));

    processor.pc = 0;
    processor.regs[20] = 11; // F(13) = 233
    for (int i = 0; i < 800; i++) processor.ProcessNext();

    QCOMPARE(bus.GetValue(512), (uint32_t)233);

    processor.pc = 0;
    processor.regs[20] = 23; // F(25) = 75025
    for (int i = 0; i < 2000; i++) processor.ProcessNext();

    QCOMPARE(bus.GetValue(512), (uint32_t)75025);
}



} // namespace core

// Run the unit test.
QTEST_MAIN(core::TestCoreProcessor)
#include "test_core_processor.moc"
