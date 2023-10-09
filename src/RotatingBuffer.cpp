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

#include "Arduino.h"
#include "RotatingBuffer.h"

RotatingBuffer::RotatingBuffer() {
  for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
    elements[i] = 0;
  }
}

void RotatingBuffer::push(uint16_t new_element) {
  const static int LAST = BUFFER_SIZE - 1;
  
  for (uint8_t i = 0; i < LAST; i++) {
    elements[i] = elements[i+1];
  }
  elements[LAST] = new_element;
}
  
int RotatingBuffer::mean() {
  uint32_t sum {};
  
  for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
    sum += elements[i];
  }
  
  return (int) (sum / BUFFER_SIZE);
}
