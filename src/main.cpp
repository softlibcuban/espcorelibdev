#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

void setup(){
    Serial.begin(115200);
}
void loop(){

    Serial.println("hola");

    delay(1000);

}