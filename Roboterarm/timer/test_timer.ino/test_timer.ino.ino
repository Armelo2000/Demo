long i = 1;
static uint32_t uiPulseWidth = 0;
void setup() {
 cli(); // disable interrupts
//PORTH = (1<<PH5);
//DDRH = (1<<DDH5);
DDRB = (1<<DDB0)|(1<<DDB1)|(1<<DDB2);

 // reset
 TCCR1A = 0; // set TCCR1A register to 0
 TCCR1B = 0; // set TCCR1B register to 0
 TCNT1 = 0; // reset counter value

 /* Values in Output compare register with 16MHz clock and 1024 prescaler
  *  - 3125 --> for each 200ms
  *  - 15625 --> for each 1s
  *  - 31250--> for each 2s
  */
 OCR1A = 160; //15625; //3125 for 200ms in
 // set prescaler
/*
 CS12 CS11 CS10 Description
0 0 0 No clock source (Timer/Counter stopped).
0 0 1 clkI/O/1 (no prescaling)
0 1 0 clkI/O/8 (from prescaler)
0 1 1 clkI/O/64 (from prescaler)
1 0 0 clkI/O/256 (from prescaler)
1 0 1 clkI/O/1024 (from prescaler)
1 1 0 External clock source on T1 pin. Clock on falling edge.
1 1 1 External clock source on T1 pin. Clock on rising edge.
*/ 
 TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10); //Prescale 1024
// 16MHz/1024=15625Hz mit OCR1A=31249 Interrupt alle 2s
// TCCR1A = (1<<2)|(1<<4)|(1<<6);
 
 TCCR1B |= (1 << WGM12); // turn on CTC mode
 TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
 pinInterruptConfig();
 sei(); // allow interrupts
 
 
 Serial.begin(9600); // start serial connection
}
ISR(TIMER1_COMPA_vect) { 
static uint32_t uiCnt = 0;
uiCnt++;
uiPulseWidth++;
// function which will be called when an interrupt 
//occurs at timer 1
  if(uiCnt == 100000)
  {
     //Serial.println(i); // send current value of i to the pc
     i++; // increment i
     PINB |= (1<<PINB0);
     //PORTB |= (1<<PB0);
     
  }
  else if(uiCnt >= 100001)
  {
    //PORTB &= ~(1<<PB0);
    PINB |= (1<<PINB0);
    uiCnt=0;
    //TIMSK1 &= ~(1 << OCIE1A); // disable timer compare interrupt
  }
}
void loop() {
 //i++; // increment i
}

void pinInterruptConfig()
{
  
  //enable the pin change interrupt on PB7 (Pin INT7)
   DDRB &= ~(1 << DDB5);
   PCMSK0 |= (1 << PCINT5);
   PCICR |= (1 << PCIE0);
}

ISR (PCINT0_vect) {
  if(PINB & (1<<PINB5))
  {
    uiPulseWidth = 0;
    //TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  }
  else
  {
    Serial.println(uiPulseWidth);
     
  }
}
