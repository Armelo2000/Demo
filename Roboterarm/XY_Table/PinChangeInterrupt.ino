

void pinInterruptConfig()
{
  //enable the pin change interrupt on PB7 (Pin INT7)
   DDRB &= ~(1 << DDB7);
   PCMSK0 |= (1 << PCINT7);
   PCICR |= (1 << PCIE0);
}

ISR (PCINT0_vect)
{
  Serial.println("Start...");
  bButtonPressed = true;
  position1_Ok = false;
  position2_Ok = false;
}
