/*

The system worker.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "app/system.h"

#include <QtCore/QObject>

namespace app {


// The system worker.
class SystemWorker : public QObject {
    Q_OBJECT
public:

    SystemWorker(System &system);


    // Run the update loop.
    void RunUpdateLoop();

    // Run the update loop in debug mode.
    void RunUpdateLoopDebug();


private:

    // Start cycle offset.
    qint64 offset_;

    // VGA screen and main window.
    Screen &screen_;
    MainWindow &window_;
    KeyboardFilter &keyboard_;

    // Peripherals.
    peripherals::Vga &vga_;
    peripherals::External &external_;

    // Processor.
    core::Processor &processor_;


signals:

    void RenderGui();
};


} // namespace app
