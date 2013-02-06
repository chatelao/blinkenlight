//
//	www.blinkenlight.net
//
//	Copyright 2011 Udo Klein         : 99% of the code
//	Copyright 2013 Olivier Chatelain : AVR32U4 (Leonardo) detection
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

volatile uint8_t current_volume = 0;
volatile uint8_t current_top_volume = 0;
volatile uint32_t speed = 0;
volatile uint32_t height = 0;

uint8_t led_to_pin(const uint8_t led) {
  #if defined (__AVR_ATmega32U4__)
  return led<14? led: led+4;
  #else
  return led;
  #endif
}

void drop() {
	if (current_volume < current_top_volume) {
		// volume decreased recently
		// ensure top_volume LED is lit
		digitalWrite(led_to_pin(current_top_volume+1), HIGH);

		// now let the top_volume indicator follow down
		++speed;
		height += speed;
		
		if (height > 20000) {
			height-= 20000;
			digitalWrite(led_to_pin(current_top_volume+1), LOW);
			--current_top_volume;
			digitalWrite(led_to_pin(current_top_volume+1), HIGH);
		}
	}
}

void set_volume(uint8_t volume) {
	cli();
	current_volume = volume;

	if (current_volume >= current_top_volume) {
		current_top_volume = current_volume;
		speed = 0;
		height = 0;
	}

	for (uint8_t pin=2; pin<20; ++pin) {
		digitalWrite(led_to_pin(pin), pin < current_volume+2);
	}
	sei();
}

void setup() {
    for (uint8_t pin=0; pin<20; ++pin) {
        pinMode(led_to_pin(pin), OUTPUT);
	digitalWrite(led_to_pin(pin), LOW);
    }
    
	Serial.begin(9600);
	Serial.println("ready, send characters a-s to control output");
	set_volume(0);

    MsTimer2::set(1, drop);
    MsTimer2::start();
}

void loop() {
	uint8_t volume = Serial.read() - 'a';
	if (volume < 't'-'a') {
		set_volume(volume);
	}
}
