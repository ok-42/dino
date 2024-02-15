#include "buffer.h"

#include <Arduino.h>

/// @brief Add a new value to the buffer
/// @param value digit 0-9 on IR remote
void Buffer::add(int value) {
    this->buffer[index] = value;
    ++index;
}

/// @brief Convert digits from the buffer to a number
int Buffer::resolve(void) {
    int result = 0;
    for (int i = 0; i < index; i++) {
        result += this->buffer[i] * pow(10, index - i - 1);
    }
    return result;
}
