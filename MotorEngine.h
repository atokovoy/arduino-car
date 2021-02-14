#ifndef MOTORENGINE_H
#define MOTORENGINE_H

#include <Arduino.h>
#include "Pin.h"

class MotorEngine
{
  public:
    MotorEngine(Pin* in1, Pin* in2, Pin* in3, Pin* in4);
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void stopMotors();
    void rotate(short grad);
    void repeat();
    void checkAutoStop();
    void setMovementAutoStop(int autoStop);
    void setRotationAutoStop(int autoStop);
  private:
    typedef void (MotorEngine::*CallbackOperation) ();
    
    Pin* _in1;
    Pin* _in2;
    Pin* _in3;
    Pin* _in4;
    CallbackOperation _lastOperation;
    unsigned long _autoStopMillis;
    int _movementAutoStop;
    int _rotationAutoStop;
};

#endif
