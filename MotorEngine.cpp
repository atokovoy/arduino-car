#include "MotorEngine.h"

MotorEngine::MotorEngine(Pin* in1, Pin* in2, Pin* in3, Pin* in4)
{
  _in1 = in1;
  _in2 = in2;
  _in3 = in3;
  _in4 = in4;
  _lastOperation = NULL;
  _movementAutoStop = 500;
  _rotationAutoStop = 200;
  _stopped = true;
}

void MotorEngine::stopMotors() {
  if (_stopped) {
    return;
  }
  
  _in1->write(LOW);
  _in2->write(LOW);
  _in3->write(LOW);
  _in4->write(LOW);

  _lastOperation = &MotorEngine::stopMotors;
  _stopped = true;
}

void MotorEngine::moveBackward() {
  _in1->write(HIGH);
  _in2->write(LOW);
  _in3->write(HIGH);
  _in4->write(LOW);

  _lastOperation = &MotorEngine::moveBackward;
  _autoStopMillis = millis() + _movementAutoStop;
  _stopped = false;
}

void MotorEngine::moveForward() {
  _in1->write(LOW);
  _in2->write(HIGH);
  _in3->write(LOW);
  _in4->write(HIGH);

  _lastOperation = &MotorEngine::moveForward;
  _autoStopMillis = millis() + _movementAutoStop;
  _stopped = false;
}

void MotorEngine::turnLeft() {
  _in1->write(LOW);
  _in2->write(HIGH);
  _in3->write(HIGH);
  _in4->write(LOW);

  _lastOperation = &MotorEngine::turnLeft;
  _autoStopMillis = millis() + _rotationAutoStop;
  _stopped = false;
}

void MotorEngine::turnRight() {
  _in1->write(HIGH);
  _in2->write(LOW);
  _in3->write(LOW);
  _in4->write(HIGH);

  _lastOperation = &MotorEngine::turnRight;
  _autoStopMillis = millis() + _rotationAutoStop;
  _stopped = false;
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

void MotorEngine::rotate(short grad) {
  if (grad == 0) {
    return;
  }
  if (grad > 0) {
    turnRight();
  } else {
    turnLeft();
  }

  delay(round(abs(grad) * 3.25));
  stopMotors();
}
