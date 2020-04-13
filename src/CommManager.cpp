#include "CommManager.h"

CommManager::CommManager() : _ssid("pordefinir"), _ip(192, 168, 8, 1),
                             _gateway(192, 168, 8, 1),
                             _subnet(255, 255, 255, 0),
                             _server(80),
                             _ws("/ws"),
                             _events("/events")
{
}

int CommManager::setupWifi()
{
    //Change to manager
    WiFi.mode(WIFI_AP); //switching to AP mode
    // WiFi.softAP(ssid, password); //initializing the AP with ssid and password. This will create a WPA2-PSK secured AP
    WiFi.softAP(_ssid);
    WiFi.config(_ip, _gateway, _subnet);
    WiFi.begin();

    return 0;
}

void CommManager::init()
{

    setupWifi();

    DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
    DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Methods"), F("GET, PUT"));
    DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("Content-Type, Origin, Referer, User-Agent"));

    ArduinoOTA.onStart([&]() {
        _events.send("Update Start", "ota");
    });
    ArduinoOTA.onEnd([]() {
        //   events.send("Update End", "ota");
    });
    ArduinoOTA.onProgress([&](unsigned int progress, unsigned int total) {
        char p[32];
        sprintf(p, "Progress: %u%%\n", (progress / (total / 100)));
        _events.send(p, "ota");
    });
    ArduinoOTA.onError([&](ota_error_t error) {
        //for later
        if (error == OTA_AUTH_ERROR)
            _events.send("Auth Failed", "ota");
        else if (error == OTA_BEGIN_ERROR)
            _events.send("Begin Failed", "ota");
        else if (error == OTA_CONNECT_ERROR)
            _events.send("Connect Failed", "ota");
        else if (error == OTA_RECEIVE_ERROR)
            _events.send("Recieve Failed", "ota");
        else if (error == OTA_END_ERROR)
            _events.send("End Failed", "ota");
    });
    ArduinoOTA.setHostname(_ssid.c_str());
    ArduinoOTA.begin();

    MDNS.addService("http", "tcp", 80);

    _ws.onEvent([&](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
        onWsEvent(server, client, type, arg, data, len);
    });
    _server.addHandler(&_ws);

    _events.onConnect([](AsyncEventSourceClient *client) {
        client->send("hello!", NULL, millis(), 1000);
    });

    _server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(ESP.getFreeHeap()));
    });
    _server.addHandler(&_events);

    _server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hello, world");
    });

    // Send a POST request to <IP>/post with a form field message set to <message>
    // _server.on("/send", HTTP_POST, [](AsyncWebServerRequest *request) {
    //     String message;
    //     if (request.hasParam(PARAM_MESSAGE, true))
    //     {
    //         message = request.getParam(PARAM_MESSAGE, true).value();
    //     }
    //     else
    //     {
    //         message = "No message sent";
    //     }
    //     request.send(200, "text/plain", "Hello, POST: " + message);
    // });

    _server.onNotFound([this](AsyncWebServerRequest *request) {
        notFound(request);
    });

    _server.begin();
}

void CommManager::update()
{
    ArduinoOTA.handle();
}

void CommManager::notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void CommManager::onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
        client->printf("Hello Client %u :)", client->id());
        client->ping();
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
    }
    else if (type == WS_EVT_ERROR)
    {
        Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
    }
    else if (type == WS_EVT_PONG)
    {
        Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
    }
    else if (type == WS_EVT_DATA)
    {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        String msg = "";
        if (info->final && info->index == 0 && info->len == len)
        {
            //the whole message is in a single frame and we got all of it's data
            Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);

            if (info->opcode == WS_TEXT)
            {
                for (size_t i = 0; i < info->len; i++)
                {
                    msg += (char)data[i];
                }
            }
            else
            {
                char buff[3];
                for (size_t i = 0; i < info->len; i++)
                {
                    sprintf(buff, "%02x ", (uint8_t)data[i]);
                    msg += buff;
                }
            }

            processWSMessage(msg);

            if (info->opcode == WS_TEXT)
                client->text("{\"status\":\"ok\"}");
            else
                client->binary("{\"status\":\"ok\"}");
        }
        else
        {
            //message is comprised of multiple frames or the frame is split into multiple packets
            if (info->index == 0)
            {
                if (info->num == 0)
                    Serial.printf("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
                Serial.printf("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
            }

            Serial.printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT) ? "text" : "binary", info->index, info->index + len);

            if (info->opcode == WS_TEXT)
            {
                for (size_t i = 0; i < info->len; i++)
                {
                    msg += (char)data[i];
                }
            }
            else
            {
                char buff[3];
                for (size_t i = 0; i < info->len; i++)
                {
                    sprintf(buff, "%02x ", (uint8_t)data[i]);
                    msg += buff;
                }
            }
            Serial.printf("%s\n", msg.c_str());

            if ((info->index + len) == info->len)
            {
                Serial.printf("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
                if (info->final)
                {
                    Serial.printf("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
                    if (info->message_opcode == WS_TEXT)
                        client->text("I got your text message");
                    else
                        client->binary("I got your binary message");
                }
            }
        }
    }
}

void CommManager::processWSMessage(String msg)
{
    Serial.printf("%s\n", msg.c_str());
}