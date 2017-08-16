volatile unsigned int TMR1Cntr = 0;
volatile unsigned int TMR2Cntr = 0;

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
// Set up TMR2 to tick 1000 times per second,  no interrupts
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

//-------------------------------------------------------------------------------------------------------

//
// Set up TMR3 to tick 1000 times per second,  no interrupts
//
void SetupTMR3()
{
  T3CONbits.ON = 0;                     // turn off TMR3
  TMR3 = 0;                             // clr TMR3
  T3CONbits.TCS = 0;                    // select internal clock
  T3CONbits.TGATE = 0;                  // select NOT gated
  T3CONbits.TCKPS = 0b01;               // select 1:2 clock prescale  
  PR3 = 40000;                          // In MAX32, PBCLK is 80 MHz.  With TCKPS set to 1:1,
                      // TMR2 counts 40000000L ticks per second
                      // with PR2 set to 40000, it sets its (T2IF) one thousand
                      // times per second.   Note, T3IF needs to be cleared 
                      // every time it gets set - otherwise TMR1 loses count
  IFS0bits.T3IF = 0;                    // clr T13F to start
  IEC0bits.T3IE = 1;                    // Enable TMR3 interrupts
  T3CONbits.ON = 1;                     // TMR 3 ON

}

//-------------------------------------------------------------------------------------------------------

/* Define the Interrupt Service Routine (ISR) */
void __attribute__((interrupt)) myISR() {
  clearIntFlag(_TIMER_2_IRQ);               /* Clear IF flag for ISR */
  Serial.print("Interrupts working\n");
  
  /*
  ***Jordan's various code bits for debug/measuring***

  if (LATBbits.LATB0 = 1){
    LATBbits.LATB0 = 0;
  }
  else LATBbits.LATB0 = 1; 
   
  //LATBbits.LATB0 = 1;                       // set port B bit 0 high
  //LATBbits.LATB0 = 0;                       // set port B bit 0 low
  
  //delay(1000);
  */
  
}

//-------------------------------------------------------------------------------------------------------
void SetupInterrupt_TMR2()
{
    setIntVector(_TIMER_2_VECTOR, myISR);   /* Attach ISR finction */
    setIntPriority(_TIMER_2_VECTOR, 4, 0);  /* Set priority- I need to find out what the other arguments represent.. */
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
//-------------------------------------------------------------------------------------------------------
//
// TMR2_Delay_100ms
// Waits 100 ms then returns
// Users TMR2.   Does not interfere with TMR1 counting
//
void TMR2_Delay_100ms()             
{
    T2CONbits.ON = 0;                       // Make sure TMR2 is off for now
    TMR2 = 0;                               // clr TMR2 register
    IFS0bits.T2IF = 0;                      // clr T12F to start
    T2CONbits.ON = 1;                       // Turn TMR2 ON

    for(TMR2Cntr=0; TMR2Cntr < 100; TMR2Cntr++)
    {
          while(IFS0bits.T2IF == 0);        // wait for TMR2 to tick
          IFS0bits.T2IF = 0;                // clear T2IF so it can tick again
    }

    T2CONbits.ON = 0;                       // Turn TMR2 OFF
}
//-------------------------------------------------------------------------------------------------------
//
// TMR2_Delay_10ms
// Waits 10 ms then returns
// Users TMR2.   Does not interfere with TMR1 counting
//
void TMR2_Delay_10ms()             
{
    T2CONbits.ON = 0;                       // Make sure TMR2 is off for now
    TMR2 = 0;                               // clr TMR2 register
    IFS0bits.T2IF = 0;                      // clr T12F to start
    T2CONbits.ON = 1;                       // Turn TMR2 ON

    for(TMR2Cntr=0; TMR2Cntr < 10; TMR2Cntr++)
    {
          while(IFS0bits.T2IF == 0);        // wait for TMR2 to tick
          IFS0bits.T2IF = 0;                // clear T2IF so it can tick again
    }

    T2CONbits.ON = 0;                       // Turn TMR2 OFF
}

void setup() {
 Serial.begin(9600);
 SetupTMR1();
 SetupTMR2();
 SetupInterrupt_TMR2();
 Serial.print("Hello World\n");

//debug code
// PORTS
  AD1PCFG = 0xFFFFFFFF;                         // Make all analog/digital pins digital ( instead of analog )

// Initialize ports
  TRISB = 0x0000;                            // Make all PORT B bits outputs
  PORTB = 0;                                 // Make all PORT B bits 0

}

void loop() {
 if (TMR1x2Tick()){
  IFS0bits.T2IF = 1;                    // set T12F to trigger interrupt
  //Serial.print("Hello World\n");
 }
 //delay(1000);
}

