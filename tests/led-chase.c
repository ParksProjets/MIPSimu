/*

A simple LED chase.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

// Standard types.
typedef unsigned int uint32_t;

// Peripheral addresses.
volatile uint32_t *led   = (volatile uint32_t *)0x4000;
volatile uint32_t *timer = (volatile uint32_t *)0x4010;


// Set the timer period and thresold.
void SetTimer(uint32_t period, uint32_t thresold)
{
    timer[0] = period;
    timer[1] = thresold;
}


// Wait for the timer.
void WaitForTimer()
{
    while (*timer != 0) ;
}


// Set the LED value.
void SetLed(uint32_t value)
{
    *led = value;
}


// Entry point of this program.
int main(void)
{
    SetTimer(50000000, 50);

    uint32_t leds = 0b1000;

    for(;;) {
        SetLed(leds);
        WaitForTimer();

        leds = (leds == 1) ? 0b1000 : leds >> 1;
    }
}
