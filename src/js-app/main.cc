/*

Entry point of the application.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "system/system.h"



// The whole system.
static System system;



// Initialize the application.
extern "C" void Initialize(int width, int height, unsigned char *u8pixels)
{
    system.Initialize();
}



// Update and render the application.
extern "C" void UpdateAndRender()
{
    // TODO

    
}
