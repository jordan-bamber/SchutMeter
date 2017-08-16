/*
 * JLB 4-12-17
 * 
 * State machine code. Interrupts & state changes every 250 micro seconds. Scope this later to confirm
 * 
 */

//volatile unsigned int TMR1Cntr = 0;
volatile unsigned int state = 0;
//-------------------------------------------------------------------------------------------------------

//
// Set up TMR2 to tick 4000 times per second
//
void SetupTMR2()
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



/* Define the Interrupt Service Routine (ISR) */
void __attribute__((interrupt)) myISR() {
  clearIntFlag(_TIMER_2_IRQ);               /* Clear IF flag for ISR */
  
  state++;
  if (state >= 9) state =1;     //reset state variable after cycle complete
  //Serial.println(state);


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
void setup() {
 Serial.begin(9600);
 SetupTMR2();
 SetupInterrupt_TMR2();

 Serial.print("Hello World\n");

}

void loop() {
   if ( IFS0bits.T2IF = 1){  //if timer 2 ticked
  
  
    switch(state) {
        case 1 :
           Serial.print("State 1\n");
           //paste code to turn on LED 1 here
           break;
        case 2 :
          Serial.print("State 2\n");
          //paste code to sample photo diode 1 here
           break;
        case 3 :
           Serial.print("State 3\n");
           //paste code to turn off LED 1 here
           break;
        case 4 :
           Serial.print("State 4\n");
           //paste code to sample photo diode 1 here
           break;
        case 5 :
           Serial.print("State 5\n");
           //paste code to turn on LED 2 here
           break;
        case 6 :
          Serial.print("State 6\n");
          //paste code to sample photo diode 2 here
           break;
        case 7 :
           Serial.print("State 7\n");
           //paste code to turn off LED 2 here
           break;
        case 8 :
           Serial.print("State 8\n");
           //paste code to sample photo diode 2 here
           break;
        default :
           Serial.print("ERROR: Invalid State ");
           Serial.println(state);
   
      }
   }

 
    
 
}

