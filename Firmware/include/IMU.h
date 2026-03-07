#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

// The MPU6050 library we are using to avoid having to configure and interact with the registers directly
// first, include the device driver
#include <MPU6050.h>

// Calibration Parameters
#include "imu_config.h"

// represent raw IMU data
struct RawIMU
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
};
// Helper struct to represent 3-axis data
struct Vec3D
{
    float x;
    float y;
    float z;
};

class IMU : public MPU6050
{
private:
    // the bytes to read our data into:
    RawIMU raw;

    // accelerometer data
    Vec3D accel_g;

    // gyroscope data
    Vec3D gyro_deg_s;

public:
    // use
    IMU() = default;

    void begin();

    // accessors

    void print() const;
    // mutators
    void read();
};

#endif