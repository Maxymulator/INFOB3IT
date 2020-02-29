///
/// LED handling
///
/// External functions:
/// OnLEDGrn() -> turn the green LED on 
/// OnLEDYlw() -> turn the yellow LED on
/// OnLEDBth() -> turn both LEDs on
/// OffLEDGrn() -> turn the green LED off
/// OffLEDYlw() -> turn the yellow LED off
/// OffLEDBth() -> turn both LEDs off
/// ToggleLEDGrn() -> toggle the green LED
/// ToggleLEDYlw() -> toggle the yellow LED
/// ToggleLEDBth() -> toggle both LEDs
///

//
/// VARIABLES ///
// Bool depicting if the green LED is turned on
bool ledGrnOn = false;
// Bool depicting if the yellow LED is turned on
bool ledYlwOn = false;
/// END OF VARIABLES ///
//

//
/// EXTERNAL COMMANDS ///
// Turn on the green LED
void OnLEDGrn()
{
  ledGrnOn = true;
  HandleLEDs();
}

// Turn on the yellow LED
void OnLEDYlw()
{
  ledYlwOn = true;
  HandleLEDs();
}

// Turn on both LEDs
void OnLEDBth()
{
  ledGrnOn = true;
  ledYlwOn = true;
  HandleLEDs();
}

// Turn off the green LED
void OffLEDGrn()
{
  ledGrnOn = false;
  HandleLEDs();
}

// Turn off the yellow LED
void OffLEDYlw()
{
  ledYlwOn = false;
  HandleLEDs();
}

// Turn off both LEDs
void OffLEDBth()
{
  ledGrnOn = false;
  ledYlwOn = false;
  HandleLEDs();
}

// Toggle the green LED
void ToggleLEDGrn()
{
  ledGrnOn = !ledGrnOn;
  HandleLEDs();
}

// Toggle the yellow LED
void ToggleLEDYlw()
{
  ledYlwOn = !ledYlwOn;
  HandleLEDs();
}

// Toggle both LEDs
void ToggleLEDBth()
{
  ledGrnOn = !ledGrnOn;
  ledYlwOn = !ledYlwOn;
  HandleLEDs();
}
/// END OF EXTERNAL COMMANDS ///
//

//
/// INTERNAL COMMANDS ///
void HandleLEDs()
{
  // Both LEDs are on
  if (ledGrnOn && ledYlwOn)
  {
    pinMode(LED_PIN, OUTPUT);
    analogWrite(LED_PIN, PMW_MID);
  }
  // both LEDs are off
  else if (!ledGrnOn && !ledYlwOn)
  {
    pinMode(LED_PIN, INPUT);
  }
  // only the green LED is on
  else if (ledGrnOn && !ledYlwOn)
  {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
  }
  // only the yellow LED is on
  else if (!ledGrnOn && ledYlwOn)
  {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
  }
}
/// END OF INTERNAL COMMANDS ///
//
