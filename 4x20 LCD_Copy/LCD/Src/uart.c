/*
 * File:    	src/uart.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	103
 * 
 * Description
 * -----------
 * The source file src/uart.c contains functions to uart.
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */



#ifdef ORIGINAL_A
	#include "uart.h"
	#include <stm32f10x.h> 
	#include "stdint.h" 
	#include "delay.h"
	#include "stm32f10x_gpio.h"
	#include "stm32f10x_usart.h"
	#include "stm32f10x_rcc.h"
	#include "misc.h"
	#include "printer.h"
#else
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
#endif

/*---------------  Bit Time ---------------*/

/* Configure the USART1 */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
UART_HandleTypeDef *hc12;
UART_HandleTypeDef *ftdi;

/****************************************************************
							usart_init
****************************************************************/
/*
 * Fct-Nr : 103.01
 *
 * void usart_init(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function usart_init initializes the uart peripheral without DMA.
 */
void usart_init(void)
{	
	
	/* Configure the GPIOs */
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable USART1 and GPIOA clock */
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	

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
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;

  if(HAL_UART_Init(&huart1) != HAL_OK)
  {
    /* Initialization Error */
    //Error_Handler();
  }
	//USART_Init(USART1, &USART_InitStructure);

	/* Enable USART1 */
	//USART_Cmd(USART1, ENABLE);
	//USART1->CR1 |= 0x2000;

	/* Enable the USART1 Receive interrupt: this interrupt is generated when the
		USART1 receive data register is not empty */
	//HAL_UART_ITConfig(USART1, UART_IT_RXNE, ENABLE);
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	
	/* Enable the USARTx Interrupt */
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/****************************************************************
							usart_dma_init
****************************************************************/
/*
 * Fct-Nr : 103.02
 *
 * void usart_dma_init(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function usart_dma_init initializes the uart 1 peripheral with DMA.
 */
void usart_dma_init(void)
{
	/* Configure the GPIOs */
	GPIO_InitTypeDef GPIO_InitStructure;
	
  static DMA_HandleTypeDef hdma_tx;
  static DMA_HandleTypeDef hdma_rx;
  
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();

  /* Enable USARTx clock */
  __HAL_RCC_USART1_CLK_ENABLE();

  /* Enable DMA clock */
  __HAL_RCC_DMA1_CLK_ENABLE();
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* UART TX GPIO pin configuration  */
  GPIO_InitStructure.Pin       = GPIO_PIN_9;
  GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull      = GPIO_PULLUP;
  GPIO_InitStructure.Speed     = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStructure.Pin = GPIO_PIN_10;
  GPIO_InitStructure.Mode      = GPIO_MODE_INPUT;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;	//BAUDRATE;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;

  if(HAL_UART_Init(&huart1) != HAL_OK)
  {
    /* Initialization Error */
    //Error_Handler();
  }
  hc12 = &huart1;
	
  /*##-3- Configure the DMA ##################################################*/
  /* Configure the DMA handler for Transmission process */
  hdma_tx.Instance                 = USART1_TX_DMA_CHANNEL;
  hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_tx.Init.Mode                = DMA_NORMAL;    //DMA_CIRCULAR;  //DMA_NORMAL;
  hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;

  HAL_DMA_Init(&hdma_tx);

  /* Associate the initialized DMA handle to the UART handle */
  __HAL_LINKDMA(&huart1, hdmatx, hdma_tx);

  /* Configure the DMA handler for reception process */
  hdma_rx.Instance                 = USART1_RX_DMA_CHANNEL;
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_rx.Init.Mode                = DMA_NORMAL;				//DMA_CIRCULAR;  //
  hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;

  HAL_DMA_Init(&hdma_rx);

  /* Associate the initialized DMA handle to the the UART handle */
  __HAL_LINKDMA(&huart1, hdmarx, hdma_rx);
    
  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt (USART1_TX) */
  //HAL_NVIC_SetPriority(USARTx_DMA_TX_IRQn, 0, 1);
  //HAL_NVIC_EnableIRQ(USARTx_DMA_TX_IRQn);
    
  /* NVIC configuration for DMA transfer complete interrupt (USART1_RX) */
  HAL_NVIC_SetPriority(USART1_DMA_RX_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(USART1_DMA_RX_IRQn);
  
  /* NVIC for USART, to catch the TX complete */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/****************************************************************
							usart_dma_init
****************************************************************/
/*
 * Fct-Nr : 103.03
 *
 * void usart3_dma_init(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function usart3_dma_init initializes the uart 3 peripheral with DMA.
 */
void usart3_dma_init(void)
{
	/* Configure the GPIOs */
	GPIO_InitTypeDef GPIO_InitStructure;
	
  static DMA_HandleTypeDef hdma_tx;
  static DMA_HandleTypeDef hdma_rx;
  
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
	__HAL_RCC_GPIOB_CLK_ENABLE();

  /* Enable USARTx clock */
  __HAL_RCC_USART3_CLK_ENABLE();

  /* Enable DMA clock */
  __HAL_RCC_DMA1_CLK_ENABLE();
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* UART TX GPIO pin configuration  */
  GPIO_InitStructure.Pin       = GPIO_PIN_10;
  GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull      = GPIO_PULLUP;
  GPIO_InitStructure.Speed     = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStructure.Pin = GPIO_PIN_11;
  GPIO_InitStructure.Mode      = GPIO_MODE_INPUT;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;   //BAUDRATE;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;

  if(HAL_UART_Init(&huart3) != HAL_OK)
  {
    /* Initialization Error */
    //Error_Handler();
  }
  ftdi = &huart3;
	
  /*##-3- Configure the DMA ##################################################*/
  /* Configure the DMA handler for Transmission process */
  hdma_tx.Instance                 = USART3_TX_DMA_CHANNEL;
  hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_tx.Init.Mode                = DMA_NORMAL;    //DMA_CIRCULAR;  //DMA_NORMAL;
  hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;

  HAL_DMA_Init(&hdma_tx);

  /* Associate the initialized DMA handle to the UART handle */
  __HAL_LINKDMA(&huart1, hdmatx, hdma_tx);

  /* Configure the DMA handler for reception process */
  hdma_rx.Instance                 = USART3_RX_DMA_CHANNEL;
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_rx.Init.Mode                = DMA_NORMAL;				//DMA_CIRCULAR;  //
  hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;

  HAL_DMA_Init(&hdma_rx);

  /* Associate the initialized DMA handle to the the UART handle */
  __HAL_LINKDMA(&huart3, hdmarx, hdma_rx);
    
  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt (USART1_TX) */
  //HAL_NVIC_SetPriority(USARTx_DMA_TX_IRQn, 0, 1);
  //HAL_NVIC_EnableIRQ(USARTx_DMA_TX_IRQn);
    
  /* NVIC configuration for DMA transfer complete interrupt (USART1_RX) */
  HAL_NVIC_SetPriority(USART3_DMA_RX_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(USART3_DMA_RX_IRQn);
  
  /* NVIC for USART, to catch the TX complete */
  HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
}


/****************************************************************
							USART1_IRQHandler
****************************************************************/
/*
 * Fct-Nr : 103.04
 *
 * void USART1_IRQHandler(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function USART1_IRQHandler is the uart interrupt for the uart 1.
 */
void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

/****************************************************************
							DMA1_Channel5_IRQHandler
****************************************************************/
/*
 * Fct-Nr : 103.05
 *
 * void DMA1_Channel5_IRQHandler(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function DMA1_Channel5_IRQHandler is the DMA1 interrupt for the Channel 5.
 */
void DMA1_Channel5_IRQHandler(void)
{
	HAL_DMA_IRQHandler(huart1.hdmarx);
}

/****************************************************************
							DMA1_Channel4_IRQHandler
****************************************************************/
/*
 * Fct-Nr : 103.06
 *
 * void DMA1_Channel4_IRQHandler(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function DMA1_Channel4_IRQHandler is the DMA1 interrupt for the Channel 4.
 */
void DMA1_Channel4_IRQHandler(void)
{
	HAL_DMA_IRQHandler(huart1.hdmatx);
}

/****************************************************************
							PutChar
****************************************************************/
/*
 * Fct-Nr : 103.07
 *
 * void PutChar(char ch);
 *
 * @Param: ch - character to send
 * @Return: None
 *
 * The function PutChar writes a character to the TX Buffer of UART1.
 */
/* This function write a character into a COM Port */
void PutChar(char ch)
{
	/* wait until the transmition is ready to be execute */
	while (!(USART1->SR & USART_SR_TXE));
  USART1->DR = (ch & 0x1FF);
	//delay(1);
}

/****************************************************************
							PutString
****************************************************************/
/*
 * Fct-Nr : 103.08
 *
 * void PutString(char *str);
 *
 * @Param: str - pointer to string to send through the UART
 * @Return: None
 *
 * The function PutString writes a string to the TX Buffer of UART1.
 */
/* This function write a character into a COM Port */
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

/****************************************************************
							Println
****************************************************************/
/*
 * Fct-Nr : 103.09
 *
 * void Println(char *str);
 *
 * @Param: str - pointer to string to send through the UART
 * @Return: None
 *
 * This function print a string with return to new line into the printer.
 */
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
/****************************************************************
							Print
****************************************************************/
/*
 * Fct-Nr : 103.10
 *
 * void Println(char *str);
 *
 * @Param: str - pointer to string to send through the UART
 * @Return: None
 *
 * This function print a string into the printer.
 */
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

/****************************************************************
							PrintDec
****************************************************************/
/*
 * Fct-Nr : 103.11
 *
 * void PrintDec(uint32_t dec);
 *
 * @Param: dec - Decimal value to print with the printer
 * @Return: None
 *
 * This function print a decimal into the printer
 */
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

/****************************************************************
							Go2NewLine
****************************************************************/
/*
 * Fct-Nr : 103.12
 *
 * void Go2NewLine(void);
 *
 * @Param: None
 * @Return: None
 *
 * This function go to a new line into the printer
 */
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

/****************************************************************
							writecmd
****************************************************************/
/*
 * Fct-Nr : 103.13
 *
 * void writecmd(uint8_t cmd);
 *
 * @Param: cmd - command to be write
 * @Return: None
 *
 * This function write a string into a COM Port
 */
void writecmd(uint8_t cmd)
{
  /* wait until the transmition is ready to be execute */
	  while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (cmd & 0x1FF);
}

/****************************************************************
							UART_ByteReceive
****************************************************************/
/*
 * Fct-Nr : 103.14
 *
 * void UART_ByteReceive(uint8_t Buf);
 *
 * @Param: Buf - Buffer for received Byte
 * @Return: received Byte
 *
 * This function returned the received Byte
 */
uint8_t UART_ByteReceive(uint8_t Buf)
{
	Buf = USART1->DR;
	if((Buf == 0x4F)||(Buf == 0x6F))
	{
		GPIOA->ODR ^= GPIO_ODR_ODR5;
	}
	return Buf;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//HAL_UART_Receive_DMA(&huart1, (uint8_t *)&tTelRecv, sizeof(tTelRecv));
	
	if(huart == &huart1)
	{
		//uart 1
		(void)CheckRecvTelg();
	}
	else if(huart == &huart3)
	{
		
	}
	else
	{
		
	}
					
}




