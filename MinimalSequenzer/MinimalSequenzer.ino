/*
 * MinimalstepSequencer with CV
 * Rubens 2018
 * I force myself to eat no Cheeseburger
 */

#include <Button.h>

Button btn0 (12, false, false, 100);
Button btn1 (2, false, false, 100);
Button btn2 (13, false, false, 100);
Button btn3 (NULL, false, false, 100);
Button btn4 (NULL, false, false, 100);
Button btn5 (NULL, false, false, 100);
Button btn6 (NULL, false, false, 100);
Button btn7 (NULL, false, false, 100);

int const latchPin = 11;
int const dataPin = 13;
int const clockPin = 12;

byte switchVar1 = 72;

int const NUMBER_OF_STEPS = 8;
int const clockIn = A5;
int const clockOut = 0;
int const gateOut = 3;
//int leds[8] = {4,5,6,7,8,9,10,11};
int const leds[8] = {10,9,8,7,6,5,4,3};
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
unsigned long newMillis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
  setBpm(0, 1);
  setBpm(1, 4);
  setBpm(2, 0);
  pinMode(gateOut, OUTPUT);
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

void setInterval() {
  if (analogRead(clockIn) > 100) {
    tempMillis = millis();
  }
  if ((tempMillis > millis()-10) && (analogRead(clockIn) > 100)) {
    newMillis = millis();
  }
  interval = newMillis - tempMillis;
  Serial.println(interval);
}

void setStepState(int step, int state) {
  stepSequence[step] = state;
}

void invertStepState(int step) {
  stepSequence[step] = stepSequence[step]? 0 : 1;
  Serial.print("Step: ");
  Serial.print(step);
  Serial.print(" to state: ");
  Serial.println(stepSequence[step]);
}

void clearSteps(){
  for (int i = 0; i < NUMBER_OF_STEPS; i++){
    setStepState(i, 0);
  }
}

void setOffset(int pos, int value) {
  offsets[pos] = value + interval;
}

void setAndSustain(int pos, int duration){
  digitalWrite(gateOut, LOW);
  digitalWrite(leds[pos], HIGH);
  if (stepSequence[pos] == 1) {
    digitalWrite(gateOut, HIGH);
  }
  else if (stepSequence[pos] == 0) {
    digitalWrite(gateOut, LOW);
  }
  sustains[pos] = millis() + duration;
}

void loop() {
  //setInterval();
  currentMillis = millis();
  btn0.read();
  btn1.read();
  btn2.read();

  for (int i = 0; i < NUMBER_OF_STEPS; i++){
    if ( sustains[i] < millis())
      digitalWrite(leds[i], stepSequence[i]);
  }

  if (currentMillis - elapsedMillis >= offsets[(beat)%NUMBER_OF_STEPS]) {
    setAndSustain((beat)%NUMBER_OF_STEPS, 50);
    elapsedMillis = currentMillis;
    beat++;
  }

  if (btn0.wasPressed()) {
    invertStepState(0);
  }
  if (btn1.wasPressed()) {
    invertStepState(1);
  }
  if (btn2.wasPressed()) {
    invertStepState(2);
  }
  if (btn3.wasPressed()) {
    invertStepState(3);
  }
  if (btn4.wasPressed()) {
    invertStepState(4);
  }
  if (btn5.wasPressed()) {
    invertStepState(5);
  }
  if (btn6.wasPressed()) {
    invertStepState(6);
  }
  if (btn7.wasPressed()) {
    invertStepState(7);
  }
}
