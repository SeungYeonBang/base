#ifndef __CIRCULAR_QUEUE_H_
#define __CIRCULAR_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include "AutoLock.h"

class CircularQueue
{
public:
    CircularQueue(int capability);
    ~CircularQueue();

    void push(int d);
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
    pthread_cond_t  mCondVar;
};

#endif /* __CIRCULAR_QUEUE_H_ */
