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

int gameMode = 0;
const char* textToDisplay = "";
const int buttonPin = 2;
int buttonState = 0;
int buttonCount = 0;
int frameCounter = 0;
char generalCounter[4];
char counterText[7];
long randomNumber;
int catX = 0;
int catY = 0;
int idlingStep = 1;
const byte ButtonPin = 2;
const unsigned long DebounceTime = 10;
boolean ButtonWasPressed = false;
unsigned long ButtonStateChangeTime = 0; // Debounce timer
int currentIcon = 0;

// Cat status variables
// Status metrics
// 0 = depleted, 1 = low, 2 = average, 3 = full
int catHunger = 3;
// long catHunger = random(1, 3);
int catHygiene = 3;
// long catHygiene = random(1, 3);
int catMorale = 2;
// long catMorale = random(1, 3);
int catEducation = 0;
// long catEducation = random(1, 3);
int catEntertainment = 1;
// long catEntertainment = random(1, 3);

// Status change timing (decrement status variable every x frames)
/*
int catHungerStep = 9000; // 1h
// long catHungerStep = random(8990, 9010);
int catHygieneStep = 18000; // 2h
// long catHygieneStep = random(17090, 18010);
int catMoraleStep = 4500; // 30m
// long catMoraleStep = random(4490, 4510);
int catEducationStep = 1500; // 10m
// long catEducationStep = random(1490, 1510);
int catEntertainementStep = 150; // 1m
// long catEntertainementStep = random(140, 160);
*/
int catHungerStep = 900; // 6m
// long catHungerStep = random(890, 910);
int catHygieneStep = 1800; // 12m
// long catHygieneStep = random(1790, 1810);
int catMoraleStep = 450; // 3m
// long catMoraleStep = random(440, 460);
int catEducationStep = 150; // 1m
// long catEducationStep = random(140, 160);
int catEntertainmentStep = 150; // 1m
// long catEntertainmentStep = random(140, 160);

// Tracking status checks
int lastCatHungerCheck = 0;
int lastCatHygieneCheck = 0;
int lastCatMoraleCheck = 0;
int lastCatEducationCheck = 0;
int lastCatEntertainmentCheck = 0;

#define comframev4_width 128
#define comframev4_height 64
static unsigned char comframev4_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff,
   0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xc0, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00,
   0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0x1f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xe0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0x1f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00,
   0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff,
   0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };

#define happy_cat_28x28_width 28
#define happy_cat_28x28_height 28
static unsigned char happy_cat_28x28_bits[] U8G_PROGMEM = {
   0xc0, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0x3f, 0x00, 0xf0, 0xff, 0xff, 0x00,
   0xf0, 0xff, 0xff, 0x00, 0xfc, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0x03,
   0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xfc, 0xf3, 0x0f,
   0xff, 0xfc, 0xf3, 0x0f, 0xff, 0xfc, 0xf3, 0x0f, 0xff, 0xfc, 0xf3, 0x0f,
   0xff, 0xfc, 0xf3, 0x0f, 0xff, 0xfc, 0xf3, 0x0f, 0xff, 0xff, 0xff, 0x0f,
   0xff, 0xff, 0xff, 0x0f, 0xff, 0xf3, 0xfc, 0x0f, 0xff, 0xf3, 0xfc, 0x0f,
   0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f, 0xff, 0x0f, 0xff, 0xff, 0xff, 0x0f,
   0xff, 0xff, 0xff, 0x0f, 0xfc, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0x03,
   0xf0, 0xff, 0xff, 0x00, 0xf0, 0xff, 0xff, 0x00, 0xc0, 0xff, 0x3f, 0x00,
   0xc0, 0xff, 0x3f, 0x00 };

