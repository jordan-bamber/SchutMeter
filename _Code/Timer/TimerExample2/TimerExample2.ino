/* This value works for DP32, at 40 MHz */
#define TICKS_PER_SECOND 40000000
 
#define T3_ON 0x8000
#define T3_PS_1_1 0           /* Is this a preset prescaler variable? */
#define T3_SOURCE_INT 0
volatile uint32_t counter = 0;
 
/* Define the Interrupt Service Routine (ISR) */
void __attribute__((interrupt)) myISR() {
  counter++;
  clearIntFlag(_TIMER_3_IRQ);               /* Clear IF flag for ISR */
  PORTBbits.RB0 = 1;                       // set port B bit 0 high
  PORTBbits.RB0 = 0;                       // set port B bit 0 low
//  LATBbits.LATB0 = 1;                       // set port B bit 0 high
//  LATBbits.LATB0 = 0;                       // set port B bit 0 low
  
}
 
/* start_timer_3 */
void start_timer_3(uint32_t frequency) {
  uint32_t period;  
  period = TICKS_PER_SECOND / frequency;   /* Define the period (40000000/8000)*/
  T3CONCLR = T3_ON;                        /* Turn the timer off */
  T3CON = T3_PS_1_1;                       /* Set the prescaler  */
  TMR3 = 0;                                /* Clear the counter  */
  PR3 = period;                            /* Set the period     */
  T3CONSET = T3_ON;                        /* Turn the timer on  */
} 
 
void setup() { 
  start_timer_3(8000);  /* 8 kHz */
  setIntVector(_TIMER_3_VECTOR, myISR);   /* Attach ISR finction */
  setIntPriority(_TIMER_3_VECTOR, 4, 0);  /* Set priority- I need to find out what the other arguments represent.. */
  clearIntFlag(_TIMER_3_IRQ);             /* Clear IF flag for initialization */
  setIntEnable(_TIMER_3_IRQ);

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
    delay(1000);
    Serial.print("Count is now: ");
    Serial.println(counter);
  }
  counter = 0;                          /* Reset counter */
}
