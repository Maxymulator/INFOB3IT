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

// LWT message
const char* lwtMessage = "Offline";

// MQTT topics
const char* topicMode    = "infob3it/107/Base/Mode";          // Topic for the current mode of the base: auto/ manual
const char* topicStatus  = "infob3it/107/Base/Status";        // Topic for the current status of this client
const char* topicSpeed   = "infob3it/107/Base/Speed";         // Topic for the driving speed
const char* topicForward = "infob3it/107/Base/Drive/Forward"; // Topic for driving forward
const char* topicBack    = "infob3it/107/Base/Drive/Back";    // Topic for driving backward
const char* topicLeft    = "infob3it/107/Base/Drive/Left";    // Topic for turning left
const char* topicRight   = "infob3it/107/Base/Drive/Right";   // Topic for turning right
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
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Re-establish the MQTT connections
bool reconnectMQTT()
{
  String clientID = "107_Base";
  Serial.println("Attempting MQTT connection");
  if (mqttClient.connect( clientID.c_str() // Client id
                          , MQTT_USERNAME    // MQTT username
                          , MQTT_PASSWORD    // MQTT password
                          , topicStatus      // Last will topic
                          , 1                // Last will QoS
                          , 1                // Last will retain flag (set to true)
                          , lwtMessage       // Last will message
                          , false))          // Clean session flag
  {
    Serial.println("MQTT connected");
    // Subscribe to your topics
    subscribeMQTT();
    // Publish that you are online
    publishMQTT(topicStatus, (char*)"Online", true);
  }
  return mqttClient.connected();
}

// Subscribe to needed topics
void subscribeMQTT()
{
  mqttClient.subscribe(topicMode, 1);
  mqttClient.subscribe(topicSpeed, 1);
  mqttClient.subscribe(topicForward, 1);
  mqttClient.subscribe(topicBack, 1);
  mqttClient.subscribe(topicLeft, 1);
  mqttClient.subscribe(topicRight, 1);
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

  if (strcmp(topic, topicMode) == 0) // switch the mode from automatic to manual and vice versa
  {
    handleModeCommand(payload);
  }
  else if(strcmp(topic, topicSpeed) == 0) // change the driving speed
  {
    handleSpeedCommand(payload, len);
  }
  else if (curDrivingMode == manual) // check if we are driving manually, otherwise ignore driving commands
  {
    if (strcmp(topic, topicForward) == 0) // drive forwards
    {
      handleForwardCommand(payload);
    }
    else if (strcmp(topic, topicBack) == 0) // drive backwards
    {
      handleBackCommand(payload);
    }
    else if (strcmp(topic, topicLeft) == 0) // turn left
    {
      handleLeftCommand(payload);
    }
    else if (strcmp(topic, topicRight) == 0) // turn right
    {
      handleRightCommand(payload);
    }
  }
}

// Handle mode change command
void handleModeCommand(byte* payload)
{
  // 1 is automatic, 0 is manual
  if ((bool)(payload[0] - 48)) 
  {
    curDrivingMode = automatic;
  }
  else
  {
    curDrivingMode = manual;
  }
}

// handle speed command
void handleSpeedCommand(byte* payload, int len)
{
  int newSpeed = 0;
  for(int i = 0; i < len; i++)
  {
    newSpeed = (newSpeed * 10) + ((int)payload[i] - 48);
  }
  Serial.println(newSpeed);
  setMotorSpeed(newSpeed);
}

// Handle driving forward command
void handleForwardCommand(byte* payload)
{
  // 1 is drive forward, 0 is stop
  if ((bool)(payload[0] - 48))
  {
    driveForward();
  }
  else
  {
    driveStop();
  }
}

// Handle driving backward command
void handleBackCommand(byte* payload)
{
  if ((bool)(payload[0] - 48))
  {
    driveBack();
  }
  else
  {
    driveStop();
  }
}

// Handle tunring left command
void handleLeftCommand(byte* payload)
{
  if ((bool)(payload[0] - 48))
  {
    turnLeft();
  }
  else
  {
    driveStop();
  }

}// Handle turning right command
void handleRightCommand(byte* payload)
{
  if ((bool)(payload[0] - 48))
  {
    turnRight();
  }
  else
  {
    driveStop();
  }
}
/// END OF INTERNAL FUNCTIONS ///
//
