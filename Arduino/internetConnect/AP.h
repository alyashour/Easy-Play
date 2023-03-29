#ifndef AP_h
#define AP_h

//#include <Arduino.h>
#include <WiFiNINA.h>

extern char ssid[]; // your network SSID (name)
extern char pass[]; // your network password (use for WPA, or use as key for WEP)
extern int status;
extern WiFiServer server;
extern String clientMessage;
extern bool flash;

extern String input_ssid;
extern String input_username;
extern String input_pass;
extern bool enterpriseNetwork;

extern int led;
extern bool lightOn;
extern double lastPulse;

void setupSVR();

void setup_AP();
bool loop_AP();
void printWiFiStatus();

/* My baby */
void html_AP(WiFiClient client);
String getSubstring(String inputString, String startWord, String endWord);
void sendResponse(WiFiClient client);

bool isEnterprise();

#endif