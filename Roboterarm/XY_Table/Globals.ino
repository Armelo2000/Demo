// Include NewPing Library
#include "NewPing.h"
 
// Define Constants

#define LEFT          0
#define RIGHT         1
#define YES           1
#define NO            0

/* Button */
#define BUTTON        13

/* Sensor 1 Pin */
#define TRIGGER_PIN_1     10
#define ECHO_PIN_1        9

/* Sensor 2  Pin */
#define TRIGGER_PIN_2     11
#define ECHO_PIN_2        12

/* Motor 1 Pin */
#define PUL_1     4    // PUL- pin
#define DIR_1     5    // DIR- pin


/* Motor 2 Pin */
#define PUL_2     6    // PUL- pin
#define DIR_2     7    // DIR- pin

/* Distance */
#define MAX_DISTANCE    400
#define TARGET_DISTANCE   7
#define OFFSET_DISTANCE   ((float)0.3)

/* Motor Speed */
#define MIN_SPEED       30
#define MAX_SPEED       600

// Initialize the ultraschall sensors
NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
 
/* Motor 1 direction  */
bool DirMotor_1 = 0;  // used to set the direction of motor 1
/* Motor 2 direction  */
bool DirMotor_2 = 0;  // used to set the direction of motor 2

// Motor Speed
int SpeedMotor_1 = 0;  // Speed of Motor 1
int SpeedMotor_2 = 0;  // Speed of Motor 2

// Sensor
float duration1; // Stores First HC-SR04 pulse duration value
float duration2; // Stores Second HC-SR04 pulse duration value
float distance1; // Stores calculated distance in cm for First Sensor
float distance2; // Stores calculated distance in cm for Second Sensor
static bool position1_Ok = false;  // flag for position 1 ok
static bool position2_Ok = false;  // flag for position 2 ok

// Flag to start the programm
static bool bButtonPressed = false;

float soundcm;  // Stores calculated speed of sound in cm/ms
int iterations = 5;
