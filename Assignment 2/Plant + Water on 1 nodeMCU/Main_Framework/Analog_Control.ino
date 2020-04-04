///
/// Analog sensor control
///
/// readLDR() -> Reads the value from the ldr and returns it
/// readSoilMoisture() -> Reads the value from the soilmoisture sensor and returns it
///

//
/// VARIABLES ///
// The state of the selector pin of the analog board
int analogState = LOW;

// The last reading of the soil moisture sensor
float lastSoilPercentage = 0;
/// END OF VARIABLES ///
//

//
/// EXTERNAL FUNCTIONS ///
// Reads the value from the ldr and returns it
int readLDR()
{
  switchAnalogToLDR();
  return analogRead(ANALOG_INPUT);
}

// Reads the value from the ldr and returns it as a percentage
float readLDRPercent()
{
  float val = (float)readLDR();
  float returnVal = (val / 1024) * 100;
  return returnVal;
}

// Reads the value from the ldr as a percentage and prints it as a string with % appended
String readLDRPercentS()
{
  return String(readLDRPercent()) + F(" %");
}

// Reads the value from the soilmoisture sensor and returns it
int readSoilMoisture()
{
  if(analogState == LOW)
  {
    switchAnalogToMoisture();
  }
  int runningTotal = 0;
  for (int i = 0; i < 10; i++)
  {
    int prev = runningTotal; //testing
    runningTotal += analogRead(ANALOG_INPUT);
    Serial.print(runningTotal - prev); //testing
    Serial.print(F(" ,")); // testing
  }
  int avg = runningTotal / 10;
  Serial.println(avg); // testing
  return avg;
}

// Reads the soil moisture and stores and returns it as a percentage
float readSoilMoisturePercent()
{
  float val = readSoilMoisture();
  float returnVal = (val / 1024) * 100;
  lastSoilPercentage = returnVal;
  return returnVal;
}

// Returns the last read soil moisture percentage as a string with % appended, reading the value if it isn't defined yet
String readSoilMoisturePercentS()
{
  if (lastSoilPercentage != 0)
  {
    return String(lastSoilPercentage) + F(" %");
  }
  else
  {
    return String(readSoilMoisturePercent()) + F(" %");
  }
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Switch the input of the analog board to the ldr
void switchAnalogToLDR()
{
  analogState = LOW;
  digitalWrite(ANALOG_SELECT_PIN, analogState);
}

// Switch the input of the analog board to the moisture sensor
void switchAnalogToMoisture()
{
  analogState = HIGH;
  digitalWrite(ANALOG_SELECT_PIN, analogState);
  // Give the soil moisture sensor some time to stabilize, also give the nodeMCU some time to do WiFi maintanance.
  //delay(100);
}
/// END OF INTERNAL FUNCTIONS ///
//
