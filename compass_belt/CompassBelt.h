#ifndef Compass_Belt_H
#define Compass_Belt_H

#include "HapticBelt.h"
#include <Arduino.h>

class CompassBelt
{
    private:
        HapticBelt* belt_;
        long onDuration_;
        long lastOn_;
        int lastDirection_;
    public:
        CompassBelt(HapticBelt* belt);
        void update(double heading);
};
#endif
