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
unsigned long frameCounter = 0;
char frameCounterString[7];
char animationStepString[1];
long randomNumber;
int animationStep = 1;
int animationStepMax = 4;
const byte ButtonPin = 2;
const unsigned long DebounceTime = 10;
boolean ButtonWasPressed = false;
unsigned long ButtonStateChangeTime = 0; // Debounce timer
int currentIcon = 0;
int cuddleCounter = 0;
int cleanCounter = 0;
int cleanSequence = 0;
int gameCounter = 0;
int gameSequence = 0;
long gamePick = 0;
int strawberryFoodStock = 0;
int appleFoodStock = 10000;
int iceCreamFoodStock = 1;
int grapeFoodStock = 0;
int milkFoodStock = 0;
int orangeFoodStock = 0;
int lessonSequence = 0;
int snailCounter = 0;
int kokoXPos = 0;
long randomQuote = 0;
int feedSequence = 0;
int feedCounter = 0;
int selectedFood = 0;
int superHappyCounter = 0;
long randomVisit = 0;
int randomVisitSequence = 0;
int randomVisitCounter = 0;
long randomGameIconXPos = 0;
long randomFoodType = 0;
int gameIconXPos = 0;

// Cat status variables
// Status metrics
// 0 = depleted, 1 = low, 2 = average, 3 = full
long catHunger = random(1, 4);
long catHygiene = random(1, 4);
long catMorale = random(1, 4);
long catEducation = random(1, 3);
long catEntertainment = random(1, 4);

// Status change timing (decrement status variable every x frames)
// Production timings
// unsigned long catHungerStep = random(7500, 8500);
unsigned long catHungerStep = 2;
// unsigned long catHygieneStep = random(15000, 20000);
unsigned long catHygieneStep = 4;
// unsigned long catMoraleStep = random(4000, 5000);
unsigned long catMoraleStep = 6;
// unsigned long catEducationStep = random(800, 1600);
unsigned long catEducationStep = 8;
// unsigned long catEntertainmentStep = random(250, 500);
unsigned long catEntertainmentStep = 10;

// Tracking status checks
unsigned long lastCatHungerCheck = 0;
unsigned long lastCatHygieneCheck = 0;
unsigned long lastCatMoraleCheck = 0;
unsigned long lastCatEducationCheck = 0;
unsigned long lastCatEntertainmentCheck = 0;

#define door_14x15_width 14
#define door_14x15_height 15
static unsigned char door_14x15_bits[] U8G_PROGMEM = {
   0xff, 0x3f, 0x01, 0x20, 0x01, 0x20, 0xfd, 0x2f, 0x0d, 0x24, 0xed, 0x25,
   0xed, 0x25, 0xfd, 0x2f, 0xf9, 0x2f, 0xf9, 0x2f, 0x0d, 0x2c, 0xed, 0x25,
   0xed, 0x25, 0xfd, 0x27, 0xfd, 0x2f };

#define coco_cake_14x16_width 14
#define coco_cake_14x16_height 16
static unsigned char coco_cake_14x16_bits[] U8G_PROGMEM = {
   0xc0, 0x01, 0xe0, 0x03, 0xef, 0x2b, 0xce, 0x29, 0x0c, 0x28, 0x13, 0x2c,
   0xcc, 0x37, 0x30, 0x2b, 0xc3, 0x3c, 0x0c, 0x3d, 0x30, 0x34, 0xc3, 0x1c,
   0x0c, 0x3d, 0x30, 0x18, 0xc0, 0x0c, 0x00, 0x05 };

#define matcha_15x16_width 15
#define matcha_15x16_height 16
static unsigned char matcha_15x16_bits[] U8G_PROGMEM = {
   0x00, 0x01, 0x00, 0x02, 0x60, 0x02, 0x90, 0x01, 0x10, 0x00, 0x20, 0x00,
   0x00, 0x00, 0xff, 0x0f, 0xff, 0x3f, 0xff, 0x63, 0xff, 0x67, 0xff, 0x67,
   0xff, 0x67, 0xfe, 0x3f, 0x00, 0x00, 0xfc, 0x03 };

#define cindy_14x13_width 14
#define cindy_14x13_height 13
static unsigned char cindy_14x13_bits[] U8G_PROGMEM = {
   0xfb, 0x37, 0xfd, 0x2f, 0x76, 0x1f, 0x76, 0x1f, 0xfe, 0x1f, 0xcf, 0x1f,
   0xff, 0x1f, 0xfe, 0x0f, 0xf0, 0x01, 0xfc, 0x0f, 0xfe, 0x1f, 0xf6, 0x1b,
   0x18, 0x06 };

#define super_happy_14x14_width 14
#define super_happy_14x14_height 14
static unsigned char super_happy_14x14_bits[] U8G_PROGMEM = {
   0xf8, 0x07, 0xfc, 0x0f, 0xfe, 0x1f, 0xef, 0x3d, 0xef, 0x3d, 0xef, 0x3d,
   0xff, 0x3f, 0x07, 0x38, 0x27, 0x39, 0xe7, 0x39, 0xef, 0x3d, 0x1e, 0x1e,
   0xfc, 0x0f, 0xf8, 0x07 };

