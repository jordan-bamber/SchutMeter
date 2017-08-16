/*
 * File:	Timers.c
 * Purpose:	Configures all clocks and timers used by the application
 *
 * Notes:	Ex.Microchip 23LCV512 has 1024 Kbits = 128 KBytes
 *			
 */

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments
#include "Timers.h"

/* Definitions */

/* Macros */

/* Public functions */

/********************************************************************
   
   TimerInit()
   
*********************************************************************/
//Initialize all timers
void TimerInit(){
    SetupTimer1();
    SetupTimer2();
    SetupTimer3();
    SetupTimer4();
    SetupTimer5();
}


/********************************************************************
   
   SetupTimer1
   
*********************************************************************/
//Timer1 used for:
// Set up TMR1 to tick 4000 times per second, interrupts enabled
//(80000000L/TCKPS)/(period) = Ticks per second
void SetupTimer1()
{
  T1CONbits.ON = 1;                     // turn ON TMR1
  TMR1 = 0;                             // clr TMR1
  T1CONbits.TCS = 0;                    // select internal clock
  T1CONbits.TGATE = 0;                  // select NOT gated
  T1CONbits.TCKPS = 0b01;               // select 1:2 clock prescale  
  PR1 = 10000;                          // In MAX32, PBCLK is 80 MHz.  With TCKPS set to 1:1,
                                        // TMR2 80000000L / 2 = 40000000 ticks per second
                                        // with PR2 set to 10000, it sets its (T1IF)40000000L/10000=4000
                                        // times per second.   
                                        // 
  IFS0bits.T1IF = 0;                    // clr T1IF to start
  IEC0bits.T1IE = 1;                    // Enable TMR1 interrupts


}

/********************************************************************
   
   SetupTimer2
   
*********************************************************************/
//Timer2 used for:
// Set up TMR2 to tick 4000 times per second, interrupts enabled
//(80000000L/TCKPS)/(period) = Ticks per second
void SetupTimer2()
{
  T2CONbits.ON = 1;                     // turn ON TMR2
  TMR2 = 0;                             // clr TMR2
  T2CONbits.TCS = 0;                    // select internal clock
  T2CONbits.TGATE = 0;                  // select NOT gated
  T2CONbits.TCKPS = 0b01;               // select 1:2 clock prescale  
  PR2 = 10000;                          // In MAX32, PBCLK is 80 MHz.  With TCKPS set to 1:1,
                                        // TMR2 80000000L / 2 = 40000000 ticks per second
                                        // with PR2 set to 10000, it sets its (T2IF)40000000L/10000=4000
                                        // times per second.   Note, T2IF needs to be cleared 
                                        // every time it gets set - otherwise TMR1 loses count
  IFS0bits.T2IF = 0;                    // clr T12F to start
  IEC0bits.T2IE = 1;                    // Enable TMR2 interrupts


}

/********************************************************************
   
   SetupTimer3
   
*********************************************************************/
//Timer3 used for:
// Set up TMR3 to tick 4000 times per second, interrupts enabled
//(80000000L/TCKPS)/(period) = Ticks per second
void SetupTimer3()
{
  T3CONbits.ON = 1;                     // turn ON TMR3
  TMR3 = 0;                             // clr TMR3
  T3CONbits.TCS = 0;                    // select internal clock
  T3CONbits.TGATE = 0;                  // select NOT gated
  T3CONbits.TCKPS = 0b01;               // select 1:2 clock prescale  
  PR3 = 10000;                          // In MAX32, PBCLK is 80 MHz.  With TCKPS set to 1:1,
                                        // TMR2 80000000L / 2 = 40000000 ticks per second
                                        // with PR3 set to 10000, it sets its (T3IF)40000000L/10000=4000
                                        // times per second.   
                                        // 
  IFS0bits.T3IF = 0;                    // clr T3IF to start
  IEC0bits.T3IE = 1;                    // Enable TMR3 interrupts


}

/********************************************************************
   
   SetupTimer4
   
*********************************************************************/
//Timer4 used for:
// Set up TMR4 to tick 4000 times per second, interrupts enabled
//(80000000L/TCKPS)/(period) = Ticks per second
void SetupTimer4()
{
  T4CONbits.ON = 1;                     // turn ON TMR4
  TMR4 = 0;                             // clr TMR4
  T4CONbits.TCS = 0;                    // select internal clock
  T4CONbits.TGATE = 0;                  // select NOT gated
  T4CONbits.TCKPS = 0b01;               // select 1:2 clock prescale  
  PR4 = 10000;                          // In MAX32, PBCLK is 80 MHz.  With TCKPS set to 1:1,
                                        // TMR2 80000000L / 2 = 40000000 ticks per second
                                        // with PR4 set to 10000, it sets its (T4IF)40000000L/10000=4000
                                        // times per second.   
                                        // 
  IFS0bits.T4IF = 0;                    // clr T4IF to start
  IEC0bits.T4IE = 1;                    // Enable TMR4 interrupts


}

/********************************************************************
   
   SetupTimer5
   
*********************************************************************/
//Timer5 used for:
// Set up TMR5 to tick 4000 times per second, interrupts enabled
//(80000000L/TCKPS)/(period) = Ticks per second

void SetupTimer5()
{
  T5CONbits.ON = 1;                     // turn ON TMR5
  TMR5 = 0;                             // clr TMR5
  T5CONbits.TCS = 0;                    // select internal clock
  T5CONbits.TGATE = 0;                  // select NOT gated
  T5CONbits.TCKPS = 0b01;               // select 1:2 clock prescale  
  PR5 = 10000;                          // In MAX32, PBCLK is 80 MHz.  With TCKPS set to 1:1,
                                        // TMR2 80000000L / 2 = 40000000 ticks per second
                                        // with PR5 set to 10000, it sets its (T5IF)40000000L/10000=4000
                                        // times per second.   
                                        // 
  IFS0bits.T5IF = 0;                    // clr T5IF to start
  IEC0bits.T5IE = 1;                    // Enable TMR5 interrupts


}

/********************************************************************
   
  Function Name Here
   
*********************************************************************/


/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */


