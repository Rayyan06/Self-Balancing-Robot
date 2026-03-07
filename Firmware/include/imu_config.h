#ifndef CONFIG_H
#define CONFIG_H

// Replace these with the values from your Calibration script
#define X_ACCEL_OFFSET 0
#define Y_ACCEL_OFFSET 0
#define Z_ACCEL_OFFSET 0

#define X_GYRO_OFFSET 87
#define Y_GYRO_OFFSET -213
#define Z_GYRO_OFFSET 2

// 1. Set the Range
// Options: MPU6050_ACCEL_FS_2, MPU6050_ACCEL_FS_4, MPU6050_ACCEL_FS_8, MPU6050_ACCEL_FS_16
#define ACCEL_RANGE MPU6050_ACCEL_FS_8

// 2. Set the matching Scale Factor
// (See table below to choose correct value!)
// MUST BE FLOAT (f)
#define ACCEL_SCALE 4096.0f

// 3. Set Gyro Range
// Options: MPU6050_GYRO_FS_250, MPU6050_GYRO_FS_500, MPU6050_GYRO_FS_1000, MPU6050_GYRO_FS_2000
#define GYRO_RANGE MPU6050_GYRO_FS_500

// 4. Set matching Gyro Scale Factor
// (See table below!)
#define GYRO_SCALE 65.5f

#endif