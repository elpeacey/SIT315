#include "pins_arduino.h"

// set LED pins
int redLED = 10;
int greenLED = 12;

int motion = 2;       // set motion sensor pin 
int motion2 = 3;	  // set second motion pin


//Global variables
int red = LOW;
int green = LOW;

 
void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(motion, INPUT);     // declare sensor as input
  pinMode(motion2, INPUT);
  
  // set interrupt
  attachInterrupt(digitalPinToInterrupt(motion), toggleRed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motion2), toggleGreen, CHANGE);
  
  Serial.begin(9600);
  
  Serial.println("Start");
}
 
void loop(){
  delay(1000);
}

void toggleRed() {
  red = !red;
  if (red == HIGH) {          // check if the input is HIGH
    digitalWrite(redLED, HIGH);  // turn LED ON
    Serial.println("LED red");
    Serial.println("Motion detected");
  }
  else {
    digitalWrite(redLED, LOW); // turn LED OFF
    Serial.println("LED off");
    Serial.println("Motion ended");
  }
}

void toggleGreen() {
  red = !red;
  if (red == HIGH) {          // check if the input is HIGH
    digitalWrite(greenLED, HIGH);  // turn LED ON
    Serial.println("LED green");
    Serial.println("Motion detected");
  }
  else {
    digitalWrite(greenLED, LOW); // turn LED OFF
    Serial.println("LED off");
    Serial.println("Motion ended");
  }
}