#define diamond_14x12_width 14
#define diamond_14x12_height 12
static unsigned char diamond_14x12_bits[] U8G_PROGMEM = {
   0xa8, 0x06, 0x94, 0x0d, 0x92, 0x1d, 0x7f, 0x00, 0x89, 0x3b, 0x89, 0x3b,
   0x8a, 0x1b, 0x8c, 0x0d, 0x98, 0x07, 0xb0, 0x03, 0xe0, 0x01, 0xc0, 0x00 };

#define koko_le_snail_13x11_width 13
#define koko_le_snail_13x11_height 11
static unsigned char koko_le_snail_13x11_bits[] U8G_PROGMEM = {
   0xc6, 0x00, 0xef, 0x01, 0xab, 0x01, 0xd6, 0x00, 0x38, 0x0e, 0x7c, 0x1b,
   0x64, 0x15, 0xfc, 0x15, 0x7c, 0x17, 0xfc, 0x18, 0xf8, 0x0f };

#define orange_14x11_width 14
#define orange_14x11_height 11
static unsigned char orange_14x11_bits[] U8G_PROGMEM = {
   0x06, 0x18, 0x1b, 0x2c, 0xfb, 0x2f, 0xdb, 0x2d, 0x6b, 0x2b, 0xfb, 0x2f,
   0xbb, 0x2e, 0xf7, 0x37, 0xee, 0x1b, 0x1c, 0x0c, 0xf8, 0x07 };

#define milk_16x16_width 16
#define milk_16x16_height 16
static unsigned char milk_16x16_bits[] U8G_PROGMEM = {
   0xe0, 0x05, 0xf0, 0x0b, 0xf0, 0x0b, 0x00, 0x00, 0xf8, 0x1b, 0xfc, 0x3d,
   0xfe, 0x7e, 0x00, 0xff, 0x7f, 0xbb, 0x7f, 0x93, 0x7f, 0xab, 0x7f, 0xbb,
   0x7f, 0xbb, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff };

#define grape_14x14_width 14
#define grape_14x14_height 14
static unsigned char grape_14x14_bits[] U8G_PROGMEM = {
   0x20, 0x00, 0x40, 0x00, 0x00, 0x00, 0xe6, 0x18, 0xb5, 0x35, 0x31, 0x25,
   0xe6, 0x18, 0x18, 0x06, 0x74, 0x0d, 0x64, 0x09, 0x38, 0x06, 0x80, 0x01,
   0x20, 0x01, 0xc0, 0x00 };

#define strawberry_12x12_width 12
#define strawberry_12x12_height 12
static unsigned char strawberry_12x12_bits[] U8G_PROGMEM = {
   0x6c, 0x03, 0x9c, 0x03, 0x60, 0x00, 0xf6, 0x06, 0x0f, 0x0f, 0xfd, 0x0f,
   0xff, 0x0b, 0x7f, 0x0f, 0xf6, 0x07, 0xfc, 0x03, 0xb8, 0x01, 0xf0, 0x00 };

#define apple_13x14_width 13
#define apple_13x14_height 14
static unsigned char apple_13x14_bits[] U8G_PROGMEM = {
   0x1e, 0x00, 0x3e, 0x00, 0x5c, 0x00, 0x40, 0x07, 0x4e, 0x0e, 0xf3, 0x1b,
   0xf1, 0x1c, 0xf9, 0x1f, 0xf9, 0x1f, 0xf9, 0x1f, 0xf1, 0x19, 0x02, 0x08,
   0x04, 0x04, 0xf8, 0x03 };

#define bar_16x15_width 16
#define bar_16x15_height 15
static unsigned char bar_16x15_bits[] U8G_PROGMEM = {
   0xfe, 0x7f, 0x01, 0x80, 0xff, 0xff, 0x00, 0x00, 0x8e, 0x39, 0x52, 0x4a,
   0x52, 0x4a, 0xce, 0x3b, 0x52, 0x4a, 0x52, 0x4a, 0x4e, 0x4a, 0x00, 0x00,
   0xff, 0xff, 0x01, 0x80, 0xfe, 0x7f };

#define casino_frame_30x30_width 30
#define casino_frame_30x30_height 30
static unsigned char casino_frame_30x30_bits[] U8G_PROGMEM = {
   0x9e, 0xff, 0x7f, 0x1e, 0x99, 0xff, 0x7f, 0x26, 0x99, 0xff, 0x7f, 0x26,
   0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38,
   0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38,
   0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38,
   0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38,
   0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38,
   0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x07, 0x00, 0x00, 0x38,
   0x99, 0xff, 0x7f, 0x26, 0x99, 0xff, 0x7f, 0x26, 0x9e, 0xff, 0x7f, 0x1e };

#define speech_bubble_22x22_width 22
#define speech_bubble_22x22_height 22
static unsigned char speech_bubble_22x22_bits[] U8G_PROGMEM = {
   0xf8, 0xff, 0x1f, 0x0c, 0x00, 0x30, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20,
   0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20,
   0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20,
   0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20,
   0x06, 0x00, 0x20, 0x07, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20,
   0x0c, 0x00, 0x30, 0xf8, 0xff, 0x1f };

