/*
   eeprom.h
   
*/
#ifndef EEPROM_H_
#define EEPROM_H_

#include "stdint.h"

/*   Prototype */

uint16_t Read_Flash(uint32_t addr);
void Unlock_Flash(void);
void Lock_Flash(void);
void Erase_Flsah(uint32_t addr);
void Write_Flash(uint32_t addr, uint16_t data);


#endif
