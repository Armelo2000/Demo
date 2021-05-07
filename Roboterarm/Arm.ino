/*
  Dual HC-SR04 
  Displays results on Serial Monitor
*/
 
 
// Include NewPing Library
#include "NewPing.h"
 
// Define Constants

/* Button */
#define BUTTON  			2

/* Sensor 1 Pin */
#define TRIGGER_PIN_1  		10
#define ECHO_PIN_1     		9

/* Sensor 2  Pin */
#define TRIGGER_PIN_2  		5
#define ECHO_PIN_2     		4

/* Motor 1 Pin */
#define PUL_1 = 4;    // PUL- pin
#define DIR_1 = 5;    // DIR- pin


/* Motor 2 Pin */
#define PUL_2 = 6;    // PUL- pin
#define DIR_2 = 7;    // DIR- pin

/* Distance */
#define MAX_DISTANCE 		400
#define TARGET_DISTANCE 	15
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

float soundcm;  // Stores calculated speed of sound in cm/ms
int iterations = 5;

void Run(){
  //The code run here
  delay(1000);  // Delay so DHT-22 sensor can stabalize

  // The standard speed of 0.0343 cm/ms is used  
  soundcm = 0.0343;
  
  // Measure duration for first sensor  
  duration1 = sonar1.ping_median(iterations);
  
  // Add a delay between sensor readings
  delay(1000);
  
  // Measure duration for second sensor
  duration2 = sonar2.ping_median(iterations);
  
  // Calculate the distances for both sensors
  distance1 = (duration1 / 2) * soundcm;
  distance2 = (duration2 / 2) * soundcm;
  
  // Send results to Serial Monitor
  Serial.print("Distance 1: ");
 
    if (distance1 >= 400 || distance1 <= 2) {
    Serial.print("Out of range");
    }
    else {
    Serial.print(distance1);
    Serial.print(" cm ");
    }
    
    Serial.print("Distance 2: ");
 
    if (distance2 >= 400 || distance2 <= 2) {
    Serial.print("Out of range");
    }
    else {
    Serial.print(distance2);
    Serial.print(" cm");
    }
  
   Serial.println(" ");
  
  //Check if the distances are equal
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
  attachInterrupt(digitalPinToInterrupt(BUTTON), Run, FALLING);
}
 
void loop()
{


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
	position2_Ok = true;
  }
}


void MotorDrive(uint8_t pinDir, uint8_t pinPull, bool setdir){
    digitalWrite(pinDir, setdir);
    digitalWrite(pinPull, HIGH);
    delayMicroseconds(5000);
    digitalWrite(pinPull, LOW);
    delayMicroseconds(5000);
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