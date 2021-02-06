//#define IR_USE_TIMER1

#include <IRremote.h>
#include "MotorEngine.h"
#include "MusicBox.h"

/* 
 * UP - FF18E7
 * REPEAT - FFFFFFFF
 * DOWN - FF4AB5
 * LEFT - FF10EF
 * RIGHT - FF5AA5
 * STOP(*) - FF6897
 * SHARP - FFB04F
 * 
 * Audio - 2
 * Echo  - 1
 * trigger - 0
 */
/***** 7 8 12 ******/
// Motor A connections
#define IN1 7
#define IN2 8

// Motor B connections
#define IN3 11
#define IN4 4

// Audio
#define SPK 2

// IR sensor
#define IR 12
#define BTN_UP 0xFF18E7
#define BTN_DOWN 0xFF4AB5
#define BTN_LEFT 0xFF10EF
#define BTN_RIGHT 0xFF5AA5
#define BTN_STAR 0xFF6897
#define BTN_SHARP 0xFFB04F

IRrecv irReceiver(IR);
MotorEngine motorEngine(IN1, IN2, IN3, IN4);
MusicBox musicBox(SPK);

void setup() {
  motorEngine.stopMotors();
  
  Serial.begin(9600);
  irReceiver.enableIRIn();  // Start the receiver
  irReceiver.blink13(true);
}

void loop() {
  if (irReceiver.decode()) {
    uint32_t tCode = irReceiver.results.value;

    switch (tCode) {
      case BTN_UP: motorEngine.moveForward(); break;
      case BTN_DOWN: motorEngine.moveBackward(); break;
      case BTN_LEFT: motorEngine.turnLeft(); break;
      case BTN_RIGHT: motorEngine.turnRight(); break;
      case BTN_STAR: motorEngine.stopMotors(); break;
      case BTN_SHARP: musicBox.sound1(); break;
      default: motorEngine.repeat(); break;
    }
    
    Serial.println(tCode, HEX);
    irReceiver.resume(); // Receive the next value
  }
  
  motorEngine.checkAutoStop();
}
