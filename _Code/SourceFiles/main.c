/*
 * File:	main.c
 * Purpose:	System initialization, main idle and invokes background processing of host commands and various functions
 *
 * Notes:	
 *			
 */

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments

#include "Comm.h"
#include "Timers.h"
#include "USB.h"
#include "Interrupts.h"
#include "LED.h"
/* Definitions */

/* Macros */

/* Public functions */

/********************************************************************
   
   main setup
   
*********************************************************************/
void setup() {
 Serial.begin(9600);
 //SetupTMR2();
 //SetupInterrupt_TMR2();

 Serial.print("Hello World\n");
 
 SetupPWMs( 5000.0, 50.0, 50.0);             // Set frequency to 5000, OC1Duty to 50.0%, OC2Duty to 50.0%

}



/********************************************************************
   
  main loop
   
*********************************************************************/
void loop() {

}
/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */


