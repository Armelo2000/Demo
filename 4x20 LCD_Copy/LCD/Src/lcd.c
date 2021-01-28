
#include "stm32f1xx_hal.h"
#include "i2c-lcd.h"
#include "lcd.h"
#include "string.h"

static void command_mode(void);
static void data_mode(void);
static void lcd_e_pulse(void);

#define timer htim1


extern TIM_HandleTypeDef timer;
void lcd_delay (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&timer, 0);
	while (__HAL_TIM_GET_COUNTER(&timer) < us);
}


void lcd_pin_init(void)
{
	GPIO_InitTypeDef GPIOx;
	//LED Init
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
	
  GPIOx.Mode = GPIO_MODE_OUTPUT_PP;
  GPIOx.Pin = (GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
  GPIOx.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIOx);
	
}

static void command_mode(void)
{
	HAL_GPIO_WritePin(GPIOB, LCD_PIN_RS, GPIO_PIN_RESET);	
}

static void data_mode(void)
{
	HAL_GPIO_WritePin(GPIOB, LCD_PIN_RS, GPIO_PIN_SET);	
}

static void lcd_e_pulse(void)
{
	HAL_GPIO_WritePin(GPIOB, LCD_PIN_E, GPIO_PIN_SET);
  lcd_delay(20);
	HAL_GPIO_WritePin(GPIOB, LCD_PIN_E, GPIO_PIN_SET);
	lcd_delay(20);
}


void send_to_lcd (char data, int rs)
{
	HAL_GPIO_WritePin(RS_GPIO_PORT, LCD_PIN_RS, rs);  // rs = 1 for data, rs=0 for command

	/* write the data to the respective pin */
	HAL_GPIO_WritePin(D7_GPIO_PORT, LCD_PIN_D7, (GPIO_PinState)((data>>3)&0x01));
	HAL_GPIO_WritePin(D6_GPIO_PORT, LCD_PIN_D6, (GPIO_PinState)((data>>2)&0x01));
	HAL_GPIO_WritePin(D5_GPIO_PORT, LCD_PIN_D5, (GPIO_PinState)((data>>1)&0x01));
	HAL_GPIO_WritePin(D4_GPIO_PORT, LCD_PIN_D4, (GPIO_PinState)((data>>0)&0x01));

	/* Toggle EN PIN to send the data
	 * if the HCLK > 100 MHz, use the  20 us lcd_delay
	 * if the LCD still doesn't work, increase the lcd_delay to 50, 80 or 100..
	 */
	HAL_GPIO_WritePin(E_GPIO_PORT, LCD_PIN_E, 1);
	lcd_delay (40);
	HAL_GPIO_WritePin(E_GPIO_PORT, LCD_PIN_E, 0);
	lcd_delay (40);
}

void lcd_send_cmd_4Bit (char cmd)
{
    char datatosend;

    /* send upper nibble first */
    datatosend = ((cmd>>4)&0x0f);
    send_to_lcd(datatosend,0);  // RS must be 0 while sending command

    /* send Lower Nibble */
    datatosend = ((cmd)&0x0f);
	send_to_lcd(datatosend, 0);
}

void lcd_send_data_4Bit (char data)
{
	char datatosend;

	/* send higher nibble */
	datatosend = ((data>>4)&0x0f);
	send_to_lcd(datatosend, 1);  // rs =1 for sending data

	/* send Lower nibble */
	datatosend = ((data)&0x0f);
	send_to_lcd(datatosend, 1);
}

void lcd_clear (void)
{
	lcd_send_cmd_4Bit(0x01);
	lcd_delay(5000);
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd_4Bit (col);
}


void lcd_init_4Bit (void)
{
	// 4 bit initialisation
	lcd_delay(50000);
	lcd_delay(50000);
	lcd_delay(50000);
	lcd_delay(50000);
	lcd_delay(50000);
	lcd_delay(50000);
	lcd_delay(50000);
	lcd_delay(50000);
	lcd_delay(50000);
	lcd_delay(50000);  // wait for >40ms
	lcd_send_cmd_4Bit (0x30);
	lcd_delay(5000);  // wait for >4.1ms
	lcd_send_cmd_4Bit (0x30);
	lcd_delay(150);  // wait for >100us
	lcd_send_cmd_4Bit (0x30);

	lcd_delay(150);
	lcd_send_cmd_4Bit (0x20);  // 4bit mode
	lcd_delay(10);

  // dislay initialisation
	lcd_send_cmd_4Bit (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	lcd_delay(150);
	lcd_send_cmd_4Bit (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	lcd_delay(150);
	lcd_send_cmd_4Bit (0x01);  // clear display
	lcd_delay(150);
	lcd_delay(150);
	lcd_send_cmd_4Bit (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	lcd_delay(150);
	lcd_send_cmd_4Bit (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	lcd_delay(200);
	lcd_send_cmd_4Bit (LCD_SET_DDRAM_ADDRESS);
	lcd_delay(200);
}

void lcd_send_string_4Bit(char *str)
{
	while (*str) lcd_send_data_4Bit(*str++);
}

void lcd_put_cursorXY(uint8_t x, uint8_t y)
{
	if (y == 0)
		lcd_send_cmd_4Bit(LCD_SET_DDRAM_ADDRESS | 
			(LCD_START_LINE_1 + x));
	else if (y == 1)
		lcd_send_cmd_4Bit(LCD_SET_DDRAM_ADDRESS | 
			(LCD_START_LINE_2 + x));
	else if (y == 2)
		lcd_send_cmd_4Bit(LCD_SET_DDRAM_ADDRESS | 
			(LCD_START_LINE_3 + x));
	else
		lcd_send_cmd_4Bit(LCD_SET_DDRAM_ADDRESS | 
			(LCD_START_LINE_4 + x));
	
	lcd_delay(20);
}

void lcd_init_dummy (void)
{
	lcd_send_cmd_4Bit (0x02);
	lcd_delay(20);  // wait 20 ms
	lcd_send_cmd_4Bit (0x28);
	lcd_delay(20);  // wait 20 ms
	lcd_send_cmd_4Bit (0x0c);
	lcd_delay(20);  // wait 20 ms
	lcd_send_cmd_4Bit (LCD_SET_DDRAM_ADDRESS);
}