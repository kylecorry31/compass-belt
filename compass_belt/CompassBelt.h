#ifndef Compass_Belt_H
#define Compass_Belt_H

#include "HapticBelt.h"
#include <Arduino.h>

class CompassBelt
{
    private:
        HapticBelt* belt_;
        unsigned long onDuration_;
        long lastOn_;
        int lastDirection_;
        bool alwaysOn_ = false;
    public:
        CompassBelt(HapticBelt* belt);
        void update(double heading);
        void setAlwaysOn(bool alwaysOn);
        bool isAlwaysOn();
};
#endif
