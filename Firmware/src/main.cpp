/*
=============Author==============
By Muhammed Rayyan Khan

=============Notes================
HINT: Before running this program, try testing an I2C Scanner located in the folder
This program interfaces with the MPU6052C I2C device and reads basic accelerometer and gyro data to the serial
=============Sources==============

// HERE IS THE LIBRARY WE ARE USING:
https://github.com/ElectronicCats/mpu6050/wiki

// UPDATE: we cannot use the library below as we have a MPU60502C, but still could be a useful reference
MPU 6050 Adafruit library:
https://adafruit.github.io/Adafruit_MPU6050/html/class_adafruit___m_p_u6050.html


*/

#include <Arduino.h>
#include <Wire.h> // for I2C
#include "pinout.h"
#include "IMU.h"
#include "Motor.h"

#include <PID_v2.h>

// Program constants
// The Serial data transfer rate in Baud (number of signal changes per second).
// works well at 8Mhz/16Mhz
// #define BAUD_RATE 38400

#define DELAY_INTERVAL 10

// if the robot tilts past this angle(degrees) it's already fallen (kill the motors)

// const float FALL_CUTOFF_DEG = 35.0;
// skipping this feature for now

// --- Per-motor deadband tuning ---
// Increase each independently until that wheel just barely starts spinning.
// They will likely be different values!
// const float LEFT_MIN_SPEED = 35.0;
// const float RIGHT_MIN_SPEED = 38.0; // tune this independently

// Create our IMU
IMU imu;

// Create two motor objects
Motor leftMotor(EN_A, IN_1, IN_2);
Motor rightMotor(EN_B, IN_3, IN_4);

// create PID
double Kp = 15.0, Ki = 0.0, Kd = 2.5;
PID_v2 myPID(Kp, Ki, Kd, PID::Reverse);

// One-time actions to initialize and configure I2C devices and Arduino
void setup()
{
    // Serial.begin(BAUD_RATE);

    // Let's wait for the serial to be setup before proceeding
    // while (!Serial)
    //     delay(10);

    // Initialize and enable I2C on arduino
    Wire.begin();

    // works best at 100kHz
    Wire.setClock(100000);
    Wire.setWireTimeout(3000, true); // 3ms timeout, auto-reset on hang

    imu.begin();

    leftMotor.begin();
    rightMotor.begin();

    // leftMotor.setDeadband(LEFT_MIN_SPEED);
    // rightMotor.setDeadband(RIGHT_MIN_SPEED);

    // Read first
    imu.read();
    // --- Allow negative motor speeds! ---
    myPID.SetOutputLimits(-255.0, 255.0);

    myPID.SetSampleTime(DELAY_INTERVAL); // match your loop timing

    // PID

    myPID.Start(imu.getPitch(),
                0, // current output
                0  // setpoint
    );
}

unsigned long lastLoop = 0;
// Everything that the Arduino needs to repetitively, constantly
void loop()
{

    imu.read();
    
    // imu.print();
    float pitch = imu.getPitch();

    float output = myPID.Run(pitch);

    leftMotor.drive(-output);
    rightMotor.drive(output);
}
