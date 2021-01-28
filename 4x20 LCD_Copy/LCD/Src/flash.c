/*
 * File:    	src/flash.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	102
 * 
 * Description
 * -----------
 * The source file src/flash.c contains all functions to write and read from flash .
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */

#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "flash.h"

/**** private function prototype  ****/
static void Lock_Flash(void);
static void Unlock_Flash(void);
static void Flsah_Erase_AllPage(void);

/****************************************************************
							Unlock_Flash
****************************************************************/

/*
 * Fct-Nr : 102.01
 *
 * void Unlock_Flash(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function Unlock_Flash() unlock the flash memory.
 */
static void Unlock_Flash(void)
{
   while((FLASH->CR & 0x00000080) != 0)
   {
	  //unlock the flash
	  FLASH->KEYR = 0x45670123;
	  FLASH->KEYR = 0xCDEF89AB;   
   }
}

/****************************************************************
							Lock_Flash
****************************************************************/
/*
 * Fct-Nr : 102.02
 *
 * void Lock_Flash(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function Lock_Flash() lock the flash memory.
 */
static void Lock_Flash(void)
{
   //set the bit at position 7 to lock the flash
   FLASH->CR = 0x00000080;
}

/****************************************************************
							Flash_Erase_Page
****************************************************************/
/*
 * Fct-Nr : 102.03
 *
 * void Flash_Erase_Page(uint8_t page_x);
 *
 * @Param: page_x - selected page to erase. Possible values [0...MAX_PAGE]
 * @Return: None
 *
 * The function Flash_Erase_Page() erase a selected page of flash memory.
 */
void Flash_Erase_Page(uint8_t page_x)
{
	//check if the page is less than the maximum page
	if(page_x < MAX_PAGE)
	{
		//check if the flash is ready
		if((FLASH->SR & 0x00000001) == READY)
		{
			//Yes flash is ready. Unlock the flash 
			Unlock_Flash();
			//choose the page to erase
			FLASH->CR |= 0x00000002;
			FLASH->AR = GET_PAGE_START_ADDRESS(page_x);
			//Start to erase the selected page
			FLASH->CR |= 0x00000040;
			//wait until the erase is finished
			while(FLASH->SR & FLASH_SR_BSY);
			//reset register
			FLASH->CR &= ~0x00000042;			
		}

	}
}

/****************************************************************
							Flsah_Erase_AllPage
****************************************************************/
/*
 * Fct-Nr : 102.04
 *
 * void Flsah_Erase_AllPage(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function Flsah_Erase_AllPage() erase all page of the flash memory.
 */
static void Flsah_Erase_AllPage(void)
{
	//check if the flash is ready
	if((FLASH->SR & 0x00000001) == READY)
	{
		//Yes flash is ready. Unlock the flash 
		Unlock_Flash();
		//choose the Mass erase to erase all page
		FLASH->CR |= 0x00000004;
		//Start to erase all page
		FLASH->CR |= 0x00000040;
		//wait until the erase is finished
		while(FLASH->SR & FLASH_SR_BSY);
		//reset register
		FLASH->CR &= ~0x00000044;
	}
}

/****************************************************************
							Flash_Write
****************************************************************/
/*
 * Fct-Nr : 102.05
 *
 * void Flash_Write(uint8_t page, uint32_t addr, uint16_t data);
 *
 * @Param: page - selected page in the flash memory possible value range [0...MAX_PAGE]
 * @Param: addr - Address where to write in flash memory. Possible values [0...SIZE_PER_PAGE]
 * @Param: data - Data to write in the selected page and address
 * @Return: None
 *
 * The function Flash_Write write data in the selected page and address of flash memory.
 */
void Flash_Write(uint8_t page, uint32_t addr, uint16_t data)
{
	//check if the page is valid
	if(page < MAX_PAGE)
	{
		//check if the address is valid
		if(addr <= SIZE_PER_PAGE)
		{
			Unlock_Flash();
			//set bit to write
			FLASH->CR |= 0x00000001;
			*(__IO uint16_t *)(GET_PAGE_START_ADDRESS(page) + addr) = data;
			//wait until flash is free again
			while(FLASH->SR & FLASH_SR_BSY);
			Lock_Flash();
		}
	}
}

/****************************************************************
							Flash_Write_xHalfWord
****************************************************************/
/*
 * Fct-Nr : 102.06
 *
 * void Flash_Write_xHalfWord(uint8_t page, uint32_t addr, uint8_t *data, uint32_t length);
 *
 * @Param: page - selected page in the flash memory possible value range [0...MAX_PAGE]
 * @Param: addr - Address where to write in flash memory. Possible values [0...SIZE_PER_PAGE]
 * @Param: data - Pointer to data to write in the selected page and address
 * @Param: length - The number of Bytes to write in the selected page and address
 * @Return: None
 *
 * The function Flash_Write_xHalfWord write data with the length "length" in the selected page and address of flash memory.
 */
