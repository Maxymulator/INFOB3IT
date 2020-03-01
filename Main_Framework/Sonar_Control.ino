///
/// Sonar control
///
/// HandleSonar() -> Handle the distance sensor, creating the average
/// SonarPingcm() -> Read the current distance
/// SprayBlocked() -> Check if the spraying mechanism is blocked
/// SonarCheckSitting() -> Check if the user, on average, was sitting down
///

//
/// CONSTANTS ///
// The delay between checking the distance
unsigned long sonarDelay = 2000;

// The minimum delay between each pulse
unsigned long sonarMinDelay = 30;
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// The last time the motion sensor triggered
unsigned long sonarPrevTrigger = 0;

// The last read value
unsigned long sonarPrevResult = 0;

// The total of all motion checks, for threshold checking
unsigned long sonarTotal = 0;

// The total amount of motion check calls
unsigned long sonarCount = 0;
/// END OF VARIABLES ///
//

//
/// EXTERNAL FUNCTIONS ///
// Handle the distance sensor, creating the average
void HandleSonar()
{
  if (millis() - sonarPrevTrigger < sonarDelay)
  {
    return;
  }
  int curDistance = SonarPingcm();
  sonarTotal += curDistance;
  sonarCount += 1;
}

// Read the current distance
int SonarPingcm()
{
  if (millis() - sonarPrevTrigger > sonarMinDelay)
  {
    int curDist = sonar.ping_cm();
    sonarPrevTrigger = millis();
    if (curDist == 0)
    {
      curDist = 200;
    }
    sonarPrevResult = curDist;
  }
  return sonarPrevResult;
}

// Check if the spray is blocked
bool SprayBlocked()
{
  int distance = SonarPingcm();
  return (distance < 10); // check if anything is closer then 10 cm
}

// Check if the user, on average, was sitting down
bool SonarCheckSitting()
{
  unsigned long average = sonarTotal / sonarCount;
  return (average < 40);
}
/// END OF EXTERNAL FUNCTIONS ///
//