#define ghost_28x28_width 28
#define ghost_28x28_height 28
static unsigned char ghost_28x28_bits[] U8G_PROGMEM = {
   0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xff, 0xff, 0x00,
   0x00, 0xff, 0xff, 0x00, 0xc0, 0xff, 0xff, 0x03, 0xc0, 0xff, 0xff, 0x03,
   0xc0, 0x0f, 0x0f, 0x03, 0xc0, 0x0f, 0x0f, 0x03, 0xf0, 0x0f, 0x0f, 0x0f,
   0xf0, 0x0f, 0x0f, 0x0f, 0xfc, 0xcf, 0x3f, 0x0f, 0xfc, 0xcf, 0x3f, 0x0f,
   0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xf3, 0x3f, 0xc0, 0x0f,
   0xf3, 0x3f, 0xc0, 0x0f, 0xfc, 0x3f, 0xcc, 0x0f, 0xfc, 0x3f, 0xcc, 0x0f,
   0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03, 0x3f, 0xff, 0xff, 0x00,
   0x3f, 0xff, 0xff, 0x00, 0xcf, 0xff, 0xfc, 0x00, 0xcf, 0xff, 0xfc, 0x00,
   0xc0, 0x3f, 0x3f, 0x00, 0xc0, 0x3f, 0x3f, 0x00, 0x00, 0x0f, 0x0f, 0x00,
   0x00, 0x0f, 0x0f, 0x00 };

#define play_32x20_width 32
#define play_32x20_height 20
static unsigned char play_32x20_bits[] U8G_PROGMEM = {
   0x30, 0xff, 0xff, 0x0f, 0x30, 0xff, 0xff, 0x0f, 0xcc, 0xff, 0xff, 0x3f,
   0xcc, 0xff, 0xff, 0x3f, 0xf3, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff,
   0xf3, 0xf3, 0x3f, 0xf3, 0xf3, 0xf3, 0x3f, 0xf3, 0xf3, 0xc0, 0xff, 0xff,
   0xf3, 0xc0, 0xff, 0xff, 0xf3, 0xf3, 0x30, 0xf3, 0xf3, 0xf3, 0x30, 0xf3,
   0xf3, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff,
   0xf3, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xf3, 0x3f, 0xcc, 0xff, 0xf3, 0x3f,
   0x30, 0x3f, 0xcc, 0x0f, 0x30, 0x3f, 0xcc, 0x0f };

#define study_26x28_width 26
#define study_26x28_height 28
static unsigned char study_26x28_bits[] U8G_PROGMEM = {
   0xfc, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0x03, 0x3f, 0xff, 0xf3, 0x03,
   0x3f, 0xff, 0xf3, 0x03, 0xcf, 0xff, 0xcf, 0x03, 0xcf, 0xff, 0xcf, 0x03,
   0xcf, 0x03, 0xcf, 0x03, 0xcf, 0x03, 0xcf, 0x03, 0xcf, 0xff, 0xcf, 0x03,
   0xcf, 0xff, 0xcf, 0x03, 0xcf, 0x00, 0xcc, 0x03, 0xcf, 0x00, 0xcc, 0x03,
   0xcf, 0xff, 0xcf, 0x03, 0xcf, 0xff, 0xcf, 0x03, 0x3f, 0xff, 0xf3, 0x03,
   0x3f, 0xff, 0xf3, 0x03, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0x03,
   0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xf3, 0xc0, 0x3f, 0x00,
   0xf3, 0xc0, 0x3f, 0x00, 0xf3, 0xff, 0x3f, 0x03, 0xf3, 0xff, 0x3f, 0x03,
   0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0xfc, 0xff, 0xff, 0x03,
   0xfc, 0xff, 0xff, 0x03 };

#define cuddle_24x24_width 24
#define cuddle_24x24_height 24
static unsigned char cuddle_24x24_bits[] U8G_PROGMEM = {
   0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xfc, 0xc3, 0x3f, 0xfc, 0xc3, 0x3f,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x3f, 0x3c, 0xfc, 0x3f, 0x3c, 0xfc, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0,
   0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0, 0x3c, 0x00, 0x3c, 0x3c, 0x00, 0x3c,
   0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xc0, 0xc3, 0x03, 0xc0, 0xc3, 0x03,
   0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00 };

