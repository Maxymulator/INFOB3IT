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
const int SERVO_PIN = D2;

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
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///

/// END OF VARIABLES ///
//

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
}

void loop() {
  // put your main code here, to run repeatedly:
  printOLEDBME();
  handleServo();
  display.display();
}
