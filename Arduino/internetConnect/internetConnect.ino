// start access point
#include "AP.h"

bool doAP = true;  // this is testing, turns off the AP code

/* Arduino Defaults */
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {;} // wait for serial port to connect. Needed for native USB port only

  if (doAP) setup_AP();
}

void loop() {
  if (doAP) loop_AP();
}