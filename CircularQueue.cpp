#include "CircularQueue.h"

#include <pthread.h>

CircularQueue::CircularQueue(int capability) 
              : mCapability(capability),
                mSize(0),
                mHead(0),
                mTail(0)
{
    mData = (int*)malloc(sizeof(int));
    pthread_cond_init(&mCondVar, NULL);
}

CircularQueue::~CircularQueue()
{
    pthread_cond_destroy(&mCondVar);
    if(mData)
        free(mData);
}

void CircularQueue::push(int d)
{
    mLock.lock();
    if (isFull())
        return;

    mData[mTail] = d;
    mTail = ( mTail + 1 ) % mCapability;
    mSize ++;
    pthread_cond_signal(&mCondVar);
    mLock.unlock();
}

int CircularQueue::pop()
{
    mLock.lock();
    if (isEmpty())
        pthread_cond_wait(&mCondVar, &mLock.mLock);

    int d = mData[mHead];
    mHead = (mHead + 1) % mCapability;
    mSize --;
    mLock.unlock();
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
