
void setup() {

  // Disable Interrupts
  cli();
  // initialize pin for Motor 1
  pinMode (PUL_1, OUTPUT);
  pinMode (DIR_1, OUTPUT);
  // initialize pin for Motor 2
  pinMode (PUL_2, OUTPUT);
  pinMode (DIR_2, OUTPUT);

  // initialize the LED Pin
  pinMode (LED, OUTPUT);
  
  Serial.begin (9600);
  
  // Button Init
  pinInterruptConfig();
  // Timer Init
  Timer1_Init();
  sei(); // allow interrupts
}
