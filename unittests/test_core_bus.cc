/*

Test the bus from core module.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include <QtTest/QtTest>

#include "core/bus.h"
#include "utils/range.h"


// Test class.
class TestCoreBus : public QObject {
    Q_OBJECT

private slots:
    void SimpleTest();
    void MultipleGapTest();
};



// Mock a peripheral.
class MockPeripheral : public core::Peripheral {
public:

    // Set a value at the address given.
    void SetValue(uint32_t addr, uint32_t value) override {
        memory[addr] = value; }

    // Get a value from an address.
    uint32_t GetValue(uint32_t addr) override {
        return memory[addr]; }

    uint32_t memory[32];
};



// Test a simple data bus.
void TestCoreBus::SimpleTest()
{
    core::Bus bus;

    MockPeripheral periph;
    bus.Add(&periph, utils::range<uint32_t>(0, 31));

    bus.SetValue(1, 0xAA);
    bus.SetValue(2, 0xABCDEF);
    bus.SetValue(4, 0x1234);
    bus.SetValue(31, bus.GetValue(2));
    bus.SetValue(32, 78);

    QVERIFY(periph.memory[1] == 0xAA);
    QVERIFY(bus.GetValue(4) == 0x1234);
    QVERIFY(bus.GetValue(31) == 0xABCDEF);
    QVERIFY(bus.GetValue(32) == 0);
}



// Test a multiple data bus with gaps.
void TestCoreBus::MultipleGapTest()
{
    core::Bus bus;

    MockPeripheral periph;
    MockPeripheral periph2;
    bus.Add(&periph, utils::range<uint32_t>(0, 31));
    bus.Add(&periph2, utils::range<uint32_t>(15000, 15013));

    bus.SetValue(1, 0xAA);
    bus.SetValue(4, 0x1234);
    bus.SetValue(15000, 0x7822);
    bus.SetValue(15013, 0xAA00AA);

    QVERIFY(periph.memory[1] == 0xAA);
    QVERIFY(bus.GetValue(4) == 0x1234);
    QVERIFY(periph2.memory[0] == 0x7822);
    QVERIFY(periph2.memory[13] == 0xAA00AA);
    QVERIFY(bus.GetValue(15013) == 0xAA00AA);
}



// Run the unit test.
QTEST_MAIN(TestCoreBus)
#include "test_core_bus.moc"
