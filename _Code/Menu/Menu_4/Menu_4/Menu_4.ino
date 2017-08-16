/*
 * JLB 6-20-17
 * 
 * New and improved state machine code with menu v2
 * State machine code. Interrupts & state changes every 250 micro seconds. Confirmed via scope
 * 
 */

#include<stdio.h>
//#include <conio.h>

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
void TurnOFF_T2()
{
  T2CONbits.ON = 0;                     // turn ON TMR2
}

void TurnOFF_T2_Interrupts()
{
  IEC0bits.T2IE = 0;                    // Enable TMR2 interrupts
}



/* Define the Interrupt Service Routine (ISR) */
void __attribute__((interrupt)) myISR() {
  clearIntFlag(_TIMER_2_IRQ);               /* Clear IF flag for ISR */
  
  state++;
  if (state >= 9) state =1;     //reset state variable after cycle complete
  ////Serial.println(state);


  float PD1_ADC1;
  float PD1_ADC2;
  float PD2_ADC1;
  float PD2_ADC2;
  float PD1_volts_sample1;
  float PD1_volts_sample2;
  float PD2_volts_sample1;
  float PD2_volts_sample2;  

   switch(state) {
           case 1 :
            //Sample Photodiode 1
            
            PD1_ADC1 = analogRead(0);
            PD1_volts_sample1 = ADC_to_Volts_3_3(PD1_ADC1);

            break;
  
          case 2 :
            //Turn LED1 ON
             
             //PIN PMD0/RE0 (Port E) 
              LATEbits.LATE0=1;     //Set pin 0 in Latch E register to 1, turn LED1 ON
             break;
          
          case 3 :
            //Sample Photodiode 1 again

            PD1_ADC2 = analogRead(0);
            PD1_volts_sample2 = ADC_to_Volts_3_3(PD1_ADC2);

            if((PD1_volts_sample2-PD1_volts_sample1) <= 1){
              //found segment!
               
               //PIN RG9 (Port G) 
               LATGbits.LATG9=1;            //Set pin 9 in Latch G register to 1, turn LED1_SEG_FOUND ON
  
            }
            else{
              //turn segment found indicator LED OFF
              //PIN RG9(Port G) 
              LATGbits.LATG9=0;     //Set pin 9 in Latch G register to 0, turn LED1_SEG_FOUND OFF
            }
  
             break;
          case 4 :
             //Turn LED1 OFF
             
             //PIN PMD0/RE0 (Port E) 
             LATEbits.LATE0=0;     //Set pin 0 in Latch E register to 0, turn LED1 OFF
             break;

          case 5 :
            //Sample Photodiode 2

            PD2_ADC1 = analogRead(2);
            PD2_volts_sample1 = ADC_to_Volts_3_3(PD2_ADC1);

            break;
  
          case 6 :
             //Turn LED2 ON
             
             //PIN PMD0/RE1 (Port E) 
             LATEbits.LATE1=1;     //Set pin 1 in Latch E register to 1, turn LED2 ON
             
             break;
          
          case 7 :
            //Sample Photodiode 2 again
            
            PD2_ADC2 = analogRead(2);
            PD2_volts_sample2 = ADC_to_Volts_3_3(PD2_ADC2);
            
            if((PD2_volts_sample2-PD2_volts_sample1) <= 1){
              //found segment!
               
               //PIN RG6 (Port G) 
               LATGbits.LATG6=1;            //Set pin 6 in Latch G register to 1, turn LED2_SEG_FOUND ON
  
            }
            else{
             
              //PIN RG6 (Port G) 
              LATGbits.LATG6=0;     //Set pin 6 in Latch G register to 0, turn LED2_SEG_FOUND OFF
            }
  
             break;
          
          case 8 :
             //Turn LED2 OFF
             
             //PIN PMD0/RE1 (Port E) 
             LATEbits.LATE1=0;     //Set pin 1 in Latch E register to 0, turn LED2 OFF
             
             break;
     
          default :
             Serial.print("ERROR: Invalid State ");
            
     
        }

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

void setup() 
{

   Serial.begin(9600);
   //configure the port registers to digital output
   TRISE = 0x0000;
   TRISG = 0x0000;  


  

  int selection = 0;

  do
  {
    Serial.println("");//print blank line
    Serial.println("Menu: ");
    Serial.println("[1] Detect Bubbles (Enter a 9 to stop)");
    Serial.println("[2] Calibrate ");
    Serial.println("[3] Turn on spectrometer white light");
    Serial.println("[4] Turn on spectrometer 450 nm light ");
    Serial.println("[5] Turn off spectrometer lights ");
    Serial.println("[6] Quit ");

    Serial.println("");//print blank line
    Serial.println("Please Input Selection...");//print or println?
    
    while(selection == 0)
    {
      
         // send data only when you receive data:
        if (Serial.available() > 0)
        {
               
                int incomingByte = 0;   // for incoming serial data
                // read the incoming byte:
                incomingByte = Serial.read();

                // For debug
                //Serial.print("I received: ");
                //Serial.println(incomingByte, DEC);

                //hardcode ascii conversion
                selection = (int)incomingByte - 48;
                
                Serial.print("Selection Value: ");
                Serial.println(selection);
                
        }
    }
    
    switch(selection)
    {
      case 1:
        Serial.println("Detecting bubbles until 9 is entered...");
        selection = 0;

        //option 1 code
         SetupTMR2();
         SetupInterrupt_TMR2();

          while(selection != 9)
          {
      
               // send data only when you receive data:
              if (Serial.available() > 0)
              { 
                      int incomingByte = 0;   // for incoming serial data
                      // read the incoming byte:
                      incomingByte = Serial.read();
      
                      // For debug
                      //Serial.print("I received: ");
                      //Serial.println(incomingByte, DEC);
      
                      //hardcode ascii conversion
                      selection = (int)incomingByte - 48;
                      
              }
          }

          Serial.println("Timer 2 spinning down");
          selection = 0;      // reset selction var for new menu use
          TurnOFF_T2();
          TurnOFF_T2_Interrupts();

        
        break;
      case 2:
        Serial.println("Success -calibrate");
        selection = 0;

        //calibration code here
        
        break;
      case 3:
        Serial.println("Success-Turn on spectrometer white light");
        selection = 0;

        //spectrometer white light code here
        //The signal that turns the white spectrometer LED  ON/OFF  is Port E bit 5 (RE5).
        LATEbits.LATE5=1;     //Set pin 5 in Regiester E, turn White Spectrometer LED ON 

        
        break;
      case 4:
        Serial.println("Success-Turn on spectrometer 450 nm light");
        selection = 0;

        //spectrometer 450nm light code here
        //The one that controls the 450 nm spectrometer LED is Port E bit 4 (RE4)
        LATEbits.LATE4=1;     //Set pin 4 in Regiester E, turn Spectrometer 450nm LED ON
        
        break;
      case 5:
        Serial.println("Success-Turn off spectrometer lights");
        selection = 0;

        //spectrometer lights off code here
        LATEbits.LATE5=0;     //Set pin 5 in Regiester E, turn White Spectrometer LED OFF
        LATEbits.LATE4=0;     //Set pin 5 in Regiester E, turn White Spectrometer LED ON
        
        break;
      case 6:
        Serial.println("Quit Intiated, please power off/disconnect");
        //selection = 0;
        break;
      default:
        Serial.println("Selection Invalid");
    }
  }while(selection != 6);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  
  

}
