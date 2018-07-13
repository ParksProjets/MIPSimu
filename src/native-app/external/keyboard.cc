/*

Manage the keyboard.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "external/keyboard.h"

#include <QtWidgets/QApplication>

namespace app {


// Constructor.
KeyboardFilter::KeyboardFilter()
    : arrow_left_{false},
      arrow_down_{false},
      arrow_right_{false}
{
}



// Install the window filter.
void KeyboardFilter::Install()
{
    QApplication::instance()->installEventFilter(this);
}



// Set 'enabled' value.
void KeyboardFilter::SetEnabled(bool enabled)
{
    enabled_ = enabled;
}



// Get the value of the buttons.
uint32_t KeyboardFilter::GetButtonValue()
{
    return
        arrow_left_ << 18 |
        arrow_down_ << 17 |
        arrow_right_ << 16;
}



// When a window event comes.
bool KeyboardFilter::eventFilter(QObject *, QEvent *event)
{
    if (!enabled_)
        return false;

    if (event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease)
        return false;

    QKeyEvent *key_event = static_cast<QKeyEvent *>(event);
    bool value = (event->type() == QEvent::KeyPress);

    switch (key_event->key()) {
        default: return false;
        case Qt::Key_Left:  arrow_left_ = value; break;
        case Qt::Key_Down:  arrow_down_ = value; break;
        case Qt::Key_Right: arrow_right_ = value; break;
    }

    return true;
}


} // namespace app

