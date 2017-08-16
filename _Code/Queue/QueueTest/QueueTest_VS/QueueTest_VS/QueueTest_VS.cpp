// QueueTest_VS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Queue.c"


int main()
{
    
	Qinit();
	//Serial.begin(9600);
	//Serial.println("Hello");

	int16_t a = 1;
	int16_t b = 2;
	int16_t c = 3;
	int16_t d = 4;
	int16_t e = 5;
	int16_t f = 6;
	int16_t g = 7;
	int16_t h = 8;
	int16_t i = 9;
	int16_t j = 10;
	int16_t k = 11;

	aQentry EntryOne ;
	EntryOne.led1on = a;
	EntryOne.led1off = b;
	EntryOne.led2on = c;
	EntryOne.led2off = d;

	aQentry EntryOne_2;
	EntryOne_2.led1on = e;
	EntryOne_2.led1off = f;
	EntryOne_2.led2on = g;
	EntryOne_2.led2off = h;

	aQentry EntryOne_3;
	EntryOne_3.led1on = i;
	EntryOne_3.led1off = j;
	EntryOne_3.led2on = k;
	EntryOne_3.led2off = a;

	
	aQentry Temp;
	aQentry *EntryOne_Temp;
	EntryOne_Temp = &Temp;

	



	//Serial.println(queue[0]);
	Qput(EntryOne);
	//Serial.println(queue[0]);
	Qput(EntryOne_2);
	Qput(EntryOne_3);
	//Qput(d);
	//Qput(e);
	//Qput(f);
	//Qput(g);
	//Qput(h);
	//Qput(i);
	//Qput(j);
	Qget(EntryOne_Temp);
	return 0;
}

