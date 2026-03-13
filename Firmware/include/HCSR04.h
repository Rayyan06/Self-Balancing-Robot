#ifndef HC_SR204
#define HC_SR204

#include <Arduino.h>

class HCSR04
{
private:
    uint8_t trigPin;
    uint8_t echoPin;

public:
    HCSR04(uint8_t trig, uint8_t echo);
    void begin();
    void pulse() const;
    float getDistance() const;
};

#endif