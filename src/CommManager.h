#ifndef COMMMANAGER_H_
#define COMMMANAGER_H_

#if defined(ESP8266)
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

class CommManager
{
public:
    CommManager();
    //function to initialize
    void init();
    int setupWifi();
    void setupServer();

    // loop
    void update();

private:
    //vars
    String _ssid;
    IPAddress _ip;
    IPAddress _gateway;
    IPAddress _subnet;

    AsyncWebServer _server;
    AsyncWebSocket _ws;

    AsyncEventSource _events;

    //TODO: Add holders for ws function parser
    //TODO: Add holders for esp status functions

    //private functions
    void processWSMessage(String msg); //?????
    void notFound(AsyncWebServerRequest *request);
    void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
};

#endif // COMMMANAGER_H_
