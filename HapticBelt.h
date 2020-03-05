#ifndef Haptic_Belt_H
#define Haptic_Belt_H

#include <Arduino.h>

/*
    A haptic belt with the following directions:

                0
           315     45
        270           90
           225    135
               180 

*/

class HapticBelt
{
    private:
        int _haptic_pins[8];
        bool IsDirectionValid(int direction);
    public:
        HapticBelt(int haptics[8]);
        void On(int direction);
        void Off(int direction);
};
#endif