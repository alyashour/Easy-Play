#ifndef firestick_h
#define firestick_h

#import "BTN.h"
#import "LED.h"

bool skipServerAttempt = false;

/* internet things */
const int PORT_NUM = 8881;

WiFiClient client;

/* button things */
bool myBool = false;
Button button(12, &myBool); // add switch var
LED led(LED_BUILTIN);
LED btnLight(11);
float fadeRate = -1;

void sendPress(char* server_ip){
  if (client.connect(server_ip, PORT_NUM)) {
    client.print("GET /button HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(server_ip);
    client.print("\r\n");
    client.print("Connection: close\r\n");
    client.print("\r\n");
    client.stop();
  } else {
    Serial.println("Connection failed");
  }
}

void loop_firestick(char* server_ip){
  // this flip moves the send delay to after the button is pressed (so there is no button press delay for the light)
  // this delay is STILL present however, and is just present after the light comes up
  // this means consecutive presses when the internet connection is slow or disconnected will be delayed by about 28 seconds
  bool doSendPress = button.update();
  //led.changeBrightness(fadeRate);
  //btnLight.changeBrightness(fadeRate);
  //delay(10);

  // button was pressed, this is only called once per press
  if (doSendPress) {
    Serial.println("button pressed in firestick loop");
    btnLight.turnOn();
    if (!skipServerAttempt) sendPress(server_ip);
  }
}

#endif