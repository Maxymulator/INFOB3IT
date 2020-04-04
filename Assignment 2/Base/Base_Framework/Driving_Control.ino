///
/// Driving Control
///
/// setMotorSpeed(int) -> Sets the speed of the motors, clamped between 500 and 1023
/// drive(driveState) -> drives the base, based on the given driveState
/// handleAutoDriving() -> Handles the autopilot, making the base follow the light
///

//
/// CONSTANTS ///

/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// The PWM signal for the motor speed
int motorSpeed = 500;
/// END OF VARIABLES ///
//

//
/// EXTERNAL FUNCTIONS ///
// Sets the speed of the motors, clamped between 500 and 1023.
// The motors wont run below 500, and 1023 is the max PWM value of the nodeMCU.
void setMotorSpeed(int val)
{
  if (val < 500)
  {
    motorSpeed = 500;
  }
  else if (val > 1023)
  {
    motorSpeed = 1023;
  }
  else
  {
    motorSpeed = val;
  }
}

// Handles the autopilot, making the base follow the light
void handleAutoDriving()
{
  switch (getAutoDriveDir())
  {
    case front:
      {
        driveForward();
        break;
      }
    case back:
      {
        driveBack();
        break;
      }
    case left:
      {
        turnLeft();
        break;
      }
    case right:
      {
        turnRight();
        break;
      }
    case still:
      {
        driveStop();
        break;
      }
  }
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Drives the base forward
void driveForward()
{
  Serial.println("driving forward");

  // Set the motor speeds
  analogWrite(LEFT_PMW, motorSpeed);
  analogWrite(RIGHT_PMW, motorSpeed);

  // Turn on the left engine -> forwards
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, HIGH);

  // Turn on the right engine -> forwards
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, HIGH);
}

// Drive the base backwards
void driveBack()
{
  Serial.println("driving backward");

  // Set the motor speeds
  analogWrite(LEFT_PMW, motorSpeed);
  analogWrite(RIGHT_PMW, motorSpeed);

  // Turn on the left engine -> backwards
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, LOW);

  // Turn on the right engine -> backwards
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, LOW);
}

// Stops the base
void driveStop()
{
  Serial.println("standing still");

  // Turn off the left engine
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, LOW);

  // Turn off the right engine
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, LOW);
}

// Turns the base left
void turnLeft()
{
  Serial.println("Turning left");

  // Set the motor speeds
  analogWrite(LEFT_PMW, motorSpeed);
  analogWrite(RIGHT_PMW, motorSpeed);

  // Turn on the left engine -> backwards
  digitalWrite(LEFT_1, HIGH);
  digitalWrite(LEFT_2, LOW);

  // Turn on the right engine -> forwards
  digitalWrite(RIGHT_1, LOW);
  digitalWrite(RIGHT_2, HIGH);
}

// Turns the base right
void turnRight()
{
  Serial.println("Turning right");

  // Set the motor speeds
  analogWrite(LEFT_PMW, motorSpeed);
  analogWrite(RIGHT_PMW, motorSpeed);

  // Turn on the left engine -> forwards
  digitalWrite(LEFT_1, LOW);
  digitalWrite(LEFT_2, HIGH);

  // Turn on the right engine -> backwards
  digitalWrite(RIGHT_1, HIGH);
  digitalWrite(RIGHT_2, LOW);
}
/// END OF INTERNAL FUNCTIONS ///
//
