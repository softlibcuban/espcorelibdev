#include <Arduino.h>


#include "config.h"
#include "CommManager.h"
//replace with wifimanager or ....

CommManager comm;


void setup()
{
    Serial.begin(9600);
    comm.init();
}

void loop()
{
    comm.update();
}

