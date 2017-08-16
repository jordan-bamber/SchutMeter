/*
  Tutorial 4:  Analog to digital conversion
  Description: Reads an analog signal input to A0 pin and send the
               10-bit ADC output to PC to display on the serial monitor.
  Board: chipKIT UNO32
 */
 
int ADC_OUTPUT;
void setup() {
  Serial.begin(9600);                         // initialize serial com through USB
  Serial.print("Hello World\n");
}
 
void loop() {
  
  /*
   By default, the supply voltage of 3.3V is used as the reference voltage for A/D conversion, 
   which means input voltages between 0 and 3.3 volts are mapped into integer values between 0 and 1023. 
   In order to use an external reference voltage applied to the A pin, use analogReference(External) function in your sketch. 
   */
  
  ADC_OUTPUT = analogRead(A2);
  Serial.print("Output = ");
  Serial.println(ADC_OUTPUT, DEC);
  delay(1000);
}
