/*
 * File:    	src/i2c_lcd.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	122
 * 
 * Description
 * -----------
 * The source file src/i2c_lcd.c contains all functions related for the 2x16 or 4x20 LCD.
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */

#include "i2c-lcd.h"
#include "string.h"

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup
//#define SLAVE_ADDRESS_LCD 0x27 // change this according to ur setup

/****************************************************************
							lcd_send_cmd
****************************************************************/

/*
 * Fct-Nr : 122.01
 *
 * void lcd_send_cmd(void);
 *
 * @Param: cmd - The command to send to the Display
 * @Return: None
 *
 * The function lcd_send_cmd send a command to the Display.
 */
void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	//HAL_Delay(10);  // wait 10 ms
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/****************************************************************
							lcd_send_data
****************************************************************/

/*
 * Fct-Nr : 122.02
 *
 * void lcd_send_data(char data);
 *
 * @Param: data - The character to send to the Display
 * @Return: None
 *
 * The function lcd_send_data send a character to the Display.
 */
void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	//HAL_Delay(10);  // wait 10 ms
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/****************************************************************
							lcd_init
****************************************************************/

/*
 * Fct-Nr : 122.03
 *
 * void lcd_init(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_init initializes the LCD Display
 */
void lcd_init (void)
{
	lcd_send_cmd (0x02);
	HAL_Delay(20);  // wait 20 ms
	lcd_send_cmd (0x28);
	HAL_Delay(20);  // wait 20 ms
	lcd_send_cmd (0x0c);
	HAL_Delay(20);  // wait 20 ms
	lcd_send_cmd (LCD16X2_SET_DDRAM_ADDRESS);
}

/****************************************************************
							lcd_send_string
****************************************************************/

/*
 * Fct-Nr : 122.04
 *
 * void lcd_send_string(char *str);
 *
 * @Param: str - pointer to the string to send to the LCD Display
 * @Return: None
 *
 * The function lcd_send_string send a string the LCD Display
 */
void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
void lcd_print_remaining(char *str)
{
	uint8_t i;
	uint8_t ucCnt = 0;
	while(*str){
		lcd_send_data (*str++);
		ucCnt++;
	}
    for(i=ucCnt; i<LCD16X2_DISP_LENGTH; i++)
	{
		// This delete the remaining column in case we have updated with shorter Text
		lcd_send_data (' ');
	}		
}

/****************************************************************
							lcd_gotoxy
****************************************************************/

/*
 * Fct-Nr : 122.05
 *
 * void lcd_gotoxy(uint8_t x, uint8_t y);
 *
 * @Param: x - LCD column
 * @Param: y - LCD row
 * @Return: None
 *
 * The function lcd_gotoxy Set LCD cursor to specific position
 */
void lcd_gotoxy(uint8_t x, uint8_t y)
{
	

#if LCD16X2_LINES == 1 
// 	lcd16X2_write_command(LCD16X2_SET_DDRAM_ADDRESS |
// 		(LCD16X2_START_LINE_1 + x));
 	lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS |
 		(LCD16X2_START_LINE_1 + x));
#elif LCD16X2_LINES == 2
	if (y == 0)
// 		lcd16x2_write_command(LCD16X2_SET_DDRAM_ADDRESS | 
// 			(LCD16X2_START_LINE_1 + x));
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_1 + x));
	else
// 		lcd16x2_write_command(LCD16X2_SET_DDRAM_ADDRESS | 
// 			(LCD16X2_START_LINE_2 + x));
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_2 + x));
#elif LCD16X2_LINES == 4
	if (y == 0)
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_1 + x));
	else if (y == 1)
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_2 + x));
	else if (y == 2)
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_3 + x));
	else
		lcd_send_cmd(LCD16X2_SET_DDRAM_ADDRESS | 
			(LCD16X2_START_LINE_4 + x));
#endif
}

/****************************************************************
							lcd_display_2Line
****************************************************************/

/*
 * Fct-Nr : 122.06
 *
 * void lcd_display_2Line(char *pcStrToLine1, char *pcStrToLine2);
 *
 * @Param: pcStrToLine1 - pointer to the string to print at the first row
 * @Param: pcStrToLine2 - pointer to the string to print at the second row
 * @Return: None
 *
 * The function lcd_display_2Line writes string to the first and the second line
 */
void lcd_display_2Line(char *pcStrToLine1, char *pcStrToLine2)
{
	lcd_send_cmd(CLEARROW);
	HAL_Delay(10);
	// set the cursor at first line and print the first Text
	lcd_gotoxy (0, 0);
	HAL_Delay(10);
	lcd_send_string(pcStrToLine1);
	HAL_Delay(10);
	// set the cursor at second line and print the second Text
	lcd_gotoxy (0, 1);
	HAL_Delay(10);
	lcd_send_string(pcStrToLine2);
   	HAL_Delay(10);
}

/****************************************************************
							lcd_display_1Line
****************************************************************/

/*
 * Fct-Nr : 122.07
 *
 * void lcd_display_1Line(char *pcStr, uint8_t line);
 *
 * @Param: pcStr - pointer to the string to be print.
 * @Param: line - row where the string should be printed
 * @Return: None
 *
 * The function lcd_display_1Line writes string to the selected row/line
 */
