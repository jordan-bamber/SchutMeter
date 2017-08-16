#define TICKS_PER_SECOND 40000000L
    void SetupPWMs( double frequency, double OC1duty, double OC2duty)
        /*         ***************************************************************  
         *   Sets up and runs PWMs for OC1 and OC2.  
         *   
         *  Notes:   best range for frequency is 1000 to 10000
         *           range for OC1duty : 0 to 100.0
         *           range for OC2duty : 0 to 100.0 
         *           
         *           Currently there is no range checking for parameters.   
         *           Unexpected results may occurr if called with a parameter
         *           that is out of range.
         *           
         *           Resources used:
         *           Timer 3
         *           OC1 (same hardware pin as RD0)
         *           OC2 (same hardware pin as RD1)
         ***************************************************************************           
       */       
       
    
        {
                
                uint16_t period  = (uint16_t)(((double)TICKS_PER_SECOND/frequency));
        
                OC1CONbits.ON = 0;               // Turn off OC1 while doing setup.
               
                OC1RS = uint16_t(OC1duty*((double)period)/100.0);       // Initialize secondary compare register
                
                OC1R = period - OC1RS;          // Initialize primary compare register
                
                OC1CONbits.OCM = 6;             // Configure for PWM mode, fault pin disabled       
                
                OC1CONbits.OCTSEL = 1;           // Configure to use TMR3
        
                IFS0bits.OC1IF = 0;             // disable interrutpts from OC1  
        
        
                OC2CONbits.ON = 0;               // Turn off OC2 while doing setup.
               
                OC2RS = uint16_t(OC2duty*((double)period)/100.0);   // Initialize secondary compare register
                
                OC2R = period - OC2RS;         // Initialize primary compare register
                
                OC2CONbits.OCM = 6;             // Configure for PWM mode, fault pin disabled       
                
                OC2CONbits.OCTSEL = 1;           // Configure to use TMR3
        
                IFS0bits.OC2IF = 0;             // disable interrutpts from OC2  
        
                      
        
                PR3 = period;                   // Set period
                T3CONbits.TCS = 0;              // select internal clock
                T3CONbits.TGATE = 0;            // select NOT gated
                T3CONbits.TCKPS = 0b01;         // select 1:2 clock prescale  
                
                IEC0bits.T3IE = 0;              // disable timer 2 interrupts
                                                //
                T3CONbits.ON = 1;               // Enable Timer2
        
                
                OC1CONbits.ON = 1;              // Turn ON OC1 
                OC2CONbits.ON = 1;              // Turn ON OC2 
                
        }
void setup() 
{

    SetupPWMs( 5000.0, 50.0, 50.0);

}

 void loop() 
 {
 }
