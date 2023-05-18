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
int buttonState = 0;
int counter = 0;
const char* textToDisplay = "";
char counterText[4];

void draw(const char* text, int posx, int posy) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr(posx, posy, text);
}

void setup(void) {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // flip screen, if required
  u8g.setRot180();
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255); // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3); // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1); // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}

void loop(void) {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // Button released
    textToDisplay = "Meuh !";
  } else {
    // Button pressed
    textToDisplay = "Coin !";
    counter += 1;
  }
  itoa(counter, counterText, 10);
  // picture loop
  u8g.firstPage();
  do {
    draw(textToDisplay, 10, 22);
    draw(counterText, 10, 42);
  } while( u8g.nextPage() );
  // rebuild the picture after some delay
  delay(50);
}
