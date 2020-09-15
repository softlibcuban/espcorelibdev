#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include "util/WifiConfig.hpp"

void setup(){

    initConfigOnSwitch(); 
}
void loop(){

    mainWifiFunction();

}