#define bubbles_30x30_width 30
#define bubbles_30x30_height 30
static unsigned char bubbles_30x30_bits[] U8G_PROGMEM = {
   0xf0, 0x0f, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00,
   0x0c, 0x30, 0x00, 0x00, 0xf3, 0xc0, 0x00, 0x00, 0xf3, 0xc0, 0x00, 0x00,
   0xf3, 0xc0, 0x00, 0x00, 0xf3, 0xc0, 0x00, 0x00, 0x03, 0xcc, 0x00, 0x00,
   0x03, 0xcc, 0x00, 0x00, 0x03, 0xc3, 0xf0, 0x03, 0x03, 0xc3, 0xf0, 0x03,
   0x0c, 0x30, 0x0c, 0x0c, 0x0c, 0x30, 0x0c, 0x0c, 0xf0, 0x0f, 0xf3, 0x30,
   0xf0, 0x0f, 0xf3, 0x30, 0x00, 0x00, 0xf3, 0x30, 0x00, 0x00, 0xf3, 0x30,
   0x00, 0x00, 0x03, 0x33, 0x00, 0x00, 0x03, 0x33, 0xc0, 0x0f, 0x0c, 0x0c,
   0xc0, 0x0f, 0x0c, 0x0c, 0x30, 0x33, 0xf0, 0x03, 0x30, 0x33, 0xf0, 0x03,
   0xf0, 0x30, 0x00, 0x00, 0xf0, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00,
   0x30, 0x30, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00 };

#define pizza_26x28_width 26
#define pizza_26x28_height 28
static unsigned char pizza_26x28_bits[] U8G_PROGMEM = {
   0xf0, 0xff, 0x3f, 0x00, 0xf0, 0xff, 0x3f, 0x00, 0xfc, 0xff, 0xff, 0x00,
   0xfc, 0xff, 0xff, 0x00, 0x3f, 0x00, 0xf0, 0x03, 0x3f, 0x00, 0xf0, 0x03,
   0xcf, 0xf3, 0xcc, 0x03, 0xcf, 0xf3, 0xcc, 0x03, 0xf0, 0x3f, 0x30, 0x00,
   0xf0, 0x3f, 0x30, 0x00, 0x3c, 0xff, 0xfc, 0x00, 0x3c, 0xff, 0xfc, 0x00,
   0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x30, 0x3f, 0x3f, 0x00,
   0x30, 0x3f, 0x3f, 0x00, 0xc0, 0x0f, 0x0c, 0x00, 0xc0, 0x0f, 0x0c, 0x00,
   0xc0, 0x3f, 0x0f, 0x00, 0xc0, 0x3f, 0x0f, 0x00, 0x00, 0xff, 0x03, 0x00,
   0x00, 0xff, 0x03, 0x00, 0x00, 0xf3, 0x03, 0x00, 0x00, 0xf3, 0x03, 0x00,
   0x00, 0xcc, 0x00, 0x00, 0x00, 0xcc, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
   0x00, 0x0c, 0x00, 0x00 };

#define cat_sitting_upscaled4x_001_width 48
#define cat_sitting_upscaled4x_001_height 48
static unsigned char cat_sitting_upscaled4x_001_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0xf0, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0xf0, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

#define cat_sitting_upscaled4x_002_width 48
#define cat_sitting_upscaled4x_002_height 48
static unsigned char cat_sitting_upscaled4x_002_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0xff, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0xff, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x0f,
   0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff };

#define cat_sitting_upscaled4x_003_width 48
#define cat_sitting_upscaled4x_003_height 48
static unsigned char cat_sitting_upscaled4x_003_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0xf0, 0xff, 0x0f, 0x00, 0x00, 0x0f, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0x0f,
   0xf0, 0xff, 0x0f, 0x00, 0x00, 0x0f, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0x0f,
   0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0xff, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0xff, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff };

#define cat_sitting_upscaled4x_004_width 48
#define cat_sitting_upscaled4x_004_height 48
static unsigned char cat_sitting_upscaled4x_004_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0xff,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff };

#define cat_sitting_upscaled4x_005_width 48
#define cat_sitting_upscaled4x_005_height 48
static unsigned char cat_sitting_upscaled4x_005_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
   0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
   0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0,
   0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0xf0, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0xf0, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

#define cat_sitting_upscaled4x_006_width 48
#define cat_sitting_upscaled4x_006_height 48
static unsigned char cat_sitting_upscaled4x_006_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
   0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
   0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0,
   0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0xff, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0xff, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x0f,
   0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff };

#define cat_sitting_upscaled4x_007_width 48
#define cat_sitting_upscaled4x_007_height 48
static unsigned char cat_sitting_upscaled4x_007_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
   0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
   0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0,
   0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0xf0, 0xff, 0x0f, 0x00, 0x00, 0x0f, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0x0f,
   0xf0, 0xff, 0x0f, 0x00, 0x00, 0x0f, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0x0f,
   0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0xff, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0xff, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff };

