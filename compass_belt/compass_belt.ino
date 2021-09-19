#include "HapticBelt.h"
#include "CompassBelt.h"
#include "Compass.h"
#include "Button.h"

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
const float declination = 0;

// The default vibration duration in milliseconds
const unsigned long vibrationDurationMillis = 200UL;

// The default vibration interval in milliseconds
const unsigned long vibrationInvervalMillis = 60UL * 1000UL;

const unsigned long serialKeepDurationMillis = 10UL * 1000UL;

// ----- END CONFIGURATION -----

int belt_pins[8] = {northPin, northWestPin, westPin, southWestPin, southPin, southEastPin, eastPin, northEastPin};
Button button{alwaysOnButtonPin};

long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;

HapticBelt belt{belt_pins};
CompassBelt compassBelt{&belt, vibrationDurationMillis, vibrationInvervalMillis};
Compass compass{declination};


void setup()
{
  compass.begin();
  Serial.begin(9600);
}

void loop()
{
  ButtonState buttonState = button.read();
  if (buttonState.isDouble){
    compassBelt.setAlwaysOn(!compassBelt.isAlwaysOn());
  }

  if (buttonState.isLong){
    calibrate();  
  }

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

void calibrate(){
  for (int i = 0; i < 360; i += 45){
    compassBelt.update(i);
    delay(200);  
  }
  compassBelt.off();
  delay(1000);
  Serial.println("Calibrating");
  compass.calibrate();
  delay(10020);
  for (int i = 360; i > 0; i -= 45){
    compassBelt.update(i);
    delay(200);  
  }
  compassBelt.off();
}
