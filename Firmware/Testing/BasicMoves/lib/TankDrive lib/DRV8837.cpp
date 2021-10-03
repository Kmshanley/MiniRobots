#include "DRV8837.h"
#include "driver/ledc.h"
#include "esp_err.h"

DRV8837::DRV8837(unsigned char IN1_PIN, unsigned char IN2_PIN, unsigned char ch0, unsigned char ch1) {
    IN1 = IN1_PIN;
    IN2 = IN2_PIN;
    IN1_Channel = ch0;
    IN2_Channel = ch1;
    updateInterval = 100; //100ms
    bitWidth = 10;
    pwmFreq = 5000;
    ledcSetup(IN1_Channel, pwmFreq, bitWidth); //default 5khz, 10bit PWM
    ledcSetup(IN2_Channel, pwmFreq, bitWidth); //default 5khz, 10bit PWM
    ledcAttachPin(IN1, ch0);
    ledcAttachPin(IN2, ch1);
}

DRV8837::DRV8837(unsigned char IN1_PIN, unsigned char IN2_PIN, unsigned char ch0, unsigned char ch1, unsigned char width, unsigned int freq){
    IN1 = IN1_PIN;
    IN2 = IN2_PIN;
    IN1_Channel = ch0;
    IN2_Channel = ch1;
    updateInterval = 100; //100ms
    bitWidth = width;
    pwmFreq = freq;
    ledcSetup(IN1_Channel, freq, width);
    ledcSetup(IN1_Channel, freq, width);
    ledcAttachPin(IN1, ch0);
    ledcAttachPin(IN2, ch1);
}

void DRV8837::run() {
    if (target == 0) {
        brake();
    }
    if ((millis() - updateTimer) > updateInterval) {
        if (target > 0) {
            if (current < abs(target)) {
                current += accel;
                ledcWrite(IN1_Channel, current);
                ledcWrite(IN2_Channel, 0);
            }
            else if (current > abs(target)) {
                current -= accel;
                ledcWrite(IN1_Channel, current);
                ledcWrite(IN2_Channel, 0);
            }
        }
        else if (target < 0) {
            if (current < abs(target)) {
                current += accel;
                ledcWrite(IN1_Channel, 0);
                ledcWrite(IN2_Channel, current);
            }
            else if (current > abs(target)) {
                current -= accel;
                ledcWrite(IN1_Channel, 0);
                ledcWrite(IN2_Channel, current);
            }
        }
        updateInterval = millis();
    }
}

//Input 0-100, ouput correct PWM value mapping (according to resolution)
void DRV8837::setPoint(float percent) {
    //(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
    target = (((pow(2, bitWidth)) - 1) / 100) * percent;
}

void DRV8837::brake() {
    ledcWrite(IN1_Channel, 0);
    ledcWrite(IN2_Channel, 0);
    current = 0;
    target = 0;
}

void DRV8837::setAccel(float rate) {
    accel = rate;
}