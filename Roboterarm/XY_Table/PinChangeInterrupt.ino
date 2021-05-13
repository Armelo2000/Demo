const unsigned long debounceTime = 50;
volatile bool ir_selector_pressed = false;

void pinInterruptConfig()
{
  //enable the pin change interrupt on PB7 (Pin INT7)
   DDRB &= ~(1 << DDB7);
   PCMSK0 |= (1 << PCINT7);
   PCICR |= (1 << PCIE0);
}

ISR (PCINT0_vect) { // handle pin change interrupt for D0 to D7 here
  static unsigned long previousStateChangeMillis = 0;
  static bool previousPinState = HIGH;
  bool pinState = digitalRead(BUTTON);
  
  if (pinState != previousPinState) { // ignore pin changes of pins other than SELECTOR_BTN
    if (pinState == LOW) { // only falling events
      if ((millis() - previousStateChangeMillis) > debounceTime) { // debounce
        Serial.println("Start...");
        bButtonPressed = true;
        position1_Ok = false;
        position2_Ok = false;
      }
    }
    previousPinState = pinState;
    previousStateChangeMillis = millis();
  }
}
