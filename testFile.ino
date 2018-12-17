int bpmArry[3] = {0, 0, 0};
int bpm;
int beat;
float interval;
unsigned long timing = 0;
unsigned long currentMillis;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);

}

void loop() {
  currentMillis = millis();
  if (currentMillis - timing > millis() ){

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
