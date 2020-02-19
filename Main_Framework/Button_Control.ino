int ReadButtons ()
{
  int b;
  int c = analogRead(BUTTON_PIN);
  if (c > 1000)
  {
    b = 0; // no buttons pressed
  }
  else if (c > 650 && c < 710)
  {
    b = 1; // button 1 pressed:
  }
  else if (c > 480 && c < 540)
  {
    b = 2; // button 2 pressed:
  }
  else if (c < 50)
  {
    b = 3; // button 3 pressed:
  }
  return b;
}

void HandleButtons()
{
  int currentButton = ReadButtons();

}
