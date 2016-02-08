/*
*	Created by Felipe Augusto Pedroso, February 08, 2016.
*/
#include "IftttMaker.h"

void IftttMaker::initialize(char* makerChannelKey){
    _makerChannelKey = makerChannelKey;
    
    lcd.begin(16, 2);
    debugPrint("Initializing", "Arduino + IFFFT");
    delay(1000);
}

void IftttMaker::connectToWifi(char* ssid, char* password){
    while (wifiStatus != WL_CONNECTED) {
        wifiStatus = WiFi.begin(ssid, password);
        debugPrint("Connecting to", ssid);
        delay(1000);
    }
    
    debugPrint("Connected!");
    delay(500);
}

bool IftttMaker::isConnected(){
    return WiFi.status() == WL_CONNECTED;
}

void IftttMaker::fireEvent(char* eventName){
    char iftttPage[128];
    sprintf(iftttPage, "/trigger/%s/with/key/%s", eventName, _makerChannelKey);
    makeGetRequest(IFTTT_SERVER, IFTTT_PORT, iftttPage);
}

void IftttMaker::fireEvent(char* eventName, char* value1, char* value2, char* value3){
    char iftttPage[128];
    sprintf(iftttPage, "/trigger/%s/with/key/%s", eventName, _makerChannelKey);

    // Creating the JSON to pass values to IFTTT Maker Channel
    char jsonValues[512]; // If you need to pass bigger strings, please adjust the size of this variable.
    sprintf(jsonValues, "{ \"value1\" : \"%s\", \"value2\" : \"%s\", \"value3\" : \"%s\" }", value1, value2, value3);

    makePostRequest(IFTTT_SERVER, IFTTT_PORT, iftttPage, jsonValues);
}

void IftttMaker::makeGetRequest(char* server, int port, char* page) {
    char strBuffer[128];

    if(!isConnected()){
        // TODO: find a better way to log this situation
        debugPrint("Please check", "wifi connection.");
        return;
    }

    if (_client.connect(server, port)) {
        sprintf(strBuffer, "GET %s HTTP/1.1", page);
        _client.println(strBuffer);

        sprintf(strBuffer, "Host: %s", server);
        _client.println(strBuffer);

        _client.println("Connection: close\r\n");
    }

    // Ignoring the answer for a while. If you want to check if the message was received you need to parse the HTTP answer.
    _client.stop();
}

void IftttMaker::makePostRequest(char* server, int port, char* page, char* data) {
    char strBuffer[512];

    if(!isConnected()){
        // TODO: find a better way to log this situation
        debugPrint("Please check", "wifi connection.");
        return;
    }

    if (_client.connect(server, port)) {
        sprintf(strBuffer, "POST %s HTTP/1.1", page);
        _client.println(strBuffer);

        sprintf(strBuffer, "Host: %s", server);
        _client.println(strBuffer);

        _client.println(F("Connection: close\r\nContent-Type: application/json"));

        sprintf(strBuffer, "Content-Length: %u\r\n", strlen(data));
        _client.println(strBuffer);

        _client.print(data);
    }

    // Ignoring the answer for a while. If you want to check if the message was received you need to parse the HTTP answer.

    _client.stop();
}

void IftttMaker::debugPrint(char* message) { // Was written using the Grove kit, feel free to replace for your favorite debug method.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void IftttMaker::debugPrint(char* line0, char* line1) {
  debugPrint(line0);
  lcd.setCursor(0, 1);
  lcd.print(line1);
}