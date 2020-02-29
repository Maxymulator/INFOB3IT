///
/// LCD Control
///
/// PrintLCD(line, message) -> print the given message on the given line
/// PrintLCDTopLine(message) -> clear the top line and print the given message
/// PrintLCDBottonLine(message) -> clear the bottom line and print the given message
/// ClearLCD() -> clear the LCD screen
///

//
/// EXTERNAL FUNCTIONS ///
// Print the given string on the given line
void PrintLCD(int line, String s) 
{
  lcd.setCursor(0,line);
  lcd.print(EMPTY_LCD_STRING);
  lcd.print(s);
}

// Clear the top line and print the given message on the top line, seperate from the bottom line
// overloaded for String, int, unsigned long, float
void PrintLCDTopLine(String input)
{
  String s = input + EMPTY_LCD_STRING;
  lcd.setCursor(0, 0);
  lcd.print(s);
}
void PrintLCDTopLine(int input)
{
  String s = input + EMPTY_LCD_STRING;
  lcd.setCursor(0, 0);
  lcd.print(s);
}
void PrintLCDTopLine(unsigned long input)
{
  String s = input + EMPTY_LCD_STRING;
  lcd.setCursor(0, 0);
  lcd.print(s);
}
void PrintLCDTopLine(float input)
{
  String s = input + EMPTY_LCD_STRING;
  lcd.setCursor(0, 0);
  lcd.print(s);
}

// Clear the bottom line and print the given message on the bottom line, seperate from the top line
// overloaded for String, int, unsigned long, float
void PrintLCDBottomLine(String input)
{
  String s = input + EMPTY_LCD_STRING;
  lcd.setCursor(0, 1);
  lcd.print(s);
}
void PrintLCDBottomLine(int input)
{
  String s = input + EMPTY_LCD_STRING;
  lcd.setCursor(0, 1);
  lcd.print(s);
}
void PrintLCDBottomLine(unsigned long input)
{
  String s = input + EMPTY_LCD_STRING;
  lcd.setCursor(0, 1);
  lcd.print(s);
}
void PrintLCDBottomLine(float input)
{
  String s = input + EMPTY_LCD_STRING;
  lcd.setCursor(0, 1);
  lcd.print(s);
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
/// END OF INTERNAL FUNCTIONS ///
//
