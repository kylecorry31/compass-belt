#include "CompassBelt.h"

CompassBelt::CompassBelt(HapticBelt* belt)
{
    _belt = belt;
    _onDuration = 20;
    _lastOn = 0;
    _lastDirection = -1;
}

void CompassBelt::Update(double heading)
{

    if (heading < 0 || heading >= 360)
    {
        // Contract violation
        return;
    }

    const int direction_threshold = 15;

    int direction = (round(heading / 45) * 45) % 360;

    // Add a buffer zone
    if (_lastDirection != -1 && abs(direction - heading) > direction_threshold)
    {
        direction = _lastDirection;
    }

    if (direction != _lastDirection)
    {
        _belt->Off(_lastDirection);
        _lastDirection = direction;
        _belt->On(direction);
        _lastOn = millis();
    }

    if (millis() - _lastOn >= _onDuration)
    {
        _belt->Off(direction);
    }

}

