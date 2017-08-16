/*
 * File:	Queue.c
 * Purpose:	Serve as a buffer for data from control cycle to ensure that no data is missed between collection and processing
 *
 * Notes:	N element FIFO queue
 *			
 */

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments
#include "Queue.h"
/* Definitions */

aQentry queue[QLEN];            //defines an array named queue, of QLEN length, of type aQentry 
aQentry *qInp, *qOutp, *qEnd;   //define pointers of type aQentry


/* Macros */

/* Public functions */

/********************************************************************
   
   Queue Initialization
   
*********************************************************************/
void Qinit(void)
{
	// “queue” by itself is a pointer to the start of the array (the first element in this case)
	qInp = queue;               // DC- “queue” by itself is a pointer to the start of the array, so the statement “qInp = queue” sets the pointer qInp to the start of the array
	qOutp = queue;              //init output pointer at beginning of queue
	qEnd = queue + QLEN;        //The pointer qEnd is initialized to point to the last queue entry + 1 entry (queue + QLEN)

								/* Individual elements can be accessed either by pointer (*qInp for example), or by index (queue[5] for example).
								Note that in this case each element is comprised of 8 bytes (four 16-bit words),
								so the statement “++qInp” tells the compiler to increment the pointer by 8 bytes.*/
}

/********************************************************************
   
  Qput
   
*********************************************************************/
// put new data in the queue    //Qput function
void Qput(aQentry qData)        //pass qData to this
{
	*qInp = qData;              //set input pointer to qData
	qInp++;						//added by JLB- DC mentioned in an email that compiler would auto increment pointers, look into this more-DC said he forgot this and it should've been added
	if (++qInp == qEnd) {
		qInp = queue; //This queue is a FIFO, i.e. circular, so after QLEN entries have been put into the queue,
	}								//the pointer must go back to the beginning of the array. That’s done with the statement “if (qInp == qEnd) qInp = queue”.
}

// get data from the queue (returns 0 if empty)
uint8_t Qget(aQentry *qData)
{
	if (qOutp == qInp) {        //if input pointer = ouput pointer, then the queue is empty and 0 is returned--if these two vars are incremented correctly, overflow/incorrect state should be able to be avoided
		return 0;
	}
	else {                    //else if queue not empty
		*qData = *qOutp;        //set value @ qdata = to value @ qOutp
		if (++qOutp == qEnd) {
			qOutp = queue;
		}//This queue is a FIFO, i.e. circular, so after QLEN enteries have been accessed/referenced, the pointer resets to the beginning of the queue                                            
		return 1;
	}
}




/* Private functions */

/* Public variables */

/* Private variables */

/* Type Definitions */

/* Special type definitions */


