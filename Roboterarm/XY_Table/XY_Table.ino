/*
  Dual HC-SR04 
  Displays results on Serial Monitor
*/
 
void loop()
{
  if(bFlagStart){
    //Run();
    bFlagStart = false;
    Serial.println("Run...");
  }
  Run();
  //Serial.println("Start1...");
  delay(200000);
}