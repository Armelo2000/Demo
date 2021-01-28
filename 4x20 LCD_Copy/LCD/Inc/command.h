/**
  ******************************************************************************
  * @file    command.h
  * @author  A. Tsannang
  * @brief   This file contains all commands for the communication between the 
  *          printer and other devices. This is valid vor 3 devices:
	*					 
	*					 		- Printer (print the ticket)
	*							- Remote controller (also call as the "Caller")
	*					 		- Display
  ******************************************************************************
  *
  */
		
#ifndef COMMAND_H
#define COMMAND_H

#include "stdint.h"
#include "rtc_clock.h"

// Command to write to RTC module.
#define CMD_WRITE_TIME				0xC000
#define CMD_WRITE_DATE				0xC100
#define CMD_WRITE_DATE_TIME		0xC10A

// Command to read from RTC module.
#define CMD_READ_TIME		0xC200
#define CMD_READ_DATE		0xC300
#define CMD_READ_TEMP		0xC400

//command to send to remote controller/Display
#define CMD_NEXT_NUMBER	0xE000

//command received from remote controller
#define CMD_CALL_NEXT_NUMBER	0xE100

// command to read diagnose 
#define CMD_READ_DIAG		0xC10D

//

typedef struct 
{
	uint16_t cmd;					
	uint16_t DeviceId;
	time_t time;
	uint8_t reserved_0;
  uint16_t reserved_1;	
	uint16_t crc;
}telremotecontoller_t;  // 16 bytes

typedef struct
{
	uint16_t cmd;
	uint16_t DeviceId;
	uint8_t length;
  time_t time;
	uint32_t currTicketCalled;
	uint32_t lastTicketPrinted;
	uint32_t totalTicketPrinted;
	uint32_t totalcalled;
	uint32_t totalremain2call;
	uint32_t ticketcode;
	uint8_t reserved_1[2];
	uint16_t crc;
}telprinter_t;	// 40 bytes (29 Bytes data)
	
#define COMMAND_COMPARE(cmd_a, cmd_b)				(cmd_a == cmd_b)
	
	
	
	
	
	
#endif
