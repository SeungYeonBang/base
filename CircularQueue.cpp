#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

class AutoLock
{
public:
    AutoLock(pthread_mutex_t* lock) : mLock(lock)
    {
        pthread_mutex_lock(mLock);
    }

    ~AutoLock()
    {
        pthread_mutex_unlock(mLock);
    }

private:
    pthread_mutex_t* mLock;
};

class CircularQueue
{
public:
    CircularQueue(int capability) : mCapability(capability),
                                    mSize(0),
                                    mHead(0),
                                    mTail(0)
    {
        mData = (int*)malloc(sizeof(int));
        pthread_mutex_init(&mLock, NULL);
        pthread_cond_init(&mCondVar, NULL);
    }

    ~CircularQueue()
    {
        pthread_cond_destroy(&mCondVar);
        pthread_mutex_destroy(&mLock);
        if(mData)
            free(mData);
    }

    void push(int d)
    {
        AutoLock lock(&mLock);
        if (isFull())
            return;

        mData[mTail] = d;
        mTail = ( mTail + 1 ) % mCapability;
        mSize ++;
        pthread_cond_signal(&mCondVar);
    }

    int pop()
    {
        AutoLock lock(&mLock);
        if (isEmpty())
            pthread_cond_wait(&mCondVar, &mLock);

        int d = mData[mHead];
        mHead = (mHead + 1) % mCapability;
        mSize --;
        return d;
    }

    bool isEmpty()
    {
        return mSize == 0;
    }

    bool isFull()
    {
        return mSize == mCapability;
    }
    
    int size()
    {
        return mSize;
    }

private:
    int mCapability;
    int mSize;
    int mHead;
    int mTail;

    int* mData;
    pthread_mutex_t mLock;
    pthread_cond_t  mCondVar;
};


static void* producer_proc(void* param)
{
    CircularQueue* queue = (CircularQueue*)param;

    int num = 0;
    while(1)
    {
        getchar();
        queue->push(num++);
    }

    return NULL;
}

static void* consumer_proc(void* param)
{
    CircularQueue* queue = (CircularQueue*)param;
    while(1)
    {
        int d = queue->pop();
        printf("%d\n", d);
    }

    return NULL;
}

int main()
{
    CircularQueue queue(5);
 
    pthread_t producer;
    pthread_t consumer;

    pthread_create(&producer, NULL, producer_proc, &queue);
    pthread_create(&consumer, NULL, consumer_proc, &queue);

    while(1)
        sleep(1);

    return 0;
}
