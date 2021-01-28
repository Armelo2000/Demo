/*
 * lcd.h
 *
 *  Created on: 22.02.2019
 *      Author: Bartek
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f103xb.h"
//#include "gpio.h"
#include "delay.h"

#define LCD_ROWS 2
#define LCD_COLS 16

#define LCD_RS_PIN	GPIO_PIN_4
#define LCD_RS_PORT	GPIOB

#define LCD_E_PIN		GPIO_PIN_5
#define LCD_E_PORT	GPIOB

#define LCD_D4_PIN	GPIO_PIN_1
#define LCD_D4_PORT	GPIOB

#define LCD_D5_PIN	GPIO_PIN_15
#define LCD_D5_PORT	GPIOB

#define LCD_D6_PIN	GPIO_PIN_14
#define LCD_D6_PORT	GPIOB

#define LCD_D7_PIN	GPIO_PIN_13
#define LCD_D7_PORT	GPIOB


#define LCD_E_HIGH 		LCD_E_PORT->ODR |= LCD_E_PIN
#define LCD_E_LOW 		LCD_E_PORT->ODR &= ~LCD_E_PIN
#define LCD_RS_LOW 		LCD_RS_PORT->ODR |= LCD_RS_PIN
#define LCD_RS_HIGH 	LCD_RS_PORT->ODR &= ~LCD_RS_PIN

#define LCD_LINE1 		0x00
#define LCD_LINE2 		0x40

#define LCD_CLEAR					0x01
#define LCD_HOME					0x02
#define LCD_ENTRY_MODE				0x04
	#define LCD_EM_SHIFT_CURSOR		    0x00
	#define LCD_EM_SHIFT_DISPLAY	 	0x01
	#define LCD_EM_LEFT		   			0x00
	#define LCD_EM_RIGHT				0x02
#define LCD_ONOFF					0x08
	#define LCD_DISP_ON				    0x04
	#define LCD_CURSOR_ON				0x02
	#define LCD_CURSOR_OFF				0x00
	#define LCD_BLINK_ON				0x01
	#define LCD_BLINK_OFF				0x00
#define LCD_SHIFT					0x10
	#define LCD_SHIFT_DISP				0x08
	#define LCD_SHIFT_CURSOR			0x00
	#define LCD_SHIFT_RIGHT			0x04
	#define LCD_SHIFT_LEFT				0x00
#define LCD_FUNC					0x20
	#define LCD_8_BIT					0x10
	#define LCD_4_BIT					0x00
	#define LCD_TWO_LINE				0x08
	#define LCD_FONT_5x10				0x04
	#define LCD_FONT_5x7				0x00
#define LCD_SET_CGRAM				0x40
#define LCD_SET_DDRAM				0x80

void lcd_sendHalf(uint8_t data);
void lcd_write_byte(uint8_t data);
void lcd_write_cmd(uint8_t cmd);
void lcd_write_char(char data);
void lcd_locate(uint8_t x, uint8_t y);
void lcd_gpio_init(void);
void LCD_Init(void);
void lcd_write_str(char *text);
void lcd_str_XY(uint8_t x, uint8_t y, char * text);

#endif /* LCD_H_ */
