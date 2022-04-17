/*
    This example code is blinking an LED once every second 
    on the pin PD5 without the use of delay functions, 
    using timers and interruptions.
    I'm using TIMER 1, because it is 16 bit.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

ISR(TIMER1_COMPA_vect) {
    PORTB ^= (1 << PB5);
}

int main() {
    // Set PORTB5 as output
    DDRB |= (1 << DDB5);

    // Set CTC mode. The mode clears the timer on Compare Match
    // Bits to set CTC mode
    // WGM10, WGM11, WGM13 = 0 in TCCR1A
    // WGM12 = 1 in TCCR1B
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B |=  (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);

    // Set the TIMER1 prescaler to 1024
    // CS10 = 1, CS11 = 0, CS12 = 1
    // Now the TIMER1 increments 15625 times a second
    TCCR1B |=  (1 << CS10) | (1 << CS12);
    TCCR1B &= ~(1 << CS11);

    // Set the compared value (OCR1A) according to the delay time (0x3D09)
    // 0x3D09 = 15 625 
    // OCR1A = 0x3D09;
    OCR1AL = 0x09;
    OCR1AH = 0x3D;

    // Trigger an interrupt at every Compare Match
    TIMSK1  |= (1 << OCIE1A);

    // Enable interrupts
    sei();

    while(true) {
        // stuff that could be running in a loop, and
        // blink would still work
    }
}