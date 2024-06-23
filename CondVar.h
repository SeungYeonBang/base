#ifndef __COND_VAR_H_
#define __COND_VAR_H_

#include "AutoLock.h"

#include <pthread.h>

class CondVar
{
public:
    CondVar();
    ~CondVar();

    void wait(AutoLock& lock);

    void signal();
    void broadcast();

private:
    CondVar(const CondVar&) = delete;
    CondVar& operator= (const CondVar&) = delete;

private:
    pthread_cond_t mCond;
};

#endif /* __COND_VAR_H_ */
