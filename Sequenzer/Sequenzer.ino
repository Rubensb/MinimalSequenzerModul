/*
 * Sequencer with adjustable offset
 * Rubens 2018
 */
int button = 2;
int poti = A0;
int NUMBER_OF_LEDS = 8;
int leds[8] = {4,5,6,7,8,9,10,11};
int sequence[8] = {0,0,0,0,0,0,0,0};
int offsets[8] = {0,0,0,0,0,0,0,0};
unsigned long sustains[8] = {0,0,0,0,0,0,0,0};
int bpm;
int beat;
float interval;
unsigned long timing = 0;
unsigned long currentMillis;

void setup() {
  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    pinMode(leds[i], OUTPUT);
  }

  pinMode(button, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), setCurrentBeat, RISING);
  setBpm(120);
  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    setOffset(i, 0);
  }
}

void setBpm(int value){
  bpm = value;
  interval = 1000 / (bpm / 60);
}

void setStepState(int step, int state) {
  sequence[step] = state;
}

void clearSteps(){
  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    setStepState(i, 0);
  }
}

void setOffset(int id, int value) {
  offsets[id] = value + interval;
}

void setCurrentBeat(){
  int id = beat % NUMBER_OF_LEDS;
  sequence[id] = sequence[id]? 0 : 1;
}

void setAndSustain(int id, int duration){
  digitalWrite(leds[id], HIGH);
  sustains[id] = millis() + duration;
}

void loop() {
  currentMillis = millis();

  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    if ( sustains[i] < millis())
      digitalWrite(leds[i], sequence[i]);
  }

  if (currentMillis - timing >= offsets[(beat)%NUMBER_OF_LEDS]) {
    timing = currentMillis;
    setAndSustain((beat)%NUMBER_OF_LEDS, 50);
    beat++;
  }
}
