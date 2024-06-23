#ifndef __CIRCULAR_QUEUE_H_
#define __CIRCULAR_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "AutoLock.h"

#define RET_SUCCESS  0
#define RET_EMPTY   -2
#define RET_FULL    -3
#define RET_EOS     -4


class CircularQueue
{
public:
    CircularQueue(int capability);
    ~CircularQueue();

    int push(int d);
    int  pop();

    bool isEmpty();
    bool isFull();
    int  size();

private:
    int mCapability;
    int mSize;
    int mHead;
    int mTail;

    int* mData;

    AutoLock mLock;
};

#endif /* __CIRCULAR_QUEUE_H_ */
