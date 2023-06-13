#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9); // SCK = 13, MOSI = 11, CS = 10, A0 = 9
/*
= OLED screen =

GND  = GND (5V)
VCC  = 5V
CLK  = 13
MOSI = 11
RES  = RES
DC   = 9
CS   = 10

= Button =

GND = GND (3V)
VCC = 3V
SIG = 2
*/

const int buttonPin = 2;
int catPosX = 0;
int catPosY = 0;

#define cat_sitting_001_width 12
#define cat_sitting_001_height 12
static unsigned char cat_sitting_001_bits[] U8G_PROGMEM = {
   0x60, 0x0c, 0xa0, 0x0b, 0x20, 0x08, 0xa0, 0x0c, 0x20, 0x08, 0x20, 0x08,
   0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x8e, 0x0a, 0x89, 0x0a, 0xff, 0x0f };

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // flip screen, if required
  u8g.setRot180();
}

void loop() {
  u8g.firstPage();
  do {
    u8g.setScale2x2();
    catPosX += 1;
    if (catPosX > 64) {
      catPosX = 0;
      catPosY += 1;
      if (catPosY > 32 ) {
        catPosY = 0;
      }
    }
    u8g.drawXBMP(catPosX, catPosY, cat_sitting_001_width, cat_sitting_001_height, cat_sitting_001_bits);
  } while( u8g.nextPage() );
}
