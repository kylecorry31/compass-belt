#include "CompassBelt.h"

CompassBelt::CompassBelt(HapticBelt* belt)
{
    belt_ = belt;
    onDuration_ = 75;
    lastOn_ = 0;
    lastDirection_ = -1;
}

void CompassBelt::update(double heading)
{

    if (heading < 0 || heading >= 360)
    {
        // Contract violation
        return;
    }

    const int direction_threshold = 15;

    int direction = (int)(round(heading / 45) * 45) % 360;

    // Add a buffer zone
    if (lastDirection_ != -1 && abs(direction - heading) > direction_threshold)
    {
        direction = lastDirection_;
    }

    if (direction != lastDirection_)
    {
        belt_->off(lastDirection_);
        lastDirection_ = direction;
        belt_->on(direction);
        lastOn_ = (long)millis();
    }

    if ((long)millis() - lastOn_ >= onDuration_)
    {
        belt_->off(direction);
    }

}
