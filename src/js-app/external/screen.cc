/*

The VGA screen.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "external/screen.h"

namespace app {


// Attach the pixel buffer.
void Screen::Attach(unsigned char *u8pixels)
{
    u8pixels_ = u8pixels;
}



// Set a value at the address given.
void Screen::SetValue(uint32_t addr, uint32_t value)
{
    uint32_t offset = addr & 0xFFFFFFFC;
    uint32_t red = value & 0xF800;
    uint32_t blue = value & 0x1F;

    u8pixels_[offset]   = (red >> 8) | (red >> 13);
    u8pixels_[offset+1] = (value & 0x7E0) >> 3;
    u8pixels_[offset+2] = blue | (blue >> 2);
}


// Get a value from an address.
uint32_t Screen::GetValue(uint32_t addr)
{
    uint32_t offset = addr & 0xFFFFFFFC;

    return 0; // TODO.
}


} // namespace app
