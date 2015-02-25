/**************************************************************
  File:     Base_Motors.ino
  Contents: This program demonstrates the use of the software
            for driving the base motors. By connecting the
            Arduino to the L293 Driver, the program is able 
            to turn each wheel clockwise or counter-clockwise
            such that the bot has full planar DOF. 

/*---------------- Pin Defines ---------------------------*/
#define EnablePin_1     11   // Connected to E1 (Enable Pin) on L293
#define DirPin_1        6   // Connected to D1 (Direction Pin) on L293

#define EnablePin_2     9   // Connected to E2 (Enable Pin) on L293
#define DirPin_2        10  // Connected to D2 (Direction Pin) on L293

/*---------------- Arduino Main Functions -------------------*/
void setup()
{
  Serial.begin(9600);
  Serial.println("Starting Arduino. Part 4.");
  pinMode(A0, INPUT);
  pinMode(EnablePin_1, OUTPUT);      // sets digital pin 11 as output
  pinMode(DirPin_1, OUTPUT);         // sets digital pin 6 as output
  pinMode(EnablePin_2, OUTPUT);      // sets digital pin 9 as output
  pinMode(DirPin_2, OUTPUT);         // sets digital pin 10 as output
  digitalWrite(DirPin_1, LOW);       // Set L293 pin 6 as LOW
  digitalWrite(DirPin_2, LOW);       // Set L293 pin 10 as LOW
}

void loop(){
  
  // Change direction if a key was pressed. 
  unsigned char KeyEventOccurred = 0;
  KeyEventOccurred = Serial.available();
  char input = Serial.read();
  if (KeyEventOccurred) {
    // If both are in a high state, returning greater than 0
    // Set to low
    if (digitalRead(DirPin_1) & digitalRead(DirPin_2)) {
      digitalWrite(DirPin_1,LOW);
      digitalWrite(DirPin_2,LOW);
    } else { // both or one is in the low state so set to High
      digitalWrite(DirPin_1,HIGH);
      digitalWrite(DirPin_2,HIGH);
    }
    Serial.println("Direction changed.");
  }
  
  // Read in the voltage from the potentiometer
  unsigned int val = 0;
  val = analogRead(A0);
  Serial.println(val);
  // Floor to 255 if val is greater than 255 for resolution
  if (val > 255){
    val = 255;
  }
  // Send a PWM signal using the arduino libraries
  analogWrite(EnablePin_1, val);
  analogWrite(EnablePin_2, val);  
}
