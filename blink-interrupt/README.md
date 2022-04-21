# blink-interrupt

This example code blinks an inbuilt LED on pin `PB5` of Arduino Nano/Uno, using timers and interrupts instead of `_delay_ms` function

The program uses `TIMER1` with Compare Match interrupts with `CTC` mode.
Every time the `TIMER1` counter hits a predefined value, an interrupt occurs, which is hadled by toggling `PB5` pin.

More in-depth explanation is provided in the source code's comments at `src/main.c`.
