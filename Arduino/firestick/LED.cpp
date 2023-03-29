#import "LED.h"
#import <Arduino.h>

LED::LED(int pin){
  this->pin = pin;
  brightness = LED::OFF;
  pinMode(pin, OUTPUT);
}

void LED::turnOn(){
  digitalWrite(pin, LED::ON);
  brightness = LED::ON;
}

void LED::turnOff(){
  digitalWrite(pin, LED::OFF);
  brightness = LED::OFF;
}

void LED::toggle(){
  brightness == LED::ON ? turnOff() : turnOn();
}

int LED::set(bool input){
  if (input == LED::ON) turnOn();
  else if (input == LED::OFF) turnOff();
  else
    // input invalid
    return -1;
  return 0;
}

int LED::changeBrightness(float &rate){
  if (brightness + rate >= 0){
    brightness += rate;
    analogWrite(pin, brightness);
  } 
}