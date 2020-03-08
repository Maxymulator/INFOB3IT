//
/// LIBRARIES ///
#include <Wire.h>            // I2C library
#include "SSD1306Wire.h"     // OLED display
#include <Adafruit_Sensor.h> // Support library for BME280
#include <Adafruit_BME280.h> // Library for BME280
/// END OF LIBRARIES ///
//

//
/// CONSTANTS ///
// BME280 setup
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

// OLED display setup
SSD1306Wire display(0x3c, D3, D4);

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

  // OLED display initialization
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  // BME280 initialization
  bme.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
