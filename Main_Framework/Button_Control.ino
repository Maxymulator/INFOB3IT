///
/// Button handling
///
/// External funtions:
/// HandleButtons() -> read the currently pressed button and perform its corresponding action
///

/// VARIABLES ///
// previous button state
int prevButton = 0;

// current button state
int curButton = 0;

// time of the last debounce check
unsigned long lastDebounceTime = 0;

// the delay to debounce
unsigned long debounceDelay = 50;
/// END OF VARIABLES ///

/// EXTERNAL FUNCTIONS ///
void HandleButtons()
{
  // the current reading of the buttons
  int reading = ReadButtons();
  
  // check if the button has changed, due to noise or pressing
  if( curButton != prevButton)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  // check if you are on the debouncing delay
  if( (millis() - lastDebounceTime) > debounceDelay)
  {
    // check if the buttonstate has actually changed
    if(reading != curButton)
    {
      // update the current buttonstate
      curButton = reading;
      // perform the action corresponding to the current button
      PerformButtonAction(curButton);
    }
  }
  // update the previous buttonstate
  prevButton = reading;
}
/// END OF EXTERNAL FUNCTIONS ///

/// INTERNAL FUNCTIONS ///
// Perform the action of the given button
void PerformButtonAction(int button)
{
  switch (button)
  {
    case 1: // button 1 pressed
      OnLEDGrn(); // TEMP for testing
      break;
    case 2: // button 2 pressed
      ToggleLEDYlw(); // TEMP for testing
      break;
    case 3: // button 3 pressed
      ToggleLEDGrn(); // TEMP for testing
      break;
    default: // no buttons pressed
      break;
  }
}

// Read which button is currently pressed
int ReadButtons ()
{
  // the button currently pressed
  int button;
  
  // read the current on the button pin
  int reading = analogRead(BUTTON_PIN);

  // check which button the measured voltage corresponds with
  if (reading > 1000) // no buttons measures in at 1030V
  {
    button = 0; // no buttons pressed
  }
  else if (reading > 650 && reading < 710) // button 1 measures in at 680V
  {
    button = 1; // button 1 pressed:
  }
  else if (reading > 480 && reading < 540) // button 2 measures in at 510V
  {
    button = 2; // button 2 pressed:
  }
  else if (reading < 30) // button 3 measures in at 0V
  {
    button = 3; // button 3 pressed:
  }
  return button;
}
/// END OF INTERNAL FUNCTIONS ///
