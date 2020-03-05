#include "HapticBelt.h"
#include "CompassBelt.h"

int belt_pins[8] = {1, 2, 3, 4, 5, 6, 7, 8};

HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt};

void setup()
{
	// TODO: Setup compass
}

void loop()
{
	// TODO: Read compass
    double heading = 0;

    compassBelt.Update(heading);
}
