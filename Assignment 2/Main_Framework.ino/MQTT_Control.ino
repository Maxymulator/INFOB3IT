///
/// MQTT Control
///

//
/// CONSTANTS ///
// The mqtt server
const char* mqtt_server = "mqtt.uu.nl";

// The mqtt credentials
#define MQTT_USERNAME "student107"
#define MQTT_PASSWORD "W42Ktgvj"
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
// Initialize the MQTT functions
void initMQTT()
{
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
}

// Handle the MQTT functions
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
void publishMQTT(const char* topic, char* payload)
{
  Serial.print("Publishing [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(payload);
  mqttClient.publish(topic, payload);
}
void publishMQTT(const char* topic, int payload)
{
  Serial.print("Publishing [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(payload);
  mqttClient.publish(topic, (byte*)payload, 4, true);
}
void publishMQTT(const char* topic, float payload)
{
  Serial.print("Publishing [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(payload);
  String messageS = String(payload);
  char message[50];
  messageS.toCharArray(message, messageS.length() + 1);
  mqttClient.publish(topic, message);
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Re-establish the MQTT connections
bool reconnectMQTT()
{
  String clientID = "ESP8266_Plant_107";
  Serial.println("Attempting MQTT connection");
  if (mqttClient.connect(clientID.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
  {
    Serial.println("MQTT connected");
    subscribeMQTT();
  }
  return mqttClient.connected();
}

// Subscribe to needed topics
void subscribeMQTT()
{
  mqttClient.subscribe(topicWater);
  mqttClient.subscribe(topicSensors);
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
  else if (strcmp(topic, topicWater) == 0)
  {
    handleWaterCommand(payload);
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

// Handle watering command
void handleWaterCommand(byte* payload)
{
  if ((bool)(payload[0] - 48))
  {
    activateServo();
  }
}
/// END OF INTERNAL FUNCTIONS ///
//
