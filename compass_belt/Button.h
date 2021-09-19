#ifndef Button_H
#define Button_H

struct ButtonState {
  bool pressed;
  bool down;
  bool up;
  bool isLong;
  bool isShort;
  bool isDouble;
  long pressDuration;
  long lastDownTime;
  long lastUpTime;
};

#include <Arduino.h>

class Button {
  public:
    Button(int pin);
    ButtonState read();

  private:
    int pin;
    bool wasPressed;
    bool wasLong;
    long lastDown;
    long lastUp;
    long lastSinglePress;
    long lastDoublePress;
};

#endif
