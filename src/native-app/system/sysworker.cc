/*

The system worker.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "app/sysworker.h"

#include <QtCore/QThread>
#include <QtCore/QElapsedTimer>

namespace app {

namespace {


// Time to wait between frames.
constexpr qint64 delay = 1000 / kFramePerSecond;

// Instructions per milliseconds.
constexpr qint64 ipms = kClockFrequency / 1000;
constexpr int ipf = kClockFrequency / kFramePerSecond;


} // anonymous namespace



// Constructor
SystemWorker::SystemWorker(System &system)
    : screen_{system.screen()},
      window_{system.window()},
      keyboard_{system.keyboard()},
      vga_{system.vga()},
      external_{system.external()},
      processor_{system.processor()},
      offset_{system.offset()}
{
    QObject::connect(this, &SystemWorker::RenderGui, &screen_, &Screen::UpdateScreen);
    QObject::connect(this, &SystemWorker::RenderGui, &window_, &MainWindow::UpdateTitle);
}



// Run the update loop.
void SystemWorker::RunUpdateLoop()
{
    QElapsedTimer timer;
    timer.start();

    qint64 current_time = 0;
    qint64 frame_count = 0;
    qint64 elapsed, desired_cpucount;

    while (true) {
        // desired_cpucount = current_time * ipms;
        desired_cpucount = offset_ + (frame_count++) * ipf;

        while (processor_.cpucount() < desired_cpucount)
            processor_.ProcessNext();

        screen_.UpdateImageScreen(vga_.buffer());
        window_.SetLedValue(external_.GetValue(0));
        external_.SetButtonValue(keyboard_.GetButtonValue());

        emit RenderGui();

        // elapsed = current_time;
        // current_time = timer.elapsed();

        // elapsed = delay - (current_time - elapsed);
        elapsed = delay - timer.restart();
        if (elapsed > 0) QThread::msleep(elapsed);
    }
}



// Run the update loop in debug mode.
void SystemWorker::RunUpdateLoopDebug()
{
    QElapsedTimer timer;
    timer.start();

    qint64 frame_count = 0;
    qint64 elapsed, desired_cpucount;

    while (true) {
        desired_cpucount = offset_ + (frame_count++) * ipf;

        while (processor_.cpucount() < desired_cpucount)
            processor_.ProcessNext();

        screen_.UpdateImageScreen(vga_.buffer());
        window_.SetLedValue(external_.GetValue(0));
        external_.SetButtonValue(keyboard_.GetButtonValue());

        emit RenderGui();

        elapsed = delay - timer.restart();
        if (elapsed > 0) QThread::msleep(elapsed);
    }
}


} // namespace app
