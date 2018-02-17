/*

Test the disassembler from core module.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include <QtTest/QtTest>

#include "core/disassembler.h"


// Test class.
class TestCoreDisassembler : public QObject {
    Q_OBJECT

private slots:
    void RegularRTypeTest();
    void ShiftRTypeTest();
    void ITypeTest();
    void JTypeTest();
};



// Test a regular RType instruction.
void TestCoreDisassembler::RegularRTypeTest()
{
    core::Disassembler d;
    d.Disassemble(0b00000001001010100100000000100001); // addu

    QVERIFY(d.rs == 9);
    QVERIFY(d.rt == 10);
    QVERIFY(d.rd == 8);
    QVERIFY(d.shamt == 0);
    QVERIFY(d.func == 33);
    QVERIFY(d.opcode == 0);
}



// Test a RType shift instruction.
void TestCoreDisassembler::ShiftRTypeTest()
{
    core::Disassembler d;
    d.Disassemble(0b00000000000010010100001111000000); // sll

    QVERIFY(d.rt == 9);
    QVERIFY(d.rd == 8);
    QVERIFY(d.shamt == 15);
    QVERIFY(d.func == 0);
    QVERIFY(d.opcode == 0);
}
    


// Test an IType instruction.
void TestCoreDisassembler::ITypeTest()
{
    core::Disassembler d;
    d.Disassemble(0b00110101001010000000000001001110); // ori

    QVERIFY(d.rs == 9);
    QVERIFY(d.rt == 8);
    QVERIFY(d.signedimm == 78);
    QVERIFY(d.opcode == 13);
}



// Test a JType instruction.
void TestCoreDisassembler::JTypeTest()
{
    core::Disassembler d;
    d.Disassemble(0b00001000000000000010011100010000); // j
    
    QVERIFY(d.address == 10000);
    QVERIFY(d.opcode == 2);
}


// Run the unit test.
QTEST_MAIN(TestCoreDisassembler)
#include "test_core_disassembler.moc"
