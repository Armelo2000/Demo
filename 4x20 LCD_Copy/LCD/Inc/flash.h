/*
   flash.h
   
*/
#ifndef FLASH_H_
#define FLASH_H_

#include "stdint.h"

#define MAX_PAGE	128		//! 128kb flash
#define READY		0
#define BUSY		1
#define LOCK		0
#define UNLOCK		1

#define EEPROM_START_ADDR			((uint32_t)0x08000000) //0x0801FC00 for page 127
#define GET_PAGE_START_ADDRESS(X)	(EEPROM_START_ADDR + (0x00000400*X))
#define SIZE_PER_PAGE				0x03FF

/*   Prototype */

void Flash_Write(uint8_t page, uint32_t addr, uint16_t data);
uint16_t Flash_Read(uint8_t page, uint32_t addr);
void Flash_Write_xHalfWord(uint8_t page, uint32_t addr, uint8_t *data, uint32_t length);
uint8_t* Flash_Read_xHalfWord(uint8_t page, uint32_t addr, uint8_t* data, uint32_t length);
uint32_t Flash_Read_Word(uint8_t page, uint32_t addr);
void Flash_Erase_Page(uint8_t page_x);

void ResetFlash(void);
void ResetPage(uint8_t page);


#endif
