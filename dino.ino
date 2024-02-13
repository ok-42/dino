#include <Servo.h>

Servo servo;

// Angles for the servo when Space button is or is not pressed
const int OFF = 70;
const int ON = 90;

void press() {
    servo.write(ON);
    delay(50);
    servo.write(OFF);
}

void setup() {
    servo.attach(3);
    servo.write(OFF);
}

void loop() {
    while (true) {
        press();
        delay(1500);
    }
}
