long i = 1;
void setup() {
 cli(); // disable interrupts
//PORTH = (1<<PH5);
//DDRH = (1<<DDH5);
DDRB = (1<<DDB5)|(1<<DDB6)|(1<<DDB7);

 // reset
 TCCR1A = 0; // set TCCR1A register to 0
 TCCR1B = 0; // set TCCR1B register to 0
 TCNT1 = 0; // reset counter value

 /* Values in Output compare register with 16MHz clock and 1024 prescaler
  *  - 3125 --> for each 200ms
  *  - 15625 --> for each 1s
  *  - 31250--> for each 2s
  */
 OCR1A = 15625; //3125 for 200ms in
 // set prescaler
 TCCR1B |= (1 << CS12) | (1 << CS10); //Prescale 1024
// 16MHz/1024=15625Hz mit OCR1A=31249 Interrupt alle 2s
 TCCR1A = (1<<2)|(1<<4)|(1<<6);
 
 TCCR1B |= (1 << WGM12); // turn on CTC mode
 TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
 
 sei(); // allow interrupts
 
 
 Serial.begin(9600); // start serial connection
}
ISR(TIMER1_COMPA_vect) { 
// function which will be called when an interrupt 
//occurs at timer 1
 Serial.println(i); // send current value of i to the pc
 i++; // increment i
 //PINH |= (1<<PINH5);
 //PORTH = (1<<PH5);
}
void loop() {
 //i++; // increment i
}
