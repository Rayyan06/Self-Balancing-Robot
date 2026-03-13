#include <Arduino.h>
#include "pinout.h"
#include "HCSR04.h"

HCSR04 ultrasonic(TRIG, ECHO);
float distance;

void setup()
{
  ultrasonic.begin();
  Serial.begin(38400);
}

void loop()
{
  distance = ultrasonic.getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}