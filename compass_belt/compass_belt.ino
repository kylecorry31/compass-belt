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
const float declination = -14;

// The maximum duration (ms) between presses to be considered a double presses 
const long doublePressDurationMillis = 500L;

// The default vibration duration in milliseconds
const unsigned long vibrationDurationMillis = 200UL;

// The default vibration interval in milliseconds
const unsigned long vibrationInvervalMillis = 60UL * 1000UL;

const unsigned long serialKeepDurationMillis = 10UL * 1000UL;

// ----- END CONFIGURATION -----

int belt_pins[8] = {northPin, northWestPin, westPin, southWestPin, southPin, southEastPin, eastPin, northEastPin};

long lastPressedTime = -10000L;
long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;
bool wasOn = false;

HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt, vibrationDurationMillis, vibrationInvervalMillis};
Compass compass{declination};


void setup()
{
  pinMode(alwaysOnButtonPin, INPUT);
  compass.begin();
  Serial.begin(9600);
//  delay(1000);
//  Serial.println("Calibrating");
//  compass.calibrate();
//  delay(10000);
}

void loop()
{
  bool isOn = digitalRead(alwaysOnButtonPin);
  if (!wasOn && isOn){
    if (millis() - lastPressedTime <= doublePressDurationMillis){
      compassBelt.setAlwaysOn(!compassBelt.isAlwaysOn());
      lastPressedTime = -10000;
    } else {
      lastPressedTime = millis();
    }
  }

  wasOn = isOn;

  float heading = compass.getHeading();

  if (Serial.available() > 0) {
    String serialHeading = Serial.readString();
    lastSerialHeading = serialHeading.toFloat();
    lastSerialRecv = millis();
  }

   if (millis() - lastSerialRecv < serialKeepDurationMillis){
    heading = lastSerialHeading;
   }
  
  // Serial.println(heading);
  compassBelt.update(heading);  
}

// Double press -> toggle always on
// Hold for 10 seconds -> toggle calibration
