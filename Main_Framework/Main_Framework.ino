/// LIBARIES ///
#include <LiquidCrystal.h> // LCD library
#include <NewPing.h> // Sonar library
/// END OF LIBRARIES ///

/// CONSTANTS ///
// The midway point for PMW
const int PMW_MID = 128;

// The LEDs are plugged in to pin 9
const int LED_PIN = 9;

// The buttons are plugged in to pin A5
const int BUTTON_PIN = A5;

// The LDR is plugged in to pin A4
const int LDR_PIN = A4;

// The motion sensor is plugged in to pin 7
const int MOTION_PIN = 7;

// Sonar
// The Sonar distance sensor is plugged in to pin 8
const int SONAR_PIN = 8;

// The max distance the sonar will see in cm
const int SONAR_MAX_DIST = 100;

// Initialize the sonar
NewPing sonar(SONAR_PIN, SONAR_PIN, SONAR_MAX_DIST);

// LCD
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
  pinMode(LDR_PIN, INPUT);
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
  //PrintLCDBottomLine(curMillis / 1000); 
  PrintClrLCDBottomLine(SonarPingcm()); 
  IsLightOn();
  HandleMotion();
  if (curMillis % 5000 < 100){
    MotionOverThreshold(0.3);
  }
}
/// END OF MAIN FUNCTIONS ///
