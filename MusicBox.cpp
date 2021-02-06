#include "MusicBox.h"

MusicBox::MusicBox(int out) {
  _out = out;
}

int MusicBox::noteDurationSec(int noteType) {
  return 1000 / noteType;
}

void MusicBox::pauseBetweenNotes(int duration) {
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pause = duration * 1.30;
  
  delay(pause);
}

void MusicBox::myTone(byte pin, uint16_t frequency, uint16_t duration)
{ // input parameters: Arduino pin number, frequency in Hz, duration in milliseconds
  unsigned long startTime = millis();
  unsigned long halfPeriod= 1000000L / frequency / 2;
  pinMode(pin, OUTPUT);
  while (millis() - startTime < duration) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin, LOW);
    delayMicroseconds(halfPeriod);
  }
  
  pinMode(pin, INPUT);
}

void MusicBox::play(int notes[], int tempo[]) {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = noteDurationSec(tempo[thisNote]);
    myTone(_out, notes[thisNote], noteDuration);

    pauseBetweenNotes(noteDuration / 4);
    // stop the tone playing:
    //noTone(_out);
  }
}

void MusicBox::sound1() {
  int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };

  play(melody, noteDurations);
}
