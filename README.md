# IftttMakerArduino

This library aims to help developers and makers to interact with IFTTT Maker Channel in a easy way. The idea is to abstract the HTTP calls and firing the events with a simple call.

# Using the library

Declare your IftttMaker object:
```cpp
IftttMaker iftttMaker;
```
Initialize your API key and Wifi or Ethernet settings:
```cpp
// Ethernet parameters
byte mac[] = { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };

// IPAddress ip(192, 168, 0, 148);
void setup() {
  iftttMaker.initialize("makerChannelKey");
  //iftttMaker.connectToWifi("SSID", "PASSWORD");
  iftttMaker.connectToEthernet(mac);
}
```

Send events as you wish:
```cpp
void loop() {
  iftttMaker.fireEvent("eventName");
  delay(5000);
}
```


# Known issues

Need to improve the connection verification.