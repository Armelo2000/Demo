#include "stm32f1xx_hal.h"

typedef struct
{
	uint8_t bFirstCall;

}lcd_line_move;


void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_gotoxy(uint8_t x, uint8_t y);

void lcd_cursor_on(void);					// Display the cursor
void lcd_cursor_off(void);				// Turn the cursor off

void lcd_blink_on(void);
void lcd_blink_off(void);

void lcd_display_on(void);
void lcd_display_off(void);

void lcd_scrollDisplayLeft(void);
void lcd_scrollDisplayRight(void);

char* scroll_lcd_left(char *str, uint8_t line, uint8_t position, lcd_line_move *lcd);
void lcd_display_2Line(char *pcStrToLine1, char *pcStrToLine2);
void lcd_display_1Line(char *pcStr, uint8_t line);
void lcd_print_remaining(char *str);
/** Display size ------------------------------------------------------------ */
// Number of visible lines of the display (1 or 2/4)
//#define LCD16X2_LINES						4
#define LCD16X2_LINES					2
// Visible characters per line of the display
//#define LCD16X2_DISP_LENGTH			20
#define LCD16X2_DISP_LENGTH		16
// DDRAM address of first char of line 1
#define LCD16X2_START_LINE_1		0x00
// DDRAM address of first char of line 2
#define LCD16X2_START_LINE_2		0x40
// DDRAM address of first char of line 3
#define LCD16X2_START_LINE_3		0x14
// DDRAM address of first char of line 4
#define LCD16X2_START_LINE_4		0x54

#define CLEARROW 0x01

//#define LCD16X2_SET_DDRAM_ADDRESS 0x80



/****************************** ARMEL *********************************************/

// commands
#define LCD_CLEARDISPLAY 									0x01
#define LCD_RETURNHOME 										0x02
#define LCD_ENTRYMODESET 									0x04
#define LCD_DISPLAYCONTROL 								0x08
#define LCD_CURSORSHIFT 									0x10
#define LCD_FUNCTIONSET 									0x20
#define LCD_SETCGRAMADDR 									0x40
#define LCD16X2_SET_DDRAM_ADDRESS 				0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0x04  // Enable bit
#define Rw 0x02  // Read/Write bit
#define Rs 0x01  // Register select bit