#define cat_sitting_upscaled4x_008_width 48
#define cat_sitting_upscaled4x_008_height 48
static unsigned char cat_sitting_upscaled4x_008_bits[] U8G_PROGMEM = {
   0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
   0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
   0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0,
   0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x0f, 0x00, 0x00, 0x0f,
   0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0, 0x0f, 0xff, 0x00, 0xf0, 0xf0, 0xf0,
   0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff };

void checkButton()
{
  unsigned long currentTime = millis();
  boolean buttonIsPressed = digitalRead(ButtonPin) == HIGH;  // Active HIGH


  // Check for button state change and do debounce
  if (buttonIsPressed != ButtonWasPressed &&
      currentTime  -  ButtonStateChangeTime > DebounceTime)
  {
    // Button state has changed
    ButtonWasPressed = buttonIsPressed;
    ButtonStateChangeTime = currentTime;


    if (ButtonWasPressed)
    {
      // Button was just pressed
    }
    else
    {
      // Button was just released
      if (gameMode == 1) {
        // Do something only if cat needs something
        switch (currentIcon) {
          case 0:
            // Happy
            gameMode = 0;
            break;
          case 1:
            // Ghost
            gameMode = 0;
            break;
          case 2:
            // Play
            gameMode = 0;
            catEntertainment = 3;
            break;
          case 3:
            // Study
            gameMode = 0;
            catEducation += 1;
            break;
          case 4:
            // Cuddle
            gameMode = 0;
            catMorale = 3;
            break;
          case 5:
            // Bubbles
            gameMode = 0;
            catHygiene = 3;
            break;
          case 6:
            // Pizza
            gameMode = 0;
            catHunger = 3;
            break;
        }
      }
    }
  }


  if (ButtonWasPressed)
  {
    // Button is being held down
  }
}

void setup(void) {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // flip screen, if required
  u8g.setRot180();
  u8g.setFont(u8g_font_unifont);
}

