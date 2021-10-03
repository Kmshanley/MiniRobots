#include "Arduino.h"
#include "DRV8837.h"

class tankdrive {
private:
    /* data */
public:
    tankdrive(DRV8837 M1, DRV8837 M2, DRV8837 M3, DRV8837 M4);
    void turn(float speed, bool direction);
    void forward(float speed);
    void backward(float speed);
    void brake();
    void drive();
    
};

