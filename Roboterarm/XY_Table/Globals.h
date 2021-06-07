// Include NewPing Library
#include "NewPing.h"
 
// Define Constants

#define FORWARD          0
#define BACKWARD         1
#define YES           1
#define NO            0

/* Button */
#define BUTTON        13

/* LED */
#define LED       52

/* Sensor 1 Pin */
#define TRIGGER_PIN_1     10
#define ECHO_PIN_1        9

/* Sensor 2  Pin */
#define TRIGGER_PIN_2     11
#define ECHO_PIN_2        12

/* Motor 1 Pin */
#define PUL_1_PIN     4    // PUL- pin
#define DIR_1_PIN     5    // DIR- pin


/* Motor 2 Pin */
#define PUL_2_PIN     6    // PUL- pin
#define DIR_2_PIN     7    // DIR- pin

#define X_MANUAL_FORWARD    3
#define X_MANUAL_BACKWARD   8

#define Y_MANUAL_FORWARD    3
#define Y_MANUAL_BACKWARD   8

/* Distance */
// 400cm is the maximum range of HC-SR04 
#define MAX_DISTANCE      180   // 350mm is the maximum distance from origine to endpoint for this application
#define MIN_DISTANCE      100    // 50mm is the minimum range for this application

#define TARGET_DISTANCE   100
#define OFFSET_DISTANCE   ((float)2.0)

/* Motor Speed */
#define MIN_SPEED       30
#define MAX_SPEED       600
// Motor pulse
#define MOTOR_XMAX_PULSE_COUNT       17500  //30000 // ? ToDo
#define MOTOR_YMAX_PULSE_COUNT       7450   //30000 // ? ToDo

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

// Sensor Out of Range
bool bSensor1_Out_Range = NO;
bool bSensor2_Out_Range = NO;

// Sensor
float duration1 = 0.000f; // Stores First HC-SR04 pulse duration value
float duration2 = 0.000f; // Stores Second HC-SR04 pulse duration value
float distance1 = 0.000f; // Stores calculated distance in cm for First Sensor
float distance2 = 0.000f; // Stores calculated distance in cm for Second Sensor
static bool position1_Ok = false;  // flag for position 1 ok
static bool position2_Ok = false;  // flag for position 2 ok

// Flag to start the programm
volatile bool bButtonPressed = false;

const float soundcm = 0.0343f;  // Stores speed of sound in cm/µs
const float soundmm = 0.343f;   // Stores speed of sound in mm/µs
const int iterations = 5;

int Motor_1_Pulse_Count = 0;
int Motor_2_Pulse_Count = 0;

typedef enum _axis_
{
  eAxis_X,
  eAxis_Y
}eAxis;

typedef struct _lcd_message_status
{
  String lcd_sensor_status;
  uint8_t msgId;
  uint8_t prevMsgId;
  eAxis axis;
}lcd_msg_status;

typedef struct _stepper
{
  uint32_t impulseCount;
  uint32_t maxImpuls;
}PU_StepperMotor;


static lcd_msg_status tSensorX;
static lcd_msg_status tSensorY;
PU_StepperMotor Motor_Xaxis;
PU_StepperMotor Motor_Yaxis;
