blink.hex: blink.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o blink.o blink.c
	avr-gcc -o blink.elf blink.o
	avr-objcopy -O ihex -R .eeprom blink.elf blink.hex

flash: blink.hex
	avrdude -c stk500v1 -p atmega328p -P /dev/ttyACM0 -b19200 -U flash:w:blink.hex:i

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.o