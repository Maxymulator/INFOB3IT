///
/// Spray control
///
/// Spray() -> Spray once
/// StartSpray(int count) -> Spray a given amount of times
/// InitSpraycount() -> Read the sprays remaining from memory
///

//
/// CONSTANTS ///
// The delay needed to allow for the spray to happen, but not burn the motor
const unsigned long sprayMotorDelay = 1000;
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// The amount of sprays remaining in this can
int sprayCountRemaining;

// The amount of sprays remaining in this cycle
int spraysRemaining;

// The time this spray started
unsigned long sprayStartTime = 0;

// The time the spray command was given
unsigned long sprayCommandTime = 0;

// The delay before a spray
unsigned long sprayDelay = 2000;

// The current state of the spraying mechanism
int sprayState = LOW;
/// END OF VARIABLES ///
//

//
/// EXTERNAL FUNCTIONS ///
// Spray once
bool Spray()
{
  if (spraysRemaining <= 0) // Check if there are no sprays remaining this cycle
  {
    return true; // done spraying
  }
  if (millis() - sprayCommandTime > sprayDelay) // Wait for the initial delay
  {
    if (sprayState == LOW)
    {
      // Turn on the yellow LED, indicating a spray is imminent
      OnLEDYlw();

      // Store the current time as the starting time of this spray
      sprayStartTime = millis();

      // Set the sprayState to high, denoting that we are currently spraying
      sprayState = HIGH;

      // Spray
      digitalWrite(SPRAY_PIN, HIGH);
    }
    else if (millis() - sprayStartTime > sprayMotorDelay) // Wait for the motor delay
    {
      // Stop spraying
      digitalWrite(SPRAY_PIN, LOW);

      // Turn off the yellow LED, indicating we're done spraying
      OffLEDYlw();

      // Set the sprayState to low, denoting that we are done with this spray
      sprayState = LOW;

      // Lower the remaining spray count
      sprayCountRemaining -= 1;

      // Lower the remaining sprays in this cycle
      spraysRemaining -= 1;

      // Store the spray count in the EEPROM on adress 0
      EEPROM.put(0, sprayCountRemaining);

      // Set the command time to the current time to initiate the delay for possible further sprays
      sprayCommandTime = millis();
    }
  }
  return false; // not done spraying yet
}

// Start spraying the given amount of time
void StartSpray(int count)
{
  // store the needed amount of sprays
  spraysRemaining = count;

  // Store the current time for the initial delay
  sprayCommandTime = millis();

  // Call the spray function for the first time
  Spray();
}

// Read the sprays remaining from memory
void InitSpraycount()
{
  // Read the sprays remaining in this can from the EEPROM memory, stored at adress 0
  EEPROM.get(0, sprayCountRemaining);
}

// Cycle the pre-spray delay between 1 and 5 seconds
void CycleSprayDelay()
{
  sprayDelay += 1000;
  if (sprayDelay > 5000)
  {
    sprayDelay = 1000;
  }
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Lower the remaining sprays in this can
void LowerSprayCount()
{
  sprayCountRemaining -= 1;
}

// Resets the remaining sprays in this can
void ResetSprayCount()
{
  sprayCountRemaining = 2400;
  EEPROM.put(0, sprayCountRemaining);
}
/// END OF INTERNAL FUNCTIONS ///
//
