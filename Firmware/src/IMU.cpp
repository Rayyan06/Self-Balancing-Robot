#include "IMU.h"

void IMU::begin()
{
    // Initialize the MPU 6050
    mpu.initialize();

    mpu.setSleepEnabled(false);                  // Clear sleep bit
    mpu.setClockSource(MPU6050_CLOCK_PLL_XGYRO); // Select X gyro as clock

    delay(100);

    Serial.println("MPU6052C Set Up!");

    // let's set the current accelerometer range by interfacing with our device
    // TODO: Make the acceleration multiplier smart calculated based on the range
    mpu.setFullScaleAccelRange(ACCEL_RANGE);
    mpu.setFullScaleGyroRange(GYRO_RANGE);

    mpu.setXAccelOffset(X_ACCEL_OFFSET);
    mpu.setYAccelOffset(Y_ACCEL_OFFSET);
    mpu.setZAccelOffset(Z_ACCEL_OFFSET);

    mpu.setXGyroOffset(X_GYRO_OFFSET);
    mpu.setYGyroOffset(Y_GYRO_OFFSET);
    mpu.setZGyroOffset(Z_GYRO_OFFSET);

    Serial.println("MPU Configured and Calibrated!");
}

Vec3D IMU::getAccel() const
{
    return accel_g;
}
Vec3D IMU::getGyro() const
{
    return gyro_deg_s;
}

float IMU::getPitch() const
{
    // calculate angle from acceleremator
    return atan2(accel_g.y, accel_g.z) * 180.0 / PI;
}

void IMU::print() const
{
    // 4. Print readable values
    Serial.print("Accel (g): ");
    Serial.print(accel_g.x);
    Serial.print("\t");
    Serial.print(accel_g.y);
    Serial.print("\t");
    Serial.print(accel_g.z);

    // Serial.print("\t | \tGyro (deg/s): ");
    // Serial.print(gyro_deg_s.x);
    // Serial.print("\t");
    // Serial.print(gyro_deg_s.y);
    // Serial.print("\t");
    // Serial.println(gyro_deg_s.z);
}

void IMU::read()
{
    mpu.getMotion6(&raw.ax, &raw.ay, &raw.az, &raw.gx, &raw.gy, &raw.gz);

    // Note: Use multiplication instead of division here, because the avr has built-in fast multiplication
    accel_g = {
        raw.ax * ACCEL_SCALE,
        raw.ay * ACCEL_SCALE,
        raw.az * ACCEL_SCALE,
    };

    gyro_deg_s = {
        raw.gx * GYRO_SCALE,
        raw.gy * GYRO_SCALE,
        raw.gz * GYRO_SCALE};
}
