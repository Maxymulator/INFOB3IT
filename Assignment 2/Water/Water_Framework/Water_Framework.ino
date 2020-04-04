//
/// LIBRARIES ///
#include <Servo.h>           // Servo library
#include <ESP8266WiFi.h>     // WiFi library
#include <PubSubClient.h>    // MQTT library
/// END OF LIBRARIES ///
//

void publishMQTT(const char* topic, char* payload, bool retain = false);
void publishMQTT(const char* topic, float payload, bool retain = false);
void publishMQTT(const char* topic, int payload, bool retain = false);

//
/// CONSTANTS ///
// The servo is connected to pin D2
const int SERVO_PIN = D5;

// Servo setup
Servo servo;

// WiFi setup
WiFiClient wifiClient;

// MQTT client setup
PubSubClient mqttClient(wifiClient);

// MQTT topics
const char* topicWater        = "infob3it/107/Water/WaterPlant";          // Topic for plant watering
const char* topicStatus       = "infob3it/107/Water/Status";              // Topic for the current status of this client
const char* topicWaterDur     = "infob3it/107/Water/WaterDuration";       // Topic for the duration of watering the plant
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// The duration of watering the plant;
int wateringDuration = 5000;
/// END OF VARIABLES ///
//

//
/// MAIN FUNCTIONS ///
void setup() {
  // put your setup code here, to run once:
  // Initialize the serial monitor
  Serial.begin(115200);

  // Initialize the pins
  pinMode(SERVO_PIN, OUTPUT);
  
  // Servo initialization
  servo.attach(SERVO_PIN);
  servo.write(0);
  
  // WiFi initialization
  initWiFi();

  // MQTT initialization
  initMQTT();

  // Random seed initialization
  randomSeed(micros());
}

void loop() {
  // put your main code here, to run repeatedly:
  handleServo();
  handleMQTT();
}
/// END OF MAIN FUNCTIONS ///
//
