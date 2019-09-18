const int ledPin = 22;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  pinMode(21, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
  ledcWrite(ledChannel, 25);

}
 
void loop(){
  digitalWrite(21, LOW);
  delay(9);
  digitalWrite(21, HIGH);
  delay(1);
}
