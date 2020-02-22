///
/// Motion Control
///
/// HandleMotion -> Handle the motion sensor, building up two values for the average
/// MotionOverThreshold(double threshold) -> Check if the current average of motion is over the given threshold
/// SufficientMotion -> Check if the average amount of motion is enough for cleaning
/// IsMotionDetected() -> Check if there has been motion detected in the last 5 seconds
///

/// CONSTANTS ///
// The needed delay after the sensor stops sensing motion
int motionDelay = 2000; // 2 seconds

/// END OF CONSTANTS///

/// VARIABLES ///
// The last time the motion sensor triggered
unsigned long motionPrevTrigger = 0;

// The result of the previous cycle
bool motionPrevResult = false;

// The total of all motion checks, for threshold checking
double motionTotal = 0;

// The total amount of motion check calls
double motionCount = 0;
/// END OF VARIABLES ///

/// EXTERNAL FUNCTIONS ///
// Check if motion has been detected in the last 5 seconds.
bool IsMotionDetected()
{
  if (millis() - motionPrevTrigger < motionDelay)
  {
    return motionPrevResult;
  }
  bool motionDetected = digitalRead(MOTION_PIN);
  motionPrevTrigger = millis();
  motionPrevResult = motionDetected;
  return motionDetected;
}

// Handle the motion sensor, building up for the average
void HandleMotion()
{
  if (millis() - motionPrevTrigger < motionDelay)
  {
    return;
  }
  double motionDetected = digitalRead(MOTION_PIN);
  motionPrevResult = motionDetected;
  motionTotal += motionDetected;
  motionCount += 1;
}

// Check if the amount of motion exceeds the given threshold
bool MotionOverThreshold(double threshold)
{
  double average = motionTotal / motionCount;
  return average > threshold;
}

// Check if the amount of motion was substantial enough during this cycle
bool SufficientMotion()
{
  return MotionOverThreshold(0.7); //from testing 0.7 seems to be a decent threshold for cleaning
}
/// END OF EXTERNAL FUNCTIONS ///
