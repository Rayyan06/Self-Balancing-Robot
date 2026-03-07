#include "IMU.h"

void IMU::begin()
{
    // Initialize the MPU 6050
    initialize();

    setSleepEnabled(false);                  // Clear sleep bit
    setClockSource(MPU6050_CLOCK_PLL_XGYRO); // Select X gyro as clock

    delay(100);

    Serial.println("MPU6052C Set Up!");

    // let's set the current accelerometer range by interfacing with our device
    setFullScaleAccelRange(ACCEL_RANGE);
    setFullScaleGyroRange(GYRO_RANGE);

    setXAccelOffset(X_ACCEL_OFFSET);
    setYAccelOffset(Y_ACCEL_OFFSET);
    setZAccelOffset(Z_ACCEL_OFFSET);

    setXGyroOffset(X_GYRO_OFFSET);
    setYGyroOffset(Y_GYRO_OFFSET);
    setZGyroOffset(Z_GYRO_OFFSET);

    Serial.println("MPU Configured and Calibrated!");
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

    Serial.print("\t | \tGyro (deg/s): ");
    Serial.print(gyro_deg_s.x);
    Serial.print("\t");
    Serial.print(gyro_deg_s.y);
    Serial.print("\t");
    Serial.println(gyro_deg_s.z);
}

void IMU::read()
{
    getMotion6(&raw.ax, &raw.ay, &raw.az, &raw.gx, &raw.gy, &raw.gz);

    accel_g = {
        raw.ax / ACCEL_SCALE,
        raw.ay / ACCEL_SCALE,
        raw.az / ACCEL_SCALE,
    };

    gyro_deg_s = {
        raw.gx / GYRO_SCALE,
        raw.gy / GYRO_SCALE,
        raw.gz / GYRO_SCALE};
}
