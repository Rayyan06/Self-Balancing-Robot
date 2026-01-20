/*
=============Author==============
By Muhammed Rayyan Khan

=============Notes================
HINT: Before running this program, try testing an I2C Scanner located in the folder
This program interfaces with the MPU6052C I2C device and reads basic accelerometer and gyro data to the serial
=============Sources==============


https://github.com/ElectronicCats/mpu6050/wiki

// UPDATE: we cannot use this library as we have a MPU60502C, but still could be a useful reference
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
// The  Accelerometer range we are using
#define ACCEL_RANGE MPU6050_RANGE_8_G

// how often (in ms) we grab data from the MPU
#define DELAY_INTERVAL 500


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
  //mpu.setAccelerometerRange(ACCEL_RANGE);






}

// Everything that the Arduino needs to repetitively, constantly
void loop()
{

  // each line will read 14 bytes from registor 0x3B. 
  // (&) it accepts the values passed by reference (as a pointer). This edits them directly, as opposed to passing a copy
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // print out the values to the serial, tab-seperated
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);

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