#include <Servo.h>

// 10-bit value from `analogRead`
typedef int int10;

// Photoresistor analog pin
const int PHOTO = A2;

// Servo control pin
const int SERVO_PIN = 3;

Servo servo;

// Angles for the servo when Space button is or is not pressed
const int OFF = 70;
const int ON = 90;

int BRIGHTNESS_WHITE = 660;
int BRIGHTNESS_BLACK = 730;

void press() {
    servo.write(ON);
    delay(100);
    servo.write(OFF);
}

void setup() {
    servo.attach(SERVO_PIN);
    servo.write(OFF);
    Serial.begin(9600);
}

void loop() {
    int10 brightness = analogRead(PHOTO);
    Serial.println(brightness);
    // press();
    delay(1500);
}
