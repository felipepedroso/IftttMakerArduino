/*
*	Created by Felipe Augusto Pedroso, February 08, 2016.
*/
#ifndef IftttMaker_h
#define IftttMaker_h

#include <Arduino.h>
#include <WiFi.h>
#include "rgb_lcd.h"

#define IFTTT_SERVER "maker.ifttt.com"

class IftttMaker
{
  public:
    void initialize(char*);
    void connectToWifi(char*, char*);
    void fireEvent(char*);
    void fireEvent(char*, char*, char*, char*);
    void debugPrint(char*);
    void debugPrint(char*, char*);
    
  private:
    char* _makerChannelKey;
    const int IFTTT_PORT = 80;
    
    WiFiClient _client;
    int wifiStatus;
    bool isConnected();
    void makeGetRequest(char*, int, char*);
    void makePostRequest(char*, int, char*, char*);
    
    rgb_lcd lcd;
};

#endif