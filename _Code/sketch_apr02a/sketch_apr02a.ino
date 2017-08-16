void setup() {
  // put your setup code here, to run once:

  #include "p32mx795f512l.h"                  //include header file
  
  Serial.begin(9600);                         // initialize serial com through USB
  Serial.print("Hello World\n");

   //configure the port registers
    //PORTSetPinsDigitalOut(IOPORT_D, BIT_0);
    
   //Sets all Port D pins to output
   TRISD = 0x0000;
    
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Set pin 0 in Latch D register to 0
  LATDbits.LATD0=0;

  //Set pin 1 in Latch D register to 1
  LATDbits.LATD1=1;
}
