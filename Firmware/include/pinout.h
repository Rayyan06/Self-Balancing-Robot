#ifndef PINOUT_H
#define PINOUT_H

// --- IMU PINS ---
// SDA -> A4
// SCL -> A5
#define INT 2 // digital pin 2

// --- MOTOR DRIVER PINS (L298N or similar) ---
#define EN_A 9 // PWM Pin for Left Motor Speed
#define IN_1 8 // Direction 1 Left
#define IN_2 7 // Direction 2 Left

#define EN_B 10 // PWM Pin for Right Motor Speed
#define IN_3 5  // Direction 1 Right
#define IN_4 4  // Direction 2 Right

// --- HC204 Pins --- 
#define TRIG 12
#define ECHO 13

#endif