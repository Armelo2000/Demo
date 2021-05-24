
void Timer1_Init(void){
 // reset
 TCCR1A = 0; // set TCCR1A register to 0
 TCCR1B = 0; // set TCCR1B register to 0
 TCNT1 = 0; // reset counter value

 /* Values in Output compare register with 16MHz clock and No prescaler
  *  for 10 microseconds OCR1A = (16 * 1000000) * 10/1000000 = 160 
  */
 OCR1A = 160; //Generate 10us Interrupt
 // set prescaler (see datasheet)
    /*
     CS12  CS11  CS10   Description
      0     0     0     No clock source (Timer/Counter stopped).
      0     0     1     clkI/O/1 (no prescaling)
      0     1     0     clkI/O/8 (from prescaler)
      0     1     1     clkI/O/64 (from prescaler)
      1     0     0     clkI/O/256 (from prescaler)
      1     0     1     clkI/O/1024 (from prescaler)
      1     1     0     External clock source on T1 pin. Clock on falling edge.
      1     1     1     External clock source on T1 pin. Clock on rising edge.
    */ 
 TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10); //No Prescale  
 TCCR1B |= (1 << WGM12); // turn on CTC mode
 TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
}

ISR(TIMER1_COMPA_vect) { 
  static uint32_t uiCnt = 0;
  static uint32_t uiLedBlinkTimer = 0;
  // Check if the button was pressed!
  if(bButtonPressed == YES)
  {
    // YES. It was pressed. The Motor run
    uiCnt++;
    uiLedBlinkTimer++;
    if(uiLedBlinkTimer >= 50000){
      // LED Blink every second
      //Toggle the LED pin each 500ms
      //digitalWrite(LED, !digitalRead(LED)); 
      //PINH |= (1 << PINH5);
      // Reset the counter for LED Blink
      uiLedBlinkTimer = 0;
    }
    if(uiCnt >= 300){
      //The Timer is called each 10us. The value 30 as counter mean 300us
      //maximum speed is related to 1 step per 300us  -> uiCnt = 30
      //minimum speed is related to 1 step per 6000us -> uiCnt = 600
      if(!position1_Ok &&(bSensor1_Out_Range == NO)){
        //keep run the Motor 1 if the target position 1 is not reached
        MotorDriveInt(DIR_1, PUL_1, DirMotor_1);
      }
      if(!position2_Ok && (bSensor2_Out_Range == NO)){
        //keep run the Motor 2 if the target position 2 is not reached
        //MotorDriveInt(DIR_2, PUL_2, DirMotor_2);
      }
      uiCnt = 0;
    }
  }
}
