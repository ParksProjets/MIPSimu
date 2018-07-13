/*

Test the instruction dumper of the debugger module.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include <QtTest/QtTest>

#include "debugger/asm/inst_dump.h"


// Test class.
class TestDebugInstDump : public QObject {
    Q_OBJECT

private slots:
    void RegularRTypeTest();
    void ShiftRTypeTest();
    void ITypeTest();
    void JTypeTest();
};



// Test a regular RType instruction.
void TestDebugInstDump::RegularRTypeTest()
{
    debugger::InstDump d;
    d.Dump(0b00000001001010100100000000100001); // addu

    QVERIFY(d.rs == 9);
    QVERIFY(d.rt == 10);
    QVERIFY(d.rd == 8);
    QVERIFY(d.shamt == 0);
    QVERIFY(d.func == 33);
    QVERIFY(d.opcode == 0);
}



// Test a RType shift instruction.
void TestDebugInstDump::ShiftRTypeTest()
{
    debugger::InstDump d;
    d.Dump(0b00000000000010010100001111000000); // sll

    QVERIFY(d.rt == 9);
    QVERIFY(d.rd == 8);
    QVERIFY(d.shamt == 15);
    QVERIFY(d.func == 0);
    QVERIFY(d.opcode == 0);
}
    


// Test an IType instruction.
void TestDebugInstDump::ITypeTest()
{
    debugger::InstDump d;
    d.Dump(0b00110101001010000000000001001110); // ori

    QVERIFY(d.rs == 9);
    QVERIFY(d.rt == 8);
    QVERIFY(d.signedimm == 78);
    QVERIFY(d.opcode == 13);
}



// Test a JType instruction.
void TestDebugInstDump::JTypeTest()
{
    debugger::InstDump d;
    d.Dump(0b00001000000000000010011100010000); // j
    
    QVERIFY(d.address == 10000);
    QVERIFY(d.opcode == 2);
}


// Run the unit test.
QTEST_MAIN(TestDebugInstDump)
#include "test_debug_instdump.moc"
