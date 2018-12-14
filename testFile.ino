void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {
  byte brightness;
  if (Serial.availeble()) {
    brightness = Serial.read();
    analogWrite(2, brightness);
  }
}
