#ifndef Rarity_h
#define Rarity_h

#include "Arduino.h"
#include "Servo.h"
#include "Timers.h"

class Rarity {
  public:
  
    Rarity(void);
  
    void setDriveSpeed(char left, char right); // HIGH is backward, LOW is forward determined by sign

    boolean isBumperHit(char bumper); // LF LB RF RB

    boolean isReady(void); // needed to pause in between states

    void setShooterAngle(char angle); // for 2 pt or 3 pt (or 1 point)

    void setShooterPower(char power); // #define ON (HIGH) #define OFF (LOW)

    void setBallRequestRate(int touch, int hold); // time in ms

    void transitionToState(char next); // have #defines for state names

  private:
    
    char state;
    Servo *turret;
    Servo *request;
    
};

#endif

