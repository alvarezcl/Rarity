#include "Rarity.h"
#include "Arduino.h"
#include "Servo.h"
#include "Timers.h"

// BUMPERS
#define BACK_RIGHT       10
#define FRONT_RIGHT      11
#define FRONT_LEFT       9
#define BACK_LEFT        8

// TANK DRIVE
#define EN_LEFT          6   // Connected to E1 (Enable Pin) on L293
#define DIR_LEFT         7   // Connected to D1 (Direction Pin) on L293
#define EN_RIGHT         5   // Connected to E2 (Enable Pin) on L293
#define DIR_RIGHT        4  // Connected to D2 (Direction Pin) on L293

// SHOOTER/LAUNCHER/TURRET/BRB
#define CAM_PIN          3 // Cam pin
#define TURRET_PIN       12 // servo
#define STRAIGHT         92
#define TWO_POINT        135
#define THREE_POINT      156 

// BALL REQUEST
#define REQUEST_PIN      13
#define REQUEST_ON       0
#define REQUEST_OFF      90
#define REQUEST_TIMER    2 

// STATES
#define STATE_TIMER      1
#define FIRST_FORWARD    9
#define BACKING_UP       10
#define TURNING          11
#define DRIVING_STRAIGHT 12
#define STOP             13
#define SLIGHT_FORWARD   14

// SERIAL
#define PRINT_TIMER      0
#define PRINT_DURATION   3000

/*---------------- Time ----------------------------------
// Timers
#define timer_one       0
#define timer_two       1
#define stall_timer     2
#define console_timer   3
#define brb_timer       4

// Time for certain states
#define period_turn     100 // in ticks (1000 ticks = 1 sec) // prev 200
#define forward_time    1000 // in ticks
#define stall_time      1000

/*---------------- States ----------------------------------*/

Rarity::Rarity(void) {
  Serial.begin(9600);
  Serial.println("Starting Rarity...");
  
  shooter = new Servo;
  shooter.attach(SHOOTER_PIN);
  shooter.write(STRAIGHT);
  
  request = new Servo;
  request.attach(REQUEST_PIN);
  request.write(REQUEST_OFF);
  
  pinMode(CAM_PIN, OUTPUT);       // Cam
  digitalWrite(CAM_PIN, LOW);
  
  pinMode(BACK_RIGHT, INPUT);                 
  pinMode(FRONT_RIGHT, INPUT);
  pinMode(FRONT_LEFT, INPUT);
  pinMode(BACK_LEFT, INPUT);
  
  pinMode(EN_LEFT, OUTPUT);      // sets digital pin 6 as output
  pinMode(DIR_LEFT, OUTPUT);         // sets digital pin 7 as output
  pinMode(EN_RIGHT, OUTPUT);      // sets digital pin 5 as output
  pinMode(DIR_RIGHT, OUTPUT);         // sets digital pin 4 as output
  
  digitalWrite(DIR_LEFT, HIGH);      // Set L293 pin 7 as HIGH (Backward)
  digitalWrite(DIR_RIGHT, HIGH);      // Set L293 pin 4 as HIGH (Backward)
  
  TMRArd_InitTimer(PRINT_TIMER,PRINT_DURATION);
}

void Rarity::setDriveSpeed(char left, char right) {
  analogWrite(EN_LEFT,left);
  analogWrite(EN,RIGHT,right);
}

boolean Rarity::isBumperHit(char bumper) {
  return digitalRead(bumper);
}

boolean Rarity::isReady(void) {
  return TMRArd_IsTimerExpired(STATE_TIMER);
}

void Rarity::setShooterAngle(char angle) {
  shooter.write(angle);
}

void Rarity::setShooterPower(char power) {
  analogWrite(CAM_PIN,power);
}

void Rarity::setBallRequestRate(int touch, int hold) {
  
}

void Rarity::transitionToState(char next) {

}
