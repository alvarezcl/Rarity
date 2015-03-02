#include <Servo.h> 
#include <Timers.h>

#define sensorIR 15
Servo myservo;  // Creates a servo object
volatile float inches;
 
void setup()
{ 
  myservo.attach(12);  // Assigns data pin to your servo object, must be digital port
  Serial.begin(9600);
  TMRArd_InitTimer(0,20);
} 

boolean dir = true;
unsigned int pos = 0;
void loop()
{ 
  if (TMRArd_IsTimerExpired(0)) {
    myservo.write(dir ? pos++ : pos--);
    if (pos >= 180 || pos <= 0) dir = !dir;
    TMRArd_InitTimer(0,20);
  }
}

