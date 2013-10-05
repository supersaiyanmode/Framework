#ifndef CONDITION_LOCK_H
#define CONDITION_LOCK_H

#include "Mutex.h"
#include "TimeUtil.h"

class Condition {
#ifdef WIN32

#else
    pthread_cond_t condition;
#endif
    bool destroyed;
    Mutex* mutex;
    Condition(Mutex*);
    void operator=(const Condition&);
public:
    static Condition* createCondition(Mutex*);
    void wait();
    int timedWait(PLATFORM_TIMESPAN);
    void signal();
    void broadcast();
	
	
    void destroy();
    
    virtual ~Condition();
};

#endif
