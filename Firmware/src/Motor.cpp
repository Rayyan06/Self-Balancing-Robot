#include "Motor.h"

// constructor sets up the pins
Motor::Motor(uint8_t en, uint8_t in1, uint8_t in2) : enPin{en}, in1Pin{in1}, in2Pin{in2} {};

void Motor::begin()
{
    pinMode(enPin, OUTPUT);
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
}

void Motor::drive(int16_t speed)
{
    // limit speed to safe PWM limits
    speed = constrain(speed, -255, 255);

    // use bit trick to get newdir
    newDir = static_cast<MotorDirection>((speed > 0) - (speed < 0));

    if (newDir != currDir)
    {
        /*
        if IN1 is Low and IN2 is High,
        motor goes forward and vice versa
        */
        switch (newDir)
        {
        case MotorDirection::FORWARD:
        {
            digitalWrite(in1Pin, LOW);
            digitalWrite(in2Pin, HIGH);
            break;
        }
        case MotorDirection::REVERSE:
        {
            digitalWrite(in1Pin, HIGH);
            digitalWrite(in2Pin, LOW);
            break;
        }
        case MotorDirection::STOP:
        { // speed = 0
            stop();
        }
            currDir = newDir;
        }

        analogWrite(enPin, abs(speed));
    }
}

void Motor::stop()
{
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(enPin, 0);
}