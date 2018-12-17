/*
 * MinimalstepSequencer with CV
 * Rubens 2018
 * I force myself to eat no Cheeseburger
 */

#include <Button.h>

Button btn0 (12, false, false, 100);
Button btn1 (2, false, false, 100);
Button btn2 (13, false, false, 100);

int const NUMBER_OF_STEPS = 8;
int const clockIn = 0;
int const clockOut = 0;
int const triggerOut = 3;
//int leds[8] = {4,5,6,7,8,9,10,11};
int const leds[8] = {11,10,9,8,7,6,5,4};
int stepSequence[8] = {0,0,0,0,0,0,0,0};
int offsets[8] = {0,0,0,0,0,0,0,0};
unsigned long sustains[8] = {0,0,0,0,0,0,0,0};
int bpmArry[3];
int bpm;
int beat;
float interval;
unsigned long elapsedMillis = 0;
unsigned long currentMillis;
unsigned long tempMillis = 0;
unsigned long duration = 50;

void setup() {
  Serial.begin(9600);
  setBpm(0, 1);
  setBpm(1, 2);
  setBpm(2, 0);
  pinMode(triggerOut, OUTPUT);
  for (int i = 0; i < NUMBER_OF_STEPS; i++){
    pinMode(leds[i], OUTPUT);
    setOffset(i, 0);
  }
}

void setBpm(int pos, int value){
  bpmArry[pos] = value;
  bpm = ((bpmArry[0]*100)+(bpmArry[1]*10)+bpmArry[2]);
  interval = (60000 / bpm);
  Serial.println(bpm);
  Serial.println(interval);
}

void setStepState(int step, int state) {
  stepSequence[step] = state;
}

void invertStepState(int step) {
  stepSequence[step] = stepSequence[step]? 0 : 1;
}

void clearSteps(){
  for (int i = 0; i < NUMBER_OF_STEPS; i++){
    setStepState(i, 0);
  }
}

void setOffset(int id, int value) {
  offsets[id] = value + interval;
}

void setAndSustain(int id, int duration){
  digitalWrite(leds[id], HIGH);
  sustains[id] = millis() + duration;
}

void loop() {
  currentMillis = millis();
  tempMillis = millis();
  btn0.read();
  btn1.read();
  btn2.read();

  for (int i = 0; i < NUMBER_OF_STEPS; i++){
    if ( sustains[i] < millis())
      digitalWrite(leds[i], stepSequence[i]);
  }

  if (currentMillis - elapsedMillis >= offsets[(beat)%NUMBER_OF_STEPS]) {
    digitalWrite(triggerOut, HIGH);
    setAndSustain((beat)%NUMBER_OF_STEPS, 50);
    elapsedMillis = currentMillis;
    beat++;
  if (tempMillis - elapsedMillis >= interval + duration) {
    digitalWrite(triggerOut, LOW);
    tempMillis = currentMillis;
    println("True");
    }
  }

  if (btn0.wasPressed()) {
    invertStepState(0);
    Serial.println("btn0");
  }
  if (btn1.wasPressed()) {
    invertStepState(1);
    Serial.println("btn1");
  }
  if (btn2.wasPressed()) {
    invertStepState(2);
    Serial.println("btn2");
  }
}
