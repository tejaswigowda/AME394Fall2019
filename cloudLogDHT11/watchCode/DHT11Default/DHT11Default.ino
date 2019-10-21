#include <SimpleDHT.h>

#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "yourNetworkName";
const char* password =  "yourPassword";

 
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 21
int pinDHT11 = 21;
SimpleDHT11 dht11(pinDHT11);


void sendData(float t, float h)
{
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("http://34.216.181.26:3000/setValue?t=" + String(t) + "&h=" + String(h)); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  sendData((float)temperature, (float)humidity);
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
