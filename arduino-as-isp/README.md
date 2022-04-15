# Arduino as ISP

This program is a test of using an Arduino board as an ISP programmer for other ATmega boards and MCUs.  
The Arduino board needs to have the "ArduinoISP" from Arduino IDE flashed. I could have included it in a C file and a proper Makefile but I was lazy.

My setup includes an Arduino Uno as a programmer and an ATmega328P on a Nano board as the programmed device.

## Connection

The devices are connected according to the following diagram.

```txt
                    
                   ┌──────────────┐           ┌──────────────┐
                   │ Arduino UNO  │           │ Arduino Nano │
                   │              │           │              │
                   │           5V ├───────────┤ 5V           │
                   │              │           │              │
 ┌─────────────┐   │          D13 ├───────────┤ D13          │
 │     PC      │   │              │           │              │
 │         USB ├───┤ USB      D12 ├───────────┤ D12          │
 │             │   │              │           │              │
 └─────────────┘   │          D11 ├───────────┤ D11          │
                   │              │           │              │
                   │          D10 ├───────────┤ RST          │
                   │              │           │              │
                   │          GND ├───────────┤ GND          │
                   └──────────────┘           └──────────────┘
```

## Building

The compilation is the same as with any other program.

Flashing the MCU with using `avrdude` with Arduino as a programmer is pretty straight-forward.  
In order to flash the ATmega the programmer flag `-c` has to be specified as `stk500v1` and baud rate needs to be set to `19200`.
