/*
 * File:	EXAMPLE.h
 * Purpose:	EX. Routines for the non-volatile RAM
 *
 * Notes:	Ex.Microchip 23LCV512 has 1024 Kbits = 128 KBytes
 *			
 */

//Preprocessor Directives
#ifndef COMM_H
#define COMM_H

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments

/* Definitions */
/*---------------Sample/maybe-------
// boot modes
#define BOOT_MODE_USER			0
#define BOOT_MODE_SYSTEM		1

// Sensor command codes
#define CMD_INIT_COMM						(0xE0)
#define CMD_TEST								(0xE1)
#define CMD_READ_VERSION				(0xE2)
#define CMD_READ_DATA						(0xE3)
#define CMD_READ_ALLDATA				(0xE4)
#define CMD_READ_COUNTERS				(0xE5)
#define CMD_WRITE_ADC_FC				(0xE6)
#define CMD_WRITE_ANALOG_SW			(0xE7)
#define CMD_WRITE_PGA_GAIN			(0xE8)
#define CMD_WRITE_VREF					(0xE9)
#define CMD_WRITE_ORIENTATION		(0xEA)
#define CMD_READ_DEVICE_ID			(0xEB)

#define CMD_ERROR								(0x01)

// message status values
#define STATUS_OK										0
#define STATUS_INVALID_CRC					1
#define STATUS_INVALID_CMD					2
#define STATUS_INVALID_MSGLEN				3

*/

/* Macros */

/* Public functions */

/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */

#endif /* EXAMPLE_H */