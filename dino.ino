#include <Servo.h>

// 10-bit value from `analogRead`
typedef int int10;

// Photoresistor
const int PHOTO = A2;

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
    int10 brightness = analogRead(PHOTO);
    press();
    delay(1500);
}
