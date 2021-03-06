/*

The whole system.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "system/system.h"
#include "system/sysworker.h"
#include "utils/range.h"

#include <QtCore/QCoreApplication>

#include <stdio.h>

namespace app {


// Constructor
System::System(MainWindow &window, bool debug, int offset)
    : window_{window},
      screen_{kScreenWidth, kScreenHeight},
      processor_{bus_},
      loader_{ram_, ram2_},
      debug_{debug},
      offset_{offset}
{
    window.SetScreen(&screen_);

    if (debug_) {
        printf("Debug mode enabled\n");
        printf("Using start cycle offset of %d\n\n", offset_);
    }

    QObject::connect(qApp, &QCoreApplication::aboutToQuit, this, &System::Stop);
}



// Initialize the system.
void System::Initialize()
{
    // Install keyboard filter.
    keyboard_.Install();

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

    // If we are in debug mode: add the debug peripheral.
    if (debug_)
        bus_.Add(&debugger_.peripheral(), utils::range<uint32_t>(0x5000, 0x507F));
}



// Start the system.
void System::Start()
{
    if (thread_.isRunning())
        return;
    
    SystemWorker *worker = new SystemWorker(*this);
    worker->moveToThread(&thread_);

    keyboard_.SetEnabled(true);

    if (debug_)
        QObject::connect(&thread_, &QThread::started, worker, &SystemWorker::RunUpdateLoopDebug);
    else
        QObject::connect(&thread_, &QThread::started, worker, &SystemWorker::RunUpdateLoop);

    thread_.start();
}



// Stop the system.
void System::Stop()
{
    if (!thread_.isRunning())
        return;

    keyboard_.SetEnabled(false);

    thread_.requestInterruption();
    thread_.quit();
    thread_.wait();
}


} // namespace app
