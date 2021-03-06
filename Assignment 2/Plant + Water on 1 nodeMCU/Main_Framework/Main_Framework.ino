//
/// LIBRARIES ///
#include <Wire.h>            // I2C library
#include "SSD1306Wire.h"     // OLED display library
#include <Adafruit_BME280.h> // BME280 library
#include <Adafruit_Sensor.h> // BME280 support library
#include <Servo.h>           // Servo library
#include <ESP8266WiFi.h>     // WiFi library
#include <PubSubClient.h>    // MQTT library
#include "images.h"          // Include the images
/// END OF LIBRARIES ///
//

void publishMQTT(const char* topic, char* payload, bool retain = false);
void publishMQTT(const char* topic, float payload, bool retain = false);
void publishMQTT(const char* topic, int payload, bool retain = false);

//
/// CONSTANTS ///
// The selector of the analog board is plugged in to pin D1
const int ANALOG_SELECT_PIN = D1;

// The analog input pin
const int ANALOG_INPUT = A0;

// The servo is connected to pin D2
const int SERVO_PIN = D5;

// BME280 setup
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1025.80) // zero'd for Tilburg NB
Adafruit_BME280 bme;

// OLED display setup
SSD1306Wire display(0x3c, D3, D4);

// Servo setup
Servo servo;

// WiFi setup
WiFiClient wifiClient;

// MQTT client setup
PubSubClient mqttClient(wifiClient);

// MQTT topics
const char* topicWater        = "infob3it/107/Plant/WaterPlant";          // Topic for plant watering
const char* topicSensors      = "infob3it/107/Plant/ReadSensors";         // Topic for reading all sensors
const char* topicMode         = "infob3it/107/Plant/Mode";                // Topic for the current mode of the plant: auto/ manual
const char* topicStatus       = "infob3it/107/Plant/Status";              // Topic for the current status of this client
const char* topicWaterTime    = "infob3it/107/Plant/LastWaterTimer";      // Topic for the timer since the last watering of the plant
const char* topicWaterDur     = "infob3it/107/Plant/WaterDuration";       // Topic for the duration of watering the plant
const char* topicTemperature  = "infob3it/107/Plant/Sensors/Temperature"; // Topic for the temperature   (in °C)
const char* topicHumidity     = "infob3it/107/Plant/Sensors/Humidity";    // Topic for the humidity      (in %)
const char* topicSoilMoisture = "infob3it/107/Plant/Sensors/Soil";        // Topic for the soil moisture (in %)
const char* topicLight        = "infob3it/107/Plant/Sensors/Light";       // Topic for the light level   (in %)
const char* topicPressure     = "infob3it/107/Plant/Sensors/Pressure";    // Topic for the pressure      (in HPa)

// MQTT auto publish delay
const unsigned long mqttDelay = 5000;
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// MQTT last auto publish time
unsigned long mqttLastPubTime = 0;

// The duration of watering the plant;
int wateringDuration = 5000;

// Time since the plant was last watered, gotten through mqtt
String lastWaterTime = "";
/// END OF VARIABLES ///
//

//
/// MAIN FUNCTIONS ///
void setup() {
  // put your setup code here, to run once:
  // Initialize the serial monitor
  Serial.begin(115200);

  // Initialize the pins
  pinMode(ANALOG_SELECT_PIN, OUTPUT);
  pinMode(ANALOG_INPUT, INPUT);

  // OLED display initialization
  display.init();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.clear();
  
  // BME280 initialization
  bme.begin();

  // Servo initialization
  servo.attach(SERVO_PIN);
  servo.write(0);
  
  // WiFi initialization
  initWiFi();

  // MQTT initialization
  initMQTT();

  // Random seed initialization
  randomSeed(micros());

  // Set the analog input to the ldr, to avoid corrosion
  switchAnalogToLDR();
  //switchAnalogToMoisture();
}

void loop() {
  // put your main code here, to run repeatedly:
  handleOLED();
  handleServo();
  handleMQTT();
  //Serial.println(String(readSoilMoisture()) + ": " + String(readSoilMoisturePercent()));

  // Publish sensor data once every 5 seconds
  if( millis() - mqttLastPubTime > mqttDelay)
  {
    readAndPublishSensors();
    mqttLastPubTime = millis();
  }
}
/// END OF MAIN FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
void readAndPublishSensors()
{
  // Read all sensor values
  // Read the ldr value
  float ldrVal = readLDRPercent();
  // Activate the soil moisture sensor, giving it some time to acclimate
  switchAnalogToMoisture();
  // Read the temperature
  float temperatureVal = getTemperature();
  // Read the pressure
  float pressureVal = getPressure();
  // Read the humidity
  float humidityVal = getHumidity();
  // Read the soil moisture level
  float soilVal = readSoilMoisturePercent();
  // Turn the soil moisture sensor off to preserve it
  switchAnalogToLDR();

  // Publish all values
  // Publish light percentage
  publishMQTT(topicLight, ldrVal);
  // Publish temperature
  publishMQTT(topicTemperature, temperatureVal);
  // Publish pressure
  publishMQTT(topicPressure, pressureVal);
  // Publish humidity
  publishMQTT(topicHumidity, humidityVal);
  // Publish soil moisture
  publishMQTT(topicSoilMoisture, soilVal);
}
/// END OF INTERNAL FUNCTIONS ///
//
