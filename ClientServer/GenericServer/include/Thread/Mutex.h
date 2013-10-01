#ifndef MUTEX__X
#define MUTEX__X

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <errno.h>
#endif

class Mutex {
    bool acquired,destroyed;
#ifdef WIN32

#else
    pthread_mutex_t mutex;
#endif
    Mutex();
    Mutex(Mutex&);
    void operator=(Mutex&);
public:
    
    static Mutex* createMutex();
    
    void acquire();
    void release();
    
    void destroy();
#ifdef WIN32
#else
    pthread_mutex_t& getPlatformMutex();
#endif
    virtual ~Mutex();
};

#endif
