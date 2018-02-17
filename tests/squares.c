/*

Draw some squares on the screen.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

// Standard types.
typedef unsigned int uint32_t;

// Peripheral addresses.
volatile uint32_t *vga = (volatile uint32_t *)0x80000;

// Screen size.
const int kScreenWidth = 320;
const int kScreenHeight = 240;

// Some 16bits colors.
enum Color {
    Black      = 0x0000,
    White      = 0xFFFF,
    Gray       = 0xAD55,
    Red        = 0xF800,
    Green      = 0x37E0,
    Blue       = 0x033F,
    Cyan       = 0x07FF,
    Yellow     = 0xFFE0,
    Orange     = 0xFCC0,
    Purple     = 0xC81F,
    Pink       = 0xF813,
};



// Draw a pixel on the screen.
void DrawPixel(uint32_t color, uint32_t x, uint32_t y)
{
    vga[y * 320 + x] = color;
}



// Draw a sqaure (don't fill it).
void DrawSquare(uint32_t color, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    uint32_t y2 = y + height - 1;
    uint32_t x2 = x + width - 1;

    for (uint32_t i = 0; i < width; i++) {
        DrawPixel(color, x + i, y);
        DrawPixel(color, x + i, y2);
    }

    for (uint32_t i = 0; i < height; i++) {
        DrawPixel(color, x, y + i);
        DrawPixel(color, x2, y + i);
    }
}



// Fill a sqaure.
void FillSquare(uint32_t color, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    for (uint32_t i = 0; i < width; i++) {
        for (uint32_t j = 0; j < height; j++)
            DrawPixel(color, x + i, y + j);
    }
}



// Entry point of this program.
int main(void)
{
    // Make the background white.
    FillSquare(White, 0, 0, kScreenWidth, kScreenHeight);

    // Draw the largest rectangle possible.
    DrawSquare(Orange, 0, 0, kScreenWidth, kScreenHeight);
    DrawSquare(Cyan, 1, 1, kScreenWidth - 2, kScreenHeight - 2);
    DrawSquare(Yellow, 2, 2, kScreenWidth - 4, kScreenHeight - 4);

    // Fill a square at (20, 20)
    FillSquare(Purple, 20, 20, 60, 60);

    // Fill a rectangle at (220, 150)
    FillSquare(Green, 220, 150, 73, 53);

    // Don't go out main().
    for(;;) ;
}
