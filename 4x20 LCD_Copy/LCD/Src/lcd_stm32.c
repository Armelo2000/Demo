/*
 * lcd.c
 *
 *  Created on: 24.02.2019
 *      Author: Bartek
 */

#include "stm32f1xx_hal.h"
#include "i2c-lcd.h"
#include "lcd.h"
#include "string.h"
#include "lcd_stm32.h"

void lcd_write_half(uint8_t data) {
	LCD_E_HIGH;

	if (data & 0x01) LCD_D4_PORT->ODR |= LCD_D4_PIN;
	else LCD_D4_PORT->ODR &= ~LCD_D4_PIN;

	if (data & 0x02) LCD_D5_PORT->ODR |= LCD_D5_PIN;
	else LCD_D5_PORT->ODR &= ~LCD_D5_PIN;

	if (data & 0x04) LCD_D6_PORT->ODR |= LCD_D6_PIN;
	else LCD_D6_PORT->ODR &= ~LCD_D6_PIN;

	if (data & 0x08) LCD_D7_PORT->ODR |= LCD_D7_PIN;
	else LCD_D7_PORT->ODR &= ~LCD_D7_PIN;

	LCD_E_LOW;
}

void lcd_write_byte(uint8_t data) {
	lcd_write_half(data >> 4);
	lcd_write_half(data);
	HAL_Delay(12);
}

void lcd_write_cmd(uint8_t cmd) {
	LCD_RS_LOW;
	lcd_write_byte(cmd);
}

void lcd_write_char(char data) {
	LCD_RS_HIGH;
	lcd_write_byte(data);
}

void lcd_locate(uint8_t x, uint8_t y) {

	switch(y) {
		case 0:
			lcd_write_cmd( LCD_SET_DDRAM | (LCD_LINE1 + x) );
			break;

		case 1:
			lcd_write_cmd( LCD_SET_DDRAM | (LCD_LINE2 + x) );
			break;
	}

}

void lcd_gpio_init(void) {
	
	GPIO_InitTypeDef GPIOx;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	//LED Init
  GPIOx.Mode = GPIO_MODE_OUTPUT_PP;
  GPIOx.Pin = (GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
  GPIOx.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIOx);

}

void LCD_Init(void) {
	lcd_gpio_init();

//	HAL_Delay(10000);
//
//	LCD_E_LOW;
//	LCD_RS_LOW;
//
//	lcd_write_half(0b11);
//	HAL_Delay(500);
//	lcd_write_half(0b11);
//	HAL_Delay(10);
//	lcd_write_half(0b11);
//	HAL_Delay(10);
//	lcd_write_half(0b10);
//	HAL_Delay(10);
//
//	lcd_write_cmd(0b00101000);
//	HAL_Delay(10);
//	lcd_write_cmd(0b00001000);
//	HAL_Delay(10);
//	lcd_write_cmd(0b00000001);
//	HAL_Delay(500);
//	lcd_write_cmd(0b00000110);
//	HAL_Delay(10);
//	lcd_write_cmd(0b00001100);
//	HAL_Delay(10);


	HAL_Delay(1500);

	LCD_E_LOW;
	LCD_RS_LOW;

	lcd_write_half(0x03);
	HAL_Delay(410);
	lcd_write_half(0x03);
	HAL_Delay(10);
	lcd_write_half(0x03);
	HAL_Delay(10);
	lcd_write_half(0x02);
	HAL_Delay(10);

	lcd_write_cmd( LCD_FUNC | LCD_4_BIT | LCD_TWO_LINE | LCD_FONT_5x7 );
	lcd_write_cmd( LCD_ONOFF | LCD_DISP_ON );
	lcd_write_cmd( LCD_CLEAR );
	HAL_Delay(500);
	lcd_write_cmd( LCD_ENTRY_MODE | LCD_EM_SHIFT_CURSOR | LCD_EM_RIGHT );

}

void lcd_write_str(char *text) {
	while(*text)
		lcd_write_char(*text++);

}


void lcd_str_XY(uint8_t x, uint8_t y, char * text) {
	lcd_locate(x,y);

	while(*text)
		lcd_write_char(*text++);

}
