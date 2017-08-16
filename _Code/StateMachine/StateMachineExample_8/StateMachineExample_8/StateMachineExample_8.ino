/*
 * JLB 4-12-17
 * 
 * State machine code. Interrupts & state changes every 250 micro seconds. Scope this later to confirm
 * 
 */

//volatile unsigned int TMR1Cntr = 0;
volatile unsigned int state = 0;

/*
volatile float ADC;
volatile float volts_sample1;
volatile float volts_sample2;
*/
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
  ////Serial.println(state);


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



 Serial.print("Hello World\n");

}

void loop() {
  float PD1_ADC1;
  float PD1_ADC2;
  float PD2_ADC1;
  float PD2_ADC2;
  float PD1_volts_sample1;
  float PD1_volts_sample2;
  float PD2_volts_sample1;
  float PD2_volts_sample2;    
  
   if ( IFS0bits.T2IF = 1){  //if timer 2 ticked
  
      switch(state) {
           case 1 :
            //Serial.print("State 1\n");
            //Sample Photodiode 1

            
  
            PD1_ADC1 = analogRead(B0);
            PD1_volts_sample1 = ADC_to_Volts_3_3(PD1_ADC1);

            //Serial.print("PD1_ADC1  = ");
            //Serial.println(PD1_ADC1);
            
            //Serial.print("Volts1 right after acquisition  = ");
            //Serial.println(PD1_volts_sample1);
  
            break;
  
          case 2 :
             //Serial.print("State 2\n");
             
             //PIN PMD0/RE0 (Port E) 
              LATEbits.LATE0=1;     //Set pin 0 in Latch E register to 1, turn LED1 ON
             break;
          case 3 :
            //Serial.print("State 3\n");
            //Sample Photodiode 1 again

            //float ADC;
            
           
            PD1_ADC2 = analogRead(B0);
            PD1_volts_sample2 = ADC_to_Volts_3_3(PD1_ADC2);

            //Serial.print("PD1_ADC2  = ");
            //Serial.println(PD1_ADC2);
            
            ////Serial.print("Volts2  = ");
            ////Serial.println(volts_sample2);
  
            //Serial.print("Volts1  = ");
            //Serial.println(PD1_volts_sample1);
            
            //Serial.print("Volts2  = ");
            //Serial.println(PD1_volts_sample2);
            
            //Serial.print("Volts after subtraction = ");
            //Serial.println(PD1_volts_sample2-PD1_volts_sample1);
  
            if((PD1_volts_sample2-PD1_volts_sample1) <= 1){
              //found segment!
               //PIN RG9 (Port G) 
               LATGbits.LATG9=1;            //Set pin 9 in Latch G register to 1, turn LED1_SEG_FOUND ON
               //Serial.print("Photodiode 1: Segment of Green Core Shell Found! \n");

               //delay(250);
  
            }
            else{
              ////Serial.print("No Segment Found... \n");
            
  
            //*****just for testing remove this later*******
            //delay(250);
  
            //turn segment found indicator LED OFF
            //PIN RG9(Port G) 
            LATGbits.LATG9=0;     //Set pin 9 in Latch G register to 0, turn LED1_SEG_FOUND OFF
            }
  
             break;
          case 4 :
             //Turn LED1 OFF
             //Serial.print("State 4\n");
             //PIN PMD0/RE0 (Port E) 
             LATEbits.LATE0=0;     //Set pin 0 in Latch E register to 0, turn LED1 OFF
             break;

          case 5 :
            //Serial.print("State 5\n");
            //Sample Photodiode 2

            
  
            PD2_ADC1 = analogRead(B1);
            PD2_volts_sample1 = ADC_to_Volts_3_3(PD2_ADC1);

            //Serial.print("PD2_ADC11  = ");
            //Serial.println(PD2_ADC1);
            
            //Serial.print("PD2 Volts1 right after acquisition  = ");
            //Serial.println(PD2_volts_sample1);

            break;
  
          case 6 :
             //Serial.print("State 6\n");
             //Turn LED2 ON
              //PIN PMD0/RE1 (Port E) 
             LATEbits.LATE1=1;     //Set pin 1 in Latch E register to 1, turn LED2 ON
             break;
          case 7 :
            //Serial.print("State 7\n");
            //Sample Photodiode 2 again

            //float ADC;
            
           
            PD2_ADC2 = analogRead(B1);
            PD2_volts_sample2 = ADC_to_Volts_3_3(PD2_ADC2);

            //Serial.print("PD2_ADC2  = ");
            //Serial.println(PD2_ADC2);
            
            ////Serial.print("Volts2  = ");
            ////Serial.println(volts_sample2);
      
  
            //Serial.print("PD2 Volts1  = ");
            //Serial.println(PD2_volts_sample1);
            
            //Serial.print("PD2 Volts2  = ");
            //Serial.println(PD2_volts_sample2);
            
            //Serial.print("PD2 Volts after subtraction = ");
            //Serial.println(PD2_volts_sample2-PD2_volts_sample1);
  
            if((PD2_volts_sample2-PD2_volts_sample1) <= 1){
              //found segment!
               //PIN RG6 (Port G) 
               LATGbits.LATG6=1;            //Set pin 6 in Latch G register to 1, turn LED2_SEG_FOUND ON
               //Serial.print("Photodiode 2: Segment of Green Core Shell Found! \n");

               //delay(250);
  
            }
            else{
              ////Serial.print("No Segment Found... \n");
            
  
            //*****just for testing remove this later*******
            //delay(250);
  
            //turn segment found indicator LED OFF
            //PIN RG6 (Port G) 
            LATGbits.LATG6=0;     //Set pin 6 in Latch G register to 0, turn LED2_SEG_FOUND OFF
            }
  
             break;
          case 8 :
             //Turn LED2 OFF
             //Serial.print("State 8\n");
             //PIN PMD0/RE1 (Port E) 
             LATEbits.LATE1=0;     //Set pin 1 in Latch E register to 0, turn LED2 OFF
             break;
     
          default :
             Serial.print("ERROR: Invalid State ");
             //Serial.println(state);
     
        }
   }

 
    
 
}

