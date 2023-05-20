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

const uint8_t rook_bitmap[] U8G_PROGMEM = {
  0x00,         // 00000000 
  0x55,         // 01010101
  0x7f,          // 01111111
  0x3e,         // 00111110
  0x3e,         // 00111110 
  0x3e,         // 00111110
  0x3e,         // 00111110 
  0x7f           // 01111111
};

#define cat_sitting_001_width 12
#define cat_sitting_001_height 12
static unsigned char cat_sitting_001_bits[] U8G_PROGMEM = {
   0x60, 0x0c, 0xa0, 0x0b, 0x20, 0x08, 0xa0, 0x0c, 0x20, 0x08, 0x20, 0x08,
   0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x8e, 0x0a, 0x89, 0x0a, 0xff, 0x0f };

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  // u8g.drawBitmapP( 0, 0, 1, 8, rook_bitmap);
  // u8g.drawBitmapP( 0, 0, 12, 12, catsitting001);
  u8g.drawXBMP(0, 0, cat_sitting_001_width, cat_sitting_001_height, cat_sitting_001_bits);
}

void setup(void) {
  // flip screen, if required
  u8g.setRot180();
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(1000);
}
