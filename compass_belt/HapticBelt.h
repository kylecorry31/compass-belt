#ifndef Haptic_Belt_H
#define Haptic_Belt_H

#include <Arduino.h>

/*
    A haptic belt with the following directions:

                0
            45     315
         90           270
           135     225
               180 

    The pins in the constructor match up to the diagram above clockwise starting at 0.

    Note: Because the belt displays where North is, vibrating 270 (middle right) will correspond to West, not East.
*/

class HapticBelt
{
    private:
        int haptic_pins_[8];
        bool isDirectionValid(int direction);
    public:
        HapticBelt(int haptics[8]);
        void on(int direction, int power);
        void off(int direction);
        void off();
};
#endif
