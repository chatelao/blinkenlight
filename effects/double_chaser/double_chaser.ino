//
//  www.blinkenlight.net
//
//  Copyright 2011 Udo Klein         : 99% of the code
//  Copyright 2013 Olivier Chatelain : AVR32U4 (Leonardo) detection
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see http://www.gnu.org/licenses/


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
}

uint8_t brightness(const int8_t led, const int8_t pos) {
	switch (min(abs(led-pos),abs(19-led-pos))) {
		case 0: 	return 32;
		case 1: 	return 16;
		case 2: 	return 6;
		case 3: 	return 2;
		default:	return 1;
	}
}

void pulse_width_modulation(const uint8_t pos) {
    for(uint8_t times=0; times<10; ++times) {
        for (uint8_t pass=0; pass<32; ++pass) {
            for (int8_t led=0; led<20; ++led) {
                digitalWrite(led_to_pin(led), (brightness(led, pos) > pass));
            }
        }
    }
}

void loop() {
    static uint8_t pos=0;

    while(pos<20) {
        pulse_width_modulation(pos);
        ++pos;
    }

    while(pos>0) {
        --pos;
        pulse_width_modulation(pos);
    }
}
