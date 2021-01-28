// RTC Module

#ifndef RTC_MODULE
#define RTC_MODULE

#include "stdint.h"

// byte
typedef uint8_t byte;


// constants
#define SECONDS_PER_MINUTE    60UL
#define SECONDS_PER_HOUR      3600UL
#define SECONDS_PER_DAY    	  86400UL

// I2C BUS ADDRESS
#define DS3231_ADDRESS 		0xD0

// define register
#define DS3231_SEC          0x0
#define DS3231_MIN          0x1
#define DS3231_HRS          0x2
#define DS3231_DAY          0x3
#define DS3231_DATE         0x4
#define DS3231_MON          0x5
#define DS3231_YEAR         0x6

// define Temperature register
#define DS3231_TEMP_MSB     0x11
#define DS3231_TEMP_LSB     0x12


typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;		//Possible values 1...7
	uint8_t dayofmonth;		//Possible values 1...31
	uint8_t month;			//Possible values 1...12
	uint8_t year;
} time_t;

uint8_t decToBcd(int val);
int bcdToDec(uint8_t val);

void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
time_t* Get_Time (void);

void WriteTime (uint8_t sec, uint8_t min, uint8_t hour);
void WriteDate (uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);

float Get_Temp (void);

#endif
