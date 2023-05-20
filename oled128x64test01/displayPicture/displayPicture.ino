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

int currentFrame = 0;
const char* textToDisplay = "";
const int buttonPin = 2;
int buttonState = 0;
int counter = 0;
char counterText[4];

#define cat_sitting_001_width 12
#define cat_sitting_001_height 12
static unsigned char cat_sitting_001_bits[] U8G_PROGMEM = {
   0x60, 0x0c, 0xa0, 0x0b, 0x20, 0x08, 0xa0, 0x0c, 0x20, 0x08, 0x20, 0x08,
   0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x8e, 0x0a, 0x89, 0x0a, 0xff, 0x0f };

#define cat_sitting_002_width 12
#define cat_sitting_002_height 12
static unsigned char cat_sitting_002_bits[] U8G_PROGMEM = {
   0x60, 0x0c, 0xa0, 0x0b, 0x20, 0x08, 0xa0, 0x0c, 0x20, 0x08, 0x20, 0x08,
   0x10, 0x04, 0x10, 0x04, 0x1c, 0x04, 0x8a, 0x0a, 0x8d, 0x0a, 0xfb, 0x0f };

void draw(int frameId, const char* text, int posx, int posy) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(posx, posy, text);
  if ( frameId == 0 ) {
    u8g.drawXBMP(0, 0, cat_sitting_001_width, cat_sitting_001_height, cat_sitting_001_bits);
  } else if ( frameId == 1 ) {
    u8g.drawXBMP(0, 0, cat_sitting_002_width, cat_sitting_002_height, cat_sitting_002_bits);
  }
}

void setup(void) {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // flip screen, if required
  u8g.setRot180();
}

void loop(void) {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // Button pressed
    currentFrame = 0;
    counter = 0;
  }
  // picture loop
  counter += 1;
  itoa(counter, counterText, 10);
  currentFrame += 1;
  if ( currentFrame > 1 ) {
    currentFrame = 0;
  }
  u8g.firstPage();  
  do {
    draw(currentFrame, counterText, 0, 50);
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(1000);
}
