#include <Arduino.h>
#include "pinout.h"
#include "Motor.h"

// Initialize motor objects using the pins defined in pinout.h
Motor leftMotor(EN_A, IN_1, IN_2);
Motor rightMotor(EN_B, IN_3, IN_4);

void setup()
{
    Serial.begin(38400);

    // Initialize the motor objects
    leftMotor.begin();
    rightMotor.begin();

    Serial.println("Starting Motor Test...");
    delay(2000);
}

void loop()
{
    Serial.println("Testing Forward at 50% Speed");
    leftMotor.drive(127); // Roughly half speed
    rightMotor.drive(127);
    delay(2000);

    Serial.println("Testing Stop");
    leftMotor.drive(0);
    rightMotor.drive(0);
    delay(1000);

    Serial.println("Testing Backward at 50% Speed");
    leftMotor.drive(-127);
    rightMotor.drive(-127);
    delay(2000);

    Serial.println("Testing Stop");
    leftMotor.drive(0);
    rightMotor.drive(0);
    delay(2000);
}