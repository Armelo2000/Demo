/*
 * File:    	src/delay.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	105
 * 
 * Description
 * -----------
 * The source file src/delay.c contains the CRC Table for the 
 * CRC16 cyclic redundancy check values. There is no function here.
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */
 
#include "delay.h"
//#include "stm32f10x.h"
#include "stm32f1xx_hal.h"

static uint32_t uiTimeInUs = 0;

/****************************************************************
							TIM2_Init
****************************************************************/

/*
 * Fct-Nr : 105.01
 *
 * void TIM2_Init(uint32_t time, Timerange unit);
 *
 * @Param: time - initialization time for Timer 2.
 * @Param: unit - represent the unit of time. Possible values are :
 *				  	- microsecond
 *				  	- millisecond
 *				  	- second
 * @Return: None.
 *
 * The function TIM2_Init() initializes the Timer 2 with a given time 
 * in microsecond, millisecond or second.
 */
void TIM2_Init(uint32_t time, Timerange unit)
{
	// enable Clock for Timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if(unit == second)
	{
		 setSecond(time);
	}
	else if (unit == millisecond)
	{
		 setMillisecond(time);
	}
	else if (unit == microsecond)
	{
		 setMicrosecond(time);
	}
	else
	{
		// do nothing here. Just for the test
	}
	// Timer interrupt enable
	TIM2->DIER |= 0x00000001;
	// Timer enable
	TIM2->CR1 |= 0x00000001;
}

/****************************************************************
							setSecond
****************************************************************/

/*
 * Fct-Nr : 105.02
 *
 * void setSecond(uint32_t val)
 *
 * @Param: val - value in second to set
 * @Return: None
 *
 * Set the value of PSC and ARR in the Timer 2 to get the Timer trigger in second ticks.
 */
void setSecond(uint32_t val)
{
	uint32_t tmpARR = 0;  // temporary ARR register
	uint32_t tmpPSC = 1;  // temporary PSC register
	uint32_t exceeded;
	uint32_t HClock;
	tmpARR = SystemCoreClock * val;
	HClock = tmpARR;
	// the maximum time value to configure is 10s
	exceeded = val > 10? 1:0;
	if(!(exceeded))
	{
		while(tmpARR > 0xFFFF)
		{
			while(((HClock / tmpPSC)>0xFFFF)||(HClock % tmpPSC))
			{
				tmpPSC++;
			}
			tmpARR = HClock / tmpPSC;
			// just break up if the PSC is bigger than 0xFFFF (PSC is only 16 bits)
			if(tmpPSC > 0xFFFF)
				break;
		}
		
		if(!(tmpPSC > 0xFFFF))
		{
			// set the register
			TIM2->PSC = tmpPSC - 1;
			TIM2->ARR = tmpARR - 1;
		}
		else
		{
			// the time value cannot be set
			//printf("The value is exceeded");
		}
	}
	else
	{
		// Overflow the value is big
	}
}

/****************************************************************
							setMillisecond
****************************************************************/

/*
 * Fct-Nr : 105.03
 *
 * void setMillisecond(uint32_t val)
 *
 * @Param: val - value in millisecond to set
 * @Return: None
 *
 * Set the value of PSC and ARR in the Timer 2 to get the Timer trigger in millisecond ticks.
 */
 
void setMillisecond(uint32_t val)
{
	uint32_t tmpARR = 0;  // temporary ARR register
	uint32_t tmpPSC = 1;  // temporary PSC register
	uint32_t exceeded;
	uint32_t HClock;
	tmpARR = (SystemCoreClock / 1000) * val;
	HClock = tmpARR;
	// the maximum time value to configure is 10s (10000ms)
	exceeded = val > 10000? 1:0; 
	if(!(exceeded))
	{
		while(tmpARR > 0xFFFF)
		{
			while(((HClock / tmpPSC)>0xFFFF)||(HClock % tmpPSC))
			{
				tmpPSC++;
			}
			tmpARR = HClock / tmpPSC;
			// just break up if the PSC is bigger than 0xFFFF (PSC is only 16 bits)
			if(tmpPSC > 0xFFFF)
				break;
		}
		
		if(!(tmpPSC > 0xFFFF))
		{
			// set the register
			TIM2->PSC = tmpPSC - 1;
			TIM2->ARR = tmpARR - 1;
		}
		else
		{
			// the time value cannot be set
			//printf("The value is exceeded");
		}
	}
	else
	{
		// Overflow the value is big	
	}
}

