#ifndef __AUTO_LOCK_H_
#define __AUTO_LOCK_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

class AutoLock
{
friend class CircularQueue;

public:
    AutoLock();
    ~AutoLock();

    void lock();
    void unlock();

private:
    pthread_mutex_t mLock;
};

#endif /* __AUTO_LOCK_H_ */

