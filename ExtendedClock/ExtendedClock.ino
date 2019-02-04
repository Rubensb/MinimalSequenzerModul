/* ArduinoMini
 * Rubens Bandelin 2019
 * Still simple but unimaginary useful
 */

int const clockOutFul = 6;
int const clockOutGth = 3;
int const clockOutSxth = 5;
int const clockOutSxt = 4;
int const clockOutTwlth = 2;
int const poti = A2;
int const swtch = 3;

int bpm = 120;

unsigned long ful = 0;
unsigned long sxth = 0;
unsigned long gth = 0;
unsigned long sxt = 0;
unsigned long twlth = 0;

unsigned long clockLen = 0;
unsigned long offset = 0;

unsigned long elapsedMillisFul = 0;
unsigned long elapsedMillisGth = 0;
unsigned long elapsedMillisSxth = 0;
unsigned long elapsedMillisSxt = 0;
unsigned long elapsedMillisTwlth = 0;
unsigned long currentMillis = 0;

void setup() {
  pinMode(clockOutFul, OUTPUT);
  pinMode(clockOutGth, OUTPUT);
  pinMode(clockOutSxth, OUTPUT);
  pinMode(clockOutSxt, OUTPUT);
  pinMode(clockOutTwlth, OUTPUT);
  pinMode(swtch, INPUT);
  pinMode(poti, INPUT);
  Serial.begin(9600);
}

void loop() {
  bpm = map(analogRead(poti), 1023, 0, 60, 190);
  Serial.println(bpm);
  ful  = (60000/bpm);
  sxth = ((15000/bpm));
  gth = ((30000/bpm));
  sxt = ((40000/bpm));
  twlth = ((20000/bpm)/2);
  clockLen = sxth/5;
  clockGen();
}

void clockGen() {
  currentMillis = millis();
  if (currentMillis - elapsedMillisSxth >= sxth) {
    digitalWrite(clockOutSxth, HIGH);
    if (currentMillis - elapsedMillisSxth >= sxth + clockLen) {
      digitalWrite(clockOutSxth, LOW);
      elapsedMillisSxth = currentMillis;
    }
  }
  if (currentMillis - elapsedMillisGth >= gth) {
    digitalWrite(clockOutGth, HIGH);
    if (currentMillis - elapsedMillisGth >= gth + clockLen) {
      digitalWrite(clockOutGth, LOW);
      elapsedMillisGth = currentMillis;
    }
  }
  if (currentMillis - elapsedMillisSxt >= sxt) {
    digitalWrite(clockOutSxt, HIGH);
    if (currentMillis - elapsedMillisSxt >= sxt + clockLen) {
      digitalWrite(clockOutSxt, LOW);
      elapsedMillisSxt = currentMillis;
    }
  }
  if (currentMillis - elapsedMillisTwlth >= twlth) {
    digitalWrite(clockOutTwlth, HIGH);
    if (currentMillis - elapsedMillisTwlth >= twlth + clockLen) {
      digitalWrite(clockOutTwlth, LOW);
      elapsedMillisTwlth = currentMillis;
    }
  }
}

void clockSync() {
  if (currentMillis - elapsedMillisFul >= ful) {
    digitalWrite(clockOutFul, HIGH);
    if (currentMillis - elapsedMillisFul >= ful + clockLen) {
      digitalWrite(clockOutFul, LOW);
      elapsedMillisFul = currentMillis;
    }
  }
}