void lcd_display_1Line(char *pcStr, uint8_t line)
{

	HAL_Delay(1);
	// set the cursor at the line to print the Text
	lcd_gotoxy (0, line);
	HAL_Delay(10);
	lcd_print_remaining(pcStr);
	HAL_Delay(10);
}

/****************************************************************
							lcd_cursor_on
****************************************************************/
/*
 * Fct-Nr : 122.08
 *
 * void lcd_cursor_on(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_cursor_on turns the cursor on
 */
void lcd_cursor_on(void)
{
	lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_CURSORON | LCD_DISPLAYON);
}

/****************************************************************
							lcd_cursor_off
****************************************************************/
/*
 * Fct-Nr : 122.09
 *
 * void lcd_cursor_off(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_cursor_off turns the cursor off
 */
void lcd_cursor_off(void)
{
	lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_CURSOROFF | LCD_DISPLAYON);
}

/****************************************************************
							lcd_blink_on
****************************************************************/
/*
 * Fct-Nr : 122.10
 *
 * void lcd_blink_on(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_blink_on let the lcd blink at the cursor position
 */
void lcd_blink_on(void)
{
	lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_BLINKON | LCD_DISPLAYON);
}

/****************************************************************
							lcd_blink_off
****************************************************************/
/*
 * Fct-Nr : 122.11
 *
 * void lcd_blink_off(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_blink_off the lcd a the cursor position is not blinked
 */
void lcd_blink_off(void)
{
	lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_BLINKOFF | LCD_DISPLAYON);
}

/****************************************************************
							lcd_display_on
****************************************************************/
/*
 * Fct-Nr : 122.12
 *
 * void lcd_display_on(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_display_on turns the LCD display on
 */
void lcd_display_on(void)
{
	lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_DISPLAYON);
}

/****************************************************************
							lcd_display_off
****************************************************************/
/*
 * Fct-Nr : 122.13
 *
 * void lcd_display_off(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_display_off turns the LCD display off
 */
void lcd_display_off(void)
{
	lcd_send_cmd(LCD_DISPLAYCONTROL | LCD_DISPLAYOFF);
}

/****************************************************************
							lcd_scrollDisplayLeft
****************************************************************/
/*
 * Fct-Nr : 122.14
 *
 * void lcd_scrollDisplayLeft(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_scrollDisplayLeft scroll the LCD display to left
 */
void lcd_scrollDisplayLeft(void) {
	lcd_send_cmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

/****************************************************************
							lcd_scrollDisplayRight
****************************************************************/
/*
 * Fct-Nr : 122.15
 *
 * void lcd_scrollDisplayRight(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function lcd_scrollDisplayRight scroll the LCD display to right
 */
void lcd_scrollDisplayRight(void) {
	lcd_send_cmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

/****************************************************************
							scroll_lcd_left
****************************************************************/
/*
 * Fct-Nr : 122.16
 *
 * char* scroll_lcd_left(char *str, uint8_t line, uint8_t position, lcd_line_move *lcd);
 *
 * @Param: str - pointer to string to scroll left
 * @Param: line - row where the string is scroll
 * @Param: position - position of cursor in the row
 * @Param: position - pointer to the lcd structure
 * @Return: the pointer to the string to scroll
 *
 * The function scroll_lcd_left scroll only one row of the LCD display to the left
 * ToDo : This function should be reviewed.
 */
char* scroll_lcd_left(char *str, uint8_t line, uint8_t position, lcd_line_move *lcd)
{
   char * str2Display;
	 static char acTempString[30] = {0};
   uint8_t Len = strlen(str) + 1;  // Length is equal the string lenght  + 1 for the space.
   uint8_t pos = position % 16;
   static int firstPos = 0;
   static int lastPos = 0;
   //static uint8_t firstCall = 1;
   static int pos2Display = 0;
   static uint8_t i = 0;
    

   memset(&acTempString[0], 0, 30);
	 strcpy(&acTempString[0], str);
   acTempString[Len-1] = ' ';

   if(lcd->bFirstCall)
   {
       firstPos = pos;
       lastPos = pos + Len;
       pos2Display = pos;
       str2Display = &acTempString[0];  //str;
       lcd_gotoxy(pos2Display, line);
       lcd->bFirstCall = 0;
       firstPos--;
       lastPos--;
   }
   else
   {
       if(pos2Display > 0)
       {
           
           str2Display = &acTempString[0];  //str;
					 lcd_gotoxy(pos2Display, line);
           pos2Display--;
				   firstPos--;
           lastPos--;
           
       }
       else
       {
            if(lastPos > 0)
            {
                pos2Display = 0;
                str2Display = &acTempString[i++];  //&str[i];
                firstPos--;
                lastPos--;
								lcd_gotoxy(pos2Display, line);
                if(lastPos == 0)
                {
                    //pos2Display = 15;
                    //firstPos = 15;
                    //lastPos = Len - 1 + 15;
                    //i = 0;
                }
                
            }
            else if(lastPos == 0)
            {
                pos2Display = 0;
                str2Display = &acTempString[i];
                firstPos = 15;
                lastPos = Len + 15;  //last position is : Len + 16 - 1 for 16 rows display
                lcd_gotoxy(pos2Display, line);
                pos2Display = 15;
                i=0;

            }
            else
            {

            }
       }

   }

   return str2Display;
}
