#include <Arduino.h>

void setup()
{
    // Start the serial port at 115200 baud rate
    Serial.begin(115200);

    // Wait for the serial port to connect
    while (!Serial)
    {
        ;
    }
    Serial.println("Robot starting up...");
}

void loop()
{
    Serial.println("Hello, IEEE Robot!");
    delay(1000); // Wait 1 second so we don't flood the monitor
}