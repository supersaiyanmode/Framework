#include "Thread.h"


void ThreadBase::sleep(int milli){
#ifdef WIN32
    Sleep(milli);
#else
    timespec ts = {milli/1000, (milli%1000)*1000000};
    nanosleep(&ts,NULL);
#endif
}