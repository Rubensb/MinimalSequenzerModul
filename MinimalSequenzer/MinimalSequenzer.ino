/*
 * MinimalSequencer with CV
 * Rubens 2018
 */

#include <Button.h>

//TODO: Assingn buttons
Button btn (2, false, false, 100);

//TODO: Sort variables and  rename them with sense!!
int button = 2;
int NUMBER_OF_STEPS = 8;
int leds[8] = {4,5,6,7,8,9,10,11};
int sequence[8] = {0,0,0,0,0,0,0,0};
int offsets[8] = {0,0,0,0,0,0,0,0};
unsigned long sustains[8] = {0,0,0,0,0,0,0,0};
int bpmArry[3] = {0, 0, 0};
int bpm;
int beat;
float interval;
unsigned long timing = 0;
unsigned long currentMillis;

int stepSequence[NUMBER_OF_STEPS] = {0,0,0,0,0,0,0,0};
int CVOuts[NUMBER_OF_STEPS] = {0,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
  setBpm(1,2,0);
  for (int i = 0; i < NUMBER_OF_STEPS; i++){
    pinMode(leds[i], OUTPUT);
    setOffset(i, 0);
  }
}

void setBpm(int n100, int n10, int n){
  bpmArry[0] = n100;
  bpmArry[1] = n10;
  bpmArry[2] = n;
  bpm = ((n100*100)+(n10*10)+n);
  interval = 1000 / (bpm / 60);
  Serial.println(bpm);
  Serial.println(interval);
}

void setStepState(int step, int state) {
  sequence[step] = state;
}

void clearSteps(){
  for (int i = 0; i < NUMBER_OF_STEPS; i++){
    setStepState(i, 0);
  }
}

void setOffset(int id, int value) {
  offsets[id] = value + interval;
}

void syncGates(int step) {

}

void syncCVs(int step) {

}

void setAndSustain(int id, int duration){
  digitalWrite(leds[id], HIGH);
  sustains[id] = millis() + duration;
}

void loop() {
  currentMillis = millis();

  //TODO: Try without using this for loop
  for (int i = 0; i < NUMBER_OF_STEPS; i++){
    if ( sustains[i] < millis())
      digitalWrite(leds[i], sequence[i]);
  }

  if (currentMillis - timing >= offsets[(beat)%NUMBER_OF_STEPS]) {
    timing = currentMillis;
    setAndSustain((beat)%NUMBER_OF_STEPS, 50);
    beat++;
  }

  setStepState(2, 1);
  setStepState(4, 1);
  for (int i = 0; i < 8; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sustains[i]);
  }
}
