// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to 
// 12 zu 22 und 13 zu 23 geändert und sensor1 und motor"1" sind noch nicht eingebunden
const int rs = 22, en = 23, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// sensor1
int echo1=8;                                  // echo pin for sensor 1 | green
int trigger1=9;                               // trigger pin for sensor 1 | brown

long duration1=0;                             // duration1 save
long distance1=0;                             // obstacle distance1 save


//sensor2
int echo2=10;                                 // echo pin for sensor 2 | yellow
int trigger2=11;                              // trigger pin for sensor 2 | orange

long duration2=0;                             // duration2 save
long distance2=0;                             // obstacle distance2 save


int time = 0;
int timeWait = 1000; //interval in milliseconds between each distance reading
int maxDelay = 1000;



void setup()
{
time = millis();  

  
pinMode(6,OUTPUT); // Enable
pinMode(13,OUTPUT); // Step
pinMode(12,OUTPUT); // Dir
digitalWrite(6,LOW); // Set Enable low
digitalWrite(5,LOW); // Set Step low
Serial.begin(9600);

// sensor1
    pinMode(trigger1, OUTPUT);               // trigger1 pin -> OUTPUT
    pinMode(echo1, INPUT);                   // echo1 pin -> INPUT

//sensor2
  pinMode(trigger2, OUTPUT);               // trigger2 pin -> OUTPUT
    pinMode(echo2, INPUT);                   // echo2 pin -> INPUT

// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
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

//sensor1 
    digitalWrite(trigger1, LOW);             // trigger1 -> "LOW" || for noise-free signal 
    delay(5);                                // 5 milliseconds delay
    digitalWrite(trigger1, HIGH);            // trigger1 -> "HIGH" || send ultrasonic wave
    delay(10);                               // 10 milliseconds delay
    digitalWrite(trigger1, LOW);             // trigger1 -> "LOW" || complete sending
    duration1 = pulseIn(echo1, HIGH);        // time until ultrasonic wave is back
    distance1 = (duration1/0.2) / 29.1;      // Convert time to path in millimeter
  
  
//sensor2 
  digitalWrite(trigger2, LOW);             // trigger2 -> "LOW" || for noise-free signal 
    delay(5);                                // 5 milliseconds delay
    digitalWrite(trigger2, HIGH);            // trigger2 -> "HIGH" || send ultrasonic wave
    delay(10);                               // 10 milliseconds delay
    digitalWrite(trigger2, LOW);             // trigger2 -> "LOW" || complete sending
    duration2 = pulseIn(echo2, HIGH);        // time until ultrasonic wave is back
    distance2 = (duration2/0.2) / 29.1;      // Convert time to path in millimeter

  if(millis()-time > timeWait){ //only read distance if 1000ms has elapsed since the last reading
    time = millis();
  }
 

  
 /*
 //sensor old 
 long duration2, distance2;
 digitalWrite(trigger2, LOW);
 delay(5);
 digitalWrite(trigger2, HIGH);
 delay(10);
 digitalWrite(trigger2, LOW);
 duration2 = pulseIn(echo2, HIGH);
 distance2 = (duration2/0.2) / 29.1;
 */
 

//mit statischen variablen 

if (distance2 > 300) 
{
  digitalWrite(13,HIGH); // Output high   
  delayMicroseconds(500); // Wait   
  digitalWrite(13,LOW); // Output low   
  delayMicroseconds(500); // Wait 
}

if (distance2 > 200 && distance2 < 300)
{
  digitalWrite(13,HIGH); // Output high   
  delay(2); // Wait   
  digitalWrite(13,LOW); // Output low   
  delay(2); // Wait
}

//hier ist der Wert der Wichtig ist

if (distance2 > 100 && distance2 < 200)
{
  digitalWrite(13,HIGH); // Output high   
  delay(10); // Wait   
  digitalWrite(13,LOW); // Output low   
  delay(10); // Wait
}

if (distance2 > 10 && distance2 < 100)
{
  //digitalWrite(13,HIGH); // Output high   
  //delayMicroseconds(1000); // Wait   
  digitalWrite(13,LOW); // Output low   
}  
  
Serial.println("Next Scan");         // Info for the user, that next scan starts        

 Serial.print("Sensor 1 = ");         // 
 Serial.print(distance1);             // output the way in millimeter
 Serial.println(" mm");               //

 Serial.print("Sensor 2 = ");         // 
 Serial.print(distance2);             // output the way in millimeter
 Serial.println(" mm");               //
 
 //displaying variables lcd 
 lcd.clear();
 lcd.print("Sens 1 = ");
 lcd.print(distance1);
 lcd.print(" mm");

 lcd.setCursor(0,1) ; //sets cursor to second line first row
       
 lcd.print("Sens 2 = ");  
 lcd.print(distance2);
 lcd.print(" mm");


 //delay(1);                              // Repeat after onehundret milliseconds



}
