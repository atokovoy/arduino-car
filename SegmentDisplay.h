#ifndef SEGMENT_DISPLAY_H
#define SEGMENT_DISPLAY_H

#include <Arduino.h>
#include "Pin.h"

/*     A
 *    ____
 *  F |  | B
 *    -G--
 *  E |  | C
 *    ----
 *     D
 *
 */

#define _SD_ST_D1 0
#define _SD_ST_D2 1
#define _SD_ST_D3 2
#define _SD_ST_D4 3
#define _SD_ST_DOT 4
#define _SD_ST_A 5
#define _SD_ST_B 6
#define _SD_ST_C 7
#define _SD_ST_D 8
#define _SD_ST_E 9
#define _SD_ST_F 10
#define _SD_ST_G 11

class SegmentDisplay
{
  public:
    SegmentDisplay(PinHolder *pinHolder);
    void clear();
    void test();
    void displayDot();
    void displayZero();
    void displayOne();
    void displayTwo();
    void displayThree();
    void displayFour();
    void displayFive();
    void displaySix();
    void displaySeven();
    void displayEight();
    void displayNine();
    void displayNull();
    void displayP();
    void displayA();
    void displayI();
    void display(const char *txt, unsigned int ms);
    
  private:
    void disableAll();
  
    PinHolder *_pinHolder;
    bool _state[12];
};

#endif
