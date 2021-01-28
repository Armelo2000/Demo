

#ifndef LCD_H
#define LCD_H

#define LCD_PIN_RS		GPIO_PIN_4
#define RS_GPIO_PORT	GPIOB
#define LCD_PIN_E			GPIO_PIN_5
#define E_GPIO_PORT		GPIOB

#define LCD_PIN_D4		GPIO_PIN_1
#define D4_GPIO_PORT	GPIOB
#define LCD_PIN_D5		GPIO_PIN_15
#define D5_GPIO_PORT	GPIOB
#define LCD_PIN_D6		GPIO_PIN_14
#define D6_GPIO_PORT	GPIOB
#define LCD_PIN_D7		GPIO_PIN_13
#define D7_GPIO_PORT	GPIOB

#define LCD_MASK_DATA     (LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4)

// commands
#define LCD_CLEARDISPLAY 									0x01
#define LCD_RETURNHOME 										0x02
#define LCD_ENTRYMODESET 									0x04
#define LCD_DISPLAYCONTROL 								0x08
#define LCD_CURSORSHIFT 									0x10
#define LCD_FUNCTIONSET 									0x20
#define LCD_SETCGRAMADDR 									0x40
#define LCD_SET_DDRAM_ADDRESS 						0x80

// Visible characters per line of the display
#define LCD_DISP_LENGTH										20
// DDRAM address of first char of line 1
#define LCD_START_LINE_1									0x00
// DDRAM address of first char of line 2
#define LCD_START_LINE_2									0x40
// DDRAM address of first char of line 3
#define LCD_START_LINE_3									0x14
// DDRAM address of first char of line 4
#define LCD_START_LINE_4									0x54

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

void lcd_init_4Bit (void);
void lcd_send_string_4Bit(char *str);
void lcd_put_cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);
void lcd_clear (void);
void lcd_send_cmd_4Bit (char cmd);
void lcd_send_data_4Bit (char data);
void lcd_put_cursorXY(uint8_t x, uint8_t y);
void lcd_init_dummy (void);

#endif
