/*
*	Created by Felipe Augusto Pedroso, February 08, 2016.
*	Modified by Paulo Leonel Teixeira. May 18, 2016.
*/
#ifndef IftttMaker_h
#define IftttMaker_h

#include <Arduino.h>
#include <WiFi.h>
#include <Ethernet.h>

#define IFTTT_SERVER "maker.ifttt.com"

class IftttMaker
{
  public:
    void initialize(char*);
    void connectToWifi(char*, char*);
	void connectToEthernet(byte*);
	void connectToEthernet(byte* mac, IPAddress ip);
    void fireEvent(char*);
    void fireEvent(char*, char*, char*, char*);
	void clientPrintln(const __FlashStringHelper * toPrint);
	void clientPrintln(char* toPrint);
	int clientConnect(char* server, int port);
	void clientStop();
    
  private:
    char* _makerChannelKey;
    const int IFTTT_PORT = 80;
    
	EthernetClient _ethernetClient;
	WiFiClient _wifiClient;
	
	bool _isEthernet;
    int wifiStatus;
    void makeGetRequest(char*, int, char*);
    void makePostRequest(char*, int, char*, char*);
};

#endif