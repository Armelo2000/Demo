
void MotorDriveInt(uint8_t pinDir, uint8_t pinPull, bool setdir){
    //Set the direction
    digitalWrite(pinDir, setdir);

    //Toggle pin to generate impuls
    digitalWrite(pinPull, !digitalRead(pinPull));   
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
    //MotorDrive(DIR_1, PUL_1, 1);  // forward
    DirMotor_1 = (bool)LEFT; 
  }
  else if(distance1 < (TARGET_DISTANCE - OFFSET_DISTANCE)){
    //MotorDrive(DIR_1, PUL_1, 0);  // back
    DirMotor_1 = (bool)RIGHT;
  }
  else{
    tSensorX.lcd_sensor_status = "P. OK ";
    tSensorX.msgId = 2;
    //Motor 1 Stop
    position1_Ok = true;
    digitalWrite(PUL_1, LOW);
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
    //MotorDrive(DIR_2, PUL_2, 1);  // forward
    DirMotor_2 = (bool)LEFT;
  }
  else if(distance2 < (TARGET_DISTANCE - OFFSET_DISTANCE)){
    //MotorDrive(DIR_2, PUL_2, 0);  // back
    DirMotor_2 = (bool)RIGHT;
  }
  else{
    tSensorY.lcd_sensor_status = "P. OK ";
    tSensorY.msgId = 2;
    //Motor 2 Stop
    position2_Ok = true;
    digitalWrite(PUL_2, LOW);
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
