//
/// LIBRARIES ///
#include <Wire.h>            // I2C library
#include "SSD1306Wire.h"     // OLED display library
#include <Adafruit_BME280.h> // BME280 library
#include <Adafruit_Sensor.h> // BME280 support library
#include <Servo.h>           // Servo library
#include <ESP8266WiFi.h>     // WiFi library
#include <PubSubClient.h>    // MQTT library
/// END OF LIBRARIES ///
//

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
const char* topicWater = "infob3it/107/WaterPlant";                 // Topic for plant watering
const char* topicSensors = "infob3it/107/ReadSensors";              // Topic for reading all sensors
const char* topicTemperature = "infob3it/107/Sensors/Temperature";  // Topic for the temperature   (in °C)
const char* topicHumidity = "infob3it/107/Sensors/Humidity";        // Topic for the humidity      (in %)
const char* topicSoilMoisture = "infob3it/107/Sensors/Soil";        // Topic for the soil moisture (in %)
const char* topicLight = "infob3it/107/Sensors/Light";              // Topic for the light level   (in %)
const char* topicPressure = "infob3it/107/Sensors/Pressure";        // Topic for the pressure      (in HPa)

// MQTT auto publish delay
const unsigned long mqttDelay = 5000;
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// MQTT last auto publish time
unsigned long mqttLastPubTime = 0;
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
  printOLEDBME();
  handleServo();
  handleMQTT();
  display.display();
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
