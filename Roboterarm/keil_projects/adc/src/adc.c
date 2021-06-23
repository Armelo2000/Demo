/* ADC */

#include "adc.h"

void ADC_Init(void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable ADC and GPIO clock
	2. Set the ADC prescalar in the (RCC_CFGR)
	3. Set the Scan Mode and Resolution in the Control Register 1 (CR1)
	4. Set the Continuous Conversion, EOC, and Data Alignment in Control Reg 2 (CR2)
	5. Set the Sampling Time for the channels in ADC_SMPRx
	6. Set the Regular channel sequence length in ADC_SQR1
	7. Set the Respective GPIO PINs in the Analog Mode
	************************************************/
	
//1. Enable ADC and GPIO clock
	RCC->APB2ENR |= (1<<9);  // enable ADC1 clock
	RCC->APB2ENR |= (1<<2);  // enable GPIOA clock
	
//2. Set the ADC prescalar in the (RCC_CFGR)
	RCC->CFGR |= (1 << 14);		 //PCLK2 divide by 4
	//ADC1->CCR |= 1<<16;  		 // PCLK2 divide by 4 (This is used in cortex M4)
	
//3. Set the Scan Mode and Resolution in the Control Register 1 (CR1)	
	ADC1->CR1 = (1 << 8);    // SCAN mode enabled
	ADC1->CR1 &= ~(1 << 24);   // 12 bit RES
	
//4. Set the Continuous Conversion, EOC, and Data Alignment in Control Reg 2 (CR2)
	ADC1->CR2 = (1<<1);     // enable continuous conversion mode
	ADC1->CR2 |= (1<<10);    // EOC after each conversion
	ADC1->CR2 &= ~(1<<11);   // Data Alignment RIGHT
	
//5. Set the Sampling Time for the channels	
	ADC1->SMPR2 &= ~((7<<3) | (7<<12));  // Sampling time of 3 cycles for channel 1 and channel 4

//6. Set the Regular channel sequence length in ADC_SQR1
	ADC1->SQR1 |= (2<<20);   // SQR1_L =2 for 3 conversions
	
//7. Set the Respective GPIO PINs in the Analog Mode	
   GPIOA->CRL &=~ (0x0F << 4);   // PA1 -> analog mode
   GPIOA->CRL &=~ (0x0F << 16);   // PA4 -> analog mode
	 
	//GPIOA->MODER |= (3<<2);  // analog mode for PA 1 (for Cortex M4)
	//GPIOA->MODER |= (3<<8);  // analog mode for PA 4 (for Cortex M4)
	
	
	/**************************************************************************************************/
	
	
	// Sampling Freq for Temp Sensor 
	ADC1->SMPR1 |= (7<<24);  // Sampling time of 21 us
	
	// Set the TSVREFE Bit to wake the sensor
	ADC1->CR2 |= (1<<23);
	//ADC1->CCR |= (1<<23);		// This is used in Cortex M4
	
	// Enable DMA for ADC
	ADC1->CR2 |= (1<<8);
	
	// Enable Continuous Request
	ADC1->CR2 |= (1<<9);
	
	// Channel Sequence
	ADC1->SQR3 |= (1<<0);  // SEQ1 for Channel 1
	ADC1->SQR3 |= (4<<5);  // SEQ2 for CHannel 4
	ADC1->SQR3 |= (18<<10);  // SEQ3 for CHannel 18
}

