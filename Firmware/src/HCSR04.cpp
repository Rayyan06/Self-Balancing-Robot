#include "HCSR04.h"

HCSR04::HCSR04(uint8_t trig, uint8_t echo)
    : trigPin{trig},
      echoPin{echo} {};

void HCSR04::begin()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void HCSR04::pulse() const
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // make sure the pin is LOW
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // send 8-bit sonic burst
    digitalWrite(trigPin, LOW);
}

float HCSR04::getDistance() const
{

    pulse();

    /*
    pulseIn waits for the pin to go in whichever state we sput in, starts timing, then stops when it switches back to LOW
    returns duration in microseconds
    the third argument is the timeout, 30000 microseconds is a good value.
    5 meter max range
    */
    float duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0)
    {
        return -1.0; // return an error value so the robot knows the reading failed
    }

    // Distance (cm) = SPEED_OF_SOUND (340) (m/s) * duration (μs) * 10^-6 (s/μs) * 10^2 (cm/m) / 2
    // Divide by 2 because duration is the round-trip time of the sound wave
    // distance = duration * SPEED_OF_SOUND * 1e-4 / 2;
    // precalculated:

    return duration * 0.017;
}