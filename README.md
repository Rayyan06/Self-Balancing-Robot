# Self Balancing Robot

An Arduino-based self-balancing robot project using an MPU6052C IMU and dual DC motors.

## Overview

This repository contains early-stage firmware, hardware references, and calibration/testing sketches for building a 2-wheel self-balancing robot.  
Current focus is on:
- IMU communication and data acquisition (accelerometer + gyroscope)
- I2C bus validation
- Sensor calibration (offset tuning)
- Motor driver bring-up and PWM direction/speed testing

---

## Project Structure

```text
Self_Balancing_Robot/
├── src/
│   └── MPU6052C/
│       └── MPU6052C.ino            # Main IMU readout sketch
├── Firmware/
│   ├── src/                         # Future main firmware
│   ├── lib/                         # Custom/shared libraries
│   └── tests/
│       ├── I2CScanner.ino/          # I2C scanner sketch
│       ├── zero.ino                 # IMU offset calibration utility
│       └── accelerometer_read.ino   # Alternate IMU read test (Adafruit lib)
├── MotorDriverTutorial/
│   └── MotorDriverTutorial.ino      # Motor direction/speed test
├── Hardware/
│   ├── BOM.xlsx                     # Bill of materials
│   └── schematic.pdf                # Electrical schematic
└── Docs/
    ├── Datasheets/
    └── Planning/
```

---

## Hardware

### Core Components
- Arduino-compatible MCU board (UNO/Nano style pinout assumed)
- MPU6052C / MPU6050-class IMU module (I2C)
- Dual DC motors + motor driver
- Chassis, wheels, battery, and support electronics

### IMU Wiring (from `src/MPU6052C/MPU6052C.ino`)
- `Arduino 5V` → `MPU VCC`
- `Arduino GND` → `MPU GND`
- `Arduino A4 (SDA)` → `MPU SDA`
- `Arduino A5 (SCL)` → `MPU SCL`
- `Arduino D2` → `MPU INT` (optional/available)

### Motor Driver Test Pin Mapping (from `MotorDriverTutorial.ino`)
- Motor A: `EN=9`, `IN1=8`, `IN2=7`
- Motor B: `EN=3`, `IN3=5`, `IN4=4`

> Adjust pin assignments in code if your board/driver wiring is different.

---

## Software & Libraries

Use Arduino IDE or PlatformIO.

### Required Arduino Libraries
Depending on sketch:
- `Wire.h` (built-in)
- `MPU6050` (Electronic Cats / I2Cdev-style usage in `src/MPU6052C` and `zero.ino`)
- `I2Cdev` (used by `zero.ino`)
- `Adafruit_MPU6050` (used by `Firmware/tests/accelerometer_read.ino`)

Because multiple test sketches use different MPU libraries, install all relevant dependencies before uploading tests.

---

## Getting Started

### 1) Verify IMU on I2C bus
Upload and run:
- `Firmware/tests/I2CScanner.ino/I2CScanner.ino`

Expected: device appears at address like `0x68`.

### 2) Calibrate IMU offsets
Upload and run:
- `Firmware/tests/zero.ino`

At the end, the sketch prints final offset values. Copy those numbers into:
- `src/MPU6052C/MPU6052C.ino`

Replace these lines in `setup()`:
```cpp
mpu.setXAccelOffset(...);
mpu.setYAccelOffset(...);
mpu.setZAccelOffset(...);
mpu.setXGyroOffset(...);
mpu.setYGyroOffset(...);
mpu.setZGyroOffset(...);
```

### 3) Read calibrated IMU data
Upload and run:
- `src/MPU6052C/MPU6052C.ino`

Serial output includes:
- Acceleration in `g`
- Angular velocity in `deg/s`

Default serial baud in this sketch: `38400`.

### 4) Validate motor driver behavior
Upload and run:
- `MotorDriverTutorial/MotorDriverTutorial.ino`

This sketch tests:
- Direction switching
- PWM acceleration/deceleration

---

## Current Status

✅ Sensor readout and range configuration  
✅ I2C scan utility  
✅ Offset calibration workflow  
✅ Motor driver bring-up test  
🚧 Closed-loop balancing control (PID/state estimator) in progress

---

## Next Milestones

- Integrate IMU + motor control into one firmware entry point under `Firmware/src`
- Implement tilt angle estimation (complementary/Kalman filter)
- Implement PID control loop for balance
- Add safety checks (motor cutoff on excessive tilt)
- Document tuning procedure and performance metrics

---

## Troubleshooting

- **No I2C device found**
  - Re-check SDA/SCL wiring and ground commonality
  - Confirm IMU power voltage compatibility
  - Try lower I2C clock (100 kHz)

- **Unstable or noisy readings**
  - Re-run `zero.ino` calibration with robot stationary
  - Verify offsets were copied correctly
  - Ensure firm mechanical mounting of IMU

- **Motors not spinning**
  - Check motor power rail and driver enable pins
  - Verify PWM-capable pins for enable lines
  - Confirm battery can supply required current

---

## Author

Muhammed Rayyan Khan

---

## License

Add a license file (e.g., MIT) if you plan to open-source publicly.