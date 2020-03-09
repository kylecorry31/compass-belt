#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"

// ----- CONFIGURATION -----

// Pins
const int northPin = 3;
const int northWestPin = 12;
const int westPin = 8;
const int southWestPin = 7;
const int southPin = 6;
const int southEastPin = 5;
const int eastPin = 4;
const int northEastPin = 10;
const int alwaysOnButtonPin = 13;

// Geomagnetic declination (set this based on your location)
const float declination = 13;

// ----- END CONFIGURATION -----

int belt_pins[8] = {northPin, northWestPin, westPin, southWestPin, southPin, southEastPin, eastPin, northEastPin};

bool wasOn = false;

HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt};
Compass compass{declination};

void setup()
{
  pinMode(alwaysOnButtonPin, INPUT);
  compass.begin();
  Serial.begin(9600);
  // delay(10000);
  // Serial.println("Calibrating");
  // compass.calibrate();
  // delay(10000);
}

void loop()
{
  bool isOn = digitalRead(alwaysOnButtonPin);
  if (!wasOn && isOn){
    compassBelt.setAlwaysOn(!compassBelt.isAlwaysOn());
  }

  wasOn = isOn;

  float heading = compass.getHeading();
  Serial.println(heading);
  compassBelt.update(heading);  
}
