#ifndef Compass_Belt_H
#define Compass_Belt_H

#include "HapticBelt.h"
#include <Arduino.h>

class CompassBelt
{
    public:
        CompassBelt(HapticBelt* belt, unsigned long vibrationDuration, unsigned long vibrationInverval);
        void update(double heading);
        void off();
        void setAlwaysOn(bool alwaysOn);
        bool isAlwaysOn();
    private:
        HapticBelt* belt_;
        unsigned long onDuration_;
        unsigned long vibrationInterval_;
        long lastOn_;
        int lastDirection_;
        bool alwaysOn_ = false;
        bool shouldStopVibrating();
        bool shouldStartVibrating();
};
#endif
