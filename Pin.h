#ifndef PIN_H
#define PIN_H

#include <Arduino.h>
#include "Register.h"

class Pin
{
  public:
    virtual void write(int mode) = 0;
    void high();
    void low();
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
    Register *_reg;
};

class PinHolder
{
  public:
    virtual void write(bool data[]) = 0;
};

class DigitalPinHolder
{
  public:
    DigitalPinHolder(byte pins[], byte num);
    virtual void write(bool data[]);
  private:
    byte *_pins;
    byte _num;
};

class RegisterPinHolder: public PinHolder
{
  public:
    RegisterPinHolder(Register *reg, byte pins[], byte num);
    virtual void write(bool data[]);
  private:
    Register *_reg;
    byte *_pins;
    byte _num;
};

#endif
