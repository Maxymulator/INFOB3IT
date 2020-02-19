/// LIBARIES ///

/// END OF LIBRARIES ///

/// CONSTANTS ///
// The midway point for PMW
const int PMW_MID = 128;

// The LEDs are plugged in to pin 9
const int LED_PIN = 9;

// The buttons are plugged in to pin 5
const int BUTTON_PIN = A5;
// <END OF CONSTANTS ///

/// MAIN FUNCTIONS ///
void setup()
{
  // put your setup code here, to run once:
  // Pin mode setup:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Other setup:
  // Turn on the power LED:
  OnLEDGrn();

  // Turn on the serial monitor on port 9600
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  unsigned long curMillis = millis();
  if (curMillis % 1000 < 10)
  {
    OnLEDYlw();
    OffLEDGrn();
  }
  if (curMillis % 2000 < 10)
  {
    OffLEDYlw();
    OnLEDGrn();
  }

  Serial.println(analogRead(BUTTON_PIN));
}
/// END OF MAIN FUNCTIONS ///
