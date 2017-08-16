/*
 * File:	EXAMPLE.h
 * Purpose:	EX. Routines for the non-volatile RAM
 *
 * Notes:	Ex.Microchip 23LCV512 has 1024 Kbits = 128 KBytes
 *			
 */

//Preprocessor Directives
#ifndef EXAMPLE_H
#define EXAMPLE_H

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments

/* Definitions */

/*---------------Sample/maybe-------*/
#define USB_RXLEN				132	// space for 16 hex words + command + CR
#define USB_TXLEN				132

/* Command codes */
#define USB_CMD(x,y)		((x<<8) + y)
/*
typedef enum {
	USB_CMD_SystemReset		= USB_CMD('R','@'),
	USB_CMD_Test					= USB_CMD('t','t'),
	USB_CMD_MainVersion		= USB_CMD('v','e'),
	USB_CMD_SensorVersion	= USB_CMD('v','s'),
	USB_CMD_MainID				= USB_CMD('i','m'),
	USB_CMD_SensorID			= USB_CMD('i','s'),
	USB_CMD_ParamSave			= USB_CMD('p','s'),
	USB_CMD_ReadMemory		= USB_CMD('r','m'),
	USB_CMD_Record				= USB_CMD('w','m'),
	USB_CMD_ReadData			= USB_CMD('r','d'),
	USB_CMD_ReadSensor		= USB_CMD('r','s'),
	USB_CMD_ReadCounters	= USB_CMD('r','c'),
	USB_CMD_ReadCalcs			= USB_CMD('c','a'),
	USB_CMD_SensorConfig	= USB_CMD('s','w'),
	USB_CMD_SensorGain		= USB_CMD('g','n'),
	USB_CMD_SensorVref		= USB_CMD('v','r'),
	USB_CMD_SensorMeasVos	= USB_CMD('m','v'),
	USB_CMD_SensorOrient	= USB_CMD('o','s'),
	USB_CMD_SensorFreq		= USB_CMD('g','f'),
	USB_CMD_MainOrient		= USB_CMD('o','m'),
	USB_CMD_FilterExp			= USB_CMD('e','x'),
	USB_CMD_AxleHeight		= USB_CMD('h','a'),
	USB_CMD_HitchHeight		= USB_CMD('h','h'),
	USB_CMD_SledHeight		= USB_CMD('h','s'),
	USB_CMD_AxleToHitch		= USB_CMD('l','h'),
	USB_CMD_ChainLength		= USB_CMD('l','c'),
	USB_CMD_PitchDelta		= USB_CMD('d','h'),
	USB_CMD_MaxVehPitch		= USB_CMD('p','v'),
	USB_CMD_ForceCoefs		= USB_CMD('f','x'),
	USB_CMD_ForceZero			= USB_CMD('f','z'),
	USB_CMD_RunStartStop	= USB_CMD('s','s'),
	USB_CMD_AnalogOut			= USB_CMD('a','n'),
	USB_CMD_AnalogForce		= USB_CMD('a','f'),
	USB_CMD_FwErase				= USB_CMD('f','e'),
	USB_CMD_FwProgram			= USB_CMD('f','p'),
	USB_CMD_FwVerify			= USB_CMD('f','v')
} aUSBcommandCode;

*/


/* Macros */

/* Public functions */

/*---------------Sample/maybe-------
void USBInit(void);
void USBreceiveCommand(void);
void USBprocessCommand(void);
*/

/* Private functions */

/* Public variables */

/*---------------Sample/maybe-------
extern volatile int USBcmdPending;
extern uint8_t USBrxBuffer[], USBtxBuffer[];
extern int32_t USBrxLen, USBtxLen;
extern const uint8_t version[];
*/

/* Private variables */

/* Type Definitions */

/* Special type definitions */

#endif /* USB_H */