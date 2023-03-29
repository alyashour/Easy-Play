#ifndef LED_h
#define LED_h

#include <Arduino.h>

class LED{
  private:
  int pin;

  public:
  float brightness;
  const static int ON = 255;
  const static int OFF = LOW;

  LED(int pin);
  void turnOn();
  void turnOff();
  void toggle();
  int set(bool input);
  int changeBrightness(float &input);
};

#endif
