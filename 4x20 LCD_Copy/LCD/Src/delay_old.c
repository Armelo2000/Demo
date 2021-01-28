/*

    All delay functions
	
*/
#include "delay.h"
//#include "stm32f10x.h"
#include "stm32f1xx_hal.h"

static __IO uint32_t uiTimeInUs = 0;
static __IO uint32_t usTicks = 0;

//static __IO uint32_t usTicks;

void SysTick_Init(uint32_t time)
{
    // Update SystemCoreClock value
    //SystemCoreClockUpdate();
    // Configure the SysTick timer to overflow every 1 us
    SysTick_Config(SystemCoreClock / time);
	
}

void SysTick_Handler_Not_Use()
{
	if (usTicks != 0)
	{
		usTicks--;
	}
	
  uiTimeInUs++;
}
uint32_t getUsTimer(void)
{
	return uiTimeInUs;
}

void TickWaitUs(uint32_t us)
{
	// Reload us value
	usTicks = us;
	// Wait until usTick reach zero
	while (usTicks);
}

void TickWaitMs(uint32_t ms)
{
	// Wait until ms reach zero
	while (ms--)
	{
		// Delay 1ms
		TickWaitUs(1000); //not 1000 because the systick is 100us
	}
}
// delay in millisecond
void delay(uint32_t uiTime)
{
	uint32_t CurrTime = getUsTimer();
	while((getUsTimer() - CurrTime) >= uiTime*1000);
}

// delay in microsecond
void delayUsxxx(uint32_t uiTimeInUs)
{
	uint32_t CurrTime = getUsTimer();
	while((getUsTimer() - CurrTime) >= uiTimeInUs);
}

void TIM2_IRQHandler(void)
{
	// increment the Tick
	uiTimeInUs++;

	TIM2->SR &= ~(0x00000001);
}

void delayUs(uint32_t uiTimeInUs)
{
  uint32_t tickstart = getUsTimer();
  uint32_t wait = uiTimeInUs;

  /* Add a freq to guarantee minimum wait */
  if (wait < 0xFFFFFFFFU)
  {
    wait += (uint32_t)1;
  }

  while ((getUsTimer() - tickstart) < wait)
  {
  }
}
