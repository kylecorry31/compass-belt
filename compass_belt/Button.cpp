#include "Button.h"

Button::Button(int pin)
{
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);  
}

ButtonState Button::read()
{
  // TODO: Add debouncer
  bool pressed = digitalRead(pin);
  bool down = pressed && !wasPressed;
  bool up = !pressed && wasPressed;
  long pressDuration = 0;

  if (down){
    lastDown = millis();  
  }

  if (up){
    lastUp = millis();  
    pressDuration = lastUp - lastDown;
  }

  wasPressed = pressed;

  bool isLongPress;
  bool isSinglePress;

  if (pressed){
    isLongPress = millis() - lastDown >= 1000;
  } else if (up){
    isLongPress = pressDuration >= 1000;  
  } else {
    isLongPress = false;
  }

  if (up){
    isSinglePress = pressDuration < 500 && pressDuration > 20;
  } else {
    isSinglePress = false;
  }

  bool isDoublePress = isSinglePress && millis() - lastSinglePress < 500 && millis() - lastDoublePress > 1000;

  if (isDoublePress){
    lastDoublePress = millis();  
  }

  if (isSinglePress){
    lastSinglePress = millis();  
  }

  bool sendLongPress = isLongPress && !wasLong;
  wasLong = isLongPress;

  return ButtonState {
    pressed,
    down,
    up,
    sendLongPress,
    isSinglePress,
    isDoublePress,
    lastDown,
    lastUp
  };
}
