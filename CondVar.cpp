#include "CondVar.h"

CondVar::CondVar()
{
    pthread_condattr_t attr;
    pthread_condattr_init(&attr);
    pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
    pthread_cond_init(&mCond, &attr);
    pthread_condattr_destroy(&attr);
}

CondVar::~CondVar()
{
    pthread_cond_destroy(&mCond);
}

void CondVar::wait(AutoLock& lock)
{
    pthread_cond_wait(&mCond, &lock.mLock);
}

void CondVar::signal()
{
    pthread_cond_signal(&mCond);
}

void CondVar::broadcast()
{
    pthread_cond_broadcast(&mCond);
}
