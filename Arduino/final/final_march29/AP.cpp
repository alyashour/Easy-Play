#include "AP.h"
#include "htmlData.h"

// const bool readEEPROM = true;

// const uint EEPROM_SSID_ADDRESS = 0;
// const uint EEPROM_PASS_ADDRESS = 100;
// const uint EEPROM_USERNAME_ADDRESS = 200;

char ssid[] = "arduino_access_point";        // your network SSID (name)
char pass[] = "1234567890";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;
WiFiServer server(80);

String clientMessage = "";
bool flash = false;

String input_ssid = "";
String input_username = "";
String input_pass = "***********";
bool enterpriseNetwork = false;

void setupSVR(bool doEnterprise, bool &doAP){
  doAP = false;

  Serial.println("=========================================================");
  Serial.println("Attempting to connect to internet.");
  Serial.println("SSID: " + input_ssid + "\nUsername: " + input_username + "\nPassword: " + input_pass + "\nEnterprise? " + enterpriseNetwork ? "true" : "false");

  if (doEnterprise){
    while(status != WL_CONNECTED){
      Serial.print("Attempting to connect to enterprise network named: ");
      Serial.println(input_ssid);
      status = WiFi.beginEnterprise((char*)input_ssid.c_str(), (char*)input_username.c_str(), (char*)input_pass.c_str());

      delay(10000);
    }
  }
  else{
    while(status != WL_CONNECTED) {
      Serial.print("Attempting to connect to network named: ");
      Serial.println(input_ssid);
      status = WiFi.begin((char*)input_ssid.c_str(), (char*)input_pass.c_str());

      delay(10000);
    }
  }

  // successful connection
  printWiFiStatus();

  // save ssid, username, & password to EEPROM
  // Serial.println("Attempting to save data");
  // EEPROM.put(EEPROM_SSID_ADDRESS, input_ssid);
  // EEPROM.put(EEPROM_PASSWORD_ADDRESS, input_password);
  // EEPROM.put(EEPROM_USERNAME_ADDRESSS, input_username);
  // Serial.println("Data saved to EEPROM");
}

void setup_AP(){
  Serial.println("\n\n=================================");
  Serial.println("Access Point Web Server");
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // this starts the AP, return is yes or no if it succeeded
  status = WiFi.beginAP(ssid, pass);

  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");

    // don't continue
    while (true);
  }

  // wait 5 seconds for connection:
  delay(5000);

  // start the web server on port 80
  server.begin();

  // you're connected now, so print out the status
  printWiFiStatus();

  // add stuff to the server
  server.println("test");
}

void printWiFiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);
}

bool loop_AP(bool &doAP){
  bool doRepeat = true;
  // compare the previous status to the current status
  if (status != WiFi.status()) {

    // it has changed update the variable
    status = WiFi.status();
  }

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    Serial.println("Client connected");

    while (client.connected()) {            // loop while the client's connected

      if (client.available()) {             // if there's bytes to read from the client,

        char c = client.read();             // read a byte, then

        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          // if (currentLine.startsWith("GET /")){
          //   Serial.println(currentLine);
          // }
          
          // this is the save form request
          if (currentLine.startsWith("GET /S")){
            /* save form data */
            // parse from "ssid=" to "&"
            input_ssid = getSubstring(currentLine, "ssid=", "&");
            // parse from "username=" to "&"
            input_username = getSubstring(currentLine, "username=", "&");
            // parse from "password=" to ' '
            input_pass = getSubstring(currentLine,"password=", " ");
            // done ssid and password
          }

          // this is the connect request
          if (currentLine.startsWith("GET /C")){
            String temp = getSubstring(currentLine, "enterprise=", " ");
            enterpriseNetwork = temp.equals("on");
            setupSVR(enterpriseNetwork, doAP);
          }

          if (currentLine.length() == 0){
            sendResponse(client);
            break;  // break out of loop when the response is sent
          }
          else {
            clientMessage += currentLine + '\n';
            currentLine = "";
          }
        }

        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }

    Serial.println("Client disconnected");

    // close the connection:

    client.stop();
  }

  return doRepeat;
}

/* My baby */
void html_AP(WiFiClient client){
  client.print(getHTML(input_ssid, input_username, input_pass));
}

String getSubstring(String inputString, String startWord, String endWord) {
  // Find the starting index of the first word
  int startIndex = inputString.indexOf(startWord);
  if (startIndex == -1) {
    // The start word was not found in the string
    return "";
  }

  // Find the starting index of the substring
  startIndex += startWord.length();

  // Find the ending index of the substring
  int endIndex = inputString.indexOf(endWord, startIndex);
  if (endIndex == -1) {
    // The end word was not found in the string
    return "";
  }

  // Extract the substring
  String substring = inputString.substring(startIndex, endIndex);

  // Return the substring
  return substring;
}

void sendResponse(WiFiClient client){
  /* THE HEADER */
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  /* CONTENT */
  // the content of the HTTP response follows the header:
  html_AP(client);

  /* END */
  // The HTTP response ends with another blank line:
  client.println();
}

bool isEnterprise(){
  return enterpriseNetwork;
}
