#ifndef __AUTO_LOCK_H_
#define __AUTO_LOCK_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

class ILockable
{
public:
    virtual ~ILockable() { }

    virtual void lock()   = 0;
    virtual void unlock() = 0;
};

class Lock
{
public:
    inline Lock(ILockable& lock) : mLock(lock)  { mLock.lock(); }
    inline Lock(ILockable* lock) : mLock(*lock) { mLock.lock(); }
    inline ~Lock() { mLock.unlock(); }

private:
    ILockable& mLock;
};

class AutoLock : public ILockable
{
friend class CondVar;

public:
    AutoLock();
    ~AutoLock();

    void lock();
    void unlock();

private:
    AutoLock(const AutoLock&) = delete;
    AutoLock& operator = (const AutoLock&) = delete;

private:
    pthread_mutex_t mLock;
};

#endif /* __AUTO_LOCK_H_ */

