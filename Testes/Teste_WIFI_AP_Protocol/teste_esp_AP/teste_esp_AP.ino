#include <ESP8266WiFi.h>

const char *ssid = "ESP-Ralph";
const char *password = "1234567890"; // WEP key: 10 characters (64-bit) or 26 characters (128-bit) in hexadecimal format.

void setup() {
  Serial.begin(115200);
  
  // Set the device as an access point
  WiFi.mode(WIFI_AP);
  
  // Set up the access point with WEP encryption
  WiFi.softAP(ssid); // The last parameter '0' specifies WEP encryption
  
  Serial.println("Access point started with WEP encryption");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Your code here
}

