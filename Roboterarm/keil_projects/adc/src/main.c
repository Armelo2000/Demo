


/*
   MAIN 


*/
#include "timer.h"
#include "adc.h"
#include "stdint.h"

uint8_t bFlag = 0;

int main(void)
{
  TIM1_Config();
	ADC_Init();

  while(1){
		bFlag = !bFlag;
		Delay_us(1000);
  
  }
}
