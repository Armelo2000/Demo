
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

  if((position1_Ok == true) /*&& (position2_Ok == true)*/ && (bButtonPressed == YES)){
     // reset the Button press
     bButtonPressed = (bool)NO; 
     digitalWrite(LED, LOW);
  }
}

void Run(){

  while((position1_Ok == false) || (position2_Ok == false)){
    //The code run here
    //delay(250);  
  
    // The standard speed of 0.0343 cm/ms is used  
    soundcm = 0.0343;
    
    // Measure duration for first sensor  
    duration1 = sonar1.ping_median(iterations);
    
    // Add a delay between sensor readings
    //delay(250);
    delay(100);
    
    // Measure duration for second sensor
    duration2 = sonar2.ping_median(iterations);
    
    // Calculate the distances for both sensors
    distance1 = (duration1 / 2) * soundcm;
    distance2 = (duration2 / 2) * soundcm;

    //compute the speed of both motor
    //SpeedMotor_1 = map(distance1, 0, 400, MIN_SPEED, MAX_SPEED);
    
    // Send results to Serial Monitor
    Serial.print("Distance 1: ");
   
      if (distance1 >= MAX_DISTANCE || distance1 <= MIN_DISTANCE) {
        bSensor1_Out_Range = YES;
        Serial.print("Out of range");
        Serial.print(distance1);
      }
      else {
        bSensor1_Out_Range = NO;
        Serial.print(distance1);
        Serial.print(" cm ");
      }
      
      Serial.print("Distance 2: ");
   
      if (distance2 >= MAX_DISTANCE || distance2 <= MIN_DISTANCE) {
        bSensor2_Out_Range = YES;
        Serial.print("Out of range");
        Serial.print(distance2);
      }
      else {
        bSensor2_Out_Range = NO;
        Serial.print(distance2);
        Serial.print(" cm");
      }
    
     Serial.println(" ");
    
    //Control the Motor direction 
    motorCtrl();
  }
    
}
