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
  
//PIN PMD0/RE0 (Port E) 
  LATGbits.LATG9=1;     //Set pin 0 in Latch E register to 1, turn LED ON

delay(500);

 //PIN PMD0/RE0 (Port E) 
  LATGbits.LATG9=0;     //Set pin 0 in Latch E register to 0, turn LED OFF
 
 
 
 //PIN PMD0/RE0 (Port E) 
  LATGbits.LATG6=1;     //Set pin 0 in Latch E register to 1, turn LED ON

delay(500);

 //PIN PMD0/RE0 (Port E) 
  LATGbits.LATG6=0;     //Set pin 0 in Latch E register to 0, turn LED OFF
}
