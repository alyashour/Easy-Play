#include <WiFiNINA.h>
#import "BTN.h"
#import "LED.h"

bool skipServerAttempt = true;

/* internet things */
const char* SSID = "Ashour";
const char* PASSWORD = "Hoda2007";
const char* SERVER = "192.168.0.14";  // the ip of the computer
const int PORT_NUM = 8881;

WiFiClient client;

/* button things */
bool myBool = false;
Button button(12, &myBool); // add switch var
LED led(LED_BUILTIN);
LED btnLight(11);
float fadeRate = -1;

void sendPress(){
  if (client.connect(SERVER, PORT_NUM)) {
    client.print("GET /button HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(SERVER);
    client.print("\r\n");
    client.print("Connection: close\r\n");
    client.print("\r\n");
    client.stop();
  } else {
    Serial.println("Connection failed");
  }
}

/* program */
void setup(){
  Serial.begin(9600);
  do {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(SSID, PASSWORD);
    delay(1000);
  } while (WiFi.status() != WL_CONNECTED);

  Serial.println("Connected to WiFi");
}

void loop(){
  // this flip moves the send delay to after the button is pressed (so there is no button press delay for the light)
  // this delay is STILL present however, and is just present after the light comes up
  // this means consecutive presses when the internet connection is slow or disconnected will be delayed by about 28 seconds
  bool doSendPress = button.update();
  led.changeBrightness(fadeRate);
  btnLight.changeBrightness(fadeRate);
  delay(10);

  // button was pressed, this is only called once per press
  if (doSendPress) {
    btnLight.turnOn();
    if (!skipServerAttempt) sendPress();
  }
}