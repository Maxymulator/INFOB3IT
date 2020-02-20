/// LIBARIES ///
#include <LiquidCrystal.h> // LCD library
/// END OF LIBRARIES ///

/// CONSTANTS ///
// The midway point for PMW
const int PMW_MID = 128;

// The LEDs are plugged in to pin 9
const int LED_PIN = 9;

// The buttons are plugged in to pin 5
const int BUTTON_PIN = A5;

// LCD pins
const int LCD_RS = 12;
const int LCD_E = 11;
const int LCD_D4 = 5;
const int LCD_D5 = 4;
const int LCD_D6 = 3;
const int LCD_D7 = 2;

// The empty string for the lcd screen
const String EMPTY_LCD_STRING = "                ";

// Initialise the lcd screen
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
// <END OF CONSTANTS ///

/// MAIN FUNCTIONS ///
void setup()
{
  // put your setup code here, to run once:
  // Pin mode setup:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_E, OUTPUT);
  pinMode(LCD_D4, OUTPUT);
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);

  // Other setup:
  // Turn on the power LED:
  OnLEDGrn();

  // Turn on the serial monitor on port 9600
  Serial.begin(9600);

  // Turn on the LCD screen
  lcd.begin(16, 2); // width 16px by height 2px
  PrintClrLCDTopLine("Hello World");
}

void loop()
{
  // put your main code here, to run repeatedly:
  unsigned long curMillis = millis();
  HandleButtons();
  PrintLCDBottomLine(curMillis / 1000); 
}
/// END OF MAIN FUNCTIONS ///
