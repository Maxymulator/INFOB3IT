///
/// Flush control
///

//
/// EXTERNAL FUNCTIONS ///
// Check if the user is currently flushing
bool CheckFlush()
{
  return digitalRead(FLUSH_PIN);
}

// Interrupt handler
void HandleFlushInterrupt()
{
  switch (currentState)
  {
    case state_inuse_one:
      {
        currentState = state_start_spray_one;
        break;
      }
    case state_inuse_two:
      {
        currentState = state_start_spray_two;
        break;
      }
    default:
      break;
  }
}
/// END OF EXTERNAL FUNCTIONS ///
//
