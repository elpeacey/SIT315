int led = 13;                // set LED pin
int sensor = 2;               // set sensor pin 

int val = LOW;                    // read pin status
 
void setup() {
  pinMode(led, OUTPUT);      // declare LED as output
  pinMode(sensor, INPUT);     // declare sensor as input
  
  // set interrupt
  attachInterrupt(digitalPinToInterrupt(sensor), toggle, CHANGE);
  
  Serial.begin(9600);
}
 
void loop(){
  
  delay(500);
}

void toggle() {
  val = !val;
  if (val == HIGH) {          // check if the input is HIGH
    digitalWrite(led, HIGH);  // turn LED ON
    Serial.println("LED on");
    Serial.println("Motion detected");
  }
  else {
    digitalWrite(led, LOW); // turn LED OFF
    Serial.println("LED off");
    Serial.println("Motion ended");
  }
}