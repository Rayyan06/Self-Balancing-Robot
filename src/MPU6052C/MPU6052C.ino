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

WIRING

Arduino -> MPU6050:
PIN 2 -> INT
5V -> VCC
GND -> GND
A4 -> SDA
A5 -> SCL

*/

// Import the Arduino I2C library because the MPU6050 is an I2C device
#include <Wire.h>

// The MPU6050 library we are using to avoid having to configure and interact with the registers directly
// first, include the device driver
#include <MPU6050.h>

// initialize an MPU class.
// default I2C address is 0x68
MPU6050 mpu;

// Program constants
// The Serial data transfer rate in Baud (number of signal changes per second).
// works well at 8Mhz/16Mhz
#define BAUD_RATE 38400

// --- USER CONFIGURATION ---

// 1. Set the Range 
// Options: MPU6050_ACCEL_FS_2, MPU6050_ACCEL_FS_4, MPU6050_ACCEL_FS_8, MPU6050_ACCEL_FS_16
#define ACCEL_RANGE     MPU6050_ACCEL_FS_8   

// 2. Set the matching Scale Factor 
// (See table below to choose correct value!)
float accel_scale = 4096.0; 

// 3. Set Gyro Range 
// Options: MPU6050_GYRO_FS_250, MPU6050_GYRO_FS_500, MPU6050_GYRO_FS_1000, MPU6050_GYRO_FS_2000
#define GYRO_RANGE      MPU6050_GYRO_FS_500

// 4. Set matching Gyro Scale Factor 
// (See table below!)
float gyro_scale = 65.5; 


// how often (in ms) we grab data from the MPU
#define DELAY_INTERVAL 100


// the bytes to read our data into:
// accelerometer
int16_t ax, ay, az;
// gyroscope
int16_t gx, gy, gz;

// One-time actions to initialize and configure I2C devices and Arduino
void setup()
{
  Serial.begin(BAUD_RATE);

  // Let's wait for the serial to be setup before proceeding
  while(!Serial) delay(10);

  // Initialize and enable I2C on arduino
  Wire.begin();

  // works best at 100kHz
  Wire.setClock(100000);


  // Initialize the MPU 6050
  mpu.initialize();

  mpu.setSleepEnabled(false);          // Clear sleep bit
  mpu.setClockSource(MPU6050_CLOCK_PLL_XGYRO); // Select X gyro as clock

  delay(100);

  // Testing the connection won't work because this is an MPU6052C 

  // if(!mpu.testConnection())
  // {
  //   Serial.println("Failed to find MPU6050 chip!");

  //   checkWhoAmI();
    
  //   while(1) {
  //     // enter an infinite loop
  //     delay(10);
  //   }
  // }

  // assume we are connected

  Serial.println("MPU6052C Set Up!");

  // let's set the current accelerometer range by interfacing with our device
  mpu.setFullScaleAccelRange(ACCEL_RANGE);
  mpu.setFullScaleGyroRange(GYRO_RANGE);

// ==========================================================
  // >>> PASTE YOUR OFFSET NUMBERS HERE <<<
  // Use the numbers from the end of the IMU_Zero script output
  // ==========================================================
  mpu.setXAccelOffset(0);   // <-- Replace 0 with your Value
  mpu.setYAccelOffset(0);   // <-- Replace 0 with your Value
  mpu.setZAccelOffset(0);   // <-- Replace 0 with your Value
  
  mpu.setXGyroOffset(0);    // <-- Replace 0 with your Value
  mpu.setYGyroOffset(0);    // <-- Replace 0 with your Value
  mpu.setZGyroOffset(0);    // <-- Replace 0 with your Value
  // ==========================================================
  
  Serial.println("MPU Configured and Calibrated!");
}

// Everything that the Arduino needs to repetitively, constantly
void loop()
{

  // each line will read 14 bytes from registor 0x3B. 
  // (&) it accepts the values passed by reference (as a pointer). This edits them directly, as opposed to passing a copy
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

// 3. Convert raw integers to real units (float)
  float accelX_g = ax / accel_scale;
  float accelY_g = ay / accel_scale;
  float accelZ_g = az / accel_scale;

  float gyroX_ds = gx / gyro_scale;
  float gyroY_ds = gy / gyro_scale;
  float gyroZ_ds = gz / gyro_scale;

// 4. Print readable values
  Serial.print("Accel (g): ");
  Serial.print(accelX_g); Serial.print("\t");
  Serial.print(accelY_g); Serial.print("\t");
  Serial.print(accelZ_g); 
  
  Serial.print("\t | \tGyro (deg/s): ");
  Serial.print(gyroX_ds); Serial.print("\t");
  Serial.print(gyroY_ds); Serial.print("\t");
  Serial.println(gyroZ_ds);

  delay(DELAY_INTERVAL);

}


void checkWhoAmI()
{
  
  // check WHOAMI manually
  Wire.beginTransmission(0x68);
  Wire.write(0x75);  // WHO_AM_I
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 1);

  if (Wire.available()) {
    byte whoami = Wire.read();
    Serial.print("WHO_AM_I = 0x");
    Serial.println(whoami, HEX);
  }
}