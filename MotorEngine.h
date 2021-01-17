#ifndef MOTORENGINE_H
#define MOTORENGINE_H

#include <Arduino.h>

class MotorEngine
{
  public:
    MotorEngine(int in1, int in2, int in3, int in4);
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void stopMotors();
    void repeat();
    void checkAutoStop();
    void setMovementAutoStop(int autoStop);
    void setRotationAutoStop(int autoStop);
  private:
    typedef void (MotorEngine::*CallbackOperation) ();
    
    int _in1;
    int _in2;
    int _in3;
    int _in4;
    CallbackOperation _lastOperation;
    unsigned long _autoStopMillis;
    int _movementAutoStop;
    int _rotationAutoStop;
};

#endif
