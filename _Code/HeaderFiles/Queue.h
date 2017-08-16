/*
 * File:	Queue.c
 * Purpose:	Serve as a buffer for data from control cycle to ensure that no data is missed between collection and processing
 *
 * Notes:	N element FIFO queue
 *			
 */

//Preprocessor Directives
#ifndef QUEUE_H  //conditionally compile if does not already exist
#define QUEUE_H  //

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments

/* Definitions */

#define QLEN	10	// number of queue entries

typedef struct {

	//define struct members
	int16_t led1on;
	int16_t led1off;
	int16_t led2on;
	int16_t led2off;
} aQentry;                  //struct name

/* Macros */
    
/* Public functions */

/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */

//close preprocessing directives
#endif  /* QUEUE_H */ 