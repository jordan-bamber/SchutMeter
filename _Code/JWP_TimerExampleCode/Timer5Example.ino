/* This value works for DP32, at 80 MHz */
#define TICKS_PER_SECOND 40000000L
 

volatile uint32_t counter = 0;
 
/* Define the Interrupt Service Routine (ISR) */
void __attribute__((interrupt)) myISR() {
  counter++;
  PORTBbits.RB0 = 1;                       // set port B bit 0 high
  PORTBbits.RB0 = 0;                       // set port B bit 0 low
//  LATBbits.LATB0 = 1;                    // set port B bit 0 high
//  LATBbits.LATB0 = 0;                    // set port B bit 0 low

  IFS0bits.T5IF = 0;                     /* Clear IF flag for ISR */
}
 
/* start_timer_5 - exits with timer 5 Off but with timer 5 interrupts enabled */
void start_timer_5(uint32_t frequency) {
  uint32_t period;  

  period = TICKS_PER_SECOND / frequency;    /* Define the period (40000000/8000)*/
  T5CONbits.ON = 0;                         /* Turn the timer off */
  T5CONbits.TCS = 0;                        // select internal clock
  T5CONbits.TGATE = 0;                      // select NOT gated
  T5CONbits.TCKPS = 0b01;                   // select 1:2 clock prescale  

  TMR5 = 0;                                 /* Clear the counter  */
  PR5 = period;                             /* Set the period     */
  IFS0bits.T5IF = 0;                        // clear interrupt flag for Timer 5
  IEC0bits.T5IE = 1;                        // Enable timer  interrupts
  T5CONbits.ON = 0;                         /* Leave timer off  */
} 
 
void setup() { 
  start_timer_5(4000);                      // set up timer 5 for  4 kHz  but leaves timer off
  setIntVector(_TIMER_5_VECTOR, myISR);     /* Attach ISR finction */
  setIntPriority(_TIMER_5_VECTOR, 4, 0);    /* Set priority- I need to find out what the other arguments represent.. */
  T5CONbits.ON = 1;                         /* Turn timer on  */

// added by JWP 04-05-2017
// PORTS
  AD1PCFG = 0xFFFFFFFF;                         // Make all analog/digital pins digital ( instead of analog )

//
// Initialize ports
//

  
  TRISB = 0x0000;                            // Make all PORT B bits outputs
  PORTB = 0;                                 // Make all PORT B bits 0

  
  Serial.begin(9600);
} 
 
void loop() {
  while (counter < 160000) {
    delay(10000);
    Serial.print("Count is now: ");
    Serial.println(counter);
  }
  counter = 0;                          /* Reset counter */
}
