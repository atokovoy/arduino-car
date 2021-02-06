#include "Register.h"

Register::Register(int dataPin, int latchPin, int clockPin, byte numCells) {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;
  _numCells = numCells;

  _data = new byte*[numCells];
  for (byte i = 0; i < numCells; ++i) {
    _data[i] = new byte[8](); //default to zero
  }
  
  shiftData();
}

byte Register::arrayToByte(byte arr[8]) {
  byte res = 0;
  for (byte i = 0; i < 8; i++) {
    res = res + arr[i] * ceil(pow(2, i));
  }

  return res;
}

void Register::shiftData() {
  digitalWrite(_latchPin, LOW);

  for (short i = _numCells - 1; i >= 0; i--) {
    Serial.print("Item ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(arrayToByte(_data[i]));
    shiftOut(_dataPin, _clockPin, MSBFIRST, arrayToByte(_data[i]));
  }
  
  digitalWrite(_latchPin, HIGH);
}

void Register::digital(byte pin, int val) {
  byte row = ceil(pin / 8);

  _data[row][pin - row * 8] = val;

  shiftData();
}

void Register::printData() {
  for (byte i = 0; i < _numCells; i++) {
    Serial.print("R ");
    Serial.print(i);
    Serial.print(" : ");
    for (byte j = 0; j < 8; j++) {
      Serial.print(_data[i][j]);
    }
    Serial.println();
  }
}

void Register::reset() {
  for (byte i = 0; i < _numCells; ++i) {
    for (byte j = 0; j < 8; j++) {
      _data[i][j] = 0;
    }
  }

  shiftData();
}
