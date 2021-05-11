/*
  Dual HC-SR04 
  Displays results on Serial Monitor
*/
 
 
// Include NewPing Library
#include "NewPing.h"
 
// Define Constants

/* Button */
#define BUTTON  			13

/* Sensor 1 Pin */
#define TRIGGER_PIN_1  		10
#define ECHO_PIN_1     		9

/* Sensor 2  Pin */
#define TRIGGER_PIN_2  		5
#define ECHO_PIN_2     		4

/* Motor 1 Pin */
#define PUL_1     4    // PUL- pin
#define DIR_1     5    // DIR- pin


/* Motor 2 Pin */
#define PUL_2     6    // PUL- pin
#define DIR_2     7    // DIR- pin

/* Distance */
#define MAX_DISTANCE 		400
#define TARGET_DISTANCE 	7
#define OFFSET_DISTANCE		((float)0.3)

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
 
/* Motor 1 direction  */
bool RevMotor_1 = 0;  // used to reverse motor direction
/* Motor 2 direction  */
bool RevMotor_2 = 0;  // used to reverse motor direction

// Sensor
float duration1; // Stores First HC-SR04 pulse duration value
float duration2; // Stores Second HC-SR04 pulse duration value
float distance1; // Stores calculated distance in cm for First Sensor
float distance2; // Stores calculated distance in cm for Second Sensor
static bool position1_Ok = false;  // flag for position 1 ok
static bool position2_Ok = false;  // flag for position 2 ok

// Flag to start the programm
static bool bFlagStart = false;

float soundcm;  // Stores calculated speed of sound in cm/ms
int iterations = 5;


void runs(){
  Serial.println("runs is called");
}
void Run(){

  while(!position1_Ok){
    //The code run here
    delay(250);  
  
    // The standard speed of 0.0343 cm/ms is used  
    soundcm = 0.0343;
    
    // Measure duration for first sensor  
    duration1 = sonar1.ping_median(iterations);
    
    // Add a delay between sensor readings
    delay(250);
    
    // Measure duration for second sensor
    duration2 = sonar2.ping_median(iterations);
    
    // Calculate the distances for both sensors
    distance1 = (duration1 / 2) * soundcm;
    distance2 = (duration2 / 2) * soundcm;
    
    // Send results to Serial Monitor
    Serial.print("Distance 1: ");
   
      if (distance1 >= 400 || distance1 <= 2) {
      Serial.print("Out of range");
      Serial.print(distance1);
      }
      else {
      Serial.print(distance1);
      Serial.print(" cm ");
      }
      
      Serial.print("Distance 2: ");
   
      if (distance2 >= 400 || distance2 <= 2) {
      Serial.print("Out of range");
      Serial.print(distance2);
      }
      else {
      Serial.print(distance2);
      Serial.print(" cm");
      }
    
     Serial.println(" ");
    
    //Check if the distances are equal
    motorCtrl();
  }
    
}
 
void setup() {
  // initialize pin for Motor 1
  pinMode (PUL_1, OUTPUT);
  pinMode (DIR_1, OUTPUT);
  // initialize pin for Motor 2
  pinMode (PUL_2, OUTPUT);
  pinMode (DIR_2, OUTPUT);
  
  Serial.begin (9600);
  //Button
  //attachInterrupt(digitalPinToInterrupt(BUTTON), Run, FALLING);
  //attachInterrupt(digitalPinToInterrupt(BUTTON), runs, FALLING);
  //sei();
  //pinInterruptConfig();
  Timer1_Init();
}
 
void loop()
{
  //Serial.println("läuft");
  //delay(1000);
  //MotorDrive(DIR_1, PUL_1, 1);
  //delay(1000);
  //for(int i=0; i<200; i++)
  //MotorDrive(DIR_1, PUL_1, 0);
  if(bFlagStart){
    //Run();
    bFlagStart = false;
    Serial.println("Run...");
  }
  //Serial.println("Start1...");
  //Serial.println("Start2...");
  //Serial.println("Start3...");
  //Serial.println("Start4...");
  //Serial.println("Start5...");
  delay(200000);
  duration1 = pulseIn(ECHO_PIN_1, HIGH);
  duration1 = sonar1.ping_median(iterations);
  
  //duration1 = sonar1.ping_median(iterations);
  //duration1 = pulseIn(ECHO_PIN_1, HIGH);//sonar1.ping_median(iterations);
}


void motorCtrl(void)
{
// Sensor 1
  if(distance1 > (TARGET_DISTANCE + OFFSET_DISTANCE)){
	MotorDrive(DIR_1, PUL_1, 1);  // forward
  }
  else if(distance1 < (TARGET_DISTANCE - OFFSET_DISTANCE)){
    MotorDrive(DIR_1, PUL_1, 0);  // back
  }
  else{
    MotorStop(PUL_1);
    Serial.println("Position 1 OK");
	  position1_Ok = true;
  }
// Sensor 2
  if(distance2 > (TARGET_DISTANCE + OFFSET_DISTANCE)){
	MotorDrive(DIR_2, PUL_2, 1);  // forward
  }
  else if(distance2 < (TARGET_DISTANCE - OFFSET_DISTANCE)){
    MotorDrive(DIR_2, PUL_2, 0);  // back
  }
  else{
    MotorStop(PUL_2);
    Serial.println("Position 2 OK");
	  position2_Ok = true;
  }
}


void MotorDrive(uint8_t pinDir, uint8_t pinPull, bool setdir){
    digitalWrite(pinDir, setdir);
    digitalWrite(pinPull, HIGH);
    //delay(500);
    delayMicroseconds(500);
    digitalWrite(pinPull, LOW);
    delayMicroseconds(500);
    //delay(500);
}

void MotorStop(uint8_t pinPull){
	digitalWrite(pinPull, LOW);
}

void CutterStart()
{
  //Send signal here
  //ToDo ...
  
  //reset the position flag for both sensors
  position1_Ok = false;
  position2_Ok = false;
}

ISR (PCINT0_vect)
{
  Serial.println("Start...");
  bFlagStart = true;
  position1_Ok = false;
  position2_Ok = false;
}

void pinInterruptConfig()
{
  //enable the pin change interrupt on PB7 (Pin INT7)
   DDRB &= ~(1 << DDB7);
   PCMSK0 |= (1 << PCINT7);
   PCICR |= (1 << PCIE0);
   sei();
}

void MotorDriveInt(uint8_t pinDir, uint8_t pinPull, bool setdir){
    digitalWrite(pinDir, setdir);
    //PIND |= (1<<PIND4);
    digitalWrite(pinPull, !digitalRead(pinPull));
    //delayMicroseconds(500);
    
}

void Timer1_Init(void){
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
 TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10); //No Prescale 
// 16MHz/1024=15625Hz mit OCR1A=31249 Interrupt alle 2s
// TCCR1A = (1<<2)|(1<<4)|(1<<6);
 
 TCCR1B |= (1 << WGM12); // turn on CTC mode
 TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
 //pinInterruptConfig();
 sei(); // allow interrupts
}

ISR(TIMER1_COMPA_vect) { 
  static uint32_t uiCnt = 0;
  uiCnt++;
  if(uiCnt >= 200){
    MotorDrive(DIR_1, PUL_1, 1);
    uiCnt = 0;
  }
}
