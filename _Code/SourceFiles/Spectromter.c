/*
 * File:	Spectrometer.c
 * Purpose:	
 *
 * Notes:	
 *			
 */

/* Includes */
#include <stdint.h>     //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments
#include "Spectrometer.h"


/* Definitions */

/* Macros */

/* Public functions */

/********************************************************************
   
  Spectrometer Initialization 
   
*********************************************************************/
void SpectrometerInit(void)
{
  // Code to initialize & calibrate spectrometer
	
}

/********************************************************************
   
  Spectrometer LED (450nm) _ON
   
*********************************************************************/
void SpectrometerLED450_ON(void)
{
  //PIN PMD4/RE4 (Port E) 
  LATEbits.LATE4=1;     //Set pin 4 in Latch E register to 1, turn LED ON

  
	
}

/********************************************************************
   
  Spectrometer LED (450nm) _OFF
   
*********************************************************************/
void SpectrometerLED450_OFF(void)
{
  //PIN PMD4/RE4 (Port E) 
  LATEbits.LATE4=0;     //Set pin 4 in Latch E register to 0, turn LED OFF
	
}

/********************************************************************
   
  Spectrometer LED (White) _ON
   
*********************************************************************/
void SpectrometerLED_White_ON(void)
{
  //PIN PMD5/RE5 (Port E) 
  LATEbits.LATE5=1;     //Set pin 5 in Latch E register to 1, turn LED ON
  
	
}

/********************************************************************
   
  Spectrometer LED (White) _OFF
   
*********************************************************************/
void SpectrometerLED_White_OFF(void)
{
   //PIN PMD5/RE5 (Port E) 
  LATEbits.LATE5=0;     //Set pin 5 in Latch E register to 0, turn LED OFF
	
}


/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */


