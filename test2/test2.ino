/*
 * OneKnobSequencer
 * Rubens Bandelin 2019
 * One knob is better than two knobs
 */

int const led0 = A0;
int const led1 = A3;

int const btn = 5; //0
int const gate = 4; //1
int const clockIn = 3;

unsigned long interval = 0;
int clockCounter = 0;
int beat = 0;
bool state = false;

unsigned long currentMillis = 0;
unsigned long elapsedMillis = 0;
unsigned long tempMillis = 0;

int stepSequence[16] = {0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0};

void setup() {
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(gate, OUTPUT);
  pinMode(btn, INPUT);
  pinMode(clockIn, INPUT);
  Serial.begin(9600);
  interval = 500;
}

void loop() {
  currentMillis = millis();
  // Check for tempSync
  if (digitalRead(clockIn) == HIGH) {
    tempSync();
  }

  if (currentMillis - elapsedMillis > interval) {
    ++beat;
    state = !state;
    if (stepSequence[beat%16] == 1) {
      digitalWrite(gate, HIGH);
    }
    else if (stepSequence[beat%16] == 0) {
      digitalWrite(gate, LOW);
    }
    if (state == false) {
      analogWrite(led0, 0);
      analogWrite(led1, 250);
    }
    if (state == true) {
      analogWrite(led0, 250);
      analogWrite(led1, 0);
    }

    elapsedMillis = currentMillis;
   }
   Serial.println(60000/interval);
}

void recordSequence(){
  if (state == false) {
    analogWrite(led0, 255);
    analogWrite(led1, 0);
  }
  if (state == true) {
    analogWrite(led0, 0);
    analogWrite(led1, 255);
  }
}

void tempSync(){
  clockCounter++;
  if ((clockCounter > 1) && (millis() - tempMillis > 15 )) {
    interval = ((millis() - tempMillis) * 2);
  }
  tempMillis = millis();
}

void printSequence() {
  for (int i = 0; i < 16; i++) {
    if (i =! 15) {
      Serial.print(stepSequence[i]);
    }
    else if (i == 15) {
      Serial.println(stepSequence[i]);
    }
  }
}

void clearSequence() {
  for (int i = 0; i < 16; i++) {
    stepSequence[i] = 0;
  }
}
