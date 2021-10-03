#include "Arduino.h"

class DRV8837 {
    private:
        float target;
        float current;
        float accel = 1;
        unsigned long updateTimer;
        unsigned long updateInterval;
        unsigned char IN1;
        unsigned char IN2;
        unsigned char IN1_Channel;
        unsigned char IN2_Channel;
        unsigned char bitWidth;
        unsigned int pwmFreq;

    public:
        DRV8837(unsigned char IN1_PIN, unsigned char IN2_PIN, unsigned char ch0, unsigned char ch1);
        DRV8837(unsigned char IN1_PIN, unsigned char IN2_PIN, unsigned char ch0, unsigned char ch1, unsigned char width, unsigned int freq);
        void setPoint(float percent);
        void setAccel(float rate);
        void run();
        void brake();
};