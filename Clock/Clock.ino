// Clock by Rubens Bandelin
// Simple but useful

void setup() {
  pinMode(0, OUTPUT);
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(0, HIGH);
  //digitalWrite(LED_BUILTIN, HIGH);
  delayMicroseconds(50000);
  digitalWrite(0, LOW);
  //digitalWrite(LED_BUILTIN, LOW);
  delayMicroseconds(250000);
}
