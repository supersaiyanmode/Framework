#include <iostream>
#include <cstdlib>

#include "Thread/ThreadLogger.h"
#include "Thread/Mutex.h"

Mutex* displayMutex = Mutex::createMutex();

void deleteDisplayMutex(){
    if (displayMutex)
        delete displayMutex;
}

int crapThreadLogger = std::atexit(deleteDisplayMutex);

void threadDisplay(const std::string& line){
    displayMutex->acquire();
    std::cout<<line<<std::endl;
    displayMutex->release();
}