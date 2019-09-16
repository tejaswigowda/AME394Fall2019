#include <Arduino.h>



char * HOSTNAME = "test";
char * WifiPASS = "";

#include <WiFi.h>
#include <WebServer.h>


WebServer server(80);


void setup() {
    Serial.begin(115200);





    

    // Start Wifi AP
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME, WifiPASS);


    
    // handle index -- HTTP Server
    
    server.on("/on", []() {
      Serial.println(0);
      server.send(200, "");
    });

    server.on("/off", []() {
      Serial.println(1);
      server.send(200, "");
    });
 
    server.begin();
    
}

void loop() {
    server.handleClient();
}
