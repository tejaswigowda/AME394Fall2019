#include <Arduino.h>



char * HOSTNAME = "test123";
char * WifiPASS = "";

#include <WiFi.h>
#include <WebServer.h>



WebServer server(80);


void setup() {
    Serial.begin(115200);

    pinMode(21, OUTPUT);

  


    

    // Start Wifi AP
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME, WifiPASS);


      
    // handle index -- HTTP Server

    
    server.on("/bright", []() {
      digitalWrite(21, 1);
      server.send(200, "text/html", "<html><head><script>function foo(v){window.location.href=\"./bright?\" + v}</script></head><body><input type='range' max='100' min=\"0\" onchange='foo(this.value)' id='theText'></body><script>document.getElementById(\"theText\").value=parseInt(window.location.search.replace(\"?\",\"\"))</script><html>");
    });

 
    server.on("/", []() {
      server.send(200, "text/html", "<html><head></head><body><a href=\"./on\">on</a><br><a href=\"./off\">off</a></body><html>");
    });

    
    server.begin();
    
}

void loop() {
    server.handleClient();
}
