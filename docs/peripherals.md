# Peripherals


### VGA Screen

This is a 16 bits color, 320x240 screen.  
The screen is mapped at address `0x80000`. Each pixel is a 32 bit word.

```c
volatile uint32_t *vga = (volatile uint32_t *)0x80000;

int x = 20, y = 40;
vga[y * 320 + y] = 0xFCC0; // Color pixel at (20, 40) in orange
```



### Timer

The timer is mapped at address `0x4010`.  
See `led-chase` test for more details.

```c
volatile uint32_t *timer = (volatile uint32_t *)0x4010;

void SetTimer(uint32_t period, uint32_t thresold) {
    timer[0] = period;
    timer[1] = thresold;
}
```



### The 4 LEDs

The LEDs are mapped at address `0x4000`. Each led is on bit, starting at bit 0.

```c
volatile uint32_t *leds = (volatile uint32_t *)0x4000;

leds = (1 << 3) | (0 << 2) | (1 << 1) | 0; // 🔴⭕🔴⭕
```



### The 3 push buttons

The push buttons are mapped at address `0x4004`. Each button is on bit, starting at bit 0.

```c
volatile uint32_t *btns = (volatile uint32_t *)0x4004;
```



### Debugger

When you run **MIPSimu** with `-d` a debug peripheral is plugged at
address `0x5000`.

This debugger has a 30 port of 4 byte each. Every time you write on
one of the debugger port, the value is printed in the terminal.  
If you write at address `0x5078` a new line is printed (useful to
separate groups of data).

Also you can pause the processor execution by writing at address `0x507C`.
