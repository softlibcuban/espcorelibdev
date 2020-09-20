# espcorelibdev
Development project for a simple communication library between an espX device and a mobile application. This project will serve as a basis for the development of multiple community projects within the android community of Cuba.

---

## Prerequisites

 0. [`VSCode` Installed](https://code.visualstudio.com/download)
 1. [`PlatformIO` plugin added to VSCode](https://platformio.org/install)
 2. [`ESP8266 Core 2.7.3+`](https://github.com/esp8266/Arduino) for ESP8266-based boards guide how to install in [PlatformIO](https://docs.platformio.org/en/latest/platforms/espressif8266.html)
 3. [`ESP32 Core 1.0.4+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards guide how to install in [PlatformIO](https://docs.platformio.org/en/latest/platforms/espressif32.html)
 
### Manual Install

1. Navigate to [espcorelibdev](https://github.com/softlibcuban/espcorelibdev) page
2. Download the latest release `espcorelibdev-master.zip`
3. Extract the zip file to `espcorelib` directory

---

## How it works:

- This project is intended to be used with a mobile [application](https://github.com/softlibcuban/espxmanagerapp) (in development). The objective is that the app can configure the hardware connected to the ESPs. In this way, the app will serve as a development environment, very user-friendly

### Current progress

- At the moment this repository covers the part of the wifi configuration, thanks to [ESPAsync_WiFiManager library](https://github.com/khoih-prog/ESPAsync_WiFiManager). 
This library offers a lot of flexibility to the project, as it allows auto-reconnection if the device is disconnected from a Wi-Fi network, save the SSIDs, and choose if there is an access point with a higher connection quality to switch to it.

- In addition, this firmware allows connection with multiple users asynchronously and with a awesome speed of connection, thanks to the library [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) who uses websockets to do its job.

- Finally, this project implements the [ArduinoJson](https://github.com/bblanchon/ArduinoJson) libray, that allow us to use JSON objects to request data over Websocket and HTTP
 
 
