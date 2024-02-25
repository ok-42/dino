#include "buffer.h"

#include <Arduino.h>

/// @brief Add a new value to the buffer
/// @param value digit 0-9 on IR remote
void Buffer::add(int value) {
    this->buffer[index] = value;
    ++index;
}

void Buffer::reset(void) {
    for (int i = 0; i < 5; i++) {
        buffer[i] = 0;
    }
    index = 0;
}

/// @brief Convert digits from the buffer to a number
int Buffer::resolve(void) {
    int result = 0;
    int mult = 1;
    for (int i = index - 1; i >= 0; i--) {
        result += this->buffer[i] * mult;
        Serial.println(result);
        mult *= 10;
    }
    return result;
}
