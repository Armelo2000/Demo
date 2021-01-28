/*
 * File:    	src/button.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	123
 * 
 * Description
 * -----------
 * The source file src/button.c contains all related functions to the button pressed.
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */

#include "stm32f1xx_hal.h"
#include "button.h"
#include "command.h"
#include "crc.h"
#include "hc12.h"
#include "i2c-lcd.h"
#include "telegram.h"

/* Local Functions */

extern eTelState fg_eTelFlag;  

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef *hc12;
extern UART_HandleTypeDef *ftdi;

extern telprinter_t tTelRecv;
extern telremotecontoller_t tTel2Send;
void lcd_display_recv(char *pcStr, uint8_t line);

/****************************************************************
							ButtonInit
****************************************************************/
/*
 * Fct-Nr : 123.01
 *
 * void ButtonInit(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function ButtonInit initializes the button that should be pressed to request a number.
 */
void ButtonInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_ConfigTypeDef EXTI_InitStructure;
	EXTI_HandleTypeDef hexti;
	//ButtonNucleoInit();

  /* Enable the BUTTON Clock */
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  /* Configure Button pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;  //GPIO_MODE_INPUT | 0x10000000U;
  GPIO_InitStructure.Pin =  GPIO_PIN_1;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Connect Button EXTI Line to Button GPIO Pin */
    //GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);

    /* Configure Button EXTI line */
    EXTI_InitStructure.Line = EXTI_LINE_1;
    EXTI_InitStructure.Mode = EXTI_MODE_INTERRUPT;
    EXTI_InitStructure.Trigger = EXTI_TRIGGER_RISING; // or EXTI_TRIGGER_FALLING
    EXTI_InitStructure.GPIOSel = EXTI_GPIOB;
	
	  hexti.Line = EXTI_LINE_1;
		hexti.PendingCallback = Button_CallBack;
		HAL_EXTI_SetConfigLine(&hexti, &EXTI_InitStructure);
    //EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure); */

		/* EXTI interrupt init*/
		HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI1_IRQn);

}




/****************************************************************
							Button_CallBack
****************************************************************/
/*
 * Fct-Nr : 123.02
 *
 * void Button_CallBack(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function Button_CallBack is the call back function for the button pressed.
 */
void Button_CallBack(void)
{
	/* EXTI line interrupt detected */
	//! Clears The Interrupt Flag
   __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1); 
   
	//! Calls The ISR Handler CallBack Function
   HAL_GPIO_EXTI_Callback(GPIO_PIN_1);   

}

/****************************************************************
							HAL_GPIO_EXTI_Callback
****************************************************************/
/*
 * Fct-Nr : 123.03
 *
 * void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
 *
 * @Param: GPIO_Pin - GPIO Pin number that generate the EXTI Call back.
 * @Return: None
 *
 * The function HAL_GPIO_EXTI_Callback is the call back function for the button pressed.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   /* EXTI line interrupt detected */
   if(HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) != 0x00u)
   {
		  ButtonPressed();
	   // Set the flag to send
	   fg_eTelFlag = eTEL_SEND;

	   //Disable the interrupt to avoid collision between send and receive Telegram
	   HAL_NVIC_DisableIRQ(EXTI1_IRQn);
   }

}

/****************************************************************
							HAL_GPIO_EXTI_Callback
****************************************************************/
/*
 * Fct-Nr : 123.04
 *
 * void EXTI1_IRQHandler(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function EXTI1_IRQHandler is an external Interrupt.
 */
void EXTI1_IRQHandler(void)
{
	Button_CallBack();
}

void CallNextTicket(void)
{
	telremotecontoller_t tNextTicket;
	char printText[100] = {0};
	
	tNextTicket.cmd = CMD_CALL_NEXT_NUMBER;
	tNextTicket.DeviceId = 0x40FA;
  tNextTicket.reserved_0 = 0x1C;
	tNextTicket.reserved_1 = 0xA580;
	tNextTicket.crc = crc_16((uint8_t *)&tNextTicket, 14);
	
	sprintf(printText, "command Send : %X\n\rDeviceId : %X\n\rCRC : %X\n\r\n\0", tNextTicket.cmd, tNextTicket.DeviceId, tNextTicket.crc);

	//HAL_UART_Transmit(&huart1, (uint8_t *)&printText[0], 64, 100);
  //hc12_send_data((uint8_t *)&printText[0], 64);
	hc12_send_data((uint8_t *)&tNextTicket, 8);
}

void lcd_display_recv(char *pcStr, uint8_t line)
{
	lcd_gotoxy (0,1);
	//lcd_send_cmd(CLEARROW);
	HAL_Delay(20);
	lcd_gotoxy (0, line);
	HAL_Delay(20);
	lcd_send_string (pcStr);
	HAL_Delay(20);	
}

void ButtonPressed(void)
{
	static uint8_t ucPressedCount = 1;
	char cStringToPrint[16] = {0};
	sprintf (cStringToPrint, "ButtonPressed %d", ucPressedCount);
	HAL_Delay(20);
	lcd_gotoxy (0,1);
	lcd_send_string (cStringToPrint);
	ucPressedCount++;
	HAL_Delay(10);
}

