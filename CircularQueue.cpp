#include "CircularQueue.h"

#include <pthread.h>

CircularQueue::CircularQueue(int capability) 
              : mCapability(capability),
                mSize(0),
                mHead(0),
                mTail(0)
{
    mData = (int*)malloc(sizeof(int));
}

CircularQueue::~CircularQueue()
{
    if(mData)
        free(mData);
}

int CircularQueue::push(int d)
{
    Lock lock(mLock);
    if (isFull())
    {
        printf("buffer size is Full!! \n");
        return RET_FULL;
    }

    mData[mTail] = d;
    mTail = ( mTail + 1 ) % mCapability;
    mSize ++;

    return RET_SUCCESS;
}

int CircularQueue::pop()
{
    Lock lock(mLock);
    if (isEmpty())
    {
        printf("is Empty!!\n");
        return RET_EMPTY;
    }

    int d = mData[mHead];
    mHead = (mHead + 1) % mCapability;
    mSize --;
    return d;
}

bool CircularQueue::isEmpty()
{
    return mSize == 0;
}

bool CircularQueue::isFull()
{
    return mSize == mCapability;
}

int CircularQueue::size()
{
    return mSize;
}
