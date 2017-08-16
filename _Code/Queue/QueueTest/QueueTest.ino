#include "Queue.h"
#include "Queue.c"

void setup() {

  Qinit();
  Serial.begin(9600);
  Serial.println("Hello");
  
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int e = 5;
  int f = 6;
  int g = 7;
  int h = 8;
  int i = 9;
  int j = 10;
  int k =11;


  Serial.println(queue[0]);
  Qput(a);
  Serial.println(queue[0]);
  Qput(b);
  Qput(c);
  Qput(d);
  Qput(e);
  Qput(f);
  Qput(g);
  Qput(h);
  Qput(i);
  Qput(j);
  Qput(k);
  
  

}

void loop() {
  


}
