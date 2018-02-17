/*

Manage the keyboard.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#pragma once

#include <QtCore/QEvent>
#include <QtGui/QKeyEvent>

#include <atomic>

namespace app {


// Filter keyboard events.
class KeyboardFilter : public QObject {
    Q_OBJECT
public:

    KeyboardFilter();


    // Install the window filter.
    void Install();

    // Set 'enabled' value.
    void SetEnabled(bool enabled);

    // Get the value of the buttons.
    uint32_t GetButtonValue();


    // When a window event comes.
    bool eventFilter(QObject *object, QEvent *event) override;


    // Getters
    bool arrow_left() const { return arrow_left_; }
    bool arrow_down() const { return arrow_down_; }
    bool arrow_right() const { return arrow_right_; }


private:

    // Is the filter enabled?
    std::atomic<bool> enabled_;

    // Arrow values.
    std::atomic<bool> arrow_left_;
    std::atomic<bool> arrow_down_;
    std::atomic<bool> arrow_right_;
};


} // namespace app
