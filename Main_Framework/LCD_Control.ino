///
/// LCD Control
///

/// EXTERNAL FUNCTIONS ///
void PrintLCD(int line, String s) 
{
  lcd.setCursor(0,line);
  lcd.print(s);
}

void PrintLCDTopLine(String s)
{
  lcd.setCursor(0, 0);
  lcd.print(EMPTY_LCD_STRING);
  lcd.setCursor(0, 0);
  lcd.print(s);
}

void PrintLCDBottomLine(String s)
{
  lcd.setCursor(0, 1);
  lcd.print(EMPTY_LCD_STRING);
  lcd.setCursor(0, 1);
  lcd.print(s);
}

void ClearLCD()
{
  lcd.clear();
}
/// END OF EXTERNAL FUNCTIONS ///

/// INTERNAL FUNCTIONS ///

/// END OF INTERNAL FUNCTIONS ///
