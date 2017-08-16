/*
 * JLB 6-6-17
 * 
 * Throw away test prog, trying to fix puin issue
 * 
 */

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

    if (LATEbits.LATE0==1)  LATEbits.LATE0=0;
    else  LATEbits.LATE0=1;


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

//-------------------------------------------------------------------------------------------------------
float ADC_to_Volts_3_3(float ADC_count)
{
   float volts;

    ////Serial.print("ADC Conversion Count  = ");
    ////Serial.println(ADC_count);
            
   volts = ((ADC_count *3.3)/1023);

    ////Serial.print("ADC Conversion Volts  = ");
    ////Serial.println(volts);

    return volts;
}

//-------------------------------------------------------------------------------------------------------
void setup() {
 Serial.begin(9600);
 SetupTMR2();
 SetupInterrupt_TMR2();

 //configure the port registers
 TRISE = 0x0000;
 TRISG = 0x0000;

pinMode(2, OUTPUT);
digitalWrite(2, HIGH);



 Serial.print("Hello World\n");

}

void loop() {
   int place = 4;
        
}

