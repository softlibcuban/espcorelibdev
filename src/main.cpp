#include <Arduino.h>

#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "util/WifiConfig.hpp"

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

    check_status();
    updateGPIO("BOTON", !(digitalRead(BUILTIN_BUTTON)));
    delay(1000);
    
}