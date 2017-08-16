/*
 * File:	EXAMPLE.c
 * Purpose:	EX. Routines for the non-volatile RAM
 *
 * Notes:	Ex.Microchip 23LCV512 has 1024 Kbits = 128 KBytes
 *			
 */

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments
#include "Interrupts.h"
#include "Timers.h"
#include "LED.h"
#include "Comm.h"
#include "PWM.h"
#include "Queue.h"
#include "ISR.h"
#include "USB.h"

/* Definitions */

/* Global Variables */
volatile unsigned int state = 1;    //controls state machine in ISR

/* Macros */

/* Public functions */

/********************************************************************
   
   ISR 1- State Machine controlling main cycle
   
*********************************************************************/
/* Define the Interrupt Service Routine (ISR) */
void __attribute__((interrupt)) myISR() {
  clearIntFlag(_TIMER_2_IRQ);               /* Clear IF flag for ISR */
  
  //these were GLOBAL vars
  //volatile unsigned int TMR1Cntr = 0;
    
  //state machine global var "state" currently defined in Interrupts.c/global vars
 
  switch(state) {
        case 1 :
           Serial.print("State 1\n");
           //paste code to turn on LED 1 here
           // First event will be to turn on two  LEDs - one from the segmentation measurement side and one from the pair just ahead of the spectrometer.
           break;
        case 2 :
          Serial.print("State 2\n");
          //paste code to sample photo diode 1 here
          //Second event will be to measure the voltage from the photodiode circuits associated with the LEDs that are on.
           break;
        case 3 :
           Serial.print("State 3\n");
           //Third event will be to turn off both LEDs.
           break;
        case 4 :
           Serial.print("State 4\n");
           //Fourth event  is to measure the photodiode voltage associated with the two LEDs that were just turned off. 
           break;
        case 5 :
           Serial.print("State 5\n");
           // Fifth event is to turn on the other two LEDs - again one is from the segmentation measurement side and the other is just prior to the spectrometer.
           break;
        case 6 :
          Serial.print("State 6\n");
          //Sixth event is to measure the output voltage of the photodiode circuits associated with the two LEDs that are on. 
           break;
        case 7 :
           Serial.print("State 7\n");
           //Seventh event is to turn off both LEDs that are on.
           break;
        case 8 :
           Serial.print("State 8\n");
           //Eighth event is to measure output voltage of photodiode circuits associated with the two LEDs just turned off.
           break;
        default :
           Serial.print("ERROR: Invalid State ");
           Serial.println(state);
           
           //Data Collection code here??
           //make a struct element full of data from control cycle
           //Qput data element
   
      }
      
      state++;
  if (state >= 9) state =1;     //reset state variable after cycle complete
  //Serial.println(state);


}

/********************************************************************
   
   InterruptInit()
   
*********************************************************************/
//Initialize all timers
void InterruptInit(){
    SetupInterrupt_TMR1();
    SetupInterrupt_TMR2();
    SetupInterrupt_TMR3();
    SetupInterrupt_TMR4();
    SetupInterrupt_TMR5();
}

/********************************************************************
   
   InterruptInit()
   
*********************************************************************/
//Initialize all timers
void InterruptInit(){
    SetupInterrupt_TMR1();
    SetupInterrupt_TMR2();
    SetupInterrupt_TMR3();
    SetupInterrupt_TMR4();
    SetupInterrupt_TMR5();
}

/********************************************************************
   
   SetupInterrupt_TMR1
   
*********************************************************************/
//
void SetupInterrupt_TMR1()
{
    setIntVector(_TIMER_1_VECTOR, myISR);   /* Attach myISR function */
    setIntPriority(_TIMER_1_VECTOR, 4, 0);  /* Set priority- vector, priority, sub priority */
    clearIntFlag(_TIMER_1_IRQ);             /* Clear IF flag for initialization */
    setIntEnable(_TIMER_1_IRQ);             /* Enable Interrupts for Timer 1 */
}

/********************************************************************
   
   SetupInterrupt_TMR2
   
*********************************************************************/
//
void SetupInterrupt_TMR2()
{
    setIntVector(_TIMER_2_VECTOR, myISR);   /* Attach myISR function */
    setIntPriority(_TIMER_2_VECTOR, 4, 0);  /* Set priority- vector, priority, sub priority */
    clearIntFlag(_TIMER_2_IRQ);             /* Clear IF flag for initialization */
    setIntEnable(_TIMER_2_IRQ);             /* Enable Interrupts for Timer 2 */
}

/********************************************************************
   
   SetupInterrupt_TMR3
   
*********************************************************************/
//
void SetupInterrupt_TMR3()
{
    setIntVector(_TIMER_3_VECTOR, myISR);   /* Attach myISR function */
    setIntPriority(_TIMER_3_VECTOR, 4, 0);  /* Set priority- vector, priority, sub priority */
    clearIntFlag(_TIMER_3_IRQ);             /* Clear IF flag for initialization */
    setIntEnable(_TIMER_3_IRQ);             /* Enable Interrupts for Timer 3 */
}

/********************************************************************
   
   SetupInterrupt_TMR4
   
*********************************************************************/
//
void SetupInterrupt_TMR4()
{
    setIntVector(_TIMER_4_VECTOR, myISR);   /* Attach myISR function */
    setIntPriority(_TIMER_4_VECTOR, 4, 0);  /* Set priority- vector, priority, sub priority */
    clearIntFlag(_TIMER_4_IRQ);             /* Clear IF flag for initialization */
    setIntEnable(_TIMER_4_IRQ);             /* Enable Interrupts for Timer 4 */
}

/********************************************************************
   
   SetupInterrupt_TMR5
   
*********************************************************************/
//
void SetupInterrupt_TMR5()
{
    setIntVector(_TIMER_5_VECTOR, myISR);   /* Attach myISR function */
    setIntPriority(_TIMER_5_VECTOR, 4, 0);  /* Set priority- vector, priority, sub priority */
    clearIntFlag(_TIMER_5_IRQ);             /* Clear IF flag for initialization */
    setIntEnable(_TIMER_5_IRQ);             /* Enable Interrupts for Timer 5 */
}

/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */


