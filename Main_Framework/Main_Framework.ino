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
const int FLUSH_PIN = 2;

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
const int SONAR_MAX_DIST = 200;

// Initialize the sonar
NewPing sonar(SONAR_PIN, SONAR_PIN, SONAR_MAX_DIST);

// LCD
// LCD pins
const int LCD_RS = 12;
const int LCD_E = 11;
const int LCD_D4 = 5;
const int LCD_D5 = 4;
const int LCD_D6 = 3;
const int LCD_D7 = 6;

// The empty string for the lcd screen
const String EMPTY_LCD_STRING = "                ";

// Initialise the lcd screen
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// The enum defining the current state of this cycle
enum programState
{
  state_standby,         // standby state
  state_inuse_unknown,   // toilet in use, unsure how
  state_inuse_one,       // toilet in use, number 1
  state_inuse_two,       // toilet in use, number 2
  state_inuse_clean,     // toilet in use, cleaning
  state_start_spray_one, // the system is about to spray once
  state_start_spray_two, // the system is about to spray twice
  state_spraying,        // the system is currently spraying
  state_menu,            // operator menu active
};
/// <END OF CONSTANTS ///
//

//
/// VARIABLES ///
// the current state of this cycle
volatile programState currentState = state_standby;

// The current state of the standard display
bool stdDisplayState = true;

// The last time the standard display toggled
unsigned long prevStdDisplayToggle = 0;

// Bool denoting if the current standby mode is forced
bool forcedStandby = false;
/// END OF VARIABLES ///
//

//
/// MAIN FUNCTIONS ///
void setup()
{
  // put your setup code here, to run once:
  // Pin mode setup:
  pinMode(LED_PIN, INPUT); // set the LED pin as input to turn off both leds
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

  // Turn on the serial monitor on port 9600
  Serial.begin(9600);

  // Turn on the LCD screen
  lcd.begin(16, 2); // width 16px by height 2px
  lcd.clear();

  // Start the temperature library
  tempSensor.begin();

  // Initialize the spraycount
  InitSpraycount();

  // Attach the interrupt to the flushing mechanism
  attachInterrupt(digitalPinToInterrupt(FLUSH_PIN), HandleFlushInterrupt, RISING);
}

void loop()
{
  // put your main code here, to run repeatedly:
  HandleMotion();
  HandleSonar();

  switch (currentState)
  {
    case state_standby:
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
// handle the standby state
void HandleStandbye()
{
  HandleButtons();
  PrintLCDTopLine(F("  System is in  "));
  PrintLCDBottomLine(F("  standby mode  "));
  OffLEDGrn();

  if (IsLightOn())
  {
    if (!forcedStandby)
    {
      currentState = state_inuse_unknown;
      forcedStandby = false;
    }
  }
  else
  {
    forcedStandby = false;
  }
}

// handle the unknown use state
void HandleInUseUnknown()
{
  HandleButtons();
  HandleStdDisplay();
  OnLEDGrn();
  if(!IsLightOn())
  {
    currentState = state_standby;
    forcedStandby = true;
  }
}

// handle the number 1 state
void HandleInUneOne()
{
  HandleButtons();
  HandleStdDisplay();
  if (!IsLightOn())
  {
    currentState = state_start_spray_one;
  }
}

// handle the number 2 state
void HandleInUseTwo()
{
  HandleButtons();
  HandleStdDisplay();
  if (!IsLightOn())
  {
    currentState = state_start_spray_two;
  }
}

// handle the cleaning state
void HandleCleaning()
{
  HandleButtons();
  HandleStdDisplay();
  if (!IsLightOn())
  {
    currentState = state_standby;
  }
}

// handle the 'about to spray' state
void HandleStartSpray(int count)
{
  ClearLCD();
  StartSpray(count);
  currentState = state_spraying;
}

// handle the spraying state
void HandleSpraying()
{
  if (Spray())
  {
    ClearLCD();
    currentState = state_standby;
    forcedStandby = true;
  }
}

// handle the menu state
void HandleMenu()
{
  HandleButtons();
  PrintMenu();
}
/// END OF STATE HANDLING ///
//

//
/// INTERNAL FUNCTIONS ///
// Toggles the standard display
void ToggleStdDisplay()
{
  stdDisplayState = !stdDisplayState;
}

// Print the standard display to the LCD
void PrintStdDisplay()
{
  if (stdDisplayState)
  {
    PrintLCDTopLine(F("Sprays remaining"));
    PrintLCDBottomLine(GetSprayCount());
  }
  else
  {
    PrintLCDTopLine(F("Room temperature"));
    PrintLCDBottomLine(GetTemperature());
  }
}

// Handles the standard display
void HandleStdDisplay()
{
  if (millis() - prevStdDisplayToggle > 2000)
  {
    ToggleStdDisplay();
    prevStdDisplayToggle = millis();
  }

  PrintStdDisplay();
}

// Guess the use of the program and change state accordingly
void GuessUse()
{
  if (SufficientMotion()) // motion is above threshold, so user must be cleaning
  {
    currentState = state_inuse_clean;
  }
  else if (SonarCheckSitting()) // distane is below threshold, so user is sitting and thus performing number 2
  {
    currentState = state_inuse_two;
  }
  else // user must be performing number 1
  {
    currentState = state_inuse_one;
  }
}
/// END OF INTERNAL FUNCTIONS ///
//
