#include <Arduino.h>

const int trigPin = 12;
const int echoPin = 11;

volatile float duration, distance;
void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(38400);
}

void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // make sure the pin is LOW
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // make sure
    digitalWrite(trigPin, LOW);
}