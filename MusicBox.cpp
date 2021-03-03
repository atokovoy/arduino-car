#include "MusicBox.h"

MusicBox::MusicBox(Pin* pin) {
  _pin = pin;
}

void MusicBox::play(int notes[], int tempo[], byte len) {
  for (int thisNote = 0; thisNote < len; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / tempo[thisNote];
    
    unsigned long endTime = millis() + noteDuration;
    unsigned long notch = 500000L / notes[thisNote];

    while (millis() < endTime) {
      _pin->write(HIGH);
      delayMicroseconds(notch / 2);
      _pin->write(LOW);
      delayMicroseconds(notch / 2);
    }
  
    delay(noteDuration * 1.3 / 3);
  }
}

void MusicBox::sound1() {
  int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

  // note durations: 4 = quarter note, 8 = eighth note, etc.
  int duration[] = {4, 8, 8, 4, 4, 4, 4, 4};

  play(melody, duration, 8);
}

void MusicBox::beep() {
  int melody[] = {NOTE_G3, NOTE_G3, NOTE_G3};
  int duration[] = {8, 4, 2};
  play(melody, duration, 3);
}
