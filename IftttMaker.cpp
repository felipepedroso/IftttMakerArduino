/*
*	Created by Felipe Augusto Pedroso, February 08, 2016.
*	Modified by Paulo Leonel Teixeira. May 18, 2016.
*/
#include "IftttMaker.h"

void IftttMaker::initialize(char* makerChannelKey){
    _makerChannelKey = makerChannelKey;
    
    Serial.begin(115200);
    Serial.println("Initializing Arduino + IFFFT");
}

void IftttMaker::connectToWifi(char* ssid, char* password){
	_isEthernet = false;
    while (wifiStatus != WL_CONNECTED) {
        wifiStatus = WiFi.begin(ssid, password);
		String message = "Connecting to " + String(ssid);
        Serial.println(message);
        delay(1000);
    }
    
    Serial.println("Connected!");
    delay(500);
}

void IftttMaker::connectToEthernet(byte* mac){
	_isEthernet = true;
	if (Ethernet.begin(mac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP. Try IP address instead.");
		return;
	}
	Serial.println("Connecting to Ethernet");
	delay(1000);
	
	if (clientConnect(IFTTT_SERVER, IFTTT_PORT)) {
        Serial.println("Ethernet is working");
		clientStop();
    } else {
		Serial.println("Please check connection.");
	}
}

void IftttMaker::connectToEthernet(byte* mac, IPAddress ip){
	_isEthernet = true;
	Ethernet.begin(mac, ip);
	Serial.println("Connecting to Ethernet");
	delay(1000);
	
	if (clientConnect(IFTTT_SERVER, IFTTT_PORT)) {
        Serial.println("Ethernet is working");
		clientStop();
	} else {
		Serial.println("Please check connection.");
	}
}

void IftttMaker::fireEvent(char* eventName){
    char iftttPage[128];
    sprintf(iftttPage, "/trigger/%s/with/key/%s", eventName, _makerChannelKey);
    makeGetRequest(IFTTT_SERVER, IFTTT_PORT, iftttPage);
	
	Serial.println("Get requested.");
}

void IftttMaker::fireEvent(char* eventName, char* value1, char* value2, char* value3){
    char iftttPage[128];
    sprintf(iftttPage, "/trigger/%s/with/key/%s", eventName, _makerChannelKey);

    // Creating the JSON to pass values to IFTTT Maker Channel
    char jsonValues[512]; // If you need to pass bigger strings, please adjust the size of this variable.
    sprintf(jsonValues, "{ \"value1\" : \"%s\", \"value2\" : \"%s\", \"value3\" : \"%s\" }", value1, value2, value3);

    makePostRequest(IFTTT_SERVER, IFTTT_PORT, iftttPage, jsonValues);
	
	Serial.println("Post requested.");
}

void IftttMaker::makeGetRequest(char* server, int port, char* page) {
    char strBuffer[128];

	 if (clientConnect(server, port)) {
        sprintf(strBuffer, "GET %s HTTP/1.1", page);
        clientPrintln(strBuffer);

        sprintf(strBuffer, "Host: %s", server);
        clientPrintln(strBuffer);

        clientPrintln("Connection: close\r\n");
    } else {
		Serial.println("Please check connection.");
	}
	
    // Ignoring the answer for a while. If you want to check if the message was received you need to parse the HTTP answer.
	clientStop();
	
}

void IftttMaker::makePostRequest(char* server, int port, char* page, char* data) {
    char strBuffer[128];

    if (clientConnect(server, port)) {
        sprintf(strBuffer, "POST %s HTTP/1.1", page);
        clientPrintln(strBuffer);

        sprintf(strBuffer, "Host: %s", server);
        clientPrintln(strBuffer);

		clientPrintln(F("Connection: close\r\nContent-Type: application/json"));
        
		sprintf(strBuffer, "Content-Length: %u\r\n", strlen(data));
        clientPrintln(strBuffer);

        clientPrintln(data);
    } else {
		Serial.println("Please check connection.");
	}

    // Ignoring the answer for a while. If you want to check if the message was received you need to parse the HTTP answer.

    clientStop();
}

void IftttMaker::clientPrintln(const __FlashStringHelper * toPrint) {
	if (_isEthernet) {
		_ethernetClient.println(toPrint);
	} else {
		_wifiClient.println(toPrint);
	}
}

void IftttMaker::clientPrintln(char* toPrint) {
	if (_isEthernet) {
		_ethernetClient.println(toPrint);
	} else {
		_wifiClient.println(toPrint);
	}
}

int IftttMaker::clientConnect(char* server, int port) {
	if (_isEthernet) { 
		return _ethernetClient.connect(server, port);
	} else {
		return _wifiClient.connect(server, port);
	}
}

void IftttMaker::clientStop() {
	if (_isEthernet) {
		_ethernetClient.stop();
	} else {
		_wifiClient.stop();
	}
}