#define happy_cat_14x14_width 14
#define happy_cat_14x14_height 14
static unsigned char happy_cat_14x14_bits[] U8G_PROGMEM = {
   0xf8, 0x07, 0xfc, 0x0f, 0xfe, 0x1f, 0xff, 0x3f, 0xef, 0x3d, 0xef, 0x3d,
   0xef, 0x3d, 0xff, 0x3f, 0xdf, 0x3e, 0x3f, 0x3f, 0xff, 0x3f, 0xfe, 0x1f,
   0xfc, 0x0f, 0xf8, 0x07 };

#define ghost_14x14_width 14
#define ghost_14x14_height 14
static unsigned char ghost_14x14_bits[] U8G_PROGMEM = {
   0xf8, 0x01, 0xfc, 0x03, 0xfe, 0x07, 0x32, 0x07, 0x33, 0x0f, 0x7b, 0x1f,
   0xcf, 0x3f, 0x87, 0x2f, 0x97, 0x1f, 0xfe, 0x3f, 0xfc, 0x3b, 0xdc, 0x37,
   0xb8, 0x07, 0x30, 0x03 };

#define play_16x10_width 16
#define play_16x10_height 10
static unsigned char play_16x10_bits[] U8G_PROGMEM = {
   0xf4, 0x3f, 0xfa, 0x7f, 0xfd, 0xff, 0xdd, 0xd7, 0x8d, 0xff, 0xdd, 0xd4,
   0xfd, 0xff, 0xfd, 0xff, 0xfa, 0x7d, 0x74, 0x3a };

#define study_13x14_width 13
#define study_13x14_height 14
static unsigned char study_13x14_bits[] U8G_PROGMEM = {
   0xfe, 0x1f, 0xf7, 0x1d, 0xfb, 0x1b, 0x1b, 0x1b, 0xfb, 0x1b, 0x0b, 0x1a,
   0xfb, 0x1b, 0xf7, 0x1d, 0xff, 0x1f, 0x03, 0x00, 0x8d, 0x07, 0xfd, 0x17,
   0x01, 0x10, 0xfe, 0x1f };

#define cuddle_12x12_width 12
#define cuddle_12x12_height 12
static unsigned char cuddle_12x12_bits[] U8G_PROGMEM = {
   0x0c, 0x03, 0x9e, 0x07, 0xff, 0x0f, 0xff, 0x0f, 0x67, 0x0e, 0x03, 0x0c,
   0x03, 0x0c, 0x06, 0x06, 0x0c, 0x03, 0x98, 0x01, 0xf0, 0x00, 0x60, 0x00 };

#define bubbles_15x15_width 15
#define bubbles_15x15_height 15
static unsigned char bubbles_15x15_bits[] U8G_PROGMEM = {
   0x3c, 0x00, 0x42, 0x00, 0x8d, 0x00, 0x8d, 0x00, 0xa1, 0x00, 0x91, 0x1c,
   0x42, 0x22, 0x3c, 0x4d, 0x00, 0x4d, 0x00, 0x51, 0x38, 0x22, 0x54, 0x1c,
   0x4c, 0x00, 0x44, 0x00, 0x38, 0x00 };

#define pizza_13x14_width 13
#define pizza_13x14_height 14
static unsigned char pizza_13x14_bits[] U8G_PROGMEM = {
   0xfc, 0x07, 0xfe, 0x0f, 0x07, 0x1c, 0xdb, 0x1a, 0x7c, 0x04, 0xf6, 0x0e,
   0xe0, 0x07, 0x74, 0x07, 0x38, 0x02, 0x78, 0x03, 0xf0, 0x01, 0xd0, 0x01,
   0xa0, 0x00, 0x20, 0x00 };

