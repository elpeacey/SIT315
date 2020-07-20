int led = 13;         // set LED pin
int motion = 2;       // set motion sensor pin 
int tempPin = 0;	  // set temp sensor pin	

//Global variables
float temp;
int val = LOW;                    // read pin status
 
void setup() {
  pinMode(led, OUTPUT);      // declare LED as output
  pinMode(motion, INPUT);     // declare sensor as input
  
  // set interrupt
  attachInterrupt(digitalPinToInterrupt(motion), toggle, CHANGE);
  
  Serial.begin(9600);
  
  Serial.println("Start");
}
 
void loop(){
  temp = analogRead(tempPin);
  temp = (temp  * 0.48828125);
  Serial.print("Temperature in celsius: ");
  Serial.print(temp);
  Serial.println();
  
  delay(1000);
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