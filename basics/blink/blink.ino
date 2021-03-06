//
//  www.blinkenlight.net
//
//  Copyright 2013 Udo Klein
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
  return led<14? led: led+4;
}

void setup() {
    for (uint8_t pin=0; pin<20; ++pin) {
        pinMode(led_to_pin(pin), OUTPUT);
    }
}

void blink(const uint8_t pos) {
    digitalWrite(led_to_pin(pos), HIGH);
    delay((sqrt(((float)20 - pos)/20) - sqrt((19.0 - pos)/20)) * 500);
    digitalWrite(led_to_pin(pos), LOW);
}

void loop() {
    for (uint8_t pos=0; pos<19; ++pos) {
        blink(pos);
    }
    for (uint8_t pos=19; pos>0; --pos) {
        blink(pos);
    }
}
