#ifndef IMU_ZERO_H
#define IMU_ZERO_H

#include <Arduino.h>
#include <MPU6050.h>

// External MPU object (declared in main/zero file)
extern MPU6050 mpu;

// --- Calibration Constants ---
const int NFast = 1000;
const int NSlow = 10000;

// Index constants for the 6-axis data array
const int iAx = 0, iAy = 1, iAz = 2;
const int iGx = 3, iGy = 4, iGz = 5;

// Function Prototypes
void SetAveraging(int NewN);
void PullBracketsOut();
void PullBracketsIn();
void GetSmoothed();
void SetOffsets(int TheOffsets[6]);

#endif