#define cat_sitting_001_24x24_width 24
#define cat_sitting_001_24x24_height 24
static unsigned char cat_sitting_001_24x24_bits[] U8G_PROGMEM = {
   0x00, 0x3c, 0xf0, 0x00, 0x3c, 0xf0, 0x00, 0xcc, 0xcf, 0x00, 0xcc, 0xcf,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0xcc, 0xf0, 0x00, 0xcc, 0xf0,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0,
   0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30,
   0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0xfc, 0xc0, 0xcc, 0xfc, 0xc0, 0xcc,
   0xc3, 0xc0, 0xcc, 0xc3, 0xc0, 0xcc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

#define cat_sitting_002_24x24_width 24
#define cat_sitting_002_24x24_height 24
static unsigned char cat_sitting_002_24x24_bits[] U8G_PROGMEM = {
   0x00, 0x3c, 0xf0, 0x00, 0x3c, 0xf0, 0x00, 0xcc, 0xcf, 0x00, 0xcc, 0xcf,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0xcc, 0xf0, 0x00, 0xcc, 0xf0,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0,
   0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30,
   0xf0, 0x03, 0x30, 0xf0, 0x03, 0x30, 0xcc, 0xc0, 0xcc, 0xcc, 0xc0, 0xcc,
   0xf3, 0xc0, 0xcc, 0xf3, 0xc0, 0xcc, 0xcf, 0xff, 0xff, 0xcf, 0xff, 0xff };

#define cat_sitting_003_24x24_width 24
#define cat_sitting_003_24x24_height 24
static unsigned char cat_sitting_003_24x24_bits[] U8G_PROGMEM = {
   0x00, 0x3c, 0xf0, 0x00, 0x3c, 0xf0, 0x00, 0xcc, 0xcf, 0x00, 0xcc, 0xcf,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0xcc, 0xf0, 0x00, 0xcc, 0xf0,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0,
   0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30,
   0xfc, 0x03, 0x30, 0xfc, 0x03, 0x30, 0xc3, 0xc0, 0xcc, 0xc3, 0xc0, 0xcc,
   0xff, 0xc0, 0xcc, 0xff, 0xc0, 0xcc, 0xc0, 0xff, 0xff, 0xc0, 0xff, 0xff };

#define cat_sitting_004_24x24_width 24
#define cat_sitting_004_24x24_height 24
static unsigned char cat_sitting_004_24x24_bits[] U8G_PROGMEM = {
   0x00, 0x3c, 0xf0, 0x00, 0x3c, 0xf0, 0x00, 0xcc, 0xcf, 0x00, 0xcc, 0xcf,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0xcc, 0xf0, 0x00, 0xcc, 0xf0,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0,
   0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30,
   0x0f, 0x03, 0x30, 0x0f, 0x03, 0x30, 0xf3, 0xc0, 0xcc, 0xf3, 0xc0, 0xcc,
   0xcc, 0xc0, 0xcc, 0xcc, 0xc0, 0xcc, 0xf0, 0xff, 0xff, 0xf0, 0xff, 0xff };

#define cat_sitting_006_24x24_width 24
#define cat_sitting_006_24x24_height 24
static unsigned char cat_sitting_006_24x24_bits[] U8G_PROGMEM = {
   0x00, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0x00, 0x30, 0xcf, 0x00, 0x30, 0xcf,
   0x00, 0x0c, 0x30, 0x00, 0x0c, 0x30, 0x00, 0x0c, 0xc3, 0x00, 0x0c, 0xc3,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0,
   0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30,
   0xf0, 0x03, 0x30, 0xf0, 0x03, 0x30, 0xcc, 0xc0, 0xcc, 0xcc, 0xc0, 0xcc,
   0xf3, 0xc0, 0xcc, 0xf3, 0xc0, 0xcc, 0xcf, 0xff, 0xff, 0xcf, 0xff, 0xff };

#define cat_sitting_007_24x24_width 24
#define cat_sitting_007_24x24_height 24
static unsigned char cat_sitting_007_24x24_bits[] U8G_PROGMEM = {
   0x00, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0x00, 0x30, 0xcf, 0x00, 0x30, 0xcf,
   0x00, 0x0c, 0x30, 0x00, 0x0c, 0x30, 0x00, 0x0c, 0xc3, 0x00, 0x0c, 0xc3,
   0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0, 0x00, 0x0c, 0xc0,
   0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30, 0x00, 0x03, 0x30,
   0xfc, 0x03, 0x30, 0xfc, 0x03, 0x30, 0xc3, 0xc0, 0xcc, 0xc3, 0xc0, 0xcc,
   0xff, 0xc0, 0xcc, 0xff, 0xc0, 0xcc, 0xc0, 0xff, 0xff, 0xc0, 0xff, 0xff };

#define cuddle_heart_11x10_width 11
#define cuddle_heart_11x10_height 10
static unsigned char cuddle_heart_11x10_bits[] U8G_PROGMEM = {
   0x8c, 0x01, 0xde, 0x03, 0xff, 0x07, 0xff, 0x07, 0xff, 0x07, 0xfe, 0x03,
   0xfc, 0x01, 0xf8, 0x00, 0x70, 0x00, 0x20, 0x00 };

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
          case 2:
            // Play
            gameCounter = 0;
            gameSequence = 0;
            gameMode = 6;
            break;
          case 3:
            // Study
            randomQuote = random(1, 7);
            kokoXPos = 128;
            snailCounter = 0;
            lessonSequence = 0;
            gameMode = 4;
            break;
          case 4:
            // Cuddle
            cuddleCounter = 0;
            gameMode = 3;
            break;
          case 5:
            // Clean
            cleanSequence = 0;
            cleanCounter = 0;
            gameMode = 5;
            break;
          case 6:
            // Feed
            selectedFood = 0;
            feedSequence = 0;
            feedCounter = 0;
            gameMode = 2;
            break;
        }
      } else if (gameMode == 5) {
        // Clean The Cat game
        cleanCounter += 14;
      } else if (gameMode == 6) {
        // Game
        if (gameSequence == 0) {
          gamePick = random (0, 7);
          gameSequence = 1;
          gameCounter = 0;
          randomGameIconXPos = random(0, 3);
          randomFoodType = random(0, 7);
        }
      } else if (gameMode == 7) {
        randomVisitSequence = 1;
        randomVisitCounter = 0;
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
  // Change the scale
  u8g.setScale2x2();
  // flip screen, if required
  u8g.setRot180();
}

