blink.hex: blink.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o blink.o blink.c
	avr-gcc -o blink.bin blink.o
	avr-objcopy -O ihex -R .eeprom blink.bin blink.hex

flash: blink.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:blink.hex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.o