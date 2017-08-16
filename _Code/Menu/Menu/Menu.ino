//basic menu template - version 1

#include<stdio.h>
//#include <conio.h>

void setup() 
{

   Serial.begin(9600);
  // put your setup code here, to run once:

  Serial.println("Menu: ");

  int selection = 0;

  do
  {
  
    Serial.println("[1] Option 1 ");
    Serial.println("[2] Option 2 ");
    Serial.println("[3] Option 3 ");
    Serial.println("[4] Option 4 ");

    Serial.println("");//print blank line
    Serial.println("Input Selection:");//print or println?
    
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
                
                Serial.print("selection value: ");
                Serial.println(selection);
                
        }
    }
    
    switch(selection)
    {
      case 1:
        Serial.println("Success option 1");
        selection = 0;
        break;
      case 2:
        Serial.println("Success option 2");
        selection = 0;
        break;
      case 3:
        Serial.println("Success option 3");
        selection = 0;
        break;
      case 4:
        Serial.println("Quit Intiated, please power off/disconnect");
        //selection = 0;
        break;
      default:
        Serial.println("Selection Invalid");
    }
  }while(selection != 4);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  
  

}
