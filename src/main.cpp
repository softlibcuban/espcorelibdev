#include <Arduino.h>

#include "util/WifiConfig.hpp"

#include <ArduinoJson.h>
#include <SPIFFS.h>
// #include <ESPAsyncWebServer.h> //contiene plugin para websockets

//Archivos locales en /include path

#include "API.hpp"
#include "WebSockets.hpp"
#include "Utils_AWS.hpp"



uint8_t BUILTIN_BUTTON = 0;


void setup(){

    Serial.begin(115200);
    while (!Serial);

    initWifiConfig();
    InitServer();
    InitWebSockets();

    pinMode(BUILTIN_BUTTON,INPUT);

}


void loop(){

    

    delay(2000);
    
    // connectMultiWiFi();
    check_status();
    delay(1000);
    updateGPIO("BOTON", !(digitalRead(BUILTIN_BUTTON)));
}