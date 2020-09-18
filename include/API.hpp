
void setGPIO(String id, bool state)
{
    Serial.print("Set GPIO ");
    Serial.print(id);
    Serial.print(": ");
    Serial.println(state);
}

void setPWM(String id, int pwm)
{

    Serial.print("Set PWM ");
    Serial.print(id);
    Serial.print(": ");
    Serial.println(pwm);

}

void doAction(String actionId)
{
    Serial.print("Doing action: ");
    Serial.println(actionId);
}

void guardarUmbrales(uint8_t nivelmin, uint8_t nivelmax, uint8_t flujomin)
{

    String paqueteJSON;
    const size_t capacity = JSON_OBJECT_SIZE(6) + 79;
    DynamicJsonDocument doc(capacity);

    doc["nivelMinimo"] = nivelmin;
    doc["nivelMaximo"] = nivelmax;
    doc["flujoMinimo"] = flujomin;

    //Vuelve a tomar los valores ya configurados para no perderlos
    doc["ssid"] = mySsid.c_str();
    doc["id"] = 2;
    doc["pass"] = myPass.c_str();

    serializeJson(doc, paqueteJSON); //en paqueteJSON ya esta serializado el Json con los respectivos campos llenos

    // Serial.println("Guardando paquete de config: " + paqueteJSON);
    writeFile(SPIFFS, "/config.json", paqueteJSON.c_str());

    vTaskDelay(pdMS_TO_TICKS(500));
    getConfig(); //obtiene la configuracion desde la SPIFFS
    
}