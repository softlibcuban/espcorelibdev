
/*******************************************************************************
 * 
 * trabajando sin la librería https://github.com/khoih-prog/ESP_WiFiManager
 * problemas de compatibilidad con https://github.com/me-no-dev/ESPAsyncWebServer
 * 
********************************************************************************/


/**********************************
 * inicia configuración de la wifi
**********************************/
void initWifiConfig(){
  SPIFFS.begin();
  getConfig();//obtiene la configuracion desde la SPIFFS
  myPass = String(PASSWORD);
  mySsid = String(SSID);
  ConnectWiFi_STA(); //inicia en modo station, se conecta a una wifi predefinida en config.h
  // ConnectWiFi_AP();//inicia en modo AP
  
                      /* sin InitServer no funciona el websocket */ 
  InitServer();       /* Ver si es posible eliminar esta función, ya que no se está trabajando
                          con una página web embebida */
  InitWebSockets();

}

/**********************************
 * comprueba el estado de la wifi
**********************************/
void check_status(){

}