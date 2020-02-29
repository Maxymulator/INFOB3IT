///
/// Menu control
///
/// CycleMenuState() -> Cycle through the menu states
/// ConfirmMenu() -> Interact with the current menu state
/// PrintMenu() -> Print the current menu to the LCD screen
///

//
/// VARIABLES \\\
// The current state of the menu
int menuState = 0;
/// END OF VARIABLES \\\
//

//
/// EXTERNAL FUNCTIONS \\\
// Cycle the current menu
void CycleMenuState()
{
  menuState += 1;
  if (menuState == 3)
  {
    menuState = 0;
  }
}

// Handle this menu state
void ConfirmMenu()
{
  switch(menuState)
  {
    case 0: // Reset spraycount
    {
      ResetSprayCount();
      break;
    }
    case 1: // Cycle the spray delay
    {
      CycleSprayDelay();
      break;
    }
    case 2: // Exit the menu
    {
      menuState = 0;
      ClearLCD();
      currentState = state_standbye;
      break;
    }
  }
}

// Print the menu
void PrintMenu()
{
  switch(menuState)
  {
    case 0: // Reset spraycount
    {
      PrintLCDTopLine(F("Reset spraycount?"));
      PrintLCDBottomLine(F("Button3: Confirm"));
      break;
    }
    case 1: // Cycle the spray delay
    {
      PrintLCDTopLine(F("Cycle spraydelay"));
      PrintClrLCDBottomLine(GetSprayDelay());
      break;
    }
    case 2: // Exit the menu
    {
      PrintLCDTopLine(F("Exit menu?      "));
      PrintLCDBottomLine(F("Button3: Confirm"));
      break;
    }
  }
}
/// END OF EXTERNAL FUNCTIONS \\\
//
