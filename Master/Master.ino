#include <Timers.h>
#include <Servo.h>
#include <Rarity.h>

Rarity rarity;

void setup() {
  Serial.begin(9600);
  rarity.initialize();
}

void loop() {
  
  if (!rarity.isReady()) return;
  //Serial.println("loop");
  
  switch(rarity.getState()) {
    case (FIRST_FORWARD):
      Serial.println("First forward.");
      rarity.setDriveSpeed(158,180);
      if (rarity.isBumperHit(FRONT_LEFT) && !rarity.isBumperHit(FRONT_RIGHT)) { // if only one side is hit, stop that wheel on that side and drive hard on the other
        Serial.println("Left Front hit");
        rarity.setDriveSpeed(0,250);
      }
      if (!rarity.isBumperHit(FRONT_LEFT) && rarity.isBumperHit(FRONT_RIGHT)) { // if only one side is hit, stop that wheel on that side and drive hard on the other
        Serial.println("Left Front hit");
        rarity.setDriveSpeed(250,0);
      }
      if (rarity.isBumperHit(FRONT_LEFT) && rarity.isBumperHit(FRONT_RIGHT)) { // if only one side is hit, stop that wheel on that side and drive hard on the other
        Serial.println("Front hit");
        rarity.transitionToState(BACKING_UP,0);
      }
      break;
    case (BACKING_UP):
      Serial.println("Backing Up");
      rarity.setDriveSpeed(-145,-175);
      if (rarity.isBumperHit(BACK_LEFT) && !rarity.isBumperHit(BACK_RIGHT)) { // if only one side is hit, stop that wheel on that side and drive hard on the other
          rarity.setDriveSpeed(0,-250);
      }
      if (!rarity.isBumperHit(BACK_LEFT) && rarity.isBumperHit(BACK_RIGHT)) { // if only one side is hit, stop that wheel on that side and drive hard on the other
          rarity.setDriveSpeed(-250,0);
      }
      if (rarity.isBumperHit(BACK_LEFT) && rarity.isBumperHit(BACK_RIGHT)) { // if only one side is hit, stop that wheel on that side and drive hard on the other
          rarity.transitionToState(SLIGHT_FORWARD,FORWARD_DURATION);
      }
      //TMRArd_InitTimer(stall_timer,stall_time);
      //TMRArd_InitTimer(timer_one,stall_time + forward_time);
      break;
    case (SLIGHT_FORWARD):
      Serial.println("Slight Forward");
      rarity.setDriveSpeed(175,190);
      if(rarity.isTimerExpired()) {
        Serial.println("Timer Expired");
        rarity.transitionToState(TURNING,TURN_DURATION);
      }
      break; 
    case (TURNING):
      Serial.println("Turning");
      rarity.setDriveSpeed(-200,0);
      if(rarity.isTimerExpired()) {
        Serial.println("Timer Expired");
        rarity.transitionToState(DRIVING_STRAIGHT,0);
      }
      break; 
    case (DRIVING_STRAIGHT):
      Serial.println("Driving Straight");
      rarity.setDriveSpeed(150,180);
      if (rarity.isBumperHit(FRONT_LEFT) && rarity.isBumperHit(FRONT_RIGHT)) { // if only one side is hit, stop that wheel on that side and drive hard on the other
          Serial.println("Front Bump Hit");
          rarity.transitionToState(STOP,0);
      }
      break;
    case (STOP):
      Serial.println("Stop");
      rarity.setShooterAngle(TWO_POINT);
      rarity.setShooterPower(150);
      rarity.updateBallRequest();
      
      if (rarity.isBumperHit(FRONT_LEFT)) {
        rarity.setDriveMotor(EN_LEFT,0); 
      }
      else {
        rarity.setDriveMotor(EN_LEFT,170);
      }
      
      if (rarity.isBumperHit(FRONT_RIGHT)) {
        rarity.setDriveMotor(EN_RIGHT,0); 
      }
      else {
        rarity.setDriveMotor(EN_RIGHT,170);
      }
      break;    
    default:
      break;
  }

}
