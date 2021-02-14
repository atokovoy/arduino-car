#include <IRremote.h>
#include <NewPing.h>
#include "MotorEngine.h"
#include "MusicBox.h"
#include "Register.h"

// Motor A connections
#define IN1 1
#define IN2 2

// Motor B connections
#define IN3 3
#define IN4 4

// Audio
#define SPK 3

// Register
#define LATCH 7
#define CLOCK 13
#define DATA 8

// IR sensor
#define IR 12
#define BTN_UP 0xFF18E7
#define BTN_DOWN 0xFF4AB5
#define BTN_LEFT 0xFF10EF
#define BTN_RIGHT 0xFF5AA5
#define BTN_STAR 0xFF6897
#define BTN_SHARP 0xFFB04F

// Echo back
#define ECHO_BACK 4
#define TRIGGER_BACK 2
#define MAX_SONAR_DISTANCE 100
#define BACK_DISTANCE_LIMIT 20
#define BACK_DISTANCE_RUN_AWAY 40

IRrecv irReceiver(IR);
Register reg(DATA, LATCH, CLOCK, 2);
MusicBox musicBox(new DigitalPin(SPK));
MotorEngine motorEngine(new RegisterPin(&reg, IN1), new RegisterPin(&reg, IN2), new RegisterPin(&reg, IN3), new RegisterPin(&reg, IN4));

NewPing sonar(TRIGGER_BACK, ECHO_BACK, MAX_SONAR_DISTANCE);

void setup() {
  Serial.begin(9600);
  irReceiver.enableIRIn();
  irReceiver.blink13(true);
  randomSeed(analogRead(0));
}

void loop() {
  double backDistance = sonar.ping_cm();
  if (backDistance == 0) {
    backDistance = 100000;
  }
  Serial.print("Distance: ");
  Serial.print(backDistance);
  Serial.println(" cm");

  motorEngine.checkAutoStop();
  
  if (irReceiver.decode()) {
    uint32_t tCode = irReceiver.results.value;

    switch (tCode) {
      case BTN_UP: motorEngine.moveForward(); break;
      case BTN_DOWN:
        if (backDistance > BACK_DISTANCE_LIMIT) {
          motorEngine.moveBackward();
        }
        break;
      case BTN_LEFT: motorEngine.turnLeft(); break;
      case BTN_RIGHT: motorEngine.turnRight(); break;
      case BTN_STAR: motorEngine.stopMotors(); break;
      case BTN_SHARP: musicBox.beep(); break;
      default: motorEngine.repeat(); break;
    }
    
    Serial.println(tCode, HEX);
    irReceiver.resume(); // Receive the next value
  } else if (backDistance < BACK_DISTANCE_RUN_AWAY) {
    Serial.println("Run away!");
    
    motorEngine.moveForward();
    delay(1000);
    motorEngine.rotate(random(360) - 180);
  }
}
