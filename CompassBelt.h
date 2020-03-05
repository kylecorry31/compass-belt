#ifndef Compass_Belt_H
#define Compass_Belt_H

#include "HapticBelt.h"
#include <Arduino.h>

class CompassBelt
{
    private:
        HapticBelt* _belt;
        long _onDuration;
        long _lastOn;
        int _lastDirection;
    public:
        CompassBelt(HapticBelt* belt);
        void Update(double heading);
};
#endif