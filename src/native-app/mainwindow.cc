/*

The main window.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "app/mainwindow.h"

#include <assert.h>

namespace app {

namespace {


// Gnome only supports a small set of unicode emojis.
#ifdef _WIN32
    constexpr char kCharLedOn[] = "🔴";
    constexpr char kCharLedOff[] = "⭕";
#else
    constexpr char kCharLedOn[] = "😀";
    constexpr char kCharLedOff[] = "😶";
#endif


} // anonymous namespace



// Constructor
MainWindow::MainWindow()
    : screen_{nullptr},
      leds_{0b1010}
{
    layout_ = new QHBoxLayout;
    layout_->setSpacing(0);
    layout_->setContentsMargins(0, 0, 0, 0);

    setLayout(layout_);
    UpdateTitle();
}



// Set the VGA screen.
void MainWindow::SetScreen(Screen *screen)
{
    screen_ = screen;
    layout_->addWidget(screen);

    CalculateResize();
}



// Calculate minimum size of the window.
void MainWindow::CalculateResize()
{
    assert(screen_ != nullptr);
    screen_->CalculateSize();

    setMinimumSize(screen_->width() + 2, screen_->height() + 2);
}



// Set the value of the leds.
void MainWindow::SetLedValue(uint8_t value)
{
    leds_ = value;
}



// Update the title with the LEDs value.
void MainWindow::UpdateTitle()
{
    // Unicode characters are at most 4 bytes long.
    static char title[11 + 4 * 4] = "MIPSimu - ";

    uint16_t masked = (leds_ & 0xF) | 0x10;

    char *position = title + 10;
    while (!(masked & 0x100)) {
        strcpy(position, (masked & 8) ? kCharLedOn : kCharLedOff);
        position += (masked & 8 ? sizeof(kCharLedOn) : sizeof(kCharLedOff)) - 1;
        masked <<= 1;
    }

    setWindowTitle(QString::fromUtf8(title));
}



} // namespace app

