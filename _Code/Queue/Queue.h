/*
	Header for Queue example
*/

//pre procesor directives
#ifndef QUEUE_H  //conditionally compile if does not already exist
#define QUEUE_H  //

#include <stdint.h>

#define QLEN	10	// number of queue entries

typedef struct {
	
    //define struct members
    int16_t led1on; 
	int16_t led1off;
	int16_t led2on;
	int16_t led2off;
} aQentry;                  //struct name

//close preprocessing directives 
#endif  /* QUEUE_H */ 
