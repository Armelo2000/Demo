int trigPin = 11;
int echoPin = 10;
int time = 0;
int timeWait = 1000; //interval in milliseconds between each distance reading
int maxDelay = 1000;

long duration=0;                             // duration save

void setup()
{
time = millis();
pinMode(trigPin, OUTPUT); //Sensor
pinMode(echoPin, INPUT); //Sensor
pinMode(6,OUTPUT); // Enable
pinMode(13,OUTPUT); // Step
pinMode(12,OUTPUT); // Dir
digitalWrite(6,LOW); // Set Enable low
digitalWrite(5,LOW); // Set Step low
Serial.begin(9600);
}



void loop()
{
//rotateleft();
//Serial.println("ik draai nu exact een rotatie linksom");
//delay(1000);
//rotateright();
//Serial.println("ik draai nu exact een rotatie rechtsom");
//delay(1000);
//velocity();

  if(millis()-time > timeWait){ //only read distance if 1000ms has elapsed since the last reading
    time = millis();

 //sensor
 long duration, distance;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(5);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration/0.2) / 29.1;
 Serial.println("Next Scan");               // Info for the user, that next scan starts
 Serial.print("Sensor 1 = ");           //
 Serial.print(distance);              // output the way in centimeter
 Serial.println(" mm");

//eigen creatie

if (distance > 300)
{
  digitalWrite(13,HIGH); // Output high
  delayMicroseconds(500); // Wait
  digitalWrite(13,LOW); // Output low
  delayMicroseconds(500); // Wait
}

if (distance > 200 && distance < 300)
{
  digitalWrite(13,HIGH); // Output high
  delayMicroseconds(2000); // Wait
  digitalWrite(13,LOW); // Output low
  delayMicroseconds(2000); // Wait
}

//hier ist der Wert der Wichtig ist

if (distance > 100 && distance < 200)
{
  digitalWrite(13,HIGH); // Output high
  delayMicroseconds(10000); // Wait
  digitalWrite(13,LOW); // Output low
  delayMicroseconds(10000); // Wait
}

if (distance > 10 && distance < 100)
{
  //digitalWrite(13,HIGH); // Output high
  //delayMicroseconds(1000); // Wait
  digitalWrite(13,LOW); // Output low
}
}
}

void velocity(int speed){
   int trim = 10;
   digitalWrite(13,HIGH); // Output high
   delayMicroseconds(maxDelay - speed*trim); // Wait
   digitalWrite(13,LOW); // Output low
   delayMicroseconds(maxDelay - speed*trim); // Wait
   duration = pulseIn(echoPin, HIGH);
   //int distance {(duration/2) / 29.1}; //your distance reading code;
}              //

//Own functions


/*void velocity()
{
 digitalWrite(13,HIGH); // Output high
 delayMicroseconds(500); // Wait
 digitalWrite(13,LOW); // Output low
 delayMicroseconds(500); // Wait
}
*/




/*
void rotateleft()
{
 digitalWrite(12,HIGH); // Set Dir high
 for(int x = 0; x < 200; x++) // Loop 200 times
  {
    digitalWrite(13,HIGH); // Output high
    delayMicroseconds(1000); // Wait
    digitalWrite(13,LOW); // Output low
    delayMicroseconds(1000); // Wait
   }
  }
  void rotateright()
  {
   digitalWrite(12,LOW); // Set Dir high
   for(int x = 0; x < 200; x++) // Loop 200 times
   {
     digitalWrite(13,HIGH); // Output high
     delayMicroseconds(1000); // Wait
     digitalWrite(13,LOW); // Output low
     delayMicroseconds(1000); // Wait
   }
 }
 */
