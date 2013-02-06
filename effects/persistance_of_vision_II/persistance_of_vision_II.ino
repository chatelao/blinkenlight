//
// Please get the newest MsTimer2 for Arduino Leonard board
//
#include <MsTimer2.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define PARSE(pattern) ((pattern>>14) & 0b111111), ((pattern>>8) & 0b111111), (pattern & 0b11111111)

uint8_t pov_pattern[] PROGMEM = {
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00001111110000000000 ),
    PARSE( 0b00111100011100000000 ),
    PARSE( 0b01110000001110000000 ),
    PARSE( 0b11100000000111000000 ),
    PARSE( 0b11000000000011000000 ),
    PARSE( 0b11000000000011000000 ),
    PARSE( 0b11000000000011000000 ),
    PARSE( 0b11000000000011000000 ),
    PARSE( 0b11100000000111000000 ),
    PARSE( 0b01110000001110000000 ),
    PARSE( 0b00111100011100000000 ),
    PARSE( 0b00001111110000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b11111111111111111111 ),
    PARSE( 0b11111111111111111111 ),
    PARSE( 0b00000011000000000000 ),
    PARSE( 0b00000011100000000000 ),
    PARSE( 0b00000111110000000000 ),
    PARSE( 0b00001110011000000000 ),
    PARSE( 0b00011100001100000000 ),
    PARSE( 0b01110000000111000000 ),
    PARSE( 0b11100000000011000000 ),
    PARSE( 0b11000000000001000000 ),
    PARSE( 0b10000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b11100011111111111110 ),
    PARSE( 0b11100011111111111110 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
    PARSE( 0b00000000000000000000 ),
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

/*
void blink() {
	static uint16_t index = 0;
	static uint32_t led32 = 0;

        led32 = pgm_read_dword(pov_pattern+(index++));
        for(uint8_t i = 0; i < 20; i++) {
          digitalWrite(led_to_pin(i), led32 && 0b1 != 0 );
          led32 >>= 1;
        }
                
	if (index >= sizeof(pov_pattern)/4) { index = 0; }
}
*/

void setup() {

      for (uint8_t pin=0; pin<20; ++pin) {
        pinMode(led_to_pin(pin), OUTPUT);
    }

	MsTimer2::set(2, blink);
	MsTimer2::start();
}

void loop() { }

