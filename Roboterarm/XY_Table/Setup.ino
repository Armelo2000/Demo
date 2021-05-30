
void setup() {

  // initialize pin for Motor 1
  pinMode (PUL_1, OUTPUT);
  pinMode (DIR_1, OUTPUT);
  // initialize pin for Motor 2
  pinMode (PUL_2, OUTPUT);
  pinMode (DIR_2, OUTPUT);

  // initialize the LED Pin
  pinMode (LED, OUTPUT);
  
  Serial.begin (9600);
  //init the lcd
  lcd_init();
  tSensorX.prevMsgId = 0xFF;
  tSensorY.prevMsgId = 0xFF;
  // Disable Interrupts
  cli();
  // Button Init
  pinInterruptConfig();
  // Timer Init
  Timer1_Init();
  sei(); // allow interrupts
  
}
