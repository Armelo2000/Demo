
/* Timer */

#include "timer.h"

#ifdef TIMER6_USED
void TIM6_Config(void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	
// 1. Enable Timer clock
	RCC->APB1ENR |= (1<<4);  // Enable the timer6 clock
	
// 2. Set the prescalar and the ARR
	TIM6->PSC = 72-1;  // 72MHz/72 = 1 MHz ~~ 1 uS delay
	TIM6->ARR = 0xFFFF - 1;  // MAX ARR value
	
// 3. Enable the Timer, and wait for the update Flag to set
	TIM6->CR1 |= (1<<0); // Enable the Counter
	while (!(TIM6->SR & (1<<0)));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
}
#endif

void Delay_us(uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us, 
		 the total waiting time will be the required us delay
	************************************************/
	TIM1->CNT = 0;
	while (TIM1->CNT < us);
}

void TIM1_Config(void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Set the update flag UG in the register EGR
	4. Enable the Timer in the register CR1 (CEN = 1)
	************************************************/
	
// 1. Enable Timer clock
	RCC->APB2ENR |= (1 << 11);  // Enable the timer 1 clock
	
// 2. Set the prescalar and the ARR
	TIM1->PSC = 72-1;  // 72MHz/72 = 1 MHz ~~ 1 uS delay
	TIM1->ARR = 0xFFFF - 1;  // MAX ARR value
	
// 3. Set the update flag UG in the register EGR
	TIM1->EGR |= (1 << 0);

// 4. Enable the Timer in the register CR1 (CEN = 1)	
	TIM1->CR1 |= (1 << 0); // Enable the Counter
}
