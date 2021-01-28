/*
    eeprom.c

*/

#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "eeprom.h"

uint16_t data = 1;
uint16_t eeprom_data[500], i = 0;

#define EEPROM_START_ADDR		((uint32_t)0x0801F800)

uint16_t Read_Flash(uint32_t addr)
{
  uint16_t *Pntr = (uint16_t *)(EEPROM_START_ADDR + addr);
  return (*Pntr);
}

void Unlock_Flash(void)
{
   FLASH->KEYR = 0x45670123;
   FLASH->KEYR = 0xCDEF89AB;   
}

void Lock_Flash(void)
{
   FLASH->CR = 0x00000080;
}

void Erase_Flsah(uint32_t addr)
{
   FLASH->CR |= 0x00000002;									// CR Page erase
   FLASH->AR = (EEPROM_START_ADDR + addr);	// CR add Erase
   FLASH->CR |= 0x00000040;									// CR Mass Erase
   while(FLASH->SR & FLASH_SR_BSY);					// Check if complete
   FLASH->CR &= ~0x00000042;								// Reset
}

void Write_Flash(uint32_t addr, uint16_t data)
{
	 Erase_Flsah(addr);
	 FLASH->CR |= 0x00000001;																// CR Page write
	 *(__IO uint16_t *)(EEPROM_START_ADDR + addr) = data;		// add
   while(FLASH->SR & FLASH_SR_BSY);												// Check if complete	
}

