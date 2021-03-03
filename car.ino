#include <IRremote.h>
#include <NewPing.h>
#include "MotorEngine.h"
#include "MusicBox.h"
#include "Register.h"
#include "SegmentDisplay.h"

// Motor A connections
#define IN1 14
#define IN2 15

// Motor B connections
#define IN3 6
#define IN4 7

// Audio
#define SPK 3

// Register
#define LATCH 7
#define CLOCK 13
#define DATA 8
#define CELLS 3

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

// Segment display
#define A_SEG 1
#define B_SEG 5
#define C_SEG 11
#define D_SEG 9
#define E_SEG 8
#define DOT_SEG 10
#define G_SEG 12
#define F_SEG 2

#define D1_SEG 0
#define D2_SEG 3
#define D3_SEG 4
#define D4_SEG 13

IRrecv irReceiver(IR);
NewPing sonar(TRIGGER_BACK, ECHO_BACK, MAX_SONAR_DISTANCE);

Register reg(DATA, LATCH, CLOCK, CELLS);
MusicBox musicBox(new DigitalPin(SPK));
MotorEngine motorEngine(new RegisterPin(&reg, IN1), new RegisterPin(&reg, IN2), new RegisterPin(&reg, IN3), new RegisterPin(&reg, IN4));

byte pinSet[12] = {D1_SEG, D2_SEG, D3_SEG, D4_SEG, DOT_SEG, A_SEG, B_SEG, C_SEG, D_SEG, E_SEG, F_SEG, G_SEG};
RegisterPinHolder pinHolder(&reg, pinSet, 12);
SegmentDisplay segment(&pinHolder);

long nextBackDistMillis = 0;

void setup() {
  Serial.begin(9600);
  irReceiver.enableIRIn();
  irReceiver.blink13(true);
  randomSeed(analogRead(0));
}

void loop() {
  long tm = millis();
  if (tm > nextBackDistMillis) {
    nextBackDistMillis = tm + 5000;
    double dist = sonar.ping_cm();

    if (dist > 1000) {
      dist = 1000;
    }
    
    String str = String(dist, 1);
    segment.display(str.c_str(), 1000);
    segment.clear();
  }
  
  /*double backDistance = sonar.ping_cm();
  if (backDistance == 0) {
    backDistance = 100000;
  }
  Serial.print("Distance: ");
  Serial.print(backDistance);
  Serial.println(" cm");*/
  double backDistance = 1000000;

  //motorEngine.checkAutoStop();
  
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
    /*Serial.println("Run away!");
    
    motorEngine.moveForward();
    delay(1000);
    motorEngine.rotate(random(360) - 180);
    motorEngine.moveForward();
    delay(500);
    motorEngine.stopMotors();
    musicBox.beep();*/
  }
}
