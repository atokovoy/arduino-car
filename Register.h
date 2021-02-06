#ifndef REGISTER_H
#define REGISTER_H

#include <Arduino.h>

class Register
{
  public:
    Register(int dataPin, int latchPin, int clockPin, byte numCells);
    void digital(byte pin, int val);
    void printData();
    void reset();
  private:
    int _dataPin;
    int _latchPin;
    int _clockPin;
    byte _numCells;
    byte **_data;

    byte arrayToByte(byte arr[]);
    void shiftData();
};

#endif
