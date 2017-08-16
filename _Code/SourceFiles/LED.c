/*
 * File:	LED.c
 * Purpose:	Routines for the LEDs
 *
 * Notes:	
 *			
 */

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments
#include "LED.h"

/* Definitions */

/* Macros */

/* Public functions */

/********************************************************************
   
  Initialization routines
   
*********************************************************************/
void LEDInit(void)
{
  //
   //Either of these works
   //
   //PORTSetPinsDigitalOut(IOPORT_B, BIT_0);  //configure the port registers
   //
   TRISE = 0x0000;    //Sets all Port E pins to digital output
   //NOte: this is also initializing the pins for the two Solenoid valves on PMD6/RE6 & PMD7/RE7  
    
  // Turn off LEDs for now
	//LED1_OFF;
	//LED2_OFF;
	//LED3_OFF;
	//LED4_OFF;
}

/********************************************************************
   
  LED 1 ON
   
*********************************************************************/
void LED_1_ON(void)
{
  //PIN PMD0/RE0 (Port E) 
  LATEbits.LATE0=1;     //Set pin 0 in Latch E register to 1, turn LED ON
}

/********************************************************************
   
  LED 1 OFF
   
*********************************************************************/
void LED_1_OFF(void)
{
  //PIN PMD0/RE0 (Port E) 
  LATEbits.LATE0=0;     //Set pin 0 in Latch E register to 0, turn LED OFF
}

/********************************************************************
   
  LED 2 ON
   
*********************************************************************/
void LED_2_ON(void)
{
  //PIN PMD1/RE1 (Port E) 
  LATEbits.LATE1=1;     //Set pin 1 in Latch E register to 1, turn LED ON
}

/********************************************************************
   
  LED 2 OFF
   
*********************************************************************/
void LED_2_OFF(void)
{
  //PIN PMD1/RE1 (Port E) 
  LATEbits.LATE1=0;     //Set pin 1 in Latch E register to 0, turn LED OFF
}

/********************************************************************
   
  LED 3 ON
   
*********************************************************************/
void LED_3_ON(void)
{
  //PIN PMD2/RE2 (Port E) 
  LATEbits.LATE2=1;     //Set pin 2 in Latch E register to 1, turn LED ON
}

/********************************************************************
   
  LED 3 OFF
   
*********************************************************************/
void LED_3_OFF(void)
{
  //PIN PMD2/RE2 (Port E) 
  LATEbits.LATE2=0;     //Set pin 2 in Latch E register to 0, turn LED OFF
}

/********************************************************************
   
  LED 4 ON
   
*********************************************************************/
void LED_4_ON(void)
{
  //PIN PMD3/RE3 (Port E) 
  LATEbits.LATE3=1;     //Set pin 3 in Latch E register to 1, turn LED ON
}

/********************************************************************
   
  LED 4 OFF
   
*********************************************************************/
void LED_4_OFF(void)
{
  //PIN PMD3/RE3 (Port E) 
  LATEbits.LATE3=0;     //Set pin 3 in Latch E register to 0, turn LED OFF
}






/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */


