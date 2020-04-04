///
/// MQTT Control
///
/// initMQTT() -> Initialize the MQTT functionality
/// handleMQTT() -> Handle the MQTT functionality
/// publishMQTT() -> Publish a given message on a given subject, overloaded for string, int, float
/// getMQTTStatus() -> Returns the status of the mqtt connection
/// getPlantStats() -> Returns the status of this plant
/// 

//
/// CONSTANTS ///
// The mqtt server
const char* mqtt_server = "mqtt.uu.nl";

// The mqtt credentials
#define MQTT_USERNAME "student107"
#define MQTT_PASSWORD "W42Ktgvj"

// LWT message
const char* lwtMessage = "Offline";
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
unsigned long mqttLastReconnectAttempt = 0;
unsigned long mqttReconnectDelay = 5000;
/// END OF VARIABLES ///
//

//
/// EXTERNAL FUNCTIONS ///
// Initialize the MQTT functionality
void initMQTT()
{
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
}

// Handle the MQTT functionality
void handleMQTT()
{
  if (!mqttClient.connected())
  {
    if (millis() - mqttLastReconnectAttempt > mqttReconnectDelay)
    {
      mqttLastReconnectAttempt = millis();
      if (reconnectMQTT())
      {
        mqttLastReconnectAttempt = 0;
      }
    }
  }
  else
  {
    mqttClient.loop();
  }
}

// Publish a given message on a given subject
// Overloaded for string, int, float
void publishMQTT(const char* topic, char* payload, bool retain)
{
  Serial.print("Publishing [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(payload);
  mqttClient.publish(topic, payload, retain);
}
void publishMQTT(const char* topic, int payload, bool retain)
{
  Serial.print("Publishing [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(payload);
  mqttClient.publish(topic, (byte*)payload, 4, retain);
}
void publishMQTT(const char* topic, float payload, bool retain)
{
  Serial.print("Publishing [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(payload);
  String messageS = String(payload);
  char message[50];
  messageS.toCharArray(message, messageS.length() + 1);
  mqttClient.publish(topic, message, retain);
}

// Returns the status of the mqtt connection
String getMQTTStatus()
{
  if(mqttClient.connected())
  {
    return "Connected";
  }
  else
  {
    return "Not Connected";
  }
}

// Returns the status of this plant
String getPlantStatus()
{
  if(mqttClient.connected())
  {
    return "Online";
  }
  else
  {
    return "Offline";
  }
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Re-establish the MQTT connections
bool reconnectMQTT()
{
  String clientID = "107_Plant";
  Serial.println("Attempting MQTT connection");
  if (mqttClient.connect( clientID.c_str() // Client id
                        , MQTT_USERNAME    // MQTT username
                        , MQTT_PASSWORD    // MQTT password
                        , topicPlantStatus // Last will topic
                        , 1                // Last will QoS
                        , 1                // Last will retain flag (set to true)
                        , lwtMessage       // Last will message
                        , false))          // Clean session flag
  {
    Serial.println("MQTT connected");
    // Subscribe to your topics
    subscribeMQTT();
    // Publish that you are online
    publishMQTT(topicPlantStatus, (char*)"Online", true);
  }
  return mqttClient.connected();
}

// Subscribe to needed topics
void subscribeMQTT()
{
  mqttClient.subscribe(topicSensors, 1);
  mqttClient.subscribe(topicWaterStatus, 1);
  mqttClient.subscribe(topicBaseStatus, 1);
  mqttClient.subscribe(topicMode, 1);
  mqttClient.subscribe(topicWaterTime, 1);
  mqttClient.subscribe(topicWaterDur, 1);
}

// Handle incoming messages
void callback(char* topic, byte* payload, unsigned int len)
{
  //FOR TESTING//
  Serial.print(F("Message arrived ["));
  Serial.print(topic);
  Serial.print(F("]: "));
  for (int i = 0; i < len; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  //END OF TESTING//
  if (strcmp(topic, topicSensors) == 0)
  {
    handleSensorCommand(payload);
  }
  else if (strcmp(topic, topicWaterTime) == 0)
  {
    handleWaterTimeCommand(payload, len);
  }
  else if (strcmp(topic, topicWaterStatus) == 0)
  {
    handleWaterStatusCommand(payload, len);
  }
  else if (strcmp(topic, topicBaseStatus) == 0)
  {
    handleBaseStatusCommand(payload, len);
  }
  else if (strcmp(topic, topicWaterDur) == 0)
  {
    handleWaterDurCommand(payload, len);
  }
}

// Handle sensor command
void handleSensorCommand(byte* payload)
{
  if ((bool)(payload[0] - 48))
  {
    readAndPublishSensors();
  }
}

// Handle water time command
void handleWaterTimeCommand(byte* payload, unsigned int len)
{
  lastWaterTime = "";
  for (int i = 0; i < len; i++) 
  {
    lastWaterTime += (char)payload[i];
  }
}

// Handle water station status command
void handleWaterStatusCommand(byte* payload, unsigned int len)
{
  waterStatus = "";
  for (int i = 0; i < len; i++) 
  {
    waterStatus += (char)payload[i];
  }
}

// Handle driving base status command
void handleBaseStatusCommand(byte* payload, unsigned int len)
{
  drivingBaseStatus = "";
  for (int i = 0; i < len; i++) 
  {
    drivingBaseStatus += (char)payload[i];
  }
}

// Handle water time command
void handleWaterDurCommand(byte* payload, unsigned int len)
{
  String valS = "";
  for (int i = 0; i < len; i++) 
  {
    valS += (char)payload[i];
  }
  Serial.print(String(valS));
  Serial.print(", ");
  int val = valS.toInt();
  Serial.print(val);
  Serial.print(", ");
  wateringDuration = val * 1000;
  Serial.println(wateringDuration);
}
/// END OF INTERNAL FUNCTIONS ///
//
