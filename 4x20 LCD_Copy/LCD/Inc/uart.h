/*
 * DALI_CMD.h
 *
 */

#ifndef UART_H_
#define UART_H_

#include "stdint.h" 
#include "stm32f1xx_hal.h"
 
/* ******* Prototype ********* */
void usart_init(void);
void usart_dma_init(void);
void usart3_dma_init(void);

void PutChar(char ch);
void PutString(char *str);
void Println(char *str);
void Print(char *str);
void PrintDec(uint32_t dec);
void Go2NewLine(void); 

void writecmd(uint8_t cmd);
uint8_t UART_ByteReceive(uint8_t Buf);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/* UART flags definition */
#define UART_TxFull          0x0200
#define UART_RxHalfFull      0x0100
#define UART_TimeOutIdle     0x0080
#define UART_TimeOutNotEmpty 0x0040
#define UART_OverrunError    0x0020
#define UART_FrameError      0x0010
#define UART_ParityError     0x0008
#define UART_TxHalfEmpty     0x0004
#define UART_TxEmpty         0x0002
#define UART_RxBufFull       0x0001

/* Definition for USARTx's DMA */
#define USART1_TX_DMA_CHANNEL             DMA1_Channel4
#define USART1_RX_DMA_CHANNEL             DMA1_Channel5
#define USART3_TX_DMA_CHANNEL             DMA1_Channel2
#define USART3_RX_DMA_CHANNEL             DMA1_Channel3

/* Definition for USARTx's NVIC */
#define USART1_DMA_TX_IRQn                DMA1_Channel4_IRQn
#define USART1_DMA_RX_IRQn                DMA1_Channel5_IRQn
#define USART3_DMA_TX_IRQn                DMA1_Channel2_IRQn
#define USART3_DMA_RX_IRQn                DMA1_Channel3_IRQn
#define USART1_DMA_TX_IRQHandler          DMA1_Channel4_IRQHandler
#define USART1_DMA_RX_IRQHandler          DMA1_Channel5_IRQHandler
#define USART3_DMA_TX_IRQHandler          DMA1_Channel2_IRQHandler
#define USART3_DMA_RX_IRQHandler          DMA1_Channel3_IRQHandler


	


#endif /* UART_H_ */
