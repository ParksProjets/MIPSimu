/*

The whole system.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "external/screen.h"

#include "core/bus.h"
#include "core/processor.h"

#include "peripherals/ram.h"
#include "peripherals/external.h"
#include "peripherals/timer.h"

namespace app {


// The frequency of the clock (50 MHz).
constexpr int kClockFrequency = 50 * 1000 * 1000;

// The number desired of FPS.
constexpr int kFramePerSecond = 30;



// The whole system.
class System {
public:

    System();


    // Initialize the system.
    void Initialize(unsigned char *u8mem, unsigned char *u8pixels, int offset = 0);

    // Update the system.
    void Update();


    // Getters
    int offset() { return offset_; }
    Screen &screen() { return screen_; }

    core::Bus &bus() { return bus_; }
    core::Processor &processor() { return processor_; }

    peripherals::Ram &ram() { return ram_; }
    peripherals::External &external() { return external_; }
    peripherals::Timer &timer() { return timer_; }


private:

    // Start cycle offset.
    int offset_;

    // VGA screen and main window.
    Screen screen_;

    // Core devices.
    core::Bus bus_;
    core::Processor processor_;

    // External devices
    peripherals::Ram ram_;
    peripherals::Ram ram2_;
    peripherals::External external_;
    peripherals::Timer timer_;
};


} // namespace app
