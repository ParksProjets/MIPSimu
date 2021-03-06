/*

The main window.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "external/screen.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtGui/QWheelEvent>

#include <atomic>

namespace app {



// Constructor.
Screen::Screen(int width, int height)
    : width_{width},
      height_{height}
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFocusPolicy(Qt::NoFocus);
    clearFocus();

    setScene(&scene_);
}



// Calculate minimum size of the screen.
void Screen::CalculateSize(double s)
{
    constexpr int kScreenMargins = 40;

    if (s == 0) {
        auto rect = QApplication::desktop()->availableGeometry(this);
        s = (rect.height() - kScreenMargins) / height_;
    }

    scale(s, s);
    resize(s * width_, s * height_);
}



// Update the screen.
void Screen::UpdateImageScreen(const uint32_t *screen)
{
    auto buffer = reinterpret_cast<const uchar *>(screen);
    auto img = std::make_shared<QImage>(buffer, width_, height_, QImage::Format_RGB16);

    std::atomic_store(&screen_image_, img);
}


// Update the screen.
void Screen::UpdateScreen()
{
    scene_.clear();

    auto img = std::atomic_load(&screen_image_);
    scene_.addPixmap(QPixmap::fromImage(*img));

    update(); 
}



// Prevent scroll event.
void Screen::wheelEvent(QWheelEvent *event)
{
    event->accept();
}



} // namespace app
