//**************************************************************//
//  Name    : shiftIn Example 1.1                              //
//  Author  : Carlyn Maw                                        //
//  Date    : 25 Jan, 2007                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a CD4021B Shift Register       //
//          :                                                   //
//****************************************************************

//define where your pins are
int const latchPin = 11;
int const dataPin = 13;
int const clockPin = 12;

//Define variables to hold the data
//for shift register.
//starting with a non-zero numbers can help
//troubleshoot
byte switchVar1 = 72;  //01001000

void setup() {
  //start serial
  Serial.begin(9600);

  //define pin modes
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);

}

void loop() {

  //Pulse the latch pin:
  //set it to 1 to collect parallel data
  digitalWrite(latchPin,1);
  //set it to 1 to collect parallel data, wait
  delayMicroseconds(20);
  //set it to 0 to transmit data serially
  digitalWrite(latchPin,0);

  //while the shift register is in serial mode
  //collect each shift register into a byte
  //the register attached to the chip comes in first
  switchVar1 = shiftIn(dataPin, clockPin);

  //Print out the results.
  //leading 0's at the top of the byte
  //(7, 6, 5, etc) will be dropped before
  //the first pin that has a high input
  //reading
  Serial.println(switchVar1, BIN);

//white space
Serial.println("-------------------");
//delay so all these print satements can keep up.
delay(500);

}

//------------------------------------------------end main loop

////// ----------------------------------------shiftIn function
///// just needs the location of the data pin and the clock pin
///// it returns a byte with each bit in the byte corresponding
///// to a pin on the shift register. leftBit 7 = Pin 7 / Bit 0= Pin 0
