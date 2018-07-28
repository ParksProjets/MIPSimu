/*

The whole system.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "system/system.h"
#include "utils/range.h"

#include <stdio.h>

namespace app {


// Constructor
System::System()
    : processor_{bus_}
{
}



// Initialize the system.
void System::Initialize()
{
    // Allocate the needed memory.
    ram_.Allocate(0x2000);
    vga_.Allocate(kScreenWidth, kScreenHeight);

    // Initialize other peripherals.
    timer_.SetProcessor(&processor_);

    // Add external peripherals on the bus.
    bus_.Add(&ram_, utils::range<uint32_t>(0x0, 0x1FFF));
    bus_.Add(&external_, utils::range<uint32_t>(0x4000, 0x4007));
    bus_.Add(&timer_, utils::range<uint32_t>(0x4010, 0x4017));
    bus_.Add(&vga_, utils::range<uint32_t>(0x80000, 0xCAFFF));

    // Allocate the second RAM.
    ram2_.Allocate(0x8000);
    bus_.Add(&ram2_, utils::range<uint32_t>(0x20000, 0x27FFF));
}



// Start the system.
void System::Start()
{
    // TODO.
}


} // namespace app
