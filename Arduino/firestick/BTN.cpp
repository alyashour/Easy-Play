#import "BTN.h"
#import <Arduino.h>

Button::Button(int pin, bool* control = nullptr){
  this->pin = pin;
  this->control = control;
  lastState = LOW;
  pinMode(pin, INPUT_PULLUP);
}

bool Button::update(){
  bool returnBool = false;
  if (millis() - timeSinceStateChange > debounceDuration){
    byte state = getState();
    if (state != lastState){
      lastState = state;
      timeSinceStateChange = millis();

      // only open the pointer if not null
      if (control){
        if (isPressed()){
          // VV do everything below VV
          //Serial.println("Variable flipped on button press");
          *control = !(*control); // unwrap and flip the boolean
          returnBool = true;
        }
        else{
          //Serial.println("Nothing done on button release");
        }
      }
      else{
        if (isPressed()) Serial.println("Button pressed");
        else Serial.println("Button released");
      }
    }
  }
  return returnBool;
}

bool Button::getState(){
   // idk why this has to be flipped
   // probably something to do with pullups and pulldowns
   // either way
  return !digitalRead(pin);
}

bool Button::isPressed(){
  return getState() == Button::PRESSED;
}
