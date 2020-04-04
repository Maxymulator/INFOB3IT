///
/// OLED Control
///
/// initOLED() -> initialize the OLED screen
/// printOLEDWiFiConnecting(int) -> Print the "WiFi Connecting" screen
/// printOLEDWiFiConnected() -> Print the "WiFi Connected!" screen
/// handleOLED() -> Handles all the OLED states and prints them
///

//
/// CONSTANTS ///
// The time between switching OLED screens
unsigned long oledDelay = 5000;

// The amount of states in the OLED screen
int oledStateCount = 4;
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
// initialize the OLED screen
void initOLED()
{
  display.init();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.clear();
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
  else if (oledState == 3)
  {
    printOLEDMQTT();
  }
  display.display();
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
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

// Print the connection status screen
void printOLEDStatus()
{
  printOLEDLine(0, "Connection data:");
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

// Print the other MQTT device status screen
void printOLEDMQTT()
{
  printOLEDLine(0, "MQTT devices data:");
  drawTopLine();
  printOLEDKeyValuePair(1, F("Plant Status: "), getPlantStatus());
  printOLEDKeyValuePair(2, F("Watering Status: "), waterStatus);
  printOLEDKeyValuePair(3, F("Base Status: "), drivingBaseStatus);
}

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
