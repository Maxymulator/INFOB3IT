/// To Do:
// - Make the spraying mechanism non-blocking
// - Add EEPROM memory support to keep track of the remaining sprays in the can without power
// - Reserach interrupts to see if they can be useful in this project
// - Write a DFA and implement it (using an enum)
// - Hook up the magnetic doorsensor
// - Write support for the magnetic doorsensor


/// LIBARIES ///
#include <LiquidCrystal.h> // LCD library
#include <NewPing.h> // Sonar library
#include <OneWire.h> // One Wire library
#include <DallasTemperature.h> // Temperature sensor library
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

// The spraying mechanism is plugged in to pin 6
const int SPRAY_PIN = 6;

// One Wire (temperature)
// The One Wire bus is plugged in to pin 10
const int ONE_WIRE_PIN = 10;

// Initialize the One Wire bus
OneWire oneWire(ONE_WIRE_PIN);

// Initialize the temperature sensor
DallasTemperature tempSensor(&oneWire);

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
  pinMode(MOTION_PIN, INPUT);
  pinMode(SPRAY_PIN, OUTPUT);
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

  // Start the temperature library
  tempSensor.begin();
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
  Serial.println(GetTemperature());
}
/// END OF MAIN FUNCTIONS ///
