/*

The main window.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include "external/screen.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

#include <atomic>
#include <stdint.h>

namespace app {


class MainWindow : public QWidget {
    Q_OBJECT
public:

    MainWindow(double scale = 0);


    // Set the VGA screen.
    void SetScreen(Screen *screen);

    // Update the title with the LEDs value.
    void UpdateTitle();

    // Set the value of the leds.
    void SetLedValue(uint8_t value);


private:

    // Calculate minimum size of the window.
    void CalculateResize();


    // Prevent scroll event.
    void wheelEvent(QWheelEvent *event);

    // When we close this window: stop the applcation.


    QHBoxLayout *layout_;

    double scale_;
    Screen *screen_;
    std::atomic<uint8_t> leds_;
};


} // namespace app
