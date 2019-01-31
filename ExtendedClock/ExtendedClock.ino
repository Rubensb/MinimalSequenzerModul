/* ArduinoMini
 * Rubens Bandelin 2019
 * Still simple but unimaginary useful
 */

int const clockOutGth = 2; //1
int const clockOutSxth = 3; //0
int const clockOutSxt = 4;
int const poti = A2;
int const swtch = 3;

int bpm = 120;

unsigned long sxth = 0;
unsigned long gth = 0;

unsigned long clockLen = 0;
unsigned long offset = 0;

unsigned long elapsedMillis = 0;
unsigned long elapsedMillisGth = 0;
unsigned long currentMillis = 0;

void setup() {
  pinMode(clockOutGth, OUTPUT);
  pinMode(clockOutSxth, OUTPUT);
  pinMode(swtch, INPUT);
  pinMode(poti, INPUT);
}

void loop() {
  //bpm = map(analogRead(poti), 0, 1023, 40, 200);
  sxth = ((60000/bpm)/4);
  gth = ((60000/bpm)/2);
  clockLen = sxth/5;
  clockGen();
}

void clockGen() {
  currentMillis = millis();
  if (currentMillis - elapsedMillis >= sxth) {
    digitalWrite(clockOutSxth, HIGH);
    if (currentMillis - elapsedMillis >= sxth + clockLen) {
      digitalWrite(clockOutSxth, LOW);
      elapsedMillis = currentMillis;
    }
  }
  if (currentMillis - elapsedMillisGth >= gth) {
    digitalWrite(clockOutGth, HIGH);
    if (currentMillis - elapsedMillisGth >= gth + clockLen) {
      digitalWrite(clockOutGth, LOW);
      elapsedMillisGth = currentMillis;
    }
  }
}

void clockDiv() {
  currentMillis = millis();
  if (currentMillis - elapsedMillis >= 125) {
    digitalWrite(clockOutSxth, HIGH);
    if (currentMillis - elapsedMillis >= 125 + 50) {
      digitalWrite(clockOutSxth, LOW);
      elapsedMillis = currentMillis;
    }
  }
}
