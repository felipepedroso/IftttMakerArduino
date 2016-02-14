# IftttMakerArduino

This library aims to help developers and makers to interact with IFTTT Maker Channel in a easy way. The idea is to abstract the HTTP calls and firing the events with a simple call.

# Using the library

Declare your IftttMaker object:
```cpp
IftttMaker iftttMaker;
```
Initialize your API key and Wifi settings:
```cpp
void setup() {
  iftttMaker.initialize("makerChannelKey");
  iftttMaker.connectToWifi("SSID", "PASSWORD");
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

Need to abstract the network interface to use WiFi or Ethernet.