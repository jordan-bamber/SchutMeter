/*
 * JLB 4-12-17
 * 
 * Timer 2 intentionally off  -it is set to tick manually using the "bool TMR1x2Tick()" method. 
Thus Timer 2 ticks once for every two ticks that Timer 1 makes(8 per sec), so (4x per sec) every 250ms. 
This implementation was used because:

In MAX32, PBCLK is 80 MHz.  With TCKPS set to 256, TMR1 counts 80000000L / 256 = 312500 ticks per second

We would need the period to be 78125, and since the maximum we could get from a 16 bit register would be 65535, 
the two solutions that first came to mind were: trying to use a 32 bit timer and/or control register, or using TMR1x2Tick() function which was already in place. 
Also I believe that the max prescale value for the 32 bit timers is still 1:256
 * 
 */

volatile unsigned int TMR1Cntr = 0;
//-------------------------------------------------------------------------------------------------------

//
// Set up TMR1 to tick 8 times per second,  no interrupts
//
void SetupTMR1()
{

  T1CONbits.ON = 0;               // turn off TMR1
  TMR1 = 0;                       // clr TMR1
  T1CONbits.TCS = 0;              // select internal clock
  T1CONbits.TGATE = 0;            // select NOT gated
  T1CONbits.TCKPS = 0b11;        // select 1:256 clock prescale  
  PR1 = 39062;                    // In MAX32, PBCLK is 80 MHz.  With TCKPS set to 256,
                                  // TMR1 counts 80000000L / 256 = 312500 ticks per second
                                  // with PR1 set to 39062, it sets its (T1IF) eight
                                  // times per second.   Note, T1IF needs to be cleared 
                                  // every time it gets set - otherwise TMR1 loses count
  IFS0bits.T1IF = 0;              // clr T1IF to start
  IEC0bits.T1IE = 0;              // disable TMR1 interrupts
  T1CONbits.ON = 1;               // turn on TMR1

}
//-------------------------------------------------------------------------------------------------------

//
// Set up TMR2 to tick 1000 times per second
//
void SetupTMR2()
{
  T2CONbits.ON = 0;                     // turn off TMR2
  TMR2 = 0;                             // clr TMR2
  T2CONbits.TCS = 0;                    // select internal clock
  T2CONbits.TGATE = 0;                  // select NOT gated
  T2CONbits.TCKPS = 0b01;               // select 1:2 clock prescale  
  PR2 = 40000;                          // In MAX32, PBCLK is 80 MHz.  With TCKPS set to 1:1,
                                        // TMR2 counts 40000000L ticks per second
                                        // with PR2 set to 40000, it sets its (T2IF) one thousand
                                        // times per second.   Note, T2IF needs to be cleared 
                                        // every time it gets set - otherwise TMR1 loses count
  IFS0bits.T2IF = 0;                    // clr T12F to start
  IEC0bits.T2IE = 1;                    // Enable TMR2 interrupts
  T2CONbits.ON = 0;                     // leave TMR2 off

}



/* Define the Interrupt Service Routine (ISR) */
void __attribute__((interrupt)) myISR() {
  clearIntFlag(_TIMER_2_IRQ);               /* Clear IF flag for ISR */
  
 Serial.println("working yo");


}

//-------------------------------------------------------------------------------------------------------
void SetupInterrupt_TMR2()
{
    setIntVector(_TIMER_2_VECTOR, myISR);   /* Attach ISR finction */
    setIntPriority(_TIMER_2_VECTOR, 4, 0);  /* Set priority- vector, priority, sub priority */
    clearIntFlag(_TIMER_2_IRQ);             /* Clear IF flag for initialization */
    setIntEnable(_TIMER_2_IRQ);
}

//-------------------------------------------------------------------------------------------------------



//  TMR1x2Tick

bool TMR1x2Tick()                 			// returns true on every second TMR1 Tick.  
											                  // Otherwise returns false
{
  bool RetVal = false;
  if (IFS0bits.T1IF)                  		// if  TMR1 tick occurred
  {
    IFS0bits.T1IF = 0;                		// clear T1IF
    TMR1Cntr++;                       		// increment counter
    if(TMR1Cntr >= 2)                 		// if above 2
    {
      TMR1Cntr = 0;                   		// reset TMR1Cntr
      RetVal = true;
    }
  }
  return RetVal;
}

void setup() {
 Serial.begin(9600);
 SetupTMR1();
 SetupTMR2();
 SetupInterrupt_TMR2();

}

void loop() {
 if (TMR1x2Tick())IFS0bits.T2IF = 1;                    // set T12F to trigger interrupt
 
}

