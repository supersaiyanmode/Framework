#include <cstdlib>
#include <sstream>

#include "Sequential.h"
#include "Mutex.h"

Mutex* sequentialMutex = Mutex::createMutex();

void deleteMutex(){
    delete sequentialMutex;
}

int crapSequential = std::atexit(deleteMutex);

UniqueID Sequential::next(){
    static long cur=0;
    long ret;
    sequentialMutex->acquire();
    ret = ++cur;
    sequentialMutex->release();
    std::stringstream ss;
    ss<<ret;
    return ss.str();
}
