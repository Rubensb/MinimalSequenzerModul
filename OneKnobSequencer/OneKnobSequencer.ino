/*
 * OneKnobSequencer
 * Rubens Bandelin 2019
 * One knob is better than two knobs
 */

int const led0 = A0;
int const led1 = A3;

int const btn = 2; //0
int const gate = 4; //1
int const clockIn = 3;

int stepSequence[16] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
int halfStep = 0;
int fullStep = 0;
int bar = 0;

void setup() {
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(gate, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(clockIn), sync, RISING);
  //attachInterrupt(digitalPinToInterrupt(btn), recordSequence, RISING);
  Serial.begin(9600);
}

void loop() {
}

void recordSequence(){
  int pos = ((halfStep%16)-1);
  stepSequence[pos] = stepSequence[pos]? 0 : 1;
  if (stepSequence[pos] == 1) {
    digitalWrite(gate, LOW);
    digitalWrite(gate, HIGH);
    ledState(2);
  }
}

void sync() {
  ++halfStep;
  digitalWrite(gate, LOW);
  if ((halfStep%2) == 1) {
    ++fullStep;
    digitalWrite(gate, HIGH);
  }
  if ((halfStep%16) == 0) {
    ++bar;
  }
  /*if (stepSequence[((halfStep%16)-1)] == 0) {
    digitalWrite(gate, LOW);
    digitalWrite(gate, HIGH);
    ledState(1);
  }
  else if (stepSequence[((halfStep%16)-1)] == 0) {
    digitalWrite(gate, LOW);
    ledState(0);
  }*/
  Serial.print("Half fullStep: ");
  Serial.print(halfStep);
  Serial.print(" | fullStep: ");
  Serial.print(fullStep);
  Serial.print(" | Bar: ");
  Serial.println(bar);
}

void ledState(int state) {
  // OFF 0
  if (state == 0) {
    analogWrite(led0, 0);
    analogWrite(led1, 0);
  }
  // Green 1
  else if (state == 1) {
    analogWrite(led0, 0);
    analogWrite(led1, 255);
  }
  // Red 2
  else if (state == 2) {
    analogWrite(led0, 255);
    analogWrite(led1, 0);
  }
}
