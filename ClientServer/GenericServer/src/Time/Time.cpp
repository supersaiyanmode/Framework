#include "Time/Time.h"

Time::Time() {
#ifdef WIN32

#else
    ::timeval now;
    gettimeofday(&now, NULL);
    seconds_ = now.tv_sec;
    useconds_ = now.tv_usec;
#endif
}

Time::~Time() {
    
}


PLATFORM_TIMESPAN Time::after(unsigned int usec){
#ifdef WIN32

#else
    ::timeval now;
    ::timespec abstimeout;

    gettimeofday(&now, NULL);
    abstimeout.tv_sec = now.tv_sec + usec/1000000;
    abstimeout.tv_nsec = 1000L * (now.tv_usec + (usec%1000000));
    if (abstimeout.tv_nsec >= 1000000000) {
        abstimeout.tv_sec++;
        abstimeout.tv_nsec -= 1000000000;
    }
    return abstimeout;
#endif
}
