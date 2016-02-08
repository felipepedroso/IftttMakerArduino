/*
*	Created by Felipe Augusto Pedroso, February 08, 2016.
*/
#include <WiFi.h>
#include "rgb_lcd.h"
#include <Wire.h>
#include <IftttMaker.h>

// Wifi parameters
char SSID[] = "<PUT_YOUR_WIFI_SSID_HERE>";
char PASSWORD[] = "<PUT_YOUR_WIFI_PASSWORD_HERE>";

IftttMaker iftttMaker;

// IFTTT Maker Channel Key. 
// Get one here: https://ifttt.com/maker
char makerChannelKey[] = "<PUT_YOUR_KEY_HERE>";

char eventName[] = "eventName"; // put your event name here.

int delayBetweenEvents = 5000;

void setup() {
  iftttMaker.initialize(makerChannelKey);
  iftttMaker.connectToWifi(SSID, PASSWORD);
}

void loop() {
  iftttMaker.fireEvent(eventName);
  delay(delayBetweenEvents);
}
