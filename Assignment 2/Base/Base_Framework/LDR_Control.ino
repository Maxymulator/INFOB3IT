///
/// LDR Control
///
/// getAutoDriveDir() -> Read the LDRs and decide in which direction the car needs to move
///

//
/// CONSTANTS ///
// The maximun difference the LDR values can have before before we start moving
int ldrNullDiff = 100;
/// END OF CONSTANTS ///
//

//
/// EXTERNAL FUNCTIONS ///

// Read the LDRs and decide in which direction the car needs to move
driveState getAutoDriveDir()
{
  int ldrFront = readLDRFront();
  int ldrBack = readLDRBack();
  if (ldrFront > ldrBack) // Front LDR receives more light
  {
    if (ldrFront - ldrBack < ldrNullDiff) // Check if light is equal enough to stand still
    {
      return still;
    }
    else
    {
      return front;
    }
  }
  else // Back LDR receives more light
  {
    if (ldrBack - ldrFront < ldrNullDiff) // Check if light is equal enough to stand still
    {
      return still;
    }
    else
    {
      return back;
    }
  }
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Read the value from the front LDR, averaged over 10 readings
int readLDRFront()
{
  switchAnalogToLDRFront();
  int runningTotal = 0;
  for (int i = 0; i < 10; i++)
  {
    runningTotal += analogRead(A0);
  }
  int avg = runningTotal / 10;
  Serial.print("Front: ");
  Serial.println(avg);
  return avg;
}

// Read the value from the read LDR, averaged over 10 readings
int readLDRBack()
{
  switchAnalogToLDRBack();
  int runningTotal = 0;
  for (int i = 0; i < 10; i++)
  {
    runningTotal += analogRead(A0);
  }
  int avg = runningTotal / 10;
  Serial.print("Back: ");
  Serial.println(avg);
  return avg;
}

// Switch the analog input to the front LDR
void switchAnalogToLDRFront()
{
  digitalWrite(LDR_SEL, HIGH);
}

// Switch the analog input to the back LDR
void switchAnalogToLDRBack()
{
  digitalWrite(LDR_SEL, LOW);
}
/// END OF INTERNAL FUNCTIONS ///
//
