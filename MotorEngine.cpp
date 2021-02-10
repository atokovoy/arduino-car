#include "MotorEngine.h"

MotorEngine::MotorEngine(int in1, int in2, int in3, int in4)
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  _in1 = in1;
  _in2 = in2;
  _in3 = in3;
  _in4 = in4;
  _lastOperation = NULL;
  _movementAutoStop = 500;
  _rotationAutoStop = 200;
  _reg = NULL;
}

MotorEngine::MotorEngine(Register* reg, int in1, int in2, int in3, int in4)
{
  _in1 = in1;
  _in2 = in2;
  _in3 = in3;
  _in4 = in4;
  _lastOperation = NULL;
  _movementAutoStop = 500;
  _rotationAutoStop = 200;
  _reg = reg;
}

void MotorEngine::digital(int pin, int val)
{
  if (NULL == _reg) {
    digitalWrite(pin, val);

    return;
  }

  _reg->digital(pin, val);
}

void MotorEngine::stopMotors() {
  digital(_in1, LOW);
  digital(_in2, LOW);
  digital(_in3, LOW);
  digital(_in4, LOW);

  _lastOperation = &MotorEngine::stopMotors;
}

void MotorEngine::moveBackward() {
  digital(_in1, HIGH);
  digital(_in2, LOW);
  digital(_in3, HIGH);
  digital(_in4, LOW);

  _lastOperation = &MotorEngine::moveBackward;
  _autoStopMillis = millis() + _movementAutoStop;
}

void MotorEngine::moveForward() {
  digital(_in1, LOW);
  digital(_in2, HIGH);
  digital(_in3, LOW);
  digital(_in4, HIGH);

  _lastOperation = &MotorEngine::moveForward;
  _autoStopMillis = millis() + _movementAutoStop;
}

void MotorEngine::turnLeft() {
  digital(_in1, LOW);
  digital(_in2, HIGH);
  digital(_in3, HIGH);
  digital(_in4, LOW);

  _lastOperation = &MotorEngine::turnLeft;
  _autoStopMillis = millis() + _rotationAutoStop;
}

void MotorEngine::turnRight() {
  digital(_in1, HIGH);
  digital(_in2, LOW);
  digital(_in3, LOW);
  digital(_in4, HIGH);

  _lastOperation = &MotorEngine::turnRight;
  _autoStopMillis = millis() + _rotationAutoStop;
}

void MotorEngine::repeat() {
  if (_lastOperation == NULL) {
    return;
  }

  (this->*_lastOperation)();
}

void MotorEngine::checkAutoStop() {
  if (millis() > _autoStopMillis) {
    stopMotors();
  }
}

void MotorEngine::setMovementAutoStop(int autoStop) {
  _movementAutoStop = autoStop;
}

void MotorEngine::setRotationAutoStop(int autoStop) {
  _rotationAutoStop = autoStop;
}
