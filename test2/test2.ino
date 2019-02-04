/*
 * OneKnobSequencer
 * Rubens Bandelin 2019
 * One knob is better than two knobs
 */

int const led = A3;

int const btn = 2;
int const swtch = 1;
int const gate = 4;
int const clockIn = 0;

int stepSequence[16] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
int halfStep = 0;

bool recording = false;
bool clean = false;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(gate, OUTPUT);
  pinMode(swtch, INPUT);
  //attachInterrupt(digitalPinToInterrupt(clockIn), sync, RISING);
  //attachInterrupt(digitalPinToInterrupt(btn), recordSequence, RISING);
  attachInterrupt(clockIn, sync, RISING);
  attachInterrupt(btn, recordSequence, RISING);
  //Serial.begin(9600);
  ledState(0);
}

void loop() {
  if (halfStep%8 == 0) {
    ledState(2);
  }
  if ((digitalRead(swtch) == true) && (clean == false)) {
    clearSequence();
    clean = true;
    recording = true;
  }
  if ((digitalRead(swtch) == true) && (clean == true)) {
    recording = true;
  }
  if (digitalRead(swtch) == false) {
    recording = false;
    clean = false;
  }
}

void recordSequence(){
  if (recording == true) {
    ledState(2);
    int pos = ((halfStep%16)-1);
    stepSequence[pos] = stepSequence[pos]? 0 : 1;
    if (stepSequence[pos] == 1) {
      digitalWrite(gate, LOW);
      digitalWrite(gate, HIGH);
    }
  }
}

void sync() {
  ++halfStep;
  digitalWrite(gate, LOW);
  if (stepSequence[((halfStep%16)-1)] == 1) {
    digitalWrite(gate, HIGH);
    ledState(1);
  }
  else if (stepSequence[((halfStep%16)-1)] == 0) {
    digitalWrite(gate, LOW);
    ledState(0);
  }
}

void ledState(int state) {
  // OFF 0
  if (state == 0) {
    digitalWrite(led, 0);
  }
  // Green 1
  else if (state == 1) {
    digitalWrite(led, 1);
  }
  // Red 2
  else if (state == 2) {
    digitalWrite(led, 1);
  }
}

void clearSequence() {
  for (int i = 0; i < 16; i++) {
    stepSequence[i] = 0;
  }
}
