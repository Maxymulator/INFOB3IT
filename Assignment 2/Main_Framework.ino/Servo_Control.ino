///
/// Servo control
///

//
/// CONSTANTS ///
// The delay to wait for the servo to reach it's position
unsigned long servoDelay = 20;
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// Bool defining if the servo should be running at the moment
bool servoRunning = false;

// Bool denoting if the servoPos is currently increasing. true = increasing, false = decreasing
bool servoIncreasing = true;

// The current position of the servo
int servoPos = 0;

// The previous time the servo was updated
unsigned long servoPrevTime = 0;
/// END OF VARIABLES ///
//

//
/// EXTERNAL FUNCTIONS ///
// Handles the servo motor 
void handleServo()
{
  if (!servoRunning) return;
  if ( millis() - servoPrevTime > servoDelay)
  {
    updateServoPos();
    servo.write(servoPos);
    servoPrevTime = millis();
  }
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
void updateServoPos()
{
  if (servoIncreasing)
  {
    servoPos += 1;
    if (servoPos == 180)
    {
      servoIncreasing = false;
    }
  }
  else
  {
    servoPos -= 1;
    if (servoPos == 0)
    {
      servoIncreasing = true;
    }
  }
}
/// END OF INTERNAL FUNCTIONS ///
//
