/*

The VGA screen.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include <QtWidgets/QGraphicsView>
#include <QtGui/QImage>

#include <memory>
#include <stdint.h>

namespace app {


// The VGA screen.
class Screen : public QGraphicsView {
    Q_OBJECT
public:

    Screen(int width, int height);


    // Update the image screen.
    void UpdateImageScreen(const uint32_t *screen);

    // Update the screen.
    void UpdateScreen();

    // Calculate minimum size of the screen.
    void CalculateSize(double scale = 0);


private:

    // Prevent scroll event.
    void wheelEvent(QWheelEvent *event);


    QGraphicsScene scene_;

    int width_, height_;
    std::shared_ptr<QImage> screen_image_;
};


} // namespace app
