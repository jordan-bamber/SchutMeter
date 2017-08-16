/*
Queue example

*/

#include "Queue.h"

// the queue
aQentry queue[QLEN];
aQentry *qInp, *qOutp, *qEnd;

// initialization
void Qinit(void)
{
	qInp = queue;
	qOutp = queue;
	qEnd = queue + QLEN;
}

// put new data in the queue (returns 0 if not full)
uint8_t Qput(aQentry qData)
{
	aQentry *qPtr;
	qPtr = qInp;
	if (++qPtr == qEnd) qPtr = queue;
	if (qPtr == qOutp) {
		// queue is full
		return 1;
	}
	else {
		// queue not full, store new data
		*qInp = qData;
		qInp = qPtr;
		return 0;
	}
}

// get data from the queue (returns 0 if empty)
uint8_t Qget(aQentry *qData)
{
	if (qOutp == qInp) {
		// empty, return nothing
		return 0;
	}
	else {
		// not empty, return next data
		*qData = *qOutp;
		if (++qOutp == qEnd) qOutp = queue;
		return 1;
	}
}