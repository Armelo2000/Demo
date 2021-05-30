
void MotorDriveInt(uint8_t pinDir, uint8_t pinPull, bool setdir, PU_StepperMotor *motor){
    //Set the direction
  if((motor->impulseCount > 0) && (motor->impulseCount < MOTOR_MAX_PULSE_COUNT)){ 
      digitalWrite(pinDir, setdir);
      //Toggle pin to generate impuls
      digitalWrite(pinPull, !digitalRead(pinPull)); 
      if(digitalRead(pinPull)){
        //count the impulse/step for each motor
        if(setdir == FORWARD)
        {
           if(motor->impulseCount < MOTOR_MAX_PULSE_COUNT){
              motor->impulseCount++;  
           }
        }else{
           if(motor->impulseCount > 0){
              motor->impulseCount++;  
           }        
        }
      }
  }
}

void motorCtrl(void)
{
/********************** Sensor 1 ********************************/
  static bool lcd_display_x_out = false;
  static bool lcd_display_y_out = false;
  
  Serial.print("Distance 1: ");
  if(bSensor1_Out_Range){
    if(!lcd_display_x_out){
      displayDistanceOut(3, 0, "---.--");
      lcd_display_x_out = true;
    }
    tSensorX.lcd_sensor_status = " OUT  ";
    tSensorX.msgId = 0;
    Serial.print("Out of range");
  }else{
    displayDistance(3, 0, distance1);
    tSensorX.lcd_sensor_status = "Messen";
    tSensorX.msgId = 1;
    
    lcd_display_x_out = false;
    Serial.print(distance1);
    Serial.print(" mm ");
  }
  
  if(distance1 > (TARGET_DISTANCE + OFFSET_DISTANCE)){
    //MotorDrive(DIR_1_PIN, PUL_1_PIN, 1);  // forward
    DirMotor_1 = (bool)FORWARD; 
  }
  else if(distance1 < (TARGET_DISTANCE - OFFSET_DISTANCE)){
    //MotorDrive(DIR_1_PIN, PUL_1_PIN, 0);  // back
    DirMotor_1 = (bool)BACKWARD;
  }
  else{
    tSensorX.lcd_sensor_status = "P. OK ";
    tSensorX.msgId = 2;
    //Motor 1 Stop
    position1_Ok = true;
    digitalWrite(PUL_1_PIN, LOW);
    Serial.print("-> Position 1 OK ");    
  }
  lcd_display_info(14, 0, &tSensorX);
  
/********************** Sensor 2 ********************************/
  Serial.print("*********** Distance 2: ");
  if(bSensor2_Out_Range){
    if(!lcd_display_y_out){
      displayDistanceOut(3, 1, "---.--");
      lcd_display_y_out = true;
    }
    tSensorY.lcd_sensor_status = " OUT  ";
    tSensorY.msgId = 0;
    Serial.print("Out of range");
  }else{
    displayDistance(3, 1, distance2);
    tSensorY.lcd_sensor_status = "Messen";
    tSensorY.msgId = 1;
    lcd_display_y_out = false;
    Serial.print(distance2);
    Serial.print(" mm ");
  }
  
  if(distance2 > (TARGET_DISTANCE + OFFSET_DISTANCE)){
    //MotorDrive(DIR_2_PIN, PUL_2_PIN, 1);  // forward
    DirMotor_2 = (bool)FORWARD;
  }
  else if(distance2 < (TARGET_DISTANCE - OFFSET_DISTANCE)){
    //MotorDrive(DIR_2_PIN, PUL_2_PIN, 0);  // back
    DirMotor_2 = (bool)BACKWARD;
  }
  else{
    tSensorY.lcd_sensor_status = "P. OK ";
    tSensorY.msgId = 2;
    //Motor 2 Stop
    position2_Ok = true;
    digitalWrite(PUL_2_PIN, LOW);
    Serial.print("-> Position 2 OK ");  
  }
lcd_display_info(14, 1, &tSensorY);

  if((position1_Ok == true) /*&& (position2_Ok == true)*/ && (bButtonPressed == YES)){
     // reset the Button press
     bButtonPressed = (bool)NO; 
     digitalWrite(LED, LOW);
  }
  Serial.println(" ");
}

void Run(){

  while((position1_Ok == false) || (position2_Ok == false)){
    //The code run here
    //delay(250);  
    delay(100);
    // The standard speed of 0.0343 cm/ms is used  
    //soundcm = 0.0343;
    
    // Measure duration for first sensor  
    duration1 = sonar1.ping_median(iterations);
    
    // Add a delay between sensor readings
    //delay(250);
    delay(100);
    
    // Measure duration for second sensor
    duration2 = sonar2.ping_median(iterations);
    
    // Calculate the distances for both sensors
    distance1 = float((duration1 / 2) * soundmm);
    distance2 = float((duration2 / 2) * soundmm);

    //compute the speed of both motor
    //SpeedMotor_1 = map(distance1, 0, 400, MIN_SPEED, MAX_SPEED);
    //SpeedMotor_2 = map(distance2, 0, 400, MIN_SPEED, MAX_SPEED);
    
    // Send results to Serial Monitor
    //Serial.print("Distance 1: ");
   
      if (distance1 >= MAX_DISTANCE || distance1 <= MIN_DISTANCE) {
        bSensor1_Out_Range = YES;
        //Serial.print("Out of range");
      }
      else {
        bSensor1_Out_Range = NO;
        //Serial.print(distance1);
        //Serial.print(" cm ");
      }
      
      //Serial.print("Distance 2: ");
   
      if (distance2 >= MAX_DISTANCE || distance2 <= MIN_DISTANCE) {
        bSensor2_Out_Range = YES;
        //Serial.print("Out of range");
      }
      else {
        bSensor2_Out_Range = NO;
        //Serial.print(distance2);
        //Serial.print(" cm");
      }
    
     //Serial.println(" ");
    
    //Control the Motor direction 
    motorCtrl();
  }
    
}
