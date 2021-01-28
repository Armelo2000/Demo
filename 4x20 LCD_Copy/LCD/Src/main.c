/*
 * File:    	src/main.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	101
 * 
 * Description
 * -----------
 * The source file src/main.c initializes all other modules.
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include <string.h>
#include "delay.h"
#include "rtc_clock.h"
#include "command.h"
#include "uart.h"
#include "button.h"
#include "hc12.h"
#include "led.h"
/* USER CODE BEGIN Includes */
#include "i2c-lcd.h"
#include "lcd.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);


/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void I2C1_Init(void);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

TIM_HandleTypeDef htim1;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
	
extern UART_HandleTypeDef huart1;	
extern UART_HandleTypeDef huart3;	

/****************************************************************
							main
****************************************************************/
/*
 * Fct-Nr : 101.01
 *
 * int main(void);
 *
 * @Param: None
 * @Return: int.
 *
 * The function main initializes the other modules.
 */
int main(void)
{
	


  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
	
	//SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start(&htim1);
  //MX_I2C1_Init();
  I2C1_Init();
	//lcd_pin_init();
	//lcd_4bit_init();
#ifdef 0
  //! lcd Init
  lcd_init ();
	//lcd_pin_init();
	//lcd_4bit_init();
	//lcd_init_dummy();
	//LCD_Init();
	lcd_send_string("Hallo");
	lcd_gotoxy(0, 1);
	lcd_send_string("World");
	lcd_gotoxy(0, 2);
	lcd_send_string("Armel");
	lcd_gotoxy(0, 3);
	lcd_send_string("Tsannang");
	
  //lcd_4bit_send_data('A');
	
	// HD44780
	//lcd_init_1();
	//lcd_print("WELCOME");
	
	/*
  // For Debug purpose
  lcd_send_cmd(CLEARROW);
  HAL_Delay(20);
  lcd_gotoxy (0,0);
  lcd_send_string ("Hello world.");
  HAL_Delay(20);
*/
#else
  lcd_pin_init();
  lcd_init_4Bit();
	//lcd_init_dummy();
	//lcd_clear();
	
  //lcd_initx();
  lcd_put_cursorXY(0, 0);
  lcd_send_string_4Bit("Vorname: Armel");

	lcd_put_cursorXY(0, 1);
  lcd_send_string_4Bit("Name: Tsannang");
	lcd_put_cursorXY(0, 2);
  lcd_send_string_4Bit("Stadt: Siegen");
	lcd_put_cursorXY(0, 3);
	lcd_send_string_4Bit("Land: Deutschland");
#endif	
  while(1)
  {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  HAL_Delay(500);

  }
  /* USER CODE END 3 */

}

/****************************************************************
							SystemClock_Config
****************************************************************/
/*
 * Fct-Nr : 101.02
 *
 * void SystemClock_Config(void);
 *
 * @Param: None
 * @Return: None.
 *
 * The function SystemClock_Config configures the system clock.
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

/****************************************************************
							MX_I2C1_Init
****************************************************************/
/*
 * Fct-Nr : 101.03
 *
 * void MX_I2C1_Init(void);
 *
 * @Param: None
 * @Return: None.
 *
 * The function MX_I2C1_Init initialization of the I2C1.
 */
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
/****************************************************************
							MX_GPIO_Init
****************************************************************/
/*
 * Fct-Nr : 101.04
 *
 * void MX_GPIO_Init(void);
 *
 * @Param: None
 * @Return: None.
 *
 * The function MX_GPIO_Init Enable the GPIO Ports clock.
 */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

}

/****************************************************************
							_Error_Handler
****************************************************************/
/*
 * Fct-Nr : 101.05
 *
 * void _Error_Handler(uint8_t* file, uint32_t line);
 *
 * @param  file: The file name as string.
 * @param  line: The line in file as a number.
 * @Return: None.
 *
 * @brief  This function is executed in case of error occurrence.
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

/****************************************************************
							assert_failed
****************************************************************/
/*
 * Fct-Nr : 101.06
 *
 * void assert_failed(uint8_t* file, uint32_t line);
 *
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @Return: None.
 *
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred. ToDo
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/****************************************************************
							I2C1_Init
****************************************************************/
/*
 * Fct-Nr : 101.07
 *
 * void I2C1_Init(void);
 *
 * @Param: None
 * @Return: None.
 *
 * The function I2C1_Init initialization of the I2C1.
 */
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

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 72-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM1)
  {
    __HAL_RCC_TIM1_CLK_ENABLE();
	}
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
