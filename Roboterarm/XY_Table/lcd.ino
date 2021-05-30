#include <Wire.h> // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek einbinden
LiquidCrystal_I2C lcd(0x27, 20, 4); //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall eines mit 16 Zeichen in 2 Zeilen und der HEX-Adresse 0x27. Für ein vierzeiliges I2C-LCD verwendet man den Code "LiquidCrystal_I2C lcd(0x27, 20, 4)" 

void lcd_init(void){
 lcd.begin();   //Im Setup wird der LCD gestartet 
  lcd.backlight(); //Hintergrundbeleuchtung einschalten (lcd.noBacklight(); schaltet die Beleuchtung aus). 
  lcd.setCursor(0, 0);//Hier wird die Position des ersten Zeichens festgelegt. In diesem Fall bedeutet (0,0) das erste Zeichen in der ersten Zeile. 
  lcd.print("X: ---.-- mm ");
  lcd.setCursor(13, 0);
  lcd.print("> -----");
  lcd.setCursor(0, 1);// In diesem Fall bedeutet (0,1) das erste Zeichen in der zweiten Zeile. 
  lcd.print("Y: ---.-- mm ");
  lcd.setCursor(13, 1);
  lcd.print("> -----"); 
  
}

void displayDistance(uint8_t col, uint8_t line, float distance)
{
  lcd.setCursor(col, line);
  lcd.print("       ");
  lcd.setCursor(col, line);
  lcd.print(distance);
}
void displayDistanceOut(uint8_t col, uint8_t line, String message)
{
  lcd.setCursor(col, line);
  lcd.print("       ");
  lcd.setCursor(col, line);
  lcd.print(message);
}

void lcd_display_info(uint8_t col, uint8_t line, lcd_msg_status *ptSensor)
{
  if(ptSensor != NULL)
  {
    if(ptSensor->msgId != ptSensor->prevMsgId)
    {
      ptSensor->prevMsgId = ptSensor->msgId;
      displayDistanceOut(col, line, ptSensor->lcd_sensor_status);
    }
  }
}
