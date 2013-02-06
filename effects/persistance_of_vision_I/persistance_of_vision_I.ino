//
//	www.blinkenlight.net
//
//	Copyright 2011 Udo Klein
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see http://www.gnu.org/licenses/


#include <MsTimer2.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

uint8_t pov_pattern[] PROGMEM = {
                                  0b000000, 0b000000, 0b00000000, // line   1: ....................
                                  0b000000, 0b000000, 0b00000000, // line   2: ....................
                                  0b000000, 0b000000, 0b00000000, // line   3: ....................
                                  0b000000, 0b000000, 0b00000000, // line   4: ....................
                                  0b000000, 0b000000, 0b00000000, // line   5: ....................
                                  0b000000, 0b000000, 0b00000000, // line   6: ....................
                                  0b000000, 0b011110, 0b00000000, // line   7: .......XXXX.........
                                  0b000001, 0b111110, 0b00000000, // line   8: .....XXXXXX.........
                                  0b000011, 0b111110, 0b00000000, // line   9: ....XXXXXXX.........
                                  0b000111, 0b111100, 0b00000000, // line  10: ...XXXXXXX..........
                                  0b001111, 0b110000, 0b00000000, // line  11: ..XXXXXX............
                                  0b001111, 0b100000, 0b00000000, // line  12: ..XXXXX.............
                                  0b011111, 0b000000, 0b00000000, // line  13: .XXXXX..............
                                  0b011110, 0b000000, 0b00000000, // line  14: .XXXX...............
                                  0b011110, 0b000000, 0b00111110, // line  15: .XXXX.........XXXXX.
                                  0b011100, 0b000000, 0b01111110, // line  16: .XXX.........XXXXXX.
                                  0b111100, 0b000000, 0b01111110, // line  17: XXXX.........XXXXXX.
                                  0b111100, 0b000000, 0b01111110, // line  18: XXXX.........XXXXXX.
                                  0b111100, 0b000000, 0b01111100, // line  19: XXXX.........XXXXX..
                                  0b111000, 0b000000, 0b00000000, // line  20: XXX.................
                                  0b111000, 0b000000, 0b00000000, // line  21: XXX.................
                                  0b111000, 0b000000, 0b00000000, // line  22: XXX.................
                                  0b111000, 0b000000, 0b00000000, // line  23: XXX.................
                                  0b111100, 0b000000, 0b01111100, // line  24: XXXX.........XXXXX..
                                  0b111100, 0b000000, 0b01111110, // line  25: XXXX.........XXXXXX.
                                  0b111110, 0b000000, 0b01111110, // line  26: XXXXX........XXXXXX.
                                  0b011111, 0b000000, 0b01111110, // line  27: .XXXXX.......XXXXXX.
                                  0b001111, 0b000000, 0b00111100, // line  28: ..XXXX........XXXX..
                                  0b001111, 0b100000, 0b00000000, // line  29: ...XXXX.............
                                  0b000111, 0b111000, 0b00000000, // line  30: ....XXXXX...........
                                  0b000011, 0b111100, 0b00000000, // line  31: .....XXXXX..........
                                  0b000001, 0b111100, 0b00000000, // line  32: ......XXXX..........
                                  0b000000, 0b111100, 0b00000000, // line  33: ........XX..........
                                  0b000000, 0b000000, 0b00000000, // line  34: ....................
                                  0b000000, 0b000000, 0b00000000, // line  35: ....................
                                  0b000000, 0b000000, 0b00000000, // line  36: ....................
                                  0b000000, 0b000000, 0b00000000, // line  37: ....................
                                  0b000000, 0b000000, 0b00000000, // line  38: ....................
                                  0b000000, 0b000000, 0b00000000, // line  39: ....................
                                  0b000000, 0b000000, 0b00000000, // line  40: ....................
                                };

uint8_t led_to_pin(const uint8_t led) {
  #if defined (__AVR_ATmega32U4__)
  return led<14? led: led+4;
  #else
  return led;
  #endif
}

void blink() {
	static uint16_t index = 0;
	static uint8_t  led8  = 0;
        static uint8_t  i = 0;
        

        led8 = pgm_read_byte(pov_pattern+(index++));
        for(i = 0; i < 6; i++) {
          digitalWrite(led_to_pin(i), led8 && 0b100000 != 0 );
          led8 <<= 1;
        }
        led8 = pgm_read_byte(pov_pattern+(index++));
        for(; i < 12; i++) {
          digitalWrite(led_to_pin(i), led8 && 0b100000 != 0 );
          led8 <<= 1;
        }
        led8 = pgm_read_byte(pov_pattern+(index++));
        for(; i < 20; i++) {
          digitalWrite(led_to_pin(i), led8 && 0b10000000 != 0 );
          led8 <<= 1;
        }
                
	if (index >= sizeof(pov_pattern)) { index = 0; }
}

void setup() {

      for (uint8_t pin=0; pin<20; ++pin) {
        pinMode(led_to_pin(pin), OUTPUT);
    }

	MsTimer2::set(2, blink);
	MsTimer2::start();
}

void loop() { }
