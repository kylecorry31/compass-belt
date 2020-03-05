#include "HapticBelt.h"

HapticBelt::HapticBelt(int haptics[8])
{
    memccpy(_haptic_pins, haptics, 8, sizeof(int));
    for (int i = 0; i < 8; i++)
    {
        pinMode(_haptic_pins[i], OUTPUT);
    }
}

bool HapticBelt::IsDirectionValid(int direction)
{
    return direction >= 0 && direction < 360 && direction % 45 == 0;
}

void HapticBelt::On(int direction)
{
    if (!IsDirectionValid(direction))
    {
        // Error condition
        return;
    }

    int position = direction / 45;

    digitalWrite(_haptic_pins[position], HIGH);
}

void HapticBelt::Off(int direction)
{
    if (!IsDirectionValid(direction))
    {
        // Error condition
        return;
    }

    int position = direction / 45;

    digitalWrite(_haptic_pins[position], LOW);
}