void setup() {

  pinMode(22, OUTPUT);
}

void loop() {
  digitalWrite(22, HIGH);
  delay(500);
  digitalWrite(22, LOW);
  delay(500);
}
