/*
 * File:    	inc/delay.h
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * 
 * Description
 * -----------
 * Contains all defines for the delay.
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */
 
#ifndef _DELAY_H
#define _DELAY_H

#include "stdint.h"

#define BYTE		unsigned char
typedef enum
{
	second = 0,
	millisecond,
	microsecond
}Timerange;

void usDelay(uint32_t usmdelay);

#ifdef ZERO
uint32_t getUsTimer(void);
void delay(uint32_t uiTime);
void delayUs(uint32_t uiTimeInUs);
void SysTick_Init(uint32_t time);
void TickWaitMs(uint32_t ms);
void TickWaitUs(uint32_t us);

#else
void setSecond(uint32_t val);
void setMillisecond(uint32_t val);
void setMicrosecond(uint32_t val);
void TIM2_Init(uint32_t time, Timerange unit);
#endif

#endif
