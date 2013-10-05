#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#include <time.h>

#ifdef WIN32

#else
#include <sys/time.h>
#define PLATFORM_TIMESPAN timespec
#endif


class Time {
    unsigned long seconds_;
    unsigned long useconds_;
public:
    Time();
    ~Time();
    
    unsigned long seconds() const;
    unsigned long useconds() const;
    
    bool operator < (const Time& other) const;
    
    static Time now();
    static PLATFORM_TIMESPAN after(unsigned int);
};




//INLINE FUNCTIONS

inline unsigned long Time::seconds() const{
    return seconds_;
}
inline unsigned long Time::useconds() const{
    return useconds_;
}

inline bool Time::operator < (const Time& other) const {
    if (seconds_ < other.seconds_)
        return true;
    else if (seconds_ > other.seconds_)
        return false;
    else 
        return useconds_ < other.useconds_;
}

#endif
