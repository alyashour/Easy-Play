#import "LED.h"
#import <Arduino.h>

LED::LED(int pin){
  this->pin = pin;
  state = LED::OFF;
  pinMode(pin, OUTPUT);
}

void LED::turnOn(){
  digitalWrite(pin, LED::ON);
  state = LED::ON;
}

void LED::turnOff(){
  digitalWrite(pin, LED::OFF);
  state = LED::OFF;
}

void LED::toggle(){
  state == LED::ON ? turnOff() : turnOn();
}

int LED::set(bool input){
  if (input == LED::ON) turnOn();
  else if (input == LED::OFF) turnOff();
  else
    // input invalid
    return -1;
  return 0;
}