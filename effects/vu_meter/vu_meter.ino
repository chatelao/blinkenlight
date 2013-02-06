//
//	www.blinkenlight.net
//
//  Copyright 2011 Udo Klein        : 99% of the code
//  Copyright 2013 Oliver Chatelain : AVR32U4 (Leonardo) detection
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

uint8_t led_to_pin(const uint8_t led) {
  #if defined (__AVR_ATmega32U4__)
  return led<14? led: led+4;
  #else
  return led;
  #endif
}

void setup() {
    for (uint8_t pin=0; pin<20; ++pin) {
        pinMode(led_to_pin(pin), OUTPUT);
    }
	Serial.begin(9600);
	Serial.println("ready, send characters a-s to control output");
	set_volume(0);
}

void set_volume(uint8_t volume) {
	volume+= 2;
	for (uint8_t pin=2; pin<20; ++pin) {
		digitalWrite(led_to_pin(pin), pin<volume);
	}
}

void loop() {
	uint8_t volume = Serial.read() - 'a';
	if (volume < 't'-'a') {
		set_volume(volume);
	}
}
