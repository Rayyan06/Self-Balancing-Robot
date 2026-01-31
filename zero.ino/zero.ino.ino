#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 mpu;

// --- USER SETTINGS ---
#define ACCEL_RANGE MPU6050_ACCEL_FS_8
#define GYRO_RANGE  MPU6050_GYRO_FS_500
// ---------------------

const int usDelay = 3150;
const int NFast = 1000; 
const int NSlow = 10000; 
const int LinesBetweenHeaders = 5;

// Index constants
const int iAx = 0; const int iAy = 1; const int iAz = 2;
const int iGx = 3; const int iGy = 4; const int iGz = 5;

int LowValue[6], HighValue[6], Smoothed[6];
int LowOffset[6], HighOffset[6], Target[6];
int LinesOut, N, i;

void setup() {
  Wire.begin();
  Wire.setClock(400000); 
  Serial.begin(9600);    

  Serial.println("Initializing MPU6052C...");
  mpu.initialize();
  mpu.setFullScaleAccelRange(ACCEL_RANGE);
  mpu.setFullScaleGyroRange(GYRO_RANGE);

  Serial.println("\n--- STEP 1: Auto-Detecting Orientation ---");
  // We take a quick reading to see which way gravity is pointing
  int16_t rax, ray, raz, rgx, rgy, rgz;
  mpu.getMotion6(&rax, &ray, &raz, &rgx, &rgy, &rgz);
  
  // Reset all targets to 0
  for (i = 0; i < 6; i++) Target[i] = 0;

  // Determine Gravity Target based on Range
  int gravity_target = 0;
  uint8_t range = mpu.getFullScaleAccelRange();
  if (range == MPU6050_ACCEL_FS_2) gravity_target = 16384;
  else if (range == MPU6050_ACCEL_FS_4) gravity_target = 8192;
  else if (range == MPU6050_ACCEL_FS_8) gravity_target = 4096;
  else if (range == MPU6050_ACCEL_FS_16) gravity_target = 2048;

  // If Z is negative, our target should be negative!
  if (raz < 0) {
     Target[iAz] = -gravity_target;
     Serial.print("Detected DOWN orientation. Target Z: ");
  } else {
     Target[iAz] = gravity_target;
     Serial.print("Detected UP orientation. Target Z: ");
  }
  Serial.println(Target[iAz]);

  SetAveraging(NFast);
  
  Serial.println("\n--- STEP 2: Bracketing (Max 10 tries) ---");
  PullBracketsOut(); // This now has a hard limit
  
  Serial.println("\n--- STEP 3: Refining (Max 30 tries) ---");
  PullBracketsIn();  // This now has a hard limit
  
  Serial.println("\n\n============== FINAL RESULTS ==============");
  Serial.println("Copy these lines into your setup():");
  Serial.println("-------------------------------------");
  mpu.PrintActiveOffsets();
  Serial.println("-------------------------------------");
  while(1);
}

void loop() { }

void SetAveraging(int NewN) {
  N = NewN;
}

void PullBracketsOut() {
  boolean Done = false;
  int NextLowOffset[6], NextHighOffset[6];

  // FORCE LIMIT: Only try to expand 10 times. If not found, use what we have.
  for(int attempt = 1; attempt <= 10; attempt++) {
    
    Serial.print("Bracket Attempt: "); Serial.print(attempt); Serial.println("/10");
    
    Done = true;
    SetOffsets(LowOffset);
    GetSmoothed();
    for (i = 0; i <= 5; i++) {
      LowValue[i] = Smoothed[i];
      if (LowValue[i] >= Target[i]) {
        Done = false;
        NextLowOffset[i] = LowOffset[i] - 1000;
      } else {
        NextLowOffset[i] = LowOffset[i];
      }
    }
    SetOffsets(HighOffset);
    GetSmoothed();
    for (i = 0; i <= 5; i++) {
      HighValue[i] = Smoothed[i];
      if (HighValue[i] <= Target[i]) {
        Done = false;
        NextHighOffset[i] = HighOffset[i] + 1000;
      } else {
        NextHighOffset[i] = HighOffset[i];
      }
    }
    
    if(Done) break; // If we found the brackets, exit early

    for (int i = 0; i <= 5; i++) {
      LowOffset[i] = NextLowOffset[i]; 
      HighOffset[i] = NextHighOffset[i];
    }
  }
}

void PullBracketsIn() {
  int NewOffset[6];
  
  // FORCE LIMIT: Only try to refine 30 times.
  for(int attempt = 1; attempt <= 30; attempt++) {
    
    Serial.print("Refine Step: "); Serial.print(attempt); Serial.println("/30");

    for (int i = 0; i <= 5; i++) {
      // Standard Binary Search Logic
      if (HighOffset[i] <= (LowOffset[i] + 1)) {
        NewOffset[i] = LowOffset[i];
      } else {
        NewOffset[i] = (LowOffset[i] + HighOffset[i]) / 2;
      }
    }
    
    SetOffsets(NewOffset);
    GetSmoothed();
    
    for (i = 0; i <= 5; i++) {
      if (Smoothed[i] > Target[i]) {
        HighOffset[i] = NewOffset[i];
      } else {
        LowOffset[i] = NewOffset[i];
      }
    }
  }
}

void GetSmoothed() {
  int16_t RawValue[6];
  long Sums[6];
  for (i = 0; i <= 5; i++) Sums[i] = 0;
  for (i = 1; i <= N; i++) {
    mpu.getMotion6(&RawValue[iAx], &RawValue[iAy], &RawValue[iAz], &RawValue[iGx], &RawValue[iGy], &RawValue[iGz]);
    // Small optimization: remove delay to speed up convergence
    // delayMicroseconds(usDelay); 
    for (int j = 0; j <= 5; j++) Sums[j] = Sums[j] + RawValue[j];
  }
  for (i = 0; i <= 5; i++) Smoothed[i] = (Sums[i] + N / 2) / N;
}

void SetOffsets(int TheOffsets[6]) {
  mpu.setXAccelOffset(TheOffsets[iAx]);
  mpu.setYAccelOffset(TheOffsets[iAy]);
  mpu.setZAccelOffset(TheOffsets[iAz]);
  mpu.setXGyroOffset(TheOffsets[iGx]);
  mpu.setYGyroOffset(TheOffsets[iGy]);
  mpu.setZGyroOffset(TheOffsets[iGz]);
}