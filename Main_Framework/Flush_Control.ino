///
/// Flush control
///
/// CheckFlush() -> Check if the user is currently flushing
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
    case state_inuse_unknown:
      {
        GuessUse();
        break;
      }
    default:
      break;
  }
}
/// END OF EXTERNAL FUNCTIONS ///
//
