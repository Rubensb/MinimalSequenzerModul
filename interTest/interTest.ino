/*
 * OneKnobSequencer
 * Rubens Bandelin 2019
 * One knob is better than two knobs
 */

int const led = 3;

int const btn = 2;
int const swtch = 1;
int const gate = 4;
int const clockIn = 0;

int stepSequence[16] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
int halfStep = 0;

bool recording = false;
bool clean = false;

bool state = false;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(gate, OUTPUT);
  pinMode(clockIn, INPUT);
}

void loop() {
  if (digitalRead(clockIn) == HIGH) {
    digitalWrite(led, HIGH);
    if (state == false) {
      sync();
      state = true;
    }
  }
  else if (digitalRead(clockIn) == LOW) {
    digitalWrite(led, LOW);
    state = false;
  }
}

void sync() {
  ++halfStep;
  digitalWrite(gate, LOW);
  if (stepSequence[((halfStep%16)-1)] == 1) {
    digitalWrite(gate, HIGH);
  }
  else if (stepSequence[((halfStep%16)-1)] == 0) {
    digitalWrite(gate, LOW);
  }
}
