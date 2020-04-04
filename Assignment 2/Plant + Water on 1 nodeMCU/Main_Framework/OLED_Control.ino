///
/// OLED Control
///

//
/// CONSTANTS ///
// The time between switching OLED screens
unsigned long oledDelay = 5000;

// The amount of states in the OLED screen
int oledStateCount = 3;
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// The screen of the OLED to currenty display
int oledState = 0;

// The previous time the OLED screen switched state
unsigned long oledPrevSwitch = 0;
/// END OF VARIABLES ///
//

//
/// EXTERNAL FUNCTIONS ///
// Print environmental data to the OLED screen
void printOLEDEnvironment()
{
  printOLEDLine(0, "Environmental data:");
  drawTopLine();
  printOLEDKeyValuePair(1, F("Temperature: "), getTemperatureString());
  printOLEDKeyValuePair(2, F("Pressure: "), getPressureString());
  //printOLEDKeyValuePair(3, F("Altitude: "), getAltitudeString());
  printOLEDKeyValuePair(3, F("Humidity: "), getHumidityString());
  printOLEDKeyValuePair(4, F("Lightlevel: "), readLDRPercentS());
}

// Print the "WiFi Connecting" screen
void printOLEDWiFiConnecting(int count)
{
  display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  String s = "Connecting";
  for (int i = 0; i < count; i++)
  {
    s += ".";
  }
  display.drawString(25, 50, s);
}

// Print the "WiFi Connected!" screen
void printOLEDWiFiConnected()
{
  display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  display.drawString(25, 50, F("Connected!"));
}

// Print the status screen
void printOLEDStatus()
{
  printOLEDLine(0, "Status data:");
  drawTopLine();
  printOLEDKeyValuePair(1, F("WiFi Status: "), getWiFiStatus());
  printOLEDKeyValuePair(2, F("MQTT Status: "), getMQTTStatus());
  printOLEDLine(3, F("WiFi SSID: "));
  printOLEDLine(4, getWiFiSSID());
}

// Print the water data screen
void printOLEDWater()
{
  printOLEDLine(0, "Watering data:");
  drawTopLine();
  printOLEDKeyValuePair(1, F("Soil moisture: "), readSoilMoisturePercentS());
  printOLEDKeyValuePair(2, F("Watering duration: "), String(wateringDuration / 1000) + 's');
  printOLEDLine(3, F("Time since last watering: "));
  printOLEDLine(4, lastWaterTime);
}

// Handles all the OLED states and prints them
void handleOLED()
{
  display.clear();
  if(millis() - oledPrevSwitch > oledDelay)
  {
    updateOLEDState();
    oledPrevSwitch = millis();
  }
  if(oledState == 0)
  {
    printOLEDEnvironment();
  }
  else if (oledState == 1)
  {
    printOLEDStatus();
  }
  else if (oledState == 2)
  {
    printOLEDWater();
  }
  display.display();
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Updates the current OLED state
void updateOLEDState()
{
  oledState += 1;
  if (oledState == oledStateCount)
  {
    oledState = 0;
  }
}

// Print the given string to the given line
void printOLEDLine(int l, String s)
{
  int line = (10 * l) + l;
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, line, s);
}

// Prints the given key value pair to the given line
void printOLEDKeyValuePair(int l, String s, String v)
{
  int line = (10 * l) + l;
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, line, s);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, line, v);
}

// Draws the line seperating the topic and contents
void drawTopLine()
{
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawHorizontalLine(0, 11, 128);
}
/// END OF INTERNAL FUNCTIONS ///
//
