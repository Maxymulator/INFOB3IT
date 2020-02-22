///
/// Temperature control
///
/// GetTemperature() > returns the current temperature in Celcius
///


/// EXTERNAL FUNCTIONS ///
// Return the current temperature
float GetTemperature()
{
  // get the temperatures on the bus
  tempSensor.requestTemperatures();

  // request the temperature in Celcius
  float curTemp = tempSensor.getTempCByIndex(0);

  // Check if the reading was succesful
  if(curTemp != DEVICE_DISCONNECTED_C)
  {
    return curTemp;
  }
  else
  {
    return 1000; // return an arbitrarily large number to signify an error
  }
}
/// END OF EXTERNAL FUNCTIONS ///
