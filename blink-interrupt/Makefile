MAIN=blink.c

blink.hex: $(MAIN)
	avr-gcc -DF_CPU=16000000ULL -mmcu=atmega328p -c -o blink.o $(MAIN)
	avr-gcc -o blink.elf blink.o
	avr-objcopy -O ihex -R .eeprom blink.elf blink.hex

flash: blink.hex
	avrdude -F -c arduino -p atmega328p -P /dev/ttyACM0 -b115200 -U flash:w:blink.hex

clean:
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.o