// set pins
int redLED = 10;
int blueLED = 11; 
int greenLED = 12;

int tempPin = 0;
int motion = 2;       // set motion sensor pin 
int motion2 = 3;	  // set 2nd motion sensor pinint tempPin = 0;	  // set temp sensor pin	

//Global variables
float temp;
float currentTemp = 0;

int val_m = LOW;
int val_m2 = LOW;

// define constant variables
const uint16_t compare = 15625;
                 

void setup() {
  // LED as output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  // sensors as input
  pinMode(motion, INPUT);
  pinMode(motion2, INPUT);
  
  // enable interrupts
  PCMSK2 |= (1 << PCINT18);
  PCMSK2 |= (1 << PCINT19);
  
  PCICR |= (1 << PCIE2);
  
  temp = analogRead(tempPin);
  
  TCCR1A = 0; // reset TCCR1A register
  
  // clear
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);
  
  
  // set prescaler
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);
  
  // set timer and compare value
  TCNT1 = 0;
  OCR1A = compare;
  
  // enable compare interrupt 
  TIMSK1 = (1 << OCIE1A);
  
  // enable global interrupts
  sei();
  
  Serial.begin(9600);
  
  Serial.println("Start");
}
 
void loop(){
  temp = analogRead(tempPin);
  temp = (temp  * 0.48828125);
  
  if(temp != currentTemp){
    Serial.print("Temperature in celsius: ");
    Serial.print(temp);
    Serial.println();
    currentTemp = temp;
  }
}

ISR(PCINT2_vect) {
  // Read values
  int pirSensor = (PIND & (1 << motion)) >> motion;
  int pirSensor2 = (PIND & (1 << motion2)) >> motion2;
  
  if (pirSensor != val_m) {
  	motionHandle();
  }
  
  if (pirSensor2 != val_m2) {
  	motion2Handle();
  }
}

ISR(TIMER1_COMPA_vect) {
  //Toggle red led
  if (digitalRead(redLED) == HIGH){
    digitalWrite(redLED, LOW);
  } 
  else {
    digitalWrite(redLED, HIGH);
  }
}

void motionHandle() {
  val_m = !val_m;
  
  digitalWrite(greenLED, val_m);  
  Serial.println("Motion changed");
}

void motion2Handle() {
  val_m2 = !val_m2;
  
  digitalWrite(blueLED, val_m2);
  Serial.println("Motion 2 changed");
}