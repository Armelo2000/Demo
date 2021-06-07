/*
  Dual HC-SR04 
  Displays results on Serial Monitor
*/
#include "Globals.h"
 
void loop()
{
  if(bButtonPressed){
    bButtonPressed = false;

    Serial.println("Start...");
  }
  Serial.print("Impulse Count X-Axis : ");
  Serial.println(Motor_Xaxis.impulseCount);
  Serial.print("Impulse Count Y-Axis : ");
  Serial.println(Motor_Yaxis.impulseCount);
  //Run();
  //Serial.println("Start1...");
  delay(200);
}
