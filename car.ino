#include <IRremote.h>
#include "MotorEngine.h"
/* 
 * STOP - IN1 LOW,  IN2 LOW,  IN3 LOW,  IN4 LOW
 * FWD  - IN1 HIGH, IN2 LOW,  IN3 HIGH, IN4 LOW
 * BKW  - IN1 LOW,  IN2 HIGH, IN3 LOW,  IN4 HIGH
 * LEFT - IN1 LOW,  IN2 HIGH, IN3 HIGH, IN4 LOW
 * RIGHT - IN1 HIGH, IN2 LOW, IN3 HIGH, IN4 LOW
 * 
 * UP - FF18E7
 * REPEAT - FFFFFFFF
 * DOWN - FF4AB5
 * LEFT - FF10EF
 * RIGHT - FF5AA5
 * STOP(*) - FF6897
 * 
 */

// Motor A connections
#define IN1 9
#define IN2 10

// Motor B connections
#define IN3 11
#define IN4 8

// IR sensor
#define IR 12
#define BTN_UP 0xFF18E7
#define BTN_DOWN 0xFF4AB5
#define BTN_LEFT 0xFF10EF
#define BTN_RIGHT 0xFF5AA5
#define BTN_STAR 0xFF6897


IRrecv irReceiver(IR);
MotorEngine motorEngine(IN1, IN2, IN3, IN4);

void setup() {
  motorEngine.stopMotors();
  
  Serial.begin(9600);
  irReceiver.enableIRIn();  // Start the receiver
  irReceiver.blink13(true);
}

void loop() {
  if (irReceiver.decode()) {
    uint32_t tCode = irReceiver.results.value;

    if (tCode == BTN_UP) {
      motorEngine.moveForward();
    } else if (tCode == BTN_DOWN) {
      motorEngine.moveBackward();
    } else if (tCode == BTN_LEFT) {
      motorEngine.turnLeft();
    } else if (tCode == BTN_RIGHT) {
      motorEngine.turnRight();
    } else if (tCode == BTN_STAR) {
      motorEngine.stopMotors();
    } else {
      motorEngine.repeat();
    }
    
    Serial.println(tCode, HEX);
    irReceiver.resume(); // Receive the next value
  }
  
  motorEngine.checkAutoStop();
}
