/*

The whole system.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "mainwindow.h"
#include "system/memoryloader.h"
#include "external/screen.h"
#include "external/keyboard.h"

#include "core/bus.h"
#include "core/processor.h"

#include "peripherals/ram.h"
#include "peripherals/external.h"
#include "peripherals/timer.h"
#include "peripherals/vga.h"

#include "debugger/debugger.h"

#include <QtCore/QThread>

namespace app {


// The frequency of the clock (50 MHz).
constexpr int kClockFrequency = 50 * 1000 * 1000;

// The number desired of FPS.
constexpr int kFramePerSecond = 30;

// Screen size.
constexpr int kScreenWidth = 320;
constexpr int kScreenHeight = 240;



// The whole system.
class System {
public:

    System(MainWindow &window, bool use_ram2 = false, bool debug = false, int offset = 0);


    // Initialize the system.
    void Initialize();

    // Start the system.
    void Start();

    // Stop the system.
    void Stop();


    // Getters
    bool debug() { return debug_; }
    int offset() { return offset_; }

    MemoryLoader &loader() { return loader_; }
    Screen &screen() { return screen_; }
    MainWindow &window() { return window_; }
    KeyboardFilter &keyboard() { return keyboard_; }

    core::Bus &bus() { return bus_; }
    core::Processor &processor() { return processor_; }

    peripherals::Ram &ram() { return ram_; }
    peripherals::External &external() { return external_; }
    peripherals::Timer &timer() { return timer_; }
    peripherals::Vga &vga() { return vga_; }


private:

    // Are we in debug mode?
    bool debug_;

    // Do we use the second RAM ?
    bool use_ram2_;

    // Start cycle offset.
    int offset_;

    // Update loop worker.
    QThread thread_;

    // VGA screen and main window.
    Screen screen_;
    MainWindow &window_;
    KeyboardFilter keyboard_;

    // RAM loader;
    MemoryLoader loader_;
    debugger::Debugger debugger_;

    // Core devices.
    core::Bus bus_;
    core::Processor processor_;

    // External devices
    peripherals::Ram ram_;
    peripherals::Ram ram2_;
    peripherals::External external_;
    peripherals::Timer timer_;
    peripherals::Vga vga_;
};


} // namespace app