void loop(void) {
  randomNumber = random(1, 10);
  checkButton();
  frameCounter += 1;
  itoa(frameCounter, counterText, 10);

  idlingStep += 1;
  if (idlingStep>4) {
    idlingStep = 1;
  }
  itoa(idlingStep, generalCounter, 10);

  // Refresh cat statistics
  // Hunger
  if (frameCounter == lastCatHungerCheck + catHungerStep) {
    catHunger -= 1;
    if (catHunger < 0) {
      catHunger = 0;
    }
    lastCatHungerCheck = frameCounter;
  }
  // Hygiene
  if (frameCounter == lastCatHygieneCheck + catHygieneStep) {
    catHygiene -= 1;
    if (catHygiene < 0) {
      catHygiene = 0;
    }
    lastCatHygieneCheck = frameCounter;
  }
  // Morale
  if (frameCounter == lastCatMoraleCheck + catMoraleStep) {
    catMorale -= 1;
    if (catMorale < 0) {
      catMorale = 0;
    }
    lastCatMoraleCheck = frameCounter;
  }
  // Education
  if (frameCounter == lastCatEducationCheck + catEducationStep) {
    if (catEducation < 3) {
      // Time to study
      currentIcon = 3;
      gameMode = 1;
    }
    lastCatEducationCheck = frameCounter;
  }
  // Entertainment
  if (frameCounter == lastCatEntertainmentCheck + catEntertainmentStep) {
    catEntertainment -= 1;
    if (catEntertainment < 0) {
      catEntertainment = 0;
    }
    lastCatEntertainmentCheck = frameCounter;
  }

  // Act on cat stats
  if (catHunger == 0) {
    // Time to feed the cat
    currentIcon = 6;
    gameMode = 1;
  } else if (catHygiene==0) {
    // Time to clean
    currentIcon = 5;
    gameMode = 1;
  } else if (catMorale==0) {
    // Time to cuddle
    currentIcon = 4;
    gameMode = 1;
  } else if (catEntertainment==0) {
    // Time to play
    currentIcon = 2;
    gameMode = 1;
  }
  
  u8g.firstPage();
  do {
    switch (gameMode) {
      case 0:
        // Idling
        checkButton();
        // Icon frame
        u8g.drawXBMP(0, 0, comframev4_width, comframev4_height, comframev4_bits);
        // Icon (always happy)
        u8g.drawXBMP(87, 12, happy_cat_28x28_width, happy_cat_28x28_height, happy_cat_28x28_bits);
        switch (idlingStep) {
          case 1:
            checkButton();
            catX = 8;
            catY = 8;
            u8g.drawXBMP(catX, catY, cat_sitting_upscaled4x_001_width, cat_sitting_upscaled4x_001_height, cat_sitting_upscaled4x_001_bits);
            break;
          case 2:
            checkButton();
            catX = 8;
            catY = 8;
            u8g.drawXBMP(catX, catY, cat_sitting_upscaled4x_002_width, cat_sitting_upscaled4x_002_height, cat_sitting_upscaled4x_002_bits);
            break;
          case 3:
            checkButton();
            catX = 8;
            catY = 8;
            u8g.drawXBMP(catX, catY, cat_sitting_upscaled4x_003_width, cat_sitting_upscaled4x_003_height, cat_sitting_upscaled4x_003_bits);
            break;
          case 4:
            checkButton();
            catX = 8;
            catY = 8;
            u8g.drawXBMP(catX, catY, cat_sitting_upscaled4x_004_width, cat_sitting_upscaled4x_004_height, cat_sitting_upscaled4x_004_bits);
            break;
        }
        break;
      case 1:
        // Idle - looking left
        checkButton();
        // Icon frame
        u8g.drawXBMP(0, 0, comframev4_width, comframev4_height, comframev4_bits);
        // Icon (anything else than happy)
        switch (currentIcon) {
          case 0:
            // Happy
            u8g.drawXBMP(87, 12, happy_cat_28x28_width, happy_cat_28x28_height, happy_cat_28x28_bits);
            break;
          case 1:
            // Ghost
            u8g.drawXBMP(87, 12, ghost_28x28_width, ghost_28x28_height, ghost_28x28_bits);
            break;
          case 2:
            // Play
            u8g.drawXBMP(85, 16, play_32x20_width, play_32x20_height, play_32x20_bits);
            break;
          case 3:
            // Study
            u8g.drawXBMP(88, 12, study_26x28_width, study_26x28_height, study_26x28_bits);
            break;
          case 4:
            // Cuddle
            u8g.drawXBMP(89, 14, cuddle_24x24_width, cuddle_24x24_height, cuddle_24x24_bits);
            break;
          case 5:
            // Bubbles
            u8g.drawXBMP(86, 11, bubbles_30x30_width, bubbles_30x30_height, bubbles_30x30_bits);
            break;
          case 6:
            // Pizza
            u8g.drawXBMP(88, 12, pizza_26x28_width, pizza_26x28_height, pizza_26x28_bits);
            break;
        }
        switch (idlingStep) {
          case 1:
            checkButton();
            catX = 8;
            catY = 8;
            u8g.drawXBMP(catX, catY, cat_sitting_upscaled4x_005_width, cat_sitting_upscaled4x_005_height, cat_sitting_upscaled4x_005_bits);
            break;
          case 2:
            checkButton();
            catX = 8;
            catY = 8;
            u8g.drawXBMP(catX, catY, cat_sitting_upscaled4x_006_width, cat_sitting_upscaled4x_006_height, cat_sitting_upscaled4x_006_bits);
            break;
          case 3:
            checkButton();
            catX = 8;
            catY = 8;
            u8g.drawXBMP(catX, catY, cat_sitting_upscaled4x_007_width, cat_sitting_upscaled4x_007_height, cat_sitting_upscaled4x_007_bits);
            break;
          case 4:
            checkButton();
            catX = 8;
            catY = 8;
            u8g.drawXBMP(catX, catY, cat_sitting_upscaled4x_008_width, cat_sitting_upscaled4x_008_height, cat_sitting_upscaled4x_008_bits);
            break;
        }
        break;
    }
    // Frame counter
    u8g.drawStr(64, 64, counterText);
    // Idling counter
    // u8g.drawStr(30, 62, generalCounter);
  } while( u8g.nextPage() );

  // delay(50);
}
