#include "Thread/Condition.h"

Condition::Condition(Mutex* m):mutex(m) {
#ifdef WIN32

#else
    pthread_cond_init(&condition, NULL);
#endif
    destroyed = false;
}

Condition::~Condition(){
    destroy();
}

void Condition::wait(){
#ifdef WIN32

#else
    pthread_cond_wait(&condition, &mutex->getPlatformMutex());
#endif
}

int Condition::timedWait(PLATFORM_TIMESPAN t){
    return pthread_cond_timedwait(&condition, &mutex->getPlatformMutex(), &t) == ETIMEDOUT? -1: 0;
}

void Condition::signal(){
#ifdef WIN32

#else
    pthread_cond_signal(&condition);
#endif
}

void Condition::broadcast() {
#ifdef WIN32
	
#else
	pthread_cond_broadcast(&condition);
#endif
}

void Condition::destroy(){
    if (destroyed)
        return;
#ifdef WIN32

#else
    pthread_cond_destroy(&condition);
#endif
    destroyed = true;
}

Condition* Condition::createCondition(Mutex* m){
    return new Condition(m);
}