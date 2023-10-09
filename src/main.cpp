/* MIT License

Copyright (c) 2023 guemax

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Adafruit_NeoPixel.h"
#include "Arduino.h"
#include "RotatingBuffer.h"

#define LED_PIN 6
#define LED_COUNT 70
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

RotatingBuffer hue_buffer = RotatingBuffer{};
RotatingBuffer sat_buffer = RotatingBuffer{};
RotatingBuffer val_buffer = RotatingBuffer{};

void setup() {
  strip.begin();
  strip.show();
}

uint16_t get_hue() {
  uint16_t raw = analogRead(A0);
  hue_buffer.push(raw);

  // Between 0 and 65535.
  return hue_buffer.mean() * 64.0616;
}

uint8_t get_value() {
  uint16_t raw = analogRead(A1);
  sat_buffer.push(raw);

  // Between 0 and 255.
  return sat_buffer.mean() * 0.249267;
}

uint8_t get_saturation() {
  uint16_t raw = analogRead(A2);
  val_buffer.push(raw);

  // Between 0 and 255.
  return val_buffer.mean() * 0.249267;
}

void loop() {
  uint16_t hue = get_hue();
  uint8_t saturation = get_saturation();
  uint8_t value = get_value();
  
  strip.fill(strip.ColorHSV(hue, saturation, value));
  strip.show();
  
  delay(10);
}
