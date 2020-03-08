///
/// BME280 sensor control
///
/// getTemperature() -> Reads the current temperature and returns the float value
/// getTemperatureString() -> Reads the temperature and returns it as string with the Celcius sign appended.
/// getPressure() -> Reads the pressure level and returns the float value
/// getPressureString() -> Reads the pressure level and returns it as a string with the hPa sign appended
/// getAltitude() -> Reads the approximated altitude and returns the float value
/// getAltitudeString() -> Reads the approximated altitude and returns it as a string with the meter sign appended
/// getHumidity() -> Reads the humidity and returns the float value
/// getHumidityString() -> Reads the humidity and returns it as a string with the percent sign appended
///

//
/// EXTERNAL FUNCTIONS ///
// Reads the current temperature and returns the float value
float getTemperature()
{
  return bme.readTemperature();
}

// Reads the temperature and returns it as string with the Celcius sign appended
String getTemperatureString()
{
  return (String(getTemperature()) + F(" °C"));
}

// Reads the pressure level and returns the float value
float getPressure()
{
  return (bme.readPressure() / 100.0F);
}

// Reads the pressure level and returns it as a string with the hectopascal sign appended
String getPressureString()
{
  return (String(getPressure()) + F(" hPa"));
}

// Reads the approximated altitude and returns the float value
float getAltitude()
{
  return bme.readAltitude(SEALEVELPRESSURE_HPA);
}

// Reads the approximated altitude and returns it as a string with the meter sign appended
String getAltitudeString()
{
  return (String(getAltitude) + F(" m"));
}

// Reads the humidity and returns the float value
float getHumidity()
{
  return bme.readHumidity();
}

// Reads the humidity and returns it as a string with the percent sign appended
String getHumidityString()
{
  return (String(getHumidity()) + F(" %"));
}
/// END OF EXTERNAL FUNCTIONS ///
//
