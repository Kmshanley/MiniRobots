#include "main.h"
#include "DRV8837.h"

DRV8837 M1 = DRV8837(M1IN1, M1IN2, 0, 1);
DRV8837 M2 = DRV8837(M2IN1, M2IN2, 2, 3);
DRV8837 M3 = DRV8837(M3IN1, M3IN2, 4, 5);
DRV8837 M4 = DRV8837(M4IN1, M4IN2, 6, 7);

uint32_t changeInterval;
float spd;

void setup() {
  spd = 70;
}

void loop() {
  if (millis() - changeInterval > 2000) {
    M1.setPoint(spd);
    M2.setPoint(spd);
    M3.setPoint(spd);
    M4.setPoint(spd);
    spd -= (spd * 2);
    changeInterval = millis();
  }
  M1.run();
  M2.run();
  M3.run();
  M4.run();
}