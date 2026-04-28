#include "pinout.h"
#include "Arduino.h"

// Note: Use your existing Motor library class,
// or if that fails, simply use pinMode/digitalWrite/analogWrite directly.

void setup()
{
  // Motor A pins
  pinMode(EN_A, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);

  // Motor B pins
  pinMode(EN_B, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  // Set Speed (0-255)
  analogWrite(EN_A, 150);
  analogWrite(EN_B, 150);
}

void loop()
{
  // --- FORWARD ---
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  delay(2000);

  // --- STOP ---
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  delay(1000);

  // --- BACKWARD ---
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  delay(2000);

  // --- STOP ---
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  delay(1000);
}