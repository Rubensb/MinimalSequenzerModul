/*
 * Sequencer with adjustable offset
 * Rubens 2018
 */

int NUMBER_OF_LEDS = 8;

int button = 2;
int leds[8] = {4,5,6,7,8,9,10,11};
int sequence[8] = {0,0,0,0,0,0,0,0};
int offsets[8] = {0,0,0,0,0,0,0,0};
int cvs[8] = {0,0,0,0,0,0,0,0};
unsigned long sustains[8] = {0,0,0,0,0,0,0,0};

int bpmArray[3] = {1, 2, 0};
int bpm = (bpmArray[0]*100)+(bpmArray[1]*10)+bpmArray[2];

int beat;
float interval;
unsigned long timing = 0;
unsigned long currentMillis;

void setup() {
  Serial.begin(9600);
  Serial.println(bpm);
  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    pinMode(leds[i], OUTPUT);
  }

  pinMode(button, INPUT);
}

void error(int index){
  Serial.print("Error: ");
  Serial.println(index);
}

void setStepState(int step, int state) {
  sequence[step] = state;
}

void clearSteps(){
  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    setStepState(i, 0);
  }
}

void syncLedsToSteps(){
  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    if (sequence[i] == 1) {
      digitalWrite(leds[i], HIGH);
    }
    else if (sequence[i] == 0) {
      digitalWrite(leds[i], LOW);
    }
    else {
      error(1);
    }
  }
}

void syncLedToActiveStep(int step, int duration) {
  for (int i = 0; currentMillis < duration) {
    digitalWrite(leds[step], HIGH)
  }
  digitalWrite(leds[step], LOW)
}

void openGate(int step){

}

void sendCv(int step, float value){

}

void setAndSustain(int id, int duration){
  digitalWrite(leds[id], HIGH);
  sustains[id] = millis() + duration;
}

void loop() {
  currentMillis = millis();
  Serial.println(currentMillis);
  setStepState(2, 1);
  setStepState(4, 1);
  syncLedsToSteps();
  syncLedToActiveStep(6, 50);

  /*for (int i = 0; i < NUMBER_OF_LEDS; i++){
    if ( sustains[i] < millis())
      digitalWrite(leds[i], sequence[i]);
  }

  if (currentMillis - timing >= offsets[(beat)%NUMBER_OF_LEDS]) {
    timing = currentMillis;
    syncLedToActiveStep(beat%NUMBER_OF_LEDS, 50);
    beat++;
  }*/
}
