///
/// Spray control
///
/// Spray() -> Spray once -- BLOCKING!
/// Spray(int count) -> Spray a given amount of times -- BLOCKING!
///

/// VARIABLES ///
// The amount of sprays remaining in this can
int sprayCountRemaining = 2400;
/// END OF VARIABLES ///

/// EXTERNAL FUNCTIONS ///
// Spray once
//  -- BLOCKING!
void Spray()
{
  OnLEDYlw();
  digitalWrite(SPRAY_PIN, HIGH);
  delay(1000);
  digitalWrite(SPRAY_PIN, LOW);
  OffLEDYlw();
}

// Spray a given amount of times
//  -- BLOCKING!
void Spray(int count)
{
  for (int i = 0; i < count; i++)
  {
    Spray();
  }
}
/// END OF EXTERNAL FUNCTIONS ///

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
}
/// END OF INTERNAL FUNCTIONS ///
