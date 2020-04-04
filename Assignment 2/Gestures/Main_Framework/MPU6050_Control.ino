///
/// MPU6050 Control
///

//
/// CONSTANTS ///
// The amount of calibration runs
const int calibAmount = 10;
/// END OF CONSTANTS ///
//

//
/// VARIABLES ///

/// END OF VARIABLES ///
//

//
/// EXTERNAL FUNCTIONS ///
// Initialize the MPU unit
void initMPU()
{
  accelgyro.initialize();
  accelgyro.CalibrateAccel(calibAmount);
  accelgyro.CalibrateGyro(calibAmount);
} // initMPU()

// read raw accel/gyro measurements from device
void readMPU()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
} // readMPU()

// Quick and dirty function to print the MPU values to the serial port
void printMPU()
{
  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);
} // printMPU()
/// END OF EXTERNAL FUNCTIONS ///
//
