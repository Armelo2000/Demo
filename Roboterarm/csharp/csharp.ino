String data;
char d1;

void setup() {
  Serial.begin(115200);
  
  // Define the LED pin as Output
  pinMode (13, OUTPUT);
}


void loop() {
 /* 
  digitalWrite(13, LOW); 
  //wait until something is received
  while(! Serial.available());
  digitalWrite(13, HIGH); 
  //read the data
  char in_read=Serial.read();
  //print the data
  Serial.print(in_read);
  delay(2000);
 */
 handleReceiveData();
}
void handleReceiveData(){
  if(Serial.available()){
    data = Serial.readString();
    d1 = data.charAt(0);
    if(d1 == 'R')
      digitalWrite(13, LOW); 
    else if(d1 == 'L')
      digitalWrite(13, HIGH); 
    Serial.print(data);
  }

  
}
