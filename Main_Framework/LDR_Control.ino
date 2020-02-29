///
/// LDR control
///
/// IsLightOn() -> Check if the light is turned on in the bathroom
///

//
/// EXTERNAL FUNCTIONS ///
// Check if the light is on
bool IsLightOn()
{
  // Read the current resistance value
  int r = analogRead(LDR_PIN); 

  // Return if the resistance is above the threshold.
  return (r > 350); // lights on measured at 400 on average, so assume everything above 350 means the light is on.
}
/// END OF EXTERNAL FUNCTIONS ///
//
