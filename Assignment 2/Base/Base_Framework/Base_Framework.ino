//
/// LIBRARIES ///
#include <ESP8266WiFi.h>     // WiFi library
#include <PubSubClient.h>    // MQTT library
/// END OF LIBRARIES ///
//

// Define function prototypes to LEFT_PMWble the default value for the retain flag
void publishMQTT(const char* topic, char* payload, bool retain = false);
void publishMQTT(const char* topic, float payload, bool retain = false);
void publishMQTT(const char* topic, int payload, bool retain = false);

//
/// CONSTANTS ///
// PWM for the left motor
int LEFT_PMW = D1;

// First input for the left motor
int LEFT_1 = D2;

// Second input for the left motor
int LEFT_2 = D3;

// PMW for the right motor
int RIGHT_PMW = D7;

// First input for the right motor
int RIGHT_1 = D5;

// Second input for the right motor
int RIGHT_2 = D6;

// Pin to select which LDR to read
int LDR_SEL = D4;

// WiFi setup
WiFiClient wifiClient;

// MQTT client setup
PubSubClient mqttClient(wifiClient);

// The driving state of the vehicle
enum driveState
{
  front,
  back,
  left,
  right,
  still,
};

// The driving mode of the vehicle
enum drivingMode
{
  automatic,
  manual,
};

// The current driving mode of the vehicle
drivingMode curDrivingMode = manual;
/// END OF CONSTANTS///
//

//
/// MAIN FUNCTIONS ///
void setup()
{
  // Set all the motor control pins to outputs
  pinMode(LEFT_PMW, OUTPUT);
  pinMode(LEFT_1, OUTPUT);
  pinMode(LEFT_2, OUTPUT);
  pinMode(RIGHT_PMW, OUTPUT);
  pinMode(RIGHT_1, OUTPUT);
  pinMode(RIGHT_2, OUTPUT);
  pinMode(LDR_SEL, OUTPUT);

  // Initialize the serial monitor
  Serial.begin(115200);

  // WiFi initialization
  initWiFi();

  // MQTT initialization
  initMQTT();
}

void loop()
{
  // put your main code here, to run repeatedly:
  handleMQTT();
  if(curDrivingMode == automatic)
  {
    handleAutoDriving();
  }
}
/// END OF MAIN FUNCTIONS ///
//
