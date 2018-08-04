/*

The whole system.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "system/system.h"
#include "utils/range.h"

#include <stdio.h>

namespace app {

namespace {


// Instructions per frames.
constexpr int ipf = kClockFrequency / kFramePerSecond;


} // anonymous namespace



// Constructor
System::System()
    : processor_{bus_}
{
}



// Initialize the system.
void System::Initialize(unsigned char *u8mem, unsigned char *u8pixels, int offset)
{
    // Options.
    offset_ = offset;


    // Allocate the needed memory.
    ram_.Attach(u8mem, 0x2000);
    screen_.Attach(u8pixels);

    // Initialize other peripherals.
    timer_.SetProcessor(&processor_);

    // Add external peripherals on the bus.
    bus_.Add(&ram_, utils::range<uint32_t>(0x0, 0x1FFF));
    bus_.Add(&external_, utils::range<uint32_t>(0x4000, 0x4007));
    bus_.Add(&timer_, utils::range<uint32_t>(0x4010, 0x4017));
    bus_.Add(&screen_, utils::range<uint32_t>(0x80000, 0xCAFFF));

    // Allocate the second RAM.
    ram2_.Attach(u8mem + 0x20000, 0x8000);
    bus_.Add(&ram2_, utils::range<uint32_t>(0x20000, 0x27FFF));
}



// Update the system.
void System::Update()
{
    uint64_t desired_cpucount = processor_.cpucount() + ipf;
    if (processor_.cpucount() == 0)
        desired_cpucount += offset_;

    while (processor_.cpucount() < desired_cpucount)
        processor_.ProcessNext();
}


} // namespace app
