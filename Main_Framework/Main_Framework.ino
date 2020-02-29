/// To Do:
// - Research interrupts to see if they can be useful in this project
// - Write a DFA
// - Write support for the magnetic doorsensor
// - implement the DFA

//
/// LIBARIES ///
#include <LiquidCrystal.h> // LCD library
#include <NewPing.h> // Sonar library
#include <OneWire.h> // One Wire library
#include <DallasTemperature.h> // Temperature sensor library
#include <EEPROM.h> // EEPROM memory library
/// END OF LIBRARIES ///
//

//
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

// The spraying mechanism is plugged in to pin 13
const int SPRAY_PIN = 13;

// The magnetic flush sensor is plugged in to pin 6
const int FLUSH_PIN = 6;

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

// The enum defining the current state of this cycle
enum programState
{
  state_standbye,        // standbye state
  state_inuse_unknown,   // toilet in use, unsure how
  state_inuse_one,       // toilet in use, number 1
  state_inuse_two,       // toilet in use, number 2
  state_inuse_clean,     // toilet in use, cleaning
  state_start_spray_one, // the system is about to spray once
  state_start_spray_two, // the system is about to spray twice
  state_spraying,        // the system is currently spraying
  state_menu,            // operator menu active
  state_test             // state for testing purposes
};
/// <END OF CONSTANTS ///
//

//
/// VARIABLES ///
// the current state of this cycle
programState currentState = state_standbye;
/// END OF VARIABLES ///
//

//
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
  pinMode(FLUSH_PIN, INPUT);
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
  lcd.clear();
  PrintClrLCDTopLine(F("Hello World"));

  // Start the temperature library
  tempSensor.begin();

  // Initialize the spraycount
  InitSpraycount();
}

void loop()
{
  // put your main code here, to run repeatedly:
  HandleMotion();

  switch (currentState)
  {
    case state_standbye:
      {
        HandleStandbye();
        break;
      }
    case state_inuse_unknown:
      {
        HandleInUseUnknown();
        break;
      }
    case state_inuse_one:
      {
        HandleInUneOne();
        break;
      }
    case state_inuse_two:
      {
        HandleInUseTwo();
        break;
      }
    case state_inuse_clean:
      {
        HandleCleaning();
        break;
      }
    case state_start_spray_one:
      {
        HandleStartSpray(1);
        break;
      }
    case state_start_spray_two:
      {
        HandleStartSpray(2);
        break;
      }
    case state_spraying:
      {
        HandleSpraying();
        break;
      }
    case state_menu:
      {
        HandleMenu();
        break;
      }
    case state_test:
      {
        HandleTest();
        break;
      }
    default:
      {
        break;
      }
  }
}
/// END OF MAIN FUNCTIONS ///
//

//
/// STATE HANDLING ///
// handle the standbye state
void HandleStandbye()
{
  HandleButtons();
  PrintLCDTopLine(F("Standbye        "));
  OffLEDGrn();
}

// handle the unknown use state
void HandleInUseUnknown()
{
  HandleButtons();

}

// handle the number 1 state
void HandleInUneOne()
{
  HandleButtons();

}

// handle the number 2 state
void HandleInUseTwo()
{
  HandleButtons();

}

// handle the cleaning state
void HandleCleaning()
{
  HandleButtons();

}

// handle the 'about to spray' state
void HandleStartSpray(int count)
{
  StartSpray(count);
  currentState = state_spraying;
}

// handle the spraying state
void HandleSpraying()
{
  if (Spray())
  {
    ClearLCD();
    currentState = state_standbye;
  }
}

// handle the menu state
void HandleMenu()
{
  HandleButtons();
  PrintMenu();
}

// handle the testing state
void HandleTest()
{
  HandleButtons();
}
/// END OF STATE HANDLING ///
//
