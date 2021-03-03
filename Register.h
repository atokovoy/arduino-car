#ifndef REGISTER_H
#define REGISTER_H

#include <Arduino.h>

class Register
{
  public:
    Register(int dataPin, int latchPin, int clockPin, byte numCells);
    void digital(byte pin, int val);
    void digital(byte pinArr[], bool valArr[], byte numItems);
    void printData();
    void reset();
    void startBatch();
    void applyBatch();
  private:
    int _dataPin;
    int _latchPin;
    int _clockPin;
    byte _numCells;
    byte *_data;
    
    bool _batch;

    void setCellValue(byte pin, int val);
    byte arrayToByte(byte arr[]);
    void shiftData();
};

#endif
