// Import the Arduino I2C library because the MPU6050 is an I2C device
#include <Wire.h>

// The Adafruit MPU6050 library we are using to avoid having to configure and interact with the registers directly
// first, include the device driver
#include <Adafruit_MPU6050.h>

// initialize an MPU class.
Adafruit_MPU6050 mpu;

// One-time actions to initialize and configure I2C devices and Arduino
void setup()
{
  Serial.begin(9600);
  
  // Initialize and enable I2C on arduino
  Wire.begin();

  // Initialize the MPU 6050
  mpu.begin(


  Serial.println("MPU6050 Set Up");
}

// Everything that the Arduino needs to repetitively, constantly
void loop()
{
  Serial.println("Repeat");
  delay(100);
}