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
const int OFF = 70;
const int ON = 90;

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

void loop() {
    int10 brightness = analogRead(PHOTO);
    // Serial.println(brightness);
    if (ir.available()) {
        auto command = ir.readCommand();
        Serial.print("Received command: ");
        Serial.println(command);
    }
}
