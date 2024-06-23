#include "AutoLock.h"

AutoLock::AutoLock()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);

    pthread_mutex_init(&mLock, &attr);
    pthread_mutexattr_destroy(&attr);
}

AutoLock::~AutoLock()
{
    pthread_mutex_destroy(&mLock);
}

void AutoLock::lock()
{
    pthread_mutex_lock(&mLock);
}

void AutoLock::unlock()
{
    pthread_mutex_unlock(&mLock);
}
