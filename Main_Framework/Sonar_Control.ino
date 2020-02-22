///
/// Sonar control
///
/// SonarPingcm -> Read the current distance
/// SprayBlocked -> Check if the spraying mechanism is blocked
/// SonarCheckSitting -> Check if the user is currently sitting
///

/// EXTERNAL FUNCTIONS ///
// Read the current distance
int SonarPingcm()
{
  delay(30); // acceptable delay, to keep functionality of timer2. min delay between pulses is 29ms.
  return sonar.ping_cm(); 
}

// Check if the spray is blocked
bool SprayBlocked(int distance)
{
  return (distance < 10); // check if anything is closer then 10 cm
}

// Check if the user is sitting down
bool SonarCheckSitting(int distance)
{
  return (distance < 40); // check if anything is closer then 40 cm
}
/// END OF EXTERNAL FUNCTIONS ///
