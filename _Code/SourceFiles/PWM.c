/*
 * File:	PWM.c
 * Purpose:	Initialize & maintain PWMs
 *
 * Notes:	PWMs require use of a timer. Currently set to use: Timer 3. See below for additional notes
 *			
 */

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments
#include "PWM.h"
/* Definitions */

#define TICKS_PER_SECOND 40000000L

/* Macros */

/* Public functions */

/********************************************************************
   
  PWM Initialization routines (all four channels)
   
*********************************************************************/
void SetupPWMs( double frequency, double OC1duty, double OC2duty, double OC3duty, double OC4duty){
        /*         ***************************************************************  
         *   Sets up and runs PWMs for OC1, OC2, OC3 & OC4 
         *   
         *  Notes:   Best range for frequency is 1000 to 10000
         *           range for OC1duty : 0 to 100.0
         *           range for OC2duty : 0 to 100.0 
         *           range for OC3duty : 0 to 100.0
         *           range for OC4duty : 0 to 100.0
         *
         *           !!!Currently there is no range checking for parameters.   
         *           Unexpected results may occur if called with a parameter
         *           that is out of range.
         *           
         *           Resources used:
         *           Timer 3
         *           OC1 (same hardware pin as RD0)
         *           OC2 (same hardware pin as RD1)
         *           OC3 (same hardware pin as RD2)
         *           OC4 (same hardware pin as RD3)
         ***************************************************************************           
       */            
        //Define the period
        uint16_t period  = (uint16_t)(((double)TICKS_PER_SECOND/frequency)); // Ticks per sec defined above in definitions section, frequency passed in function arguments
        
                
        //channel 1                           Pin 3 J14 OC1
        //*************************************************************************** 
                OC1CONbits.ON = 0;               // Turn off OC1 while doing setup.
               
                OC1RS = uint16_t(OC1duty*((double)period)/100.0);       // Initialize secondary compare register
                
                OC1R = period - OC1RS;          // Initialize primary compare register
                
                OC1CONbits.OCM = 6;             // Configure for PWM mode, fault pin disabled       
                
                OC1CONbits.OCTSEL = 1;           // Configure to use TMR3
        
                IFS0bits.OC1IF = 0;             // disable interrutpts from OC1 
        //***************************************************************************  
        
        
         //channel 2                          Pin 5 J14 OC2
        //*************************************************************************** 
                OC2CONbits.ON = 0;               // Turn off OC2 while doing setup.
               
                OC2RS = uint16_t(OC2duty*((double)period)/100.0);   // Initialize secondary compare register
                
                OC2R = period - OC2RS;         // Initialize primary compare register
                
                OC2CONbits.OCM = 6;             // Configure for PWM mode, fault pin disabled       
                
                OC2CONbits.OCTSEL = 1;           // Configure to use TMR3
        
                IFS0bits.OC2IF = 0;             // disable interrutpts from OC2  
        //*************************************************************************** 

         //channel 3                           Pin 6 J14 OC3
        //*************************************************************************** 
                OC3CONbits.ON = 0;               // Turn off OC1 while doing setup.
               
                OC3RS = uint16_t(OC3duty*((double)period)/100.0);       // Initialize secondary compare register
                
                OC3R = period - OC3RS;          // Initialize primary compare register
                
                OC3CONbits.OCM = 6;             // Configure for PWM mode, fault pin disabled       
                
                OC3CONbits.OCTSEL = 1;           // Configure to use TMR3
        
                IFS0bits.OC3IF = 0;             // disable interrutpts from OC1 
        //***************************************************************************  
        
        
         //channel 4                          Pin 9 J3 OC4
        //*************************************************************************** 
                OC4CONbits.ON = 0;               // Turn off OC2 while doing setup.
               
                OC4RS = uint16_t(OC4duty*((double)period)/100.0);   // Initialize secondary compare register
                
                OC4R = period - OC4RS;         // Initialize primary compare register
                
                OC4CONbits.OCM = 6;             // Configure for PWM mode, fault pin disabled       
                
                OC4CONbits.OCTSEL = 1;           // Configure to use TMR3
        
                IFS0bits.OC4IF = 0;             // disable interrutpts from OC2  
        //***************************************************************************
        
        //Initialize
        //*************************************************************************** 
                PR3 = period;                   // Set PR3 to period(defined above)
                T3CONbits.TCS = 0;              // select internal clock
                T3CONbits.TGATE = 0;            // select NOT gated
                T3CONbits.TCKPS = 0b01;         // select 1:2 clock prescale  
                
                IEC0bits.T3IE = 0;              // disable timer 3 interrupts
                                                //
                T3CONbits.ON = 1;               // Enable Timer3
        
                
                OC1CONbits.ON = 1;              // Turn ON OC1 
                OC2CONbits.ON = 1;              // Turn ON OC2
                OC3CONbits.ON = 1;              // Turn ON OC1 
                OC4CONbits.ON = 1;              // Turn ON OC2  
                
        }


/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */


