
void setup() {

  // initialize pin for Motor 1
  pinMode (PUL_1_PIN, OUTPUT);
  pinMode (DIR_1_PIN, OUTPUT);
  // initialize pin for Motor 2
  pinMode (PUL_2_PIN, OUTPUT);
  pinMode (DIR_2_PIN, OUTPUT);

  // initialize the LED Pin
  pinMode (LED, OUTPUT);

  //Init pin for manual drive
  pinMode(X_MANUAL_FORWARD, INPUT);
  pinMode(X_MANUAL_BACKWARD, INPUT);

  pinMode(Y_MANUAL_FORWARD, INPUT);
  pinMode(Y_MANUAL_BACKWARD, INPUT);
  
  Serial.begin (9600);
  //init the lcd
  lcd_init();
  tSensorX.prevMsgId = 0xFF;
  tSensorY.prevMsgId = 0xFF;
  Motor_Xaxis.impulseCount = 0;
  Motor_Yaxis.impulseCount = 0;
  Motor_Xaxis.maxImpuls = MOTOR_XMAX_PULSE_COUNT;
  Motor_Yaxis.maxImpuls = MOTOR_YMAX_PULSE_COUNT; 
  // Disable Interrupts
  cli();
  // Button Init
  pinInterruptConfig();
  // Timer Init
  Timer1_Init();
  sei(); // allow interrupts
  
}
