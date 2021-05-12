
void MotorDriveInt(uint8_t pinDir, uint8_t pinPull, bool setdir){
    //Set the direction
    digitalWrite(pinDir, setdir);

    //Toggle pin to generate impuls
    digitalWrite(pinPull, !digitalRead(pinPull));   
}

void motorCtrl(void)
{
/********************** Sensor 1 ********************************/
  if(distance1 > (TARGET_DISTANCE + OFFSET_DISTANCE)){
    //MotorDrive(DIR_1, PUL_1, 1);  // forward
    DirMotor_1 = (bool)RIGHT;  
  }
  else if(distance1 < (TARGET_DISTANCE - OFFSET_DISTANCE)){
    //MotorDrive(DIR_1, PUL_1, 0);  // back
    DirMotor_1 = (bool)LEFT;
  }
  else{
    //Motor 1 Stop
    digitalWrite(PUL_1, LOW);
    Serial.println("Position 1 OK");
    position1_Ok = true;
  }
  
/********************** Sensor 2 ********************************/
  if(distance2 > (TARGET_DISTANCE + OFFSET_DISTANCE)){
    //MotorDrive(DIR_2, PUL_2, 1);  // forward
    DirMotor_2 = (bool)RIGHT;
  }
  else if(distance2 < (TARGET_DISTANCE - OFFSET_DISTANCE)){
    //MotorDrive(DIR_2, PUL_2, 0);  // back
    DirMotor_2 = (bool)LEFT;
  }
  else{
    //Motor 2 Stop
    digitalWrite(PUL_2, LOW);
    Serial.println("Position 2 OK");
    position2_Ok = true;
  }

  if((position1_Ok == true) && (position2_Ok == true) && (bButtonPressed == YES)){
     // reset the Button press
     bButtonPressed = (bool)NO; 
  }
}

void Run(){

  while((position1_Ok == false) || (position2_Ok == false)){
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
    
    //Control the Motor direction 
    motorCtrl();
  }
    
}
