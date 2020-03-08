#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"

// int belt_pins[8] = {3, 10, 4, 5, 6, 7, 8, 12};
int belt_pins[8] = {3, 12, 8, 7, 6, 5, 4, 10};
int alwaysOnPin = 13;

bool wasOn = false;

HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt};
Compass compass{};

void setup()
{
  pinMode(alwaysOnPin, INPUT);
  compass.begin();
  Serial.begin(9600);
  // delay(10000);
  // Serial.println("Calibrating");
  // compass.calibrate();
  // delay(10000);
}

void loop()
{
  bool isOn = digitalRead(alwaysOnPin);
  if (!wasOn && isOn){
    compassBelt.setAlwaysOn(!compassBelt.isAlwaysOn());
  }

  wasOn = isOn;

  float heading = compass.getHeading();
  Serial.println(heading);
  compassBelt.update(heading);  
}
