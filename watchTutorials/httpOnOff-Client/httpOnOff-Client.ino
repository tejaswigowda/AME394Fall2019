#include <Arduino.h>

extern "C" {
#include "user_interface.h"
}


char * HOSTNAME = "test";
char * WifiPASS = "";

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Hash.h>



ESP8266WebServer server = ESP8266WebServer(80);


void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);




    

    // Start Wifi AP
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME, WifiPASS);


    
    // handle index -- HTTP Server

    
    server.on("/on", []() {
      digitalWrite(LED_BUILTIN, 0);
      server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
    });

    server.on("/off", []() {
      digitalWrite(LED_BUILTIN, 1);
      server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
     });

 
    server.on("/", []() {
      server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
    });

    
    server.begin();
    
}

void loop() {
    server.handleClient();
}
