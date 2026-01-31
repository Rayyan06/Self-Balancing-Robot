/*
An I2C scanner to test for I2C devices
*/

#include <Wire.h>

void setup() {
  // Initialize I2C and Serial communication
  Wire.begin();
  Serial.begin(9600);

  //wait for the serial to wakeup from its snooze
  while(!Serial);

  Serial.println("Scanning...");
}

void loop() {
  // arduino "byte" object is essentially what we know as u_int8_t
  byte error, address;

  int nDevices = 0;

  // I presume this scans all open ports
  for(address = 0; address < 127; address++)
  {
    // Telegraph: SEND MESSAGE!
    Wire.beginTransmission(address);
    // the endTransmission method presumably returns the error code if failed.
    error = Wire.endTransmission();

    // 0 is often used for no error. So, device found!
    if(error == 0)
    {
      Serial.print("I2C device found at 0x");
      //lets print the hex of the port
      if(address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
    // no else, because if error, no device was found at that port
  }

  if(nDevices == 0)
  {
    Serial.println("No I2C Devices Found."); 
  }

  // repeatedly scanning
  delay(2000);

}
