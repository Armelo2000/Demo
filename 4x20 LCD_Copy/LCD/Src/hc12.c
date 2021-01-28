/*
 * File:    	src/hc12.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	104
 * 
 * Description
 * -----------
 * The source file src/hc12.c contains all functions related to the module HC-12.
 * The module is configured with the standard Baudrate of 9600 Baud
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */

#include "hc12.h"


/* Local Functions */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef *hc12;

/****************************************************************
							hc12_init
****************************************************************/

/*
 * Fct-Nr : 104.01
 *
 * void hc12_init(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function hc12_init initialize the GPIO Pin for the SET input of the HC-12 module.
 */
void hc12_init(void)
{
  GPIO_InitTypeDef GPIOx;
  //initialize the µC pin connect to SET as Output
  GPIOx.Mode = GPIO_MODE_OUTPUT_PP;
  GPIOx.Pin = HC12_PIN_SET;
  GPIOx.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIOx);
	
	//set pin to high
	HAL_GPIO_WritePin(GPIOB, HC12_PIN_SET, GPIO_PIN_SET);
}

/****************************************************************
							hc12_send_command
****************************************************************/

/*
 * Fct-Nr : 104.02
 *
 * void hc12_send_command(uint8_t * pucCmd);
 *
 * @Param: pucCmd - command to send through the HC-12 module for the configuration
 * @Return: None
 *
 * The function hc12_send_command send command through the HC-12 module.
 */
void hc12_send_command(uint8_t * pucCmd)
{
	if(pucCmd != (uint8_t*)0)
	{
		uint32_t ulCmdLen = 0;
		uint32_t index = 0;
		while(pucCmd[index++] != '\0')
		{
			ulCmdLen++;
		}
	  //Put the set pin to Low
	  HAL_GPIO_WritePin(GPIOB, HC12_PIN_SET, GPIO_PIN_RESET);
	
	  //write cmd
	  HAL_UART_Transmit(hc12, pucCmd, ulCmdLen, 100);
	}
}
/****************************************************************
							hc12_send_data
****************************************************************/

/*
 * Fct-Nr : 104.03
 *
 * void hc12_send_data(uint8_t * pucData, const uint32_t ulLen);
 *
 * @Param: pucData - Data to send through the HC-12 module
 * @Param: ulLen - Length of the data to send
 * @Return: None
 *
 * The function hc12_send_data send data through the HC-12 module.
 */
void hc12_send_data(uint8_t * pucData, const uint32_t ulLen)
{
	if(pucData != (uint8_t*)0)
	{
	  //Put the set pin to High
	  HAL_GPIO_WritePin(GPIOB, HC12_PIN_SET, GPIO_PIN_SET);
	
	  //write cmd
	  HAL_UART_Transmit(hc12, pucData, ulLen, 100);
	}
}
