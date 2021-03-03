#include "SegmentDisplay.h"

// d1 d2 d3 d4 dot a b c d e f g
SegmentDisplay::SegmentDisplay(PinHolder *pinHolder) {
  _pinHolder = pinHolder;
}

void SegmentDisplay::display(const char *txt, unsigned int ms) { 
  char str[4] = "    ";
  char tmp[4];
  bool dots[4] = {1, 1, 1, 1};
  
  byte len = strlen(txt);
  byte i = 0, j = 0, k = 0, l = 0;

  while ((i < 4) && (j < len)) {
    if ((k < 4) && (txt[j] == '.')) {
      if (i == 0) {
        dots[0] = 0;
      } else {
        dots[i - 1] = 0;
      }
      k++;
      j++;

      continue;
    }
    tmp[i] = txt[j];
    
    i++;
    j++;
    l++;
  }

  if ((j < len) && (k < 4) && (txt[j] == '.')) {
    dots[3] = 0;
  }

  if (k > 0) {
    for (i = 0; i < 4 - l; i++) {
      for (j = 3; j > 0; j--) {
        dots[j] = dots[j - 1];
      }
      dots[0] = 1;
    }
  }

  for (i = 4 - l, j = 0; i < 4; i++, j++) {
    str[i] = tmp[j];
  }
  
  long tm = millis();

  while (millis() - tm < ms) {
    for (byte i = 0; i < 4; i++) {
      disableAll();

      _state[i] = 1;
      _state[_SD_ST_DOT] = dots[i];
     
      switch(str[i]) {
        case '0': displayZero(); break;
        case '1': displayOne(); break;
        case '2': displayTwo(); break;
        case '3': displayThree(); break;
        case '4': displayFour(); break;
        case '5': displayFive(); break;
        case '6': displaySix(); break;
        case '7': displaySeven(); break;
        case '8': displayEight(); break;
        case '9': displayNine(); break;
        case ' ': displayNull(); break;
        case 'P': displayP(); break;
        case 'A': displayA(); break;
        case 'I': displayI(); break;
        default: displayNull(); break;
      }
  
      _pinHolder->write(_state);
      
      delayMicroseconds(54);
    }
  }
}

void SegmentDisplay::clear() {
  disableAll();

  _pinHolder->write(_state);
}

void SegmentDisplay::test() {
  bool data[12] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
  _pinHolder->write(data);
}

void SegmentDisplay::displayDot() {
    _state[_SD_ST_DOT] = 0;
}

//Display function ‘0-9’ 
void SegmentDisplay::displayZero() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 0;
  _state[_SD_ST_E] = 0;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 1;
}

void SegmentDisplay::displayOne() { 
  _state[_SD_ST_A] = 1;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 1;
  _state[_SD_ST_E] = 1;
  _state[_SD_ST_F] = 1;
  _state[_SD_ST_G] = 1;
}

void SegmentDisplay::displayTwo() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 1;
  _state[_SD_ST_D] = 0;
  _state[_SD_ST_E] = 0;
  _state[_SD_ST_F] = 1;
  _state[_SD_ST_G] = 0;
}

void SegmentDisplay::displayThree() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 0;
  _state[_SD_ST_E] = 1;
  _state[_SD_ST_F] = 1;
  _state[_SD_ST_G] = 0;
}

void SegmentDisplay::displayFour() {
  _state[_SD_ST_A] = 1;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 1;
  _state[_SD_ST_E] = 1;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 0;
}

void SegmentDisplay::displayFive() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 1;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 0;
  _state[_SD_ST_E] = 1;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 0;
}

void SegmentDisplay::displaySix() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 1;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 0;
  _state[_SD_ST_E] = 0;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 0;
}

void SegmentDisplay::displaySeven() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 1;
  _state[_SD_ST_E] = 1;
  _state[_SD_ST_F] = 1;
  _state[_SD_ST_G] = 1;
}

void SegmentDisplay::displayEight() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 0;
  _state[_SD_ST_E] = 0;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 0;
}

void SegmentDisplay::displayNine() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 0;
  _state[_SD_ST_E] = 1;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 0;
}

void SegmentDisplay::displayNull() {
  _state[_SD_ST_A] = 1;
  _state[_SD_ST_B] = 1;
  _state[_SD_ST_C] = 1;
  _state[_SD_ST_D] = 1;
  _state[_SD_ST_E] = 1;
  _state[_SD_ST_F] = 1;
  _state[_SD_ST_G] = 1;
}

void SegmentDisplay::displayP() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 1;
  _state[_SD_ST_D] = 1;
  _state[_SD_ST_E] = 0;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 0;  
}


void SegmentDisplay::displayA() {
  _state[_SD_ST_A] = 0;
  _state[_SD_ST_B] = 0;
  _state[_SD_ST_C] = 0;
  _state[_SD_ST_D] = 1;
  _state[_SD_ST_E] = 0;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 0;
}

void SegmentDisplay::displayI() {
  _state[_SD_ST_A] = 1;
  _state[_SD_ST_B] = 1;
  _state[_SD_ST_C] = 1;
  _state[_SD_ST_D] = 1;
  _state[_SD_ST_E] = 0;
  _state[_SD_ST_F] = 0;
  _state[_SD_ST_G] = 1;
}

void SegmentDisplay::disableAll() {
  _state[_SD_ST_D1] = 0;
  _state[_SD_ST_D2] = 0;
  _state[_SD_ST_D3] = 0;
  _state[_SD_ST_D4] = 0;
  _state[_SD_ST_DOT] = 1;
  
  displayNull();
}
