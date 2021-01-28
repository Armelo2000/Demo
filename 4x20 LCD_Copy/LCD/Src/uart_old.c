/*
 * uart.c
 *
 */




#include "uart.h"
//#include <stm32f10x.h> 
#include <stm32f1xx_hal.h> 
#include "stdint.h" 
#include "delay.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_usart.h"
//#include "stm32f10x_rcc.h"
#include "stm32f1xx_hal_gpio.h"

#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_uart.h"
//#include "misc.h"
#include "printer.h"

/*---------------  Bit Time ---------------*/

	/* Configure the USART1 */
	UART_HandleTypeDef huart1;
 
void usart_init(void)
{	
	
	/* Configure the GPIOs */
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable USART1 and GPIOA clock */
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	/* Enable the USARTx Interrupt */
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.Pin = GPIO_PIN_9;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;  //GPIO_Speed_50MHz;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.Pin = GPIO_PIN_10;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* USART1 configuration ------------------------------------------------------*/
	/* USART1 configured as follow:
		- BaudRate = 115200 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
		- USART Clock disabled
		- USART CPOL: Clock is active low
		- USART CPHA: Data is captured on the middle
		- USART LastBit: The clock pulse of the last data bit is not output to
			the SCLK pin
	 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = BAUDRATE;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;

  if(HAL_UART_Init(&huart1) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
	//USART_Init(USART1, &USART_InitStructure);

	/* Enable USART1 */
	//USART_Cmd(USART1, ENABLE);
	//USART1->CR1 |= 0x2000;

	/* Enable the USART1 Receive interrupt: this interrupt is generated when the
		USART1 receive data register is not empty */
	//HAL_UART_ITConfig(USART1, UART_IT_RXNE, ENABLE);
}


//USART Interrupt
void USART1_IRQHandler(void)
{
	static int x = 0;
	 x++;
}

/* This function write a character into a COM Port */
void PutChar(char ch)
{
	/* wait until the transmition is ready to be execute */
	while (!(USART1->SR & USART_SR_TXE));
  USART1->DR = (ch & 0x1FF);
	//delay(1);
}

/* This function write a string into a COM Port */
void PutString(char *str)
{
	int i;
	char acPosSet[2]={'\n','\r'};
  /* Set Position back to new line when new String is write */
  for(i=0; i<2; i++)
  {
	  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (acPosSet[i] & 0x1FF);
	}
	/* Go to through all Character until the end in reach and write them into COM Port */
	while(*str!= '\0')  /* The end of string is : \0 */
	{
	  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (*str & 0x1FF);
		str++;
		//delay(1);
	}
}
/* This function print a string into the printer */
void Println(char *str)
{
	int i;
	char acPosSet[2]={'\n','\r'};

	/* Go to through all Character until the end in reach and write them into COM Port */
	while(*str!= '\0')  /* The end of string is : \0 */
	{
	  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (*str & 0x1FF);
		str++;
		//delay(1);
	}
  /* Set Position back to new line when new String is write */
  for(i=0; i<2; i++)
  {
	  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (acPosSet[i] & 0x1FF);
	}
}

/* This function print a string into the printer */
void Print(char *str)
{
	/* Go to through all Character until the end in reach and write them into COM Port */
	while(*str!= '\0')  /* The end of string is : \0 */
	{
	  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (*str & 0x1FF);
		str++;
		//delay(1);
	}
}

/* This function print a decimal into the printer */
void PrintDec(uint32_t dec)
{
	uint8_t *pucDec;
	uint8_t aucDec[15]={0x00};
	uint8_t ucCount = 0;
  do
	{
		aucDec[ucCount++] = dec % 10;
		dec /= 10;
	}while(dec);
	pucDec = (uint8_t *)&aucDec[ucCount-1];
	/* Go to through all Character until the end in reach and write them into COM Port */
	while(ucCount--)  /* The end of string is : \0 */
	{
	  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = ((*pucDec + 0x30) & 0x1FF);
		pucDec--;
	}
}

/* This function go to a new line into the printer */
void Go2NewLine(void)
{
	int i;
	char acPosSet[2]={'\n','\r'};

  /* Set Position back to new line */
  for(i=0; i<2; i++)
  {
	  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (acPosSet[i] & 0x1FF);
	}
}

/* This function write a string into a COM Port */
void writecmd(uint8_t cmd)
{
  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (cmd & 0x1FF);
}

uint8_t UART_ByteReceive(uint8_t Buf)
{
	Buf = USART1->DR;
	if((Buf == 0x4F)||(Buf == 0x6F))
	{
		GPIOA->ODR ^= GPIO_ODR_ODR5;
	}
	return Buf;
}