void Flash_Write_xHalfWord(uint8_t page, uint32_t addr, uint8_t *data, uint32_t length)
{
	//check if the page is valid
	if(page < MAX_PAGE)
	{
		//check if the address is valid
		if((addr <= SIZE_PER_PAGE) && (data != (uint8_t *)0))
		{
			uint32_t i;
			Unlock_Flash();
			//set bit to write
			FLASH->CR |= 0x00000001;
			for(i=0; i<length; i+=2){
					*(__IO uint16_t *)(GET_PAGE_START_ADDRESS(page) + addr + i) = *(uint16_t *)(&data[i]);
			}
			//wait until flash is free again
			while(FLASH->SR & FLASH_SR_BSY);
			Lock_Flash();
		}
	}
}

/****************************************************************
							Flash_Read
****************************************************************/
/*
 * Fct-Nr : 102.07
 *
 * uint16_t Flash_Read(uint8_t page, uint32_t addr);
 *
 * @Param: page - selected page in the flash memory possible value range [0...MAX_PAGE]
 * @Param: addr - Address where to write in flash memory. Possible values [0...SIZE_PER_PAGE]
 * @Return: The contain of the flash memory at the selected page and address is returned.
 *
 * The function Flash_Read read data with at the selected page and address of flash memory.
 */
uint16_t Flash_Read(uint8_t page, uint32_t addr)
{
	//check if the page is valid
	if(page < MAX_PAGE)
	{
		//check if the address is valid
		if(addr <= SIZE_PER_PAGE)
		{
			uint16_t *Pntr = (uint16_t *)(GET_PAGE_START_ADDRESS(page) + addr);
			return (*Pntr);
		}
	}
	return 0xFFFF; //error
}

/****************************************************************
							Flash_Read_xHalfWord
****************************************************************/
/*
 * Fct-Nr : 102.08
 *
 * uint8_t* Flash_Read_xHalfWord(uint8_t page, uint32_t addr, uint8_t *data, uint32_t length);
 *
 * @Param: page - selected page in the flash memory possible value range [0...MAX_PAGE]
 * @Param: addr - Address where to write in flash memory. Possible values [0...SIZE_PER_PAGE]
 * @Param: data - Pointer to data to write in the selected page and address
 * @Param: length - The number of Bytes to write in the selected page and address
 * @Return: The pointer to the data
 *
 * The function Flash_Read_xHalfWord read data with the length "length" in the selected page and address of flash memory.
 */
uint8_t* Flash_Read_xHalfWord(uint8_t page, uint32_t addr, uint8_t* data, uint32_t length)
{
	//check if the page is valid
	if(page < MAX_PAGE)
	{
		//check if the address is valid
		if((addr <= SIZE_PER_PAGE) && (data != (uint8_t *)0))
		{
			uint32_t i;
			uint16_t tmp;
			for(i=0; i<length; i+=2)
			{
				tmp = *(uint16_t *)(GET_PAGE_START_ADDRESS(page) + addr + i);
				data[i] = tmp & 0xFF;
				if(i < (length - 1))
				{
					data[i+1] = (tmp >> 8) & 0xFF;
				}
			}

		}
	}
	return data; 
}

/****************************************************************
							Flash_Read_Word
****************************************************************/
/*
 * Fct-Nr : 102.16
 *
 * uint32_t Flash_Read_Word(uint8_t page, uint32_t addr);
 *
 * @Param: page - selected page in the flash memory possible value range [0...MAX_PAGE]
 * @Param: addr - Address where to write in flash memory. Possible values [0...SIZE_PER_PAGE]
 * @Return: The pointer to the data
 *
 * The function Flash_Read_Word read 4 byte data in the selected page and address of flash memory.
 */
uint32_t Flash_Read_Word(uint8_t page, uint32_t addr)
{
	uint32_t data = 0xFFFFFFFFUL;
	//check if the page is valid
	if(page < MAX_PAGE)
	{
		//check if the address is valid
		if(addr <= SIZE_PER_PAGE)
		{
			uint16_t temp[2];

			temp[0] = *(uint16_t *)(GET_PAGE_START_ADDRESS(page) + addr + 0);
      temp[1] = *(uint16_t *)(GET_PAGE_START_ADDRESS(page) + addr + 2);
      data = (uint32_t)temp[0] | (uint32_t)(temp[1] << 16);
		}
	}
	return data; 
}

/****************************************************************
							ResetFlash
****************************************************************/
/*
 * Fct-Nr : 102.09
 *
 * void ResetFlash(void);
 *
 * @Param: None
 * @Return: None
 *
 * The function ResetFlash erase all page in the flash memory.
 */
void ResetFlash(void)
{
	Flsah_Erase_AllPage();
}

/****************************************************************
							ResetPage
****************************************************************/
/*
 * Fct-Nr : 102.10
 *
 * void ResetPage(uint8_t page);
 *
 * @Param: page - selected page to erase
 * @Return: None
 *
 * The function ResetPage erase the selected page in the flash memory.
 */
void ResetPage(uint8_t page)
{
	Flash_Erase_Page(page);
}
