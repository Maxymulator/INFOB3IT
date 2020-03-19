///
/// WiFi Control
///

//
/// CONSTANTS ///
const char* ssid = "...."; // Fill in your ssid credentials here
const char* password = "...."; // Fill in your password here
/// END OF CONSTANTS ///
//

//
/// EXTERNAL FUNCTIONS ///
// Start the WiFi connections
void initWiFi()
{
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }

  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.print(F("NodeMCU IP address: "));
  Serial.println(WiFi.localIP());
}
/// END OF EXTERNAL FUNCTIONS ///
//
