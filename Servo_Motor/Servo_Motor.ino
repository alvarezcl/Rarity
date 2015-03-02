#include <Servo.h> 
#include <Timers.h>

#define period_shooter  10
Servo myservo;  // Creates a servo object
int pos = 0;    // Variable to store the servos angle 
 
void setup()
{ 
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
} 

void loop()
{  
  analogWrite(9,150);
  analogWrite(10,150);
}
