

#ifndef HC12_H
#define HC12_H

#include "stm32f1xx_hal.h"
#include "button.h"
#include "command.h"
#include "crc.h"
#include "uart.h"

void hc12_send_data(uint8_t * pucData, const uint32_t ulLen);
void hc12_send_command(uint8_t * pucCmd);
void hc12_init(void);

#define HC12_PIN_SET		GPIO_PIN_0

//Commands for HC12 Module
#define HC12_CMD_READ											"AT"  		//! This command return OK
#define HC12_CMD_READ_BAUDRATE						"AT+RB"  	//! This command return the baudrate
#define HC12_CMD_READ_SENDER_CHANNEL			"AT+RC"		//! This command return the sender channel
#define HC12_CMD_READ_XFER_MODE						"AT+RF"		//! This command return the transfer modus
#define HC12_CMD_READ_TRANSMITTER_POWER		"AT+RP"		//! This command return the transmitter power
#define HC12_CMD_READ_ALL_PARAMETERS			"AT+RX"		//! This command return all HC12 Parameters
#define HC12_CMD_READ_FIRMWARE_VERSION		"AT+V"		//! This command return the firmware version

#define HC12_CMD_SET_DEFAULT_VALUES				"AT+DEFAULT"		//! This command set all parameters to default value
#define HC12_CMD_SET_SLEEP_MODE						"AT+SLEEP"		//! This command set the sleep mode

#define HC12_CMD_SET_BAUDRATE_1200				"AT+B1200"		//! This command set the baudrate to 1200
#define HC12_CMD_SET_BAUDRATE_2400				"AT+B2400"		//! This command set the baudrate to 2400
#define HC12_CMD_SET_BAUDRATE_4800				"AT+B4800"		//! This command set the baudrate to 4800
#define HC12_CMD_SET_BAUDRATE_9600				"AT+B9600"		//! This command set the baudrate to 9600
#define HC12_CMD_SET_BAUDRATE_19200				"AT+B19200"		//! This command set the baudrate to 19200
#define HC12_CMD_SET_BAUDRATE_38400				"AT+B38400"		//! This command set the baudrate to 38400
#define HC12_CMD_SET_BAUDRATE_57600				"AT+B57600"		//! This command set the baudrate to 57600
#define HC12_CMD_SET_BAUDRATE_115200			"AT+B115200"		//! This command set the baudrate to 115200

#define HC12_CMD_SET_XFER_MODE_1					"AT+FU1"		  //! This command set the transfer mode FU1
#define HC12_CMD_SET_XFER_MODE_2					"AT+FU2"		  //! This command set the transfer mode FU2
#define HC12_CMD_SET_XFER_MODE_3					"AT+FU3"		  //! This command set the transfer mode FU3
#define HC12_CMD_SET_XFER_MODE_4					"AT+FU4"		  //! This command set the transfer mode FU4

#define HC12_CMD_SET_TRNSMITTER_POWER_1		"AT+P1"		  //! This command set the transmition power -1 dbm
#define HC12_CMD_SET_TRNSMITTER_POWER_2		"AT+P2"		  //! This command set the transmition power 2 dbm
#define HC12_CMD_SET_TRNSMITTER_POWER_3		"AT+P3"		  //! This command set the transmition power 5 dbm
#define HC12_CMD_SET_TRNSMITTER_POWER_4		"AT+P4"		  //! This command set the transmition power 8 dbm
#define HC12_CMD_SET_TRNSMITTER_POWER_5		"AT+P5"		  //! This command set the transmition power 11 dbm
#define HC12_CMD_SET_TRNSMITTER_POWER_6		"AT+P6"		  //! This command set the transmition power 14 dbm
#define HC12_CMD_SET_TRNSMITTER_POWER_7		"AT+P7"		  //! This command set the transmition power 17 dbm
#define HC12_CMD_SET_TRNSMITTER_POWER_8		"AT+P8"		  //! This command set the transmition power 20 dbm




#endif
