#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/delay.h>

                    //ED.CGAFB
#define SEGMENT_A   0b00000100
#define SEGMENT_B   0b00000001
#define SEGMENT_C   0b00010000
#define SEGMENT_D   0b01000000
#define SEGMENT_E   0b10000000
#define SEGMENT_F   0b00000010
#define SEGMENT_G   0b00001000
#define DIGIT_1     0b00010001
#define DIGIT_2     0b11001101
#define DIGIT_3     0b01011101
#define DIGIT_4     0b00011011
#define DIGIT_5     0b01011110
#define DIGIT_6     0b11011110
#define DIGIT_7     0b00010101
#define DIGIT_8     0b11011111
#define DIGIT_9     0b01011111
#define DIGIT_0     0b11010111
#define DIGIT_DOT   0b00100000

#define POS_1 0b00001110
#define POS_2 0b00001011
#define POS_3 0b00001101
#define POS_4 0b00000111

uint8_t segments[] = {
    SEGMENT_A,
    SEGMENT_B,
    SEGMENT_C,
    SEGMENT_D,
    SEGMENT_E,
    SEGMENT_F,
    SEGMENT_G
};
uint8_t digits[] = {
    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9,
    DIGIT_DOT
};
uint8_t positions[] = {
    POS_1,
    POS_2,
    POS_3,
    POS_4
};

#define display(digit, pos, dp)\
    PORTC = positions[pos - 1];\
    PORTD = digits[digit] | (dp ? DIGIT_DOT : 0);



bool showdot = false;
uint8_t seconds10 = 0;
uint8_t seconds1 = 0;
uint8_t minutes10 = 0;
uint8_t minutes1 = 0;

ISR(TIMER1_COMPA_vect) {
    showdot = !showdot;
    seconds1++;
    if(seconds1 == 10) {
        seconds10++;
        seconds1 = 0;
        if(seconds10 == 6) {
            seconds10 = 0;
            minutes1++;
            if(minutes1 == 10) {
                minutes1 = 0;
                minutes10++;
            }
        }
    }
}

int main() {
    //setup
    DDRC  |= 0b00001111;
    PORTC |= POS_1;
    DDRD = 0xFF;

    //
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B |=  (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);

    TCCR1B |=  (1 << CS10) | (1 << CS12);
    TCCR1B &= ~(1 << CS11);

    OCR1A = 0x3D09;
    OCR1AL = 0x12;
    OCR1AH = 0x7A;

    TIMSK1  |= (1 << OCIE1A);
   
    sei();
    

    int del = 100; // microseconds


    while(true) {
        display(minutes10, 1, 0);
        _delay_us(del);

        display(minutes1, 2, showdot);
        _delay_us(del);

        display(seconds10, 3, 0);
        _delay_us(del);

        display(seconds1, 4, 0);
        _delay_us(del);
    }
}