// start access point
#include "AP.h"
#include "firestick.h"

bool doAP = true;  // this is testing, turns off the AP code
char* SERVER = "192.168.0.14";

/* Arduino Defaults */
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {;} // wait for serial port to connect. Needed for native USB port only

  setup_AP();
}

void loop() {
  if (doAP) loop_AP(doAP);
  else loop_firestick(SERVER);
}