void loop(void) {
  randomNumber = random(1, 11);
  checkButton();
  frameCounter += 1;
  ltoa(frameCounter, frameCounterString, 10);
  animationStep += 1;
  if (animationStep>animationStepMax) {
    animationStep=1;
  }
  ltoa(animationStep, animationStepString, 10);

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
    if (catEducation < 3 && gameMode == 0) {
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
  if (catHunger == 0 && gameMode == 0) {
    // Time to feed the cat
    currentIcon = 6;
    randomVisit = random(0, 3136);
    if (randomVisit<2000 && randomVisit % 2 == 0) {
      randomVisitSequence = 0;
      randomVisitCounter = 0;
      gameMode = 7;
    } else {
      gameMode = 1;
    }
  } else if (catHygiene==0 && gameMode == 0) {
    // Time to clean
    currentIcon = 5;
    gameMode = 1;
  } else if (catMorale==0 && gameMode == 0) {
    // Time to cuddle
    currentIcon = 4;
    gameMode = 1;
  } else if (catEntertainment==0 && gameMode == 0) {
    // Time to play
    currentIcon = 2;
    gameMode = 1;
  }
  
  u8g.firstPage();
  do {
    switch (gameMode) {
      case 0:
        // Idling
        animationStepMax = 4;
        checkButton();
        // Icon frame
        u8g.drawXBMP(38, 2, speech_bubble_22x22_width, speech_bubble_22x22_height, speech_bubble_22x22_bits);
        // Icon (always happy)
        if (superHappyCounter<1) {
          u8g.drawXBMP(43, 6, happy_cat_14x14_width, happy_cat_14x14_height, happy_cat_14x14_bits);
        } else {
          u8g.drawXBMP(43, 6, super_happy_14x14_width, super_happy_14x14_height, super_happy_14x14_bits);
          superHappyCounter -= 1;
        }
        switch (animationStep) {
          case 1:
            checkButton();
            u8g.drawXBMP(4, 4, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            break;
          case 2:
            checkButton();
            u8g.drawXBMP(4, 4, cat_sitting_002_24x24_width, cat_sitting_002_24x24_height, cat_sitting_002_24x24_bits);
            break;
          case 3:
            checkButton();
            u8g.drawXBMP(4, 4, cat_sitting_003_24x24_width, cat_sitting_003_24x24_height, cat_sitting_003_24x24_bits);
            break;
          case 4:
            checkButton();
            u8g.drawXBMP(4, 4, cat_sitting_004_24x24_width, cat_sitting_004_24x24_height, cat_sitting_004_24x24_bits);
            break;
        }
        break;
      case 1:
        // Idle - looking left
        animationStepMax = 4;
        checkButton();
        // Icon frame
        u8g.drawXBMP(38, 2, speech_bubble_22x22_width, speech_bubble_22x22_height, speech_bubble_22x22_bits);
        // Icon (anything else than happy)
        switch (currentIcon) {
          case 0:
            // Happy
            u8g.drawXBMP(43, 6, happy_cat_14x14_width, happy_cat_14x14_height, happy_cat_14x14_bits);
            break;
          case 1:
            // Ghost
            u8g.drawXBMP(43, 6, ghost_14x14_width, ghost_14x14_height, ghost_14x14_bits);
            break;
          case 2:
            // Play
            u8g.drawXBMP(42, 8, play_16x10_width, play_16x10_height, play_16x10_bits);
            break;
          case 3:
            // Study
            u8g.drawXBMP(43, 6, study_13x14_width, study_13x14_height, study_13x14_bits);
            break;
          case 4:
            // Cuddle
            u8g.drawXBMP(44, 7, cuddle_12x12_width, cuddle_12x12_height, cuddle_12x12_bits);
            break;
          case 5:
            // Bubbles
            u8g.drawXBMP(42, 5, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
            break;
          case 6:
            // Pizza
            u8g.drawXBMP(44, 6, pizza_13x14_width, pizza_13x14_height, pizza_13x14_bits);
            break;
        }
        switch (animationStep) {
          case 1:
            checkButton();
            u8g.drawXBMP(4, 4, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            break;
          case 2:
            checkButton();
            u8g.drawXBMP(4, 4, cat_sitting_006_24x24_width, cat_sitting_006_24x24_height, cat_sitting_006_24x24_bits);
            break;
          case 3:
            checkButton();
            u8g.drawXBMP(4, 4, cat_sitting_007_24x24_width, cat_sitting_007_24x24_height, cat_sitting_007_24x24_bits);
            break;
          case 4:
            checkButton();
            u8g.drawXBMP(4, 4, cat_sitting_004_24x24_width, cat_sitting_004_24x24_height, cat_sitting_004_24x24_bits);
            break;
        }
        break;
      case 2:
        // Feed
        u8g.setFont(u8g_font_unifont);
        switch (feedSequence) {
          case 0:
            // Select food
            if (strawberryFoodStock > 0) {
              selectedFood = 1;
              strawberryFoodStock -= 1;
            } else if (grapeFoodStock > 0) {
              selectedFood = 2;
              grapeFoodStock -= 1;
            } else if (milkFoodStock > 0) {
              selectedFood = 3;
              milkFoodStock -= 1;
            } else if (orangeFoodStock > 0) {
              selectedFood = 4;
              orangeFoodStock -= 1;
            } else if (appleFoodStock > 0) {
              selectedFood = 5;
              appleFoodStock -= 1;
            } else {
              selectedFood = 6;
            }
            feedSequence = 1;
            break;
          case 1:
            // Eat food
            switch (selectedFood) {
              case 1:
                u8g.drawXBMP(50, 14, strawberry_12x12_width, strawberry_12x12_height, strawberry_12x12_bits);
                u8g.drawStr(0, 58, "Yummy strawberry");
                break;
              case 2:
                u8g.drawXBMP(50, 14, grape_14x14_width, grape_14x14_height, grape_14x14_bits);
                u8g.drawStr(0, 58, "  Fresh grapes  ");
                break;
              case 3:
                u8g.drawXBMP(50, 14, milk_16x16_width, milk_16x16_height, milk_16x16_bits);
                u8g.drawStr(0, 58, "   Farm milk    ");
                break;
              case 4:
                u8g.drawXBMP(50, 14, orange_14x11_width, orange_14x11_height, orange_14x11_bits);
                u8g.drawStr(0, 58, "  Juicy orange  ");
                break;
              case 5:
                u8g.drawXBMP(50, 14, apple_13x14_width, apple_13x14_height, apple_13x14_bits);
                u8g.drawStr(0, 58, "  Tasty apple   ");
                break;
              case 6:
                u8g.drawXBMP(50, 14, ghost_14x14_width, ghost_14x14_height, ghost_14x14_bits);
                u8g.drawStr(0, 58, "    No food     ");
                break;
            }
            feedCounter += 1;
            if (feedCounter>300) {
              feedCounter = 0;
              feedSequence = 2;
            }
            break;
          case 2:
            // Yum
            u8g.drawXBMP(-24, 13, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            if (selectedFood != 6) {
              u8g.drawStr(0, 30, "      Yum!      ");
            }
            feedCounter += 1;
            if (feedCounter>300) {
              feedCounter = 0;
              if (selectedFood < 6) {
                superHappyCounter = 100;
                catHunger = 3;
              }
              gameMode = 0;
            }
            break;
        }
        break;
      case 3:
        // Cuddle
        u8g.drawXBMP(4, 4, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
        cuddleCounter += 1;
        if (cuddleCounter<31) {
          u8g.drawXBMP(80, 45 - cuddleCounter, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
          u8g.drawXBMP(92, 40 - cuddleCounter, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
          u8g.drawXBMP(104, 45 - cuddleCounter, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
        } else if (cuddleCounter>30 && cuddleCounter < 161) {
          u8g.drawXBMP(80, 15, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
          u8g.drawXBMP(92, 10, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
          u8g.drawXBMP(104, 15, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
          u8g.setFont(u8g_font_baby);
          u8g.drawStr(70, 40, "I love you too <3");
        } else if (cuddleCounter>160 && cuddleCounter < 240) {
          u8g.setFont(u8g_font_baby);
          u8g.drawStr(70, 40, "I love you too <3");
        } else if (cuddleCounter==240) {
          superHappyCounter = 100;
          catMorale = 3;
          gameMode = 0;
        }
        break;
      case 4:
        // Educate
        switch (lessonSequence) {
          case 0:
            // Snail arrives
            u8g.drawXBMP(-24, 13, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            u8g.drawXBMP(kokoXPos, 40, koko_le_snail_13x11_width, koko_le_snail_13x11_height, koko_le_snail_13x11_bits);
            kokoXPos -= 1;
            if (kokoXPos < 97) {
              kokoXPos = 97;
            }
            snailCounter += 1;
            if (snailCounter>100) {
              snailCounter = 0;
              lessonSequence = 1;
            }
            break;
          case 1:
            // Snail says hello
            u8g.setFont(u8g_font_baby);
            u8g.drawXBMP(-24, 13, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            u8g.drawXBMP(97, 40, koko_le_snail_13x11_width, koko_le_snail_13x11_height, koko_le_snail_13x11_bits);
            u8g.drawStr(54, 23, "~~ Welcome to a");
            u8g.drawStr(54, 29, "new lesson with");
            u8g.drawStr(54, 35, "Koko Le Snail ~~");
            snailCounter += 1;
            if (snailCounter>300) {
              snailCounter = 0;
              lessonSequence = 2;
            }
            break;
          case 2:
            // Snail wisdom quote
            u8g.setFont(u8g_font_baby);
            u8g.drawXBMP(-24, 13, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            u8g.drawXBMP(97, 40, koko_le_snail_13x11_width, koko_le_snail_13x11_height, koko_le_snail_13x11_bits);
            switch (randomQuote) {
              case 1:
                u8g.drawStr(54, 16, "Sometimes dogs");
                u8g.drawStr(54, 23, "are grey.");
                u8g.drawStr(54, 29, "");
                u8g.drawStr(54, 35, "  -- Koko");
                break;
              case 2:
                u8g.drawStr(54, 16, "Do not sneeze");
                u8g.drawStr(54, 23, "on the bus.");
                u8g.drawStr(54, 29, "");
                u8g.drawStr(54, 35, "  -- Koko");
                break;
              case 3:
                u8g.drawStr(54, 16, "Always wear");
                u8g.drawStr(54, 23, "pants.");
                u8g.drawStr(54, 29, "");
                u8g.drawStr(54, 35, "  -- Koko");
                break;
              case 4:
                u8g.drawStr(54, 16, "Never yawn");
                u8g.drawStr(54, 23, "during class.");
                u8g.drawStr(54, 29, "");
                u8g.drawStr(54, 35, "  -- Koko");
                break;
              case 5:
                u8g.drawStr(54, 16, "Wash your hands");
                u8g.drawStr(54, 23, "after lunch.");
                u8g.drawStr(54, 29, "");
                u8g.drawStr(54, 35, "  -- Koko");
                break;
              case 6:
                u8g.drawStr(54, 16, "Pull my finger...");
                u8g.drawStr(54, 23, "teehee!");
                u8g.drawStr(54, 29, "");
                u8g.drawStr(54, 35, "  -- Koko");
                break;
            }
            snailCounter += 1;
            if (snailCounter>300) {
              snailCounter = 0;
              lessonSequence = 3;
            }
            break;
          case 3:
            // Score
            u8g.setFont(u8g_font_unifont);
            u8g.drawXBMP(51, 12, study_13x14_width, study_13x14_height, study_13x14_bits);
            u8g.drawStr(0, 58, "  + 1 Education ");
            snailCounter += 1;
            if (snailCounter>300) {
              snailCounter = 0;
              superHappyCounter = 100;
              catEducation += 1;
              gameMode = 0;
            }
            break;
        }
        break;
      case 5:
        // Clean
        switch (cleanSequence) {
          case 0:
            // Clean The Cat game
            u8g.drawXBMP(34, 4, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            checkButton();
            cleanCounter -= 1;
            if (cleanCounter<0) {
              cleanCounter = 0;
            } else if (cleanCounter>100) {
              cleanCounter = 0;
              cleanSequence = 1;
            }
            switch(cleanCounter) {
              case 5 ... 25:
                u8g.drawXBMP(38, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                break;
              case 26 ... 46:
                u8g.drawXBMP(38, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(58, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                break;
              case 47 ... 67:
                u8g.drawXBMP(23, 16, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(38, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(58, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(73, 16, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                break;
              case 68 ... 88:
                u8g.drawXBMP(23, 16, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(38, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(58, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(73, 16, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(32, 0, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(64, 0, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                break;
              case 89 ... 100:
                u8g.drawXBMP(23, 16, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(38, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(58, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(73, 16, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(0, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(32, 0, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(64, 0, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                u8g.drawXBMP(96, 32, bubbles_15x15_width, bubbles_15x15_height, bubbles_15x15_bits);
                break;
            }
            break;
          case 1:
            u8g.drawXBMP(-24, 13, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            u8g.drawXBMP(72, 22, diamond_14x12_width, diamond_14x12_height, diamond_14x12_bits);
            u8g.drawXBMP(69, 50, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
            u8g.drawXBMP(81, 50, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
            u8g.drawXBMP(93, 50, cuddle_heart_11x10_width, cuddle_heart_11x10_height, cuddle_heart_11x10_bits);
            u8g.setFont(u8g_font_unifont);
            u8g.drawStr(0, 16, "      All clean ");
            cleanCounter += 1;
            if (cleanCounter>300) {
              cleanCounter = 0;
              superHappyCounter = 100;
              catHygiene = 3;
              gameMode = 0;
            }
            break;
        }
        break;
      case 6:
        // Play
        if (gameSequence == 0) {
          // Roll the dice
          checkButton();
          animationStepMax = 7;
          u8g.setFont(u8g_font_baby);
          u8g.drawStr(13, 6, "xxxx Catsino Deluxe xxxx");
          u8g.drawXBMP(3, 18, casino_frame_30x30_width, casino_frame_30x30_height, casino_frame_30x30_bits);
          u8g.drawXBMP(44, 18, casino_frame_30x30_width, casino_frame_30x30_height, casino_frame_30x30_bits);
          u8g.drawXBMP(85, 18, casino_frame_30x30_width, casino_frame_30x30_height, casino_frame_30x30_bits);
          checkButton();
          if ( (gameCounter % 3) == 0) {
            randomGameIconXPos = random(0, 3);
            randomFoodType = random(0, 7);
          }
          switch (randomGameIconXPos) {
            case 0:
              gameIconXPos = 9;
              break;
            case 1:
              gameIconXPos = 50;
              break;
            case 2:
              gameIconXPos = 91;
              break;
          }
          checkButton();
          switch (randomFoodType) {
            case 0:
              u8g.drawXBMP(gameIconXPos, 24, ghost_14x14_width, ghost_14x14_height, ghost_14x14_bits);
              break;
            case 1:
              u8g.drawXBMP(gameIconXPos, 24, bar_16x15_width, bar_16x15_height, bar_16x15_bits);
              break;
            case 2:
              u8g.drawXBMP(gameIconXPos, 24, strawberry_12x12_width, strawberry_12x12_height, strawberry_12x12_bits);
              break;
            case 3:
              u8g.drawXBMP(gameIconXPos, 24, apple_13x14_width, apple_13x14_height, apple_13x14_bits);
              break;
            case 4:
              u8g.drawXBMP(gameIconXPos, 24, grape_14x14_width, grape_14x14_height, grape_14x14_bits);
              break;
            case 5:
              u8g.drawXBMP(gameIconXPos, 24, milk_16x16_width, milk_16x16_height, milk_16x16_bits);
              break;
            case 6:
              u8g.drawXBMP(gameIconXPos, 24, orange_14x11_width, orange_14x11_height, orange_14x11_bits);
              break;
          }
          gameCounter += 1;
          if (gameCounter>600) {
            gameCounter = 0;
            gameMode = 0;
          }
        } else if (gameSequence == 1) {
          // See the result
          u8g.setFont(u8g_font_unifont);
          switch (gamePick) {
            case 0:
              // Ghost
              u8g.drawXBMP(50, 12, ghost_14x14_width, ghost_14x14_height, ghost_14x14_bits);
              u8g.drawStr(0, 58, " Nothing, boo!  ");
              break;
            case 1:
              // Bar
              u8g.drawXBMP(50, 12, bar_16x15_width, bar_16x15_height, bar_16x15_bits);
              u8g.drawStr(0, 58, "  + 1 of all!   ");
              strawberryFoodStock += 1;
              appleFoodStock += 1;
              grapeFoodStock += 1;
              milkFoodStock += 1;
              orangeFoodStock += 1;
              break;
            case 2:
              // Strawberry
              u8g.drawXBMP(50, 12, strawberry_12x12_width, strawberry_12x12_height, strawberry_12x12_bits);
              u8g.drawStr(0, 58, " + 1 strawberry ");
              strawberryFoodStock += 1;
              break;
            case 3:
              // Apple
              u8g.drawXBMP(50, 12, apple_13x14_width, apple_13x14_height, apple_13x14_bits);
              u8g.drawStr(0, 58, "   + 1 apple    ");
              appleFoodStock += 1;
              break;
            case 4:
              // Grape
              u8g.drawXBMP(50, 12, grape_14x14_width, grape_14x14_height, grape_14x14_bits);
              u8g.drawStr(0, 58, "   + 1 grape    ");
              grapeFoodStock += 1;
              break;
            case 5:
              // Milk
              u8g.drawXBMP(50, 12, milk_16x16_width, milk_16x16_height, milk_16x16_bits);
              u8g.drawStr(0, 58, "    + 1 milk    ");
              milkFoodStock += 1;
              break;
            case 6:
              // Orange
              u8g.drawXBMP(50, 12, orange_14x11_width, orange_14x11_height, orange_14x11_bits);
              u8g.drawStr(0, 58, "   + 1 orange   ");
              orangeFoodStock += 1;
              break;
          }
          gameCounter += 1;
          if (gameCounter>400) {
            gameCounter = 0;
            if (gamePick > 0) {
              superHappyCounter = 100;
              catEntertainment = 3;
            }
            gameMode = 0;
          }
        }
        break;
      case 7:
        // Random visitor
        u8g.setFont(u8g_font_baby);
        switch (randomVisitSequence) {
          case 0:
            // Knock
            checkButton();
            u8g.drawXBMP(50, 14, door_14x15_width, door_14x15_height, door_14x15_bits);
            u8g.drawStr(40, 59, "Knock knock!");
            randomVisitCounter += 1;
            if (randomVisitCounter>4000) {
              randomVisitSequence = 1;
              randomVisitCounter = 0;
            }
            break;
          case 1:
            // Hello
            u8g.drawXBMP(-24, 13, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            u8g.drawXBMP(96, 14, cindy_14x13_width, cindy_14x13_height, cindy_14x13_bits);
            u8g.drawStr(45, 59, "Hi friend!");
            randomVisitCounter += 1;
            if (randomVisitCounter>200) {
              randomVisitSequence = 2;
              randomVisitCounter = 0;
            }
            break;
          case 2:
            // Gift
            u8g.drawXBMP(-24, 13, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            u8g.drawXBMP(96, 14, cindy_14x13_width, cindy_14x13_height, cindy_14x13_bits);
            if (randomVisit<51) {
              // Matcha
              u8g.drawStr(45, 59, "I got matcha tea!");
            } else {
              u8g.drawStr(45, 59, "I got coco cake!");
            }
            randomVisitCounter += 1;
            if (randomVisitCounter>200) {
              randomVisitSequence = 3;
              randomVisitCounter = 0;
            }
            break;
          case 3:
            // Drink
            u8g.drawXBMP(-24, 13, cat_sitting_001_24x24_width, cat_sitting_001_24x24_height, cat_sitting_001_24x24_bits);
            if (randomVisit<51) {
              // Matcha
              u8g.drawXBMP(49, 14, matcha_15x16_width, matcha_15x16_height, matcha_15x16_bits);
            } else {
              u8g.drawXBMP(49, 14, coco_cake_14x16_width, coco_cake_14x16_height, coco_cake_14x16_bits);
            }
            u8g.drawXBMP(96, 14, cindy_14x13_width, cindy_14x13_height, cindy_14x13_bits);
            u8g.drawStr(45, 59, "Have some <3");
            randomVisitCounter += 1;
            if (randomVisitCounter>200) {
              randomVisitSequence = 4;
              randomVisitCounter = 0;
            }
            break;
          case 4:
            // Bonus
            u8g.setFont(u8g_font_unifont);
            if (randomVisit<51) {
              // Matcha
              u8g.drawXBMP(49, 14, matcha_15x16_width, matcha_15x16_height, matcha_15x16_bits);
            } else {
              u8g.drawXBMP(49, 14, coco_cake_14x16_width, coco_cake_14x16_height, coco_cake_14x16_bits);
            }
            u8g.drawStr(0, 59, "      Yum!      ");
            randomVisitCounter += 1;
            if (randomVisitCounter>200) {
              randomVisitSequence = 0;
              randomVisitCounter = 0;
              superHappyCounter = 100;
              catHunger = 3;
              gameMode = 0;
            }
            break;
        }
        break;
    }
    /*
    // Frame counter
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(8, 50, frameCounterString);
    u8g.drawStr(8, 10, animationStepString);
    */
  } while( u8g.nextPage() );
}
