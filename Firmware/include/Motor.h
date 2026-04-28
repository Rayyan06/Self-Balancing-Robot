#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

enum class MotorDirection
{
    REVERSE = -1,
    STOP,
    FORWARD
};

class Motor
{
private:
    uint8_t enPin;
    uint8_t in1Pin;
    uint8_t in2Pin;

    uint8_t deadSpeedRange;

    // the previous and current directions of the motor
    MotorDirection newDir{MotorDirection::STOP};
    MotorDirection currDir{MotorDirection::STOP};

public:
    // constructor sets up the pins
    Motor(uint8_t en, uint8_t in1, uint8_t in2);

    // Sets up pin config
    void begin();

    // speed is from -255 (full reverse) to 255 (full forward)
    void drive(int16_t speed);

    void setDeadband(uint8_t deadbandRange);

    // shutdown the motors
    void stop();
};

#endif