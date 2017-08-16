void setup() {
  // put your setup code here, to run once:

  #include "p32mx795f512l.h"                  //include header file
  
  Serial.begin(9600);                         // initialize serial com through USB
  Serial.print("Hello World\n");

   //configure the port registers
   //PORTSetPinsDigitalOut(IOPORT_B, BIT_0);

    //AD1PCFG = 0xFFFFFFFF;                         // Make all analog/digital pins digital-but still need to be configured for either input or output ( instead of analog )
    
   //Sets all Port B pins to digital output
   TRISE = 0x0000;
   TRISG = 0x0000;
   //PORTB = 0;                                 // Make all PORT B bits 0
    
}

void loop() {
  // put your main code here, to run repeatedly:

  /*
 //PIN PMD0/RE0 (Port E) 
  LATEbits.LATE0=1;     //Set pin 0 in Latch E register to 1, turn LED1 ON

 //PIN PMD0/RE0 (Port E) 
  LATEbits.LATE0=0;     //Set pin 0 in Latch E register to 0, turn LED1 OFF
*/

  //PIN RG6/G_4 (Port G) 
  LATGbits.LATG6=1;     //Set pin 4 in Latch G register to 1, turn LED1_SEG_FOUND ON
//PIN RG6/G_4 (Port G) 
  LATGbits.LATG6=0;     //Set pin 4 in Latch G register to 0, turn LED1_SEG_FOUND OFF

   //PIN RG6/G_4 (Port G) 
  LATGbits.LATG9=1;     //Set pin 4 in Latch G register to 1, turn LED1_SEG_FOUND ON
//PIN RG6/G_4 (Port G) 
  LATGbits.LATG9=0;     //Set pin 4 in Latch G register to 0, turn LED1_SEG_FOUND OFF
}
