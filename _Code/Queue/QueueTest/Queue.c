/*
	Queue example
	
*/

#include "Queue.h"

// the queue
aQentry queue[QLEN];            //defines an array named queue, of QLEN length, of type aQentry 
aQentry *qInp, *qOutp, *qEnd;   //define pointers of type aQentry

// initialization               //Qinit function
void Qinit(void)            
{
    // “queue” by itself is a pointer to the start of the array (the first element in this case)
	qInp = queue;               // so the statement “qInp = queue” sets the pointer qInp to the start of the array
	qOutp = queue;              //init output pointer at beginning of queue
	qEnd = queue + QLEN;        //The pointer qEnd is initialized to point to the last queue entry + 1 entry (queue + QLEN)
    
    /* Individual elements can be accessed either by pointer (*qInp for example), or by index (queue[5] for example). 
       Note that in this case each element is comprised of 8 bytes (four 16-bit words),
       so the statement “++qInp” tells the compiler to increment the pointer by 8 bytes.*/
}

// put new data in the queue    //Qput function
void Qput(aQentry qData)        //pass qData to this
{
	*qInp = qData;              //set input pointer to qData
	if (qInp == qEnd) qInp = queue; //This queue is a FIFO, i.e. circular, so after QLEN entries have been put into the queue,
                                     //the pointer must go back to the beginning of the array. That’s done with the statement “if (qInp == qEnd) qInp = queue”.
}

// get data from the queue (returns 0 if empty)
uint8_t Qget(aQentry *qData)
{
	if (qOutp == qInp) {        //if input pointer = ouput pointer, then the queue is empty and 0 is returned
		return 0;
	} else {                    //else if queue not empty
		*qData = *qOutp;        //set value @ qdata = to value @ qOutp
		if (qOutp == qEnd) qOutp = queue;   //This queue is a FIFO, i.e. circular, so after QLEN enteries have been accessed/referenced, the pointer resets to the beginning of the queue                                            
		return 1;
	}
}
