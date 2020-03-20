///
/// OLED Control
///

//
/// EXTERNAL FUNCTIONS ///
void printOLEDBME()
{
  display.clear();
  printOLEDLine(0, "Environmental data:");
  drawTopLine();
  printOLEDKeyValuePair(1, F("Temperature: "), getTemperatureString());
  printOLEDKeyValuePair(2, F("Pressure: "), getPressureString());
  printOLEDKeyValuePair(3, F("Altitude: "), getAltitudeString());
  printOLEDKeyValuePair(4, F("Humidity: "), getHumidityString());
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
void printOLEDLine(int l, String s)
{
  int line = (10 * l) + l;
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, line, s);
}

void printOLEDKeyValuePair(int l, String s, String v)
{
  int line = (10 * l) + l;
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, line, s);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, line, v);
}

void drawTopLine()
{
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawHorizontalLine(0, 11, 128);
}
/// END OF INTERNAL FUNCTIONS ///
//
