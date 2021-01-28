/*
 * File:    	src/led.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	124
 * 
 * Description
 * -----------
 * The source file src/led.c control the LED.
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */

#include "led.h"


/* Local Functions */

/****************************************************************
							led_init
****************************************************************/
/*
 * Fct-Nr : 124.01
 *
 * void led_init(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function led_init initializes the LED.
 */
void led_init(void)
{
  GPIO_InitTypeDef GPIOx;
	//LED Init
  GPIOx.Mode = GPIO_MODE_OUTPUT_PP;
  GPIOx.Pin = GPIO_PIN_13;
  GPIOx.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIOx);
}

