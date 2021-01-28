/*
 * File:    	src/rtc_clock.c
 * Author:  	Armel Tsannang
 * Date:		23-12-2020
 * Module-ID:	121
 * 
 * Description
 * -----------
 * The source file src/rtc_clock.c contains functions to read/write the date and the time.
 *
 * $Rev: 3 $
 * $Date: 2021-01-03 02:26:20 +0100 (So, 03 Jan 2021) $
 *
 */

#include "rtc_clock.h"
#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

time_t time = {0};

/****************************************************************
							decToBcd
****************************************************************/
/*
 * Fct-Nr : 121.01
 *
 * uint8_t decToBcd(int val);
 *
 * @Param: val - value to convert to BCD(binary coded decimal)
 * @Return: the converted value in BCD(binary coded decimal)
 *
 * The function decToBcd convert decimal number to binary coded decimal.
 */
uint8_t decToBcd(int val)
{
  return (uint8_t)( (val/10*16) + (val%10) );
}

/****************************************************************
							bcdToDec
****************************************************************/
/*
 * Fct-Nr : 121.02
 *
 * int bcdToDec(uint8_t val);
 *
 * @Param: val - BCD value to convert to decimal number
 * @Return: the converted decimal number
 *
 * The function bcdToDec convert the binary coded decimal to decimal number.
 */
int bcdToDec(uint8_t val)
{
  return (int)( (val/16*10) + (val%16) );
}

/****************************************************************
							Set_Time
****************************************************************/
/*
 * Fct-Nr : 121.03
 *
 * void Set_Time(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
 *
 * @Param: sec - second to set
 * @Param: min - minute to set
 * @Param: hour - hour to set
 * @Param: dow - day of week to set
 * @Param: dom - day of month to set
 * @Param: month - month to set
 * @Param: year - year to set
 * @Return: None
 *
 * The function Set_Time set all parameters to configure the date and time.
 */
void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(dow);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
}

/****************************************************************
							WriteTime
****************************************************************/
/*
 * Fct-Nr : 121.04
 *
 * void WriteTime(uint8_t sec, uint8_t min, uint8_t hour);
 *
 * @Param: sec - second to set
 * @Param: min - minute to set
 * @Param: hour - hour to set
 * @Return: None
 *
 * The function WriteTime set all parameters to configure the time (hour-min-sec).
 */
void WriteTime (uint8_t sec, uint8_t min, uint8_t hour)
{
	uint8_t set_time[3];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, 1, set_time, 3, 1000);
}

/****************************************************************
							WriteDate
****************************************************************/
/*
 * Fct-Nr : 121.05
 *
 * void WriteDate(uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
 *
 * @Param: dow - day of week to set
 * @Param: dom - day of month to set
 * @Param: month - month to set
 * @Param: year - year to set
 * @Return: None
 *
 * The function WriteDate set all parameters to configure the date .
 */
void WriteDate (uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_date[4];
	set_date[0] = decToBcd(dow);   // values should be 1..7 (Monday...Sunday)
	set_date[1] = decToBcd(dom);   // values should be 1..31 (Max. 31 days in the month)
	set_date[2] = decToBcd(month); // values should be 1..12 (January...December)
	set_date[3] = decToBcd(year);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, DS3231_DAY, 1, set_date, 4, 1000);
}

/****************************************************************
							Get_Time
****************************************************************/
/*
 * Fct-Nr : 121.06
 *
 * time_t* Get_Time(void);
 *
 * @Param: None
 * @Return: pointer to the time structure
 *
 * The function Get_Time return the date and the time in the time structure.
 */
time_t* Get_Time (void)
{
	uint8_t get_time[7];
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000);
	time.seconds = bcdToDec(get_time[0]);
	time.minutes = bcdToDec(get_time[1]);
	time.hour = bcdToDec(get_time[2]);
	time.dayofweek = bcdToDec(get_time[3]);
	time.dayofmonth = bcdToDec(get_time[4]);
	time.month = bcdToDec(get_time[5]);
	time.year = bcdToDec(get_time[6]);

	return &time;
}

/****************************************************************
							Get_Temp
****************************************************************/
/*
 * Fct-Nr : 121.07
 *
 * float Get_Temp(void);
 *
 * @Param: None
 * @Return: the temperature in degre celsius
 *
 * The function Get_Time return the temperature of the rtc module.
 */
float Get_Temp (void)
{
	uint8_t temp[2];

	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x11, 1, temp, 2, 1000);
	return ((temp[0])+(temp[1]>>6)/4.0);
}
