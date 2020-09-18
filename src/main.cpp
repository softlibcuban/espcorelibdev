#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif


#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h> //contiene plugin para websockets

/***
    Arreglar esto o cambiar de librería:
    #include "util/WifiConfig.hpp"
    Esta libreria entra en conflicto con ESPAsyncWebServer
****/


//Archivos locales en /include path
#include "config.h" // Posee datos de la red defaults que se deben sustituir por los gravados en la SPIFFS
#include "TanqueUtil.hpp"
#include "Wifi_Utils.hpp"
#include "JSON_SPIFF.hpp"//maneja el archivo config.json con todas las configuraciones reescribe a config.h
#include "API.hpp"
#include "WebSockets.hpp"
#include "Utils_AWS.hpp"





void setup(){

    // initConfigOnSwitch(); 
}
void loop(){

    // check_status();

}