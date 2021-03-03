#include "Pin.h"


void Pin::high() {
  this->write(HIGH);
}

void Pin::low() {
  this->write(LOW);
}

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

DigitalPinHolder::DigitalPinHolder(byte pins[], byte num) {
  _pins = pins;
  _num = num;
}

void DigitalPinHolder::write(bool data[]) {
  for (byte i = 0; i < _num; i++) {
    digitalWrite(_pins[i], data[i]);
  }
}

RegisterPinHolder::RegisterPinHolder(Register* reg, byte pins[], byte num) {
  _reg = reg;
  _pins = pins;
  _num = num;
}

void RegisterPinHolder::write(bool data[]) {
  _reg->digital(_pins, data, _num);
}
