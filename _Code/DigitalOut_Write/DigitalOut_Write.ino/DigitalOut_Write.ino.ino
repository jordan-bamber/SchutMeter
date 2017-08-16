void setup() {
  // put your setup code here, to run once:

  #include "p32mx795f512l.h"                  //include header file
  
  Serial.begin(9600);                         // initialize serial com through USB
  Serial.print("Hello World\n");

   //configure the port registers
    PORTSetPinsDigitalOut(IOPORT_D, BIT_0);
    
    //"PORTWrite not declared in this scope"-needs "plib.h"
    //PORTWrite(IOPORT_D, BIT_5);
    
}

void loop() {
  // put your main code here, to run repeatedly:
  //PORTWrite(IOPORT_D, BIT_5);

  //set bits to 0000000000000001 via bit mask OR
  PORTSetBits(IOPORT_D, BIT_0 | 1);
}