/****************************************************************
							setMicrosecond
****************************************************************/

/*
 * Fct-Nr : 105.04
 *
 * void setMicrosecond(uint32_t val)
 *
 * @Param: val - value in microsecond to set
 * @Return: None
 *
 * Set the value of PSC and ARR in the Timer 2 to get the Timer trigger in microsecond ticks.
 */
 
void setMicrosecond(uint32_t val)
{
	uint32_t tmpARR = 0;  // temporary ARR register
	uint32_t tmpPSC = 1;  // temporary PSC register
	uint32_t exceeded;
	uint32_t HClock;
	tmpARR = (SystemCoreClock / 1000000) * val;
	HClock = tmpARR;
	// the maximum time value to configure is 10s (10000000us)
	exceeded = val > 10000000? 1:0; 
	if(!(exceeded))
	{
		while(tmpARR > 0xFFFF)
		{
			while(((HClock / tmpPSC)>0xFFFF)||(HClock % tmpPSC))
			{
				tmpPSC++;
			}
			tmpARR = HClock / tmpPSC;
			// just break up if the PSC is bigger than 0xFFFF (PSC is only 16 bits)
			if(tmpPSC > 0xFFFF)
				break;
		}
		
		if(!(tmpPSC > 0xFFFF))
		{
			// set the register
			TIM2->PSC = tmpPSC - 1;
			TIM2->ARR = tmpARR - 1;
		}
		else
		{
			// the time value cannot be set
			//printf("The value is exceeded");
		}
	}
	else
	{
		// Overflow the value is big
	}
}

/****************************************************************
							getUsTimer
****************************************************************/

/*
 * Fct-Nr : 105.04
 *
 * uint32_t getUsTimer(void)
 *
 * @Param: None
 * @Return:  current value of Timer in microsecond	 
 *
 * Return the current value in microsecond ticks.
 */

uint32_t getUsTimer(void)
{
	return uiTimeInUs;
}

/****************************************************************
							delay
****************************************************************/
/*
 * Fct-Nr : 105.05
 *
 * void delay(uint32_t uiTime)
 *
 * @Param: uiTime - value to set to wait in millisecond ticks
 * @Return:  None
 *
 * Delay function to wait in millisecond ticks.
 */
 
void delay(uint32_t uiTime)
{
	uint32_t CurrTime = getUsTimer();
	while((getUsTimer() - CurrTime) >= uiTime*1000);
}

/****************************************************************
							delayUs
****************************************************************/
/*
 * Fct-Nr : 105.06
 *
 * void delayUs(uint32_t uiTimeInUs)
 *
 * @Param: uiTimeInUs - value to set to wait in microsecond ticks
 * @Return:  None
 *
 * Delay function to wait in microsecond ticks.
 */
 
void delayUs(uint32_t uiTimeInUs)
{
	uint32_t CurrTime = getUsTimer();
	while((getUsTimer() - CurrTime) >= uiTimeInUs);
}

/****************************************************************
							TIM2_IRQHandler
****************************************************************/
/*
 * Fct-Nr : 105.07
 *
 * void TIM2_IRQHandler(void)
 *
 * @Param: None
 * @Return: None
 *
 * Timer Interrupt Handler .
 */
void TIM2_IRQHandler(void)
{
	// increment the Tick
	uiTimeInUs++;
	//reset the flag
	TIM2->SR &= ~(0x00000001);
}

/****************************************************************
							usDelay
****************************************************************/
/*
 * Fct-Nr : 105.08
 *
 * void usDelay(uint32_t usmdelay)
 *
 * @Param: usmdelay - value to set to wait in microsecond ticks
 * @Return:  None
 *
 * Delay function to wait in microsecond ticks.
 */
void usDelay(uint32_t usmdelay)
{
  __IO uint32_t DelayInUs = usmdelay * (SystemCoreClock / 8U / 1000000U);
  do 
  {
    __NOP();
  } 
  while (DelayInUs --);
}
