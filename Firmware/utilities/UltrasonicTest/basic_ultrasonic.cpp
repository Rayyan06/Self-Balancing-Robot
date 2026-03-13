#include <Arduino.h>

const int trigPin = 12;
const int echoPin = 11;

const int SPEED_OF_SOUND = 340; // Speed of sound in m/s

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
    delayMicroseconds(10); // send 8-bit sonic burst
    digitalWrite(trigPin, LOW);

    /*
    pulseIn waits for the pin to go in whichever state we sput in, starts timing, then stops when it switches back to LOW
    returns duration in microseconds
    */
    duration = pulseIn(echoPin, HIGH);

    // Distance (cm) = SPEED_OF_SOUND (m/s) * duration (μs) * 10^-6 (s/μs) * 10^2 (cm/m) / 2
    // Divide by 2 because duration is the round-trip time of the sound wave
    // distance = duration * SPEED_OF_SOUND * 1e-4 / 2;
    // precalculated:
    distance = duration * 0.017;

    Serial.print("Distance: ");
    Serial.println(distance);
    delay(100);
}