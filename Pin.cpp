#include "Pin.h"

DigitalPin::DigitalPin(byte pin) {
  _pin = pin;
  pinMode(pin, OUTPUT);
}

void DigitalPin::write(int mode) {
  digitalWrite(_pin, mode);
}

RegisterPin::RegisterPin(Register *reg, byte pin) {
  _reg = reg;
  _pin = pin;
}

void RegisterPin::write(int mode) {
  _reg->digital(_pin, mode);
}
