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

float readLDRPercent()
{
  float val = (float)readLDR();
  float returnVal = (val / 1024) * 100;
  return returnVal;
}

// Reads the value from the soilmoisture sensor and returns it
int readSoilMoisture()
{
  if(analogState == LOW)
  {
    switchAnalogToMoisture();
  }
  return analogRead(ANALOG_INPUT);
}

float readSoilMoisturePercent()
{
  float val = readSoilMoisture();
  float returnVal = (val / 1024) * 100;
  return returnVal;
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
