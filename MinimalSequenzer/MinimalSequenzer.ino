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

int bpmArray[3] = {0, 0, 0}
int bpm = (bpmArray[0]*100)+(bpmArray[1]*10)+bpmArray[2];

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
  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    setOffset(i, 0);
  }
}

void setStepState(int step, int state) {
  sequence[step] = state;
}

void setPattern(int id, int value) {
  sequence[id] =  value;
}

void clearPattern(){
  for (int i = 0; i < NUMBER_OF_LEDS; i++){
    setPattern(i, 0);
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
