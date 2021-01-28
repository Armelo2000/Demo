
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include <string.h>
#include "printer_p.h"
#include "flash.h"
#include "delay.h"
#include "rtc_clock.h"
#include "command.h"
#include "uart.h"

/* USER CODE BEGIN Includes */
#include "i2c-lcd.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char mavariable_buf[8]; //affichage variable
int mavariable = 200;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

void printTicket(void);

uint16_t usTicketNumber;
uint16_t flash16 = 0;
uint8_t flash8 = 0;

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void I2C1_Init(void);
void Exti_CallBack(void);
void  ButtonInit(void);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
PRINTER printer;
uint8_t printerFlag = 0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
	
extern UART_HandleTypeDef huart1;	
extern UART_HandleTypeDef huart3;	
telremotecontoller_t tTelRecv;
telprinter_t tTel2Send;
	
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_DMA(&huart1, (uint8_t *)&tTelRecv, sizeof(tTelRecv));
}

uint32_t readflash;
uint16_t tmp1, tmp2;
uint8_t aucTmp[2];
uint8_t * pucTmp1;
int main(void)
{
	time_t *time;
	char buffer[15];
	uint8_t command;
	

  lcd_line_move lcd_info = {1};
  (void)lcd_info;
  tmp1 = 0x5AC2;
   aucTmp[0] = tmp1 & 0xFF;
	 aucTmp[1] = (tmp1 >>8) & 0xFF;
  tmp2 = (aucTmp[1] << 8) | aucTmp[0];
  pucTmp1 = (uint8_t *)&tmp1;
  tmp1 = sizeof(tTelRecv);
  tmp2 = sizeof(tTel2Send);
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  //SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  //I2C1_Init();
  usart_dma_init();
  ButtonInit();
 
 //NVIC_EnableIRQ(TIM2_IRQn); 
 //TIM2_Init(100, microsecond);
 
#ifndef ONLYLCD
  /* USER CODE BEGIN 2 */
	lcd_init ();
	lcd_send_cmd(CLEARROW);
	HAL_Delay(2);
	lcd_gotoxy (0,0);
	//lcd_send_string ("Hello world !!");
	HAL_Delay(2);
#endif
	
	Init_Funct_Pointer(&printer);
	printer.begin(80);
	
	lcd_gotoxy(0,0);
	lcd_send_string ("timeBuffer");
//printTicket();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//while(1);
		HAL_Delay(50);
		HAL_UART_Receive_DMA(&huart1, (uint8_t *)&tTelRecv, sizeof(tTelRecv));
	ResetPage(126);
	ResetPage(127);
	Flash_Write(126, 0, 0x4B2E);
	Flash_Write(126, 2, 0xAC05);
	Flash_Write(126, 4, 0x0C42);
	Flash_Write_xHalfWord(126, 6, (uint8_t *)"Hallo", 5);
	Flash_Write(127, 0, 0x530E);
	Flash_Write(127, 8, 0x4B06);
	readflash = Flash_Read(126, 0);
	readflash |= (Flash_Read(126, 2)<<16);

  while(1)
  {

		time=Get_Time();
		buffer[14] = 1;
		
		buffer[14] = COMMAND_COMPARE(command, 'A');
		if((char)command == 'A')
		{
			lcd_gotoxy (0,1);
			lcd_send_string ("COMMAND OK");
			command = 0;		
			HAL_Delay(50);		
		}
		
		if(tTelRecv.cmd == CMD_READ_TIME)
		{
			char timeBuffer[16];
			time_t *timetmp = Get_Time();
			sprintf (timeBuffer, "%02d:%02d:%02d", timetmp->hour, timetmp->minutes, timetmp->seconds);
			lcd_gotoxy(0,0);
			lcd_send_string (timeBuffer);
			 
		}

		if(tTelRecv.cmd == CMD_READ_DATE)
		{
			char timeBuffer[16];
			time_t *timetmp = Get_Time();
			sprintf (timeBuffer, "%02d-%02d-20%02d", timetmp->dayofmonth, timetmp->month, timetmp->year);
			lcd_gotoxy(0,1);
			lcd_send_string (timeBuffer);
		}
		
		if(tTelRecv.cmd == CMD_READ_TEMP)
		{
			char timeBuffer[16];
			float temp = Get_Temp();
			sprintf (timeBuffer, "%.01f C", temp);
			lcd_gotoxy(11,0);
			lcd_send_string (timeBuffer);
		}
		if(tTelRecv.cmd == CMD_WRITE_DATE)
		{
			uint8_t *pucRecvTel = (uint8_t *)&tTelRecv;
			char printText[50];
			sprintf(printText, "Date has been set to : %02d-%02d-20%02d \n\r\0", pucRecvTel[2], pucRecvTel[3], pucRecvTel[4]);
			WriteDate(pucRecvTel[1], pucRecvTel[2], pucRecvTel[3], pucRecvTel[4]);
			HAL_UART_Transmit(&huart1, (uint8_t *)&printText[0], sizeof(printText), 1000);
			tTelRecv.cmd = 0xFF;
		}
		if(tTelRecv.cmd == CMD_WRITE_TIME)
		{
			uint8_t *pucRecvTel = (uint8_t *)&tTelRecv;
			WriteTime(pucRecvTel[3], pucRecvTel[2], pucRecvTel[1]);
			tTelRecv.cmd = 0xFF;
		}	
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

void I2C1_Init(void)
{
  //uint32_t flag = 0;
	// Enable clock for GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	// Enable clock for GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		// Enable clock for GPIOC
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		// Enable clock for GPIOD
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	// Enable clock for I2C
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	
	  /**I2C1 GPIO Configuration    
    PB8    ------> I2C1_SCL
    PB9    ------> I2C1_SDA 
	*/
	// Pin8 MODE8 = 0x03(Max speed : 50MHz) - CNF8 = 0x03
	// Pin9 MODE9 = 0x03(Max speed : 50MHz) - CNF9 = 0x03
	GPIOB->CRH |= 0x000000FF;
	
	// Alternate Function AFIO remap = 1 for I2C
	AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
	
	// reset the I2C peripheral first before the configuration start
	I2C1->CR1 |= (1 << 15);
	I2C1->CR1 &= ~(1 << 15);
	I2C1->CR2 = 36;
	I2C1->TRISE = 37;
	I2C1->CCR = 180;
	I2C1->CR1 = 0;
	I2C1->OAR1 = 0x00004000;
	I2C1->OAR2 = 0x00000000;
	/* Enable the I2C1 peripheral */
	I2C1->CR1 |= 0x00000001;
	
	//flag = I2C1->SR2 & 0x02;
	
	hi2c1.ErrorCode = HAL_I2C_ERROR_NONE;
  hi2c1.State = HAL_I2C_STATE_READY;
  hi2c1.PreviousState = HAL_I2C_MODE_NONE;
  hi2c1.Mode = HAL_I2C_MODE_NONE;
	hi2c1.Lock = HAL_UNLOCKED;
	
}

void printTicket(void)
{
	usTicketNumber = Flash_Read(126, 0);
	printer.justify('C');
  printer.setSize('M');
	printer.boldOn();
	printer.println("AFRILAND FIRSTBANK");
	
	printer.justify('L');
  printer.setSize('S');
	printer.println("Date: ");
	printer.println("Time: ");
	
	printer.justify('C');
  printer.setSize('M');
	printer.println("NUMBER");
	printer.printNumber(usTicketNumber);
	printer.NewLine();

	printer.justify('C');
  printer.setSize('S');
	printer.println("****** Welcome ******");	
	printer.println("****** Bienvenue ******");
	printer.NewLine();
	printer.NewLine();
	
	printer.doubleWidthOn();

	usTicketNumber +=1;

	Flash_Write(126, 0, usTicketNumber);
  Flash_Write(126, 0, usTicketNumber);
	
}

void ButtonInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_ConfigTypeDef EXTI_InitStructure;
	EXTI_HandleTypeDef hexti;

  /* Enable the BUTTON Clock */
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  /* Configure Button pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;  //GPIO_MODE_INPUT | 0x10000000U;
  GPIO_InitStructure.Pin =  GPIO_PIN_13;
	//GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Connect Button EXTI Line to Button GPIO Pin */
    //GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);

    /* Configure Button EXTI line */
    EXTI_InitStructure.Line = EXTI_LINE_13;
    EXTI_InitStructure.Mode = EXTI_MODE_INTERRUPT;
    EXTI_InitStructure.Trigger = EXTI_TRIGGER_RISING; // or EXTI_TRIGGER_FALLING
    EXTI_InitStructure.GPIOSel = EXTI_GPIOC;
	
	  hexti.Line = EXTI_LINE_13;
		hexti.PendingCallback = Exti_CallBack;
		HAL_EXTI_SetConfigLine(&hexti, &EXTI_InitStructure);
    //EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure); */

		/* EXTI interrupt init*/
		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void Exti_CallBack(void)
{
	int y=0;
	y++;
	printerFlag = 1;
	
}

void EXTI15_10_IRQHandler(void)
{
	int x = 0;
	x++;
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
	//EXTI->PR = EXTI_LINE_13;
	Exti_CallBack();
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
