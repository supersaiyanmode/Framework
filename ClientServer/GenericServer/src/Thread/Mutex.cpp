#include "Thread/Mutex.h"

Mutex::Mutex() {
#ifdef WIN32
    
#else
    pthread_mutex_init(&mutex, NULL);
#endif
    destroyed = false;
}

Mutex* Mutex::createMutex(){
    return new Mutex();
}

#ifdef WIN32
    
#else
pthread_mutex_t& Mutex::getPlatformMutex(){
    return mutex;
}
#endif

void Mutex::acquire(){
#ifdef WIN32

#else
    pthread_mutex_lock(&mutex);
#endif
    acquired = true;
}


void Mutex::release(){
#ifdef WIN32

#else
    pthread_mutex_unlock(&mutex);
#endif
    acquired = false;
}

void Mutex::destroy(){
    if (destroyed)
        return;
#ifdef WIN32

#else
    pthread_mutex_destroy(&mutex);
#endif
    destroyed = true;
}

Mutex::~Mutex(){
    destroy();
}
