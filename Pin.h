#ifndef PIN_H
#define PIN_H

#include <Arduino.h>
#include "Register.h"

class Pin
{
  public:
    virtual void write(int mode) = 0;
};

class DigitalPin: public Pin
{
  public:
    DigitalPin(byte pin);
    virtual void write(int mode);
  private:
    byte _pin;
};

class RegisterPin: public Pin
{
  public:
    RegisterPin(Register *reg, byte pin);
    virtual void write(int mode);
  private:
    byte _pin;
    Register* _reg;
};

#endif
