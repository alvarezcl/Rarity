/*---------------- Headers---- ---------------------------*/
#include <Pulse.h>
#include <Timers.h>

/*---------------- Pin Defines ---------------------------*/
#define StepPin    6
#define DirPin     5
#define Low        0
#define High       1

/*---------------- Time -----------------------------------*/
#define degree     45
#define whole_time 5
#define period     10

/*---------------- Arduino Main Functions -------------------*/

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Arduino.");
  pinMode(A0, INPUT);           // sets the analog pin as input
  pinMode(DirPin, OUTPUT);      // sets the digital pin as output
  // Setup timer
  TMRArd_InitTimer(0,1000);
}

void loop() {
  // Read in if keyboard is pressed
  unsigned char KeyEventOccurred = 0;
  KeyEventOccurred = Serial.available();
  static unsigned int state = 0;
  char input = Serial.read();
  // Change the direction if the keyboard is pressed
  if (KeyEventOccurred) {
    if (state == 0){
      digitalWrite(DirPin,HIGH);   // Change to High.
      state = 1;
    } else {
      digitalWrite(DirPin,LOW);   // Change to Low.
      state = 0;
    }
  }  
  
  if (TMRArd_IsTimerExpired(0)) {
    TMRArd_InitTimer(0,1000*whole_time); // in seconds
    digitalWrite(DirPin,HIGH);   // Change to High.
  } else {
    digitalWrite(DirPin,LOW);   // Change to Low. 
  }
  
  unsigned double pulse = (32/1.8)*(degree*whole_time)/(period*10^-4);
  
  unsigned int val = 0;
  val = analogRead(A0)/10;
  Serial.println(val);
  
  // Send pulse to stepper motor
  if (IsPulseFinished()) {
  Serial.println("Pulse Finished.");
  InitPulse(StepPin, period); 
  Pulse(int(pulse)); 
  }
}
