#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"

int belt_pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt};
Compass compass{};

void setup()
{
  Serial.begin(9600);
  compass.begin();
}

void loop()
{
  float heading = compass.getHeading();
  compassBelt.update(heading);
}
