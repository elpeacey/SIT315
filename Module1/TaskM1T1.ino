int led = 13;                // set LED pin
int sensor = 2;               // set sensor pin 

bool motionDetected = false;    // check if motion is detected 
int val = 0;                    // read pin status
int previous = 0;				// check previous pin status
 
void setup() {
  pinMode(led, OUTPUT);      // declare LED as output
  pinMode(sensor, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(sensor);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(led, HIGH);  // turn LED ON
    if (previous == 0) {
        Serial.println("LED on");
    }
    previous = 1;
    
  	if (motionDetected == false) {	
      Serial.println("Motion detected");
      motionDetected = true;
    }
  } 
  
  else {
    digitalWrite(led, LOW); // turn LED OFF
    if (previous == 1) {
        Serial.println("LED off");
    }
    previous = 0;
    
    if (motionDetected == true){
      Serial.println("Motion ended");
      motionDetected = false;
    }
  }
}