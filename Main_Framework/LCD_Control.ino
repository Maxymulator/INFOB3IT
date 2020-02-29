///
/// LCD Control
///
/// PrintLCDTopLine(message) -> clear the top line and print the given message
/// PrintLCDBottonLine(message) -> clear the bottom line and print the given message
/// ClearLCD() -> clear the LCD screen
///

//
/// EXTERNAL FUNCTIONS ///
// Clear the top line and print the given message on the top line, seperate from the bottom line
// overloaded for String, int, unsigned long, float
void PrintLCDTopLine(String input)
{
  // Pad the string with spaces on the right
  String s = input + EMPTY_LCD_STRING;

  //Print the padded string to the LCD
  PrintLCD(0, s);
}
void PrintLCDTopLine(int input)
{
  String s = input + EMPTY_LCD_STRING;
  PrintLCD(0, s);
}
void PrintLCDTopLine(unsigned long input)
{
  String s = input + EMPTY_LCD_STRING;
  PrintLCD(0, s);
}
void PrintLCDTopLine(float input)
{
  String s = input + EMPTY_LCD_STRING;
  PrintLCD(0, s);
}

// Clear the bottom line and print the given message on the bottom line, seperate from the top line
// overloaded for String, int, unsigned long, float
void PrintLCDBottomLine(String input)
{
  // Pad the string with spaces on the right
  String s = input + EMPTY_LCD_STRING;

  //Print the padded string to the LCD
  PrintLCD(1, s);
}
void PrintLCDBottomLine(int input)
{
  String s = input + EMPTY_LCD_STRING;
  PrintLCD(1, s);
}
void PrintLCDBottomLine(unsigned long input)
{
  String s = input + EMPTY_LCD_STRING;
  PrintLCD(1, s);
}
void PrintLCDBottomLine(float input)
{
  String s = input + EMPTY_LCD_STRING;
  PrintLCD(1, s);
}

// Clears the LCD screen
void ClearLCD()
{
  ClearLCDLine(0);
  ClearLCDLine(1);
}
/// END OF EXTERNAL FUNCTIONS ///
//

//
/// INTERNAL FUNCTIONS ///
// Clears the given LCD line without touching the other line
void ClearLCDLine(int line)
{
  lcd.setCursor(0, line);
  lcd.print(EMPTY_LCD_STRING);
}

// Print the given string on the given line -- This assumes the given string is padded
void PrintLCD(int line, String s) 
{
  lcd.setCursor(0,line);
  lcd.print(s);
}
/// END OF INTERNAL FUNCTIONS ///
//
