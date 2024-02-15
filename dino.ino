#include <NecDecoder.h>
#include <Servo.h>

#include "buffer.h"
#include "buttons.h"

// 10-bit value from `analogRead`
typedef int int10;

// Photoresistor analog pin
const int PHOTO = A2;

// Servo control pin
const int SERVO_PIN = 3;

Buffer buffer;
NecDecoder ir;
Servo servo;

// Angles for the servo when Space button is or is not pressed
int OFF = 70;
int ON = 90;

/// @brief Digits from the IR remote are stored to the buffer. `EState` is
/// where those values are applied to. E.g., if it is `ReadBaseAngle`, all
/// values in the buffer are interpreted as a servo angle
enum EState {
    Default,
    ReadBaseAngle,
    ReadDiffAngle,
};

volatile EState state = Default;

void interrupt() {
    ir.tick();
}

void press() {
    servo.write(ON);
    delay(100);
    servo.write(OFF);
}

void setup() {
    attachInterrupt(0, interrupt, FALLING);
    Serial.begin(9600);
    servo.attach(SERVO_PIN);
    servo.write(OFF);
}

/* IR buttons:

Digits - add the digit to the buffer.
All other buttons - set buffer content to a parameter:
    - Left: servo angle when OFF
    - Right: servo rotation when switching between OFF and ON
*/

void loop() {
    int10 brightness = analogRead(PHOTO);
    // Serial.println(brightness);
    if (ir.available()) {
        auto command = ir.readCommand();
        Serial.print("Received command: ");
        Serial.println(command);
        switch (command) {
            case IR_LEFT:
                // TODO Remove `EState`. These buttons must apply buffer
                state = ReadBaseAngle;
                Serial.println("LEFT: read base angle");
                break;
            case IR_RIGHT:
                state = ReadDiffAngle;
                Serial.println("RIGHT: read diff angle");
                break;
            default:
                for (int i = 0; i < 10; i++) {
                    if (command == digits[i]) {
                        buffer.add(i);
                    }
                }
                break;
        }
    }
}
