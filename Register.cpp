#include "Register.h"

Register::Register(int dataPin, int latchPin, int clockPin, byte numCells) {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;
  _numCells = numCells;
  _batch = false;

  _data = new byte[numCells]();
  
  shiftData();
}

void Register::shiftData() {
  digitalWrite(_latchPin, LOW);

  for (short i = _numCells - 1; i >= 0; i--) {
    shiftOut(_dataPin, _clockPin, MSBFIRST, _data[i]);
  }
  
  digitalWrite(_latchPin, HIGH);

  _batch = false;
}

void Register::setCellValue(byte pin, int val) {
  byte row = ceil(pin / 8);
  byte old = _data[row];

  bitWrite(old, pin - row * 8, val);
  _data[row] = old;
}

void Register::reset() {
  for (byte i = 0; i < _numCells; ++i) {
      _data[i] = 0;
  }

  shiftData();
}

void Register::digital(byte pin, int val) {
  setCellValue(pin, val);

  if (false == _batch) {
    shiftData();
  }
}

void Register::digital(byte pinArr[], bool valArr[], byte numItems) {
  for (byte i = 0; i < numItems; i++) {
    setCellValue(pinArr[i], valArr[i]);
  }

  if (false == _batch) {
    shiftData();
  }
}

void Register::printData() {
  Serial.print("Num cells: ");
  Serial.println(_numCells);
  Serial.println("      01234567");
  Serial.println("      --------");
  for (byte i = 0; i < _numCells; i++) {
    Serial.print("R ");
    Serial.print(i);
    Serial.print(" : ");
    for (byte j = 0; j < 8; j++) {
        bool b = bitRead(_data[i], j);
        Serial.print(b);
    }
    Serial.println();
  }
}

void Register::startBatch() {
  _batch = true;
}

void Register::applyBatch() {
  if (false == _batch) {
    return;
  }

  shiftData();
}
