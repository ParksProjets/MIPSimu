/*

Entry point of the application.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "system/system.h"

#include <emscripten.h>


// The whole system.
static app::System system_app;



// Initialize the application.
EMSCRIPTEN_KEEPALIVE
extern "C" void Initialize(unsigned char *u8mem, unsigned char *u8pixels)
{
    system_app.Initialize(u8mem, u8pixels, 500000);
}



// Update and render the application.
EMSCRIPTEN_KEEPALIVE
extern "C" void UpdateAndRender()
{
    system_app.Update();

    // TODO.
    // window_.SetLedValue(external_.GetValue(0));
    // external_.SetButtonValue(keyboard_.GetButtonValue());
}
