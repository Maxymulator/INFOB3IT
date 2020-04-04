///
/// WiFi Control
///
/// initWiFi() -> Start the WiFi connection
/// getWiFiStatus() -> Returns the status of the WiFi connection
/// getWiFiSSID() -> Return the WiFi ssid
///

//
/// CONSTANTS ///
//const char* ssid = "...."; // Fill in your ssid credentials here
//const char* password = "...."; // Fill in your password here
/// END OF CONSTANTS ///
//

//
/// EXTERNAL FUNCTIONS ///
// Start the WiFi connection
void initWiFi()
{
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  printOLEDWiFiConnecting(0);
  display.display();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.print('.');
    display.clear();
    printOLEDWiFiConnecting(i);
    display.display();
    i += 1;
    if(i > 3)
    {
      i = 0;
    }
    delay(200);
  }
  for (int j = i; j <= 3; j++)
  {
    printOLEDWiFiConnecting(j);
    display.display();
    delay(200);
  }
  display.clear();
  printOLEDWiFiConnected();
  display.display();
  delay(200);

  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.print(F("NodeMCU IP address: "));
  Serial.println(WiFi.localIP());
}

// Returns the status of the WiFi connection
String getWiFiStatus()
{
  if(WiFi.waitForConnectResult() == WL_CONNECTED)
  {
    return "Connected";
  }
  else
  {
    return "Not Connected";
  }
}

// Return the WiFi ssid
String getWiFiSSID()
{
  return String(ssid);
}
/// END OF EXTERNAL FUNCTIONS ///
//
