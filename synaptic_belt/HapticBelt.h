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

    Pins are listed clockwise, starting at index 0 equaling 0 degrees and ending with index 7 equaling 315 degrees.

*/

class HapticBelt
{
    private:
        int haptic_pins_[8];
        bool isDirectionValid(int direction);
    public:
        HapticBelt(int haptics[8]);
        void on(int direction);
        void off(int direction);
};
#endif
