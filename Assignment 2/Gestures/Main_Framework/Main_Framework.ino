///
/// Gesture recognition
///

//
/// LIBRARIES ///
#include "I2Cdev.h"  // I2C protocol library
#include "MPU6050.h" // MPU6050 library
#include "Wire.h"    // OneWire protocol library
/// END OF LIBRARIES ///
//

//
/// CONSTANTS ///
// MPU6050 setup
MPU6050 accelgyro;

// The time each subcommand stays active
unsigned long subCommandTimer = 1000;
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///
// accelometer values
int16_t ax, ay, az;
// gyroscope values
int16_t gx, gy, gz;


// All command activator
bool commandActivator = false;

// All command activator timer
unsigned long commandActivatorTime = 0;

// Watering command subcommands
bool wateringCommandInit = false;
bool wateringCommandMotion = false;
bool wateringCommandExecute = false;

// Watering command timers
unsigned long wateringInitTime = 0;
unsigned long wateringMotionTime = 0;

// Sensor command subcommands
bool sensorCommandInit = false;
bool sensorCommandMotion = false;
bool sensorCommandExecute = false;

// Sensor command timers
unsigned long sensorInitTime = 0;
unsigned long sensorMotionTime = 0;
/// END OF VARIABLES ///
//

//
/// MAIN FUNCTIONS ///
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Wire.begin();
  initMPU();
  Serial.println();
} // setup()

void loop() {
  // put your main code here, to run repeatedly:
  // Check if an execute command was given
  if (wateringCommandExecute)
  {
    // Make sure it is only written once
    wateringCommandExecute = false;
    // Send the watering command
    Serial.println(F("w"));
  }
  else if (sensorCommandExecute)
  {
    // Make sure it is only written once
    sensorCommandExecute = false;
    // Send the read sensors command
    Serial.println(F("r"));
  }
  else
  {
    // Check if any timer has expired
    checkTimers();

    // Read the MPU values
    readMPU();

    // Check if the command activator is given
    checkActivator();

    // Check if any sub command is given
    checkWaterSubCommands();
    checkSensorSubCommands();
  }
  //printMPU();
} // loop()
/// END OF MAIN FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Checks all timers to see if they havent expired
void checkTimers()
{
  unsigned long curTime = millis();
  // check the command activator timer
  if (curTime - commandActivatorTime > subCommandTimer && !wateringCommandInit && !sensorCommandInit)
  {
    commandActivator = false;
  }

  // check the watering init timer
  if (curTime - wateringInitTime > subCommandTimer)
  {
    wateringCommandInit = false;
  }

  // check the watering motion timer
  if (curTime - wateringMotionTime > subCommandTimer)
  {
    wateringCommandMotion = false;
  }

  // check the sensor init timer
  if (curTime - sensorInitTime > subCommandTimer)
  {
    sensorCommandInit = false;
  }

  // check the sensor motion timer
  if (curTime - sensorMotionTime > subCommandTimer)
  {
    sensorCommandMotion = false;
  }
} // checkTimers()

// Check if the commands are activated
void checkActivator()
{
  // a hand at hip level, fingers pointed parallel to the ground, palm down
  if (ax > - 3000 && ax < 3000 // fingers pointed parallel to the ground
      && az > 15000 // palm pointed down
      && gx > -500 && gx < 500 && gy > -500 && gy < 500 && gz > -500 && gz < 500) // still
  {
    commandActivator = true;
    //Serial.println("command activator");
    commandActivatorTime = millis();
  }
} // checkActivator()

// Check if any watering subcommands were given
void checkWaterSubCommands()
{
  // check for the watering init command
  // a raised hand at shoulder level, fingers pointed upwards
  if (commandActivator && ax > 15000)
  {
    wateringCommandInit = true;
    //Serial.println("water init");
    wateringInitTime = millis();
  }
  // check for the watering motion command
  // the hand moving right in a semi circle with a decent constant speed, after the watering init command was given
  if (wateringCommandInit && gz < -30000)
  {
    wateringCommandInit = false; // make sure this only fires once per command cycle
    wateringCommandMotion = true;
    //Serial.println("water motion");
    wateringMotionTime = millis();
  }
  // check for the watering execute command
  // a lowered hand at hip level, with the fingers pointed downwards, after the watering motion command was given
  if (wateringCommandMotion && ax < - 10000)
  {
    wateringCommandMotion = false; // make sure this only fires once per command cycle
    wateringCommandExecute = true;
    //Serial.println("water execute");
  }
} // checkWaterSubCommands()

// Check if any sensor reading subcommands were given
void checkSensorSubCommands()
{
  // Check for the sensor init command
  // a level hand at hip level, fingers pointed parallel to the ground, palm pointed upwards
  if (commandActivator && ax > -3000 && ax < 3000 && az < -15000)
  {
    sensorCommandInit = true;
    //Serial.println("sensor init");
    sensorInitTime = millis();
  }
  // check for the sensor motion command
  // hand moving upwards, palm pointed upwards
  if (sensorCommandInit && az < -15000 && gy > 10000)
  {
    sensorCommandInit = false; // make sure this only fires once per command cycle
    sensorCommandMotion = true;
    //Serial.println("sensor motion");
    sensorMotionTime = millis();
  }
  // check for the sensor execute command
  // hand stops moving at shoulder level, fingers pointed upwards
  if (sensorCommandMotion && ax > 15000 && gy > -3000 && gy < 3000)
  {
    sensorCommandMotion = false; // make sure this only fires once per command cycle
    sensorCommandExecute = true;
    //Serial.println("sensor execute");
  }
} // checkSensorSubCommands()
/// END OF INTERNAL FUNCTIONS ///
//
