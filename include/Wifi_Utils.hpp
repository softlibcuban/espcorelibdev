String mySsid;
String myPass;
void ConnectWiFi_STA(bool useStaticIP = false)
{
    int cont=0;
    Serial.println("");
    WiFi.mode(WIFI_STA);

    WiFi.begin("MyAp", "12345678Leo");
    if(useStaticIP) WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) 
    { 
      vTaskDelay(pdMS_TO_TICKS(100));
      Serial.print('.'); 
      cont++;
      if(cont >=10){
        Serial.print("Error de conexion. Reiniciando..."); 
        ESP.restart();
      }
    }
  
    Serial.println("");
    Serial.print("Iniciado STA:\t");
    Serial.println(SSID);
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
}

void ConnectWiFi_AP(bool useStaticIP = false)
{   

    
    WiFi.mode(WIFI_AP);
    while(!WiFi.softAP(mySsid.c_str(), myPass.c_str()))//while(!WiFi.softAP(ssid, password))
    {
      
      Serial.println("Error en configurar la AP");
      while(1){
        vTaskDelay(pdMS_TO_TICKS(100));
      }
      
    }
    if(useStaticIP) WiFi.softAPConfig(ip, gateway, subnet);
    Serial.println("");
    Serial.print("Iniciado AP:\t");Serial.println(mySsid);
    Serial.print("IP address:\t");
    Serial.println(WiFi.softAPIP());
    Serial.println("");
}