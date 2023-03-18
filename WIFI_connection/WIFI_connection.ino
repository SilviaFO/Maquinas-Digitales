#include <WiFi.h>


#include "credentials.h"

void setup() {
    Serial.begin(115200);
    while(!Serial){delay(100);}

    Serial.println();
    Serial.println("******************************************************");
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:

}
