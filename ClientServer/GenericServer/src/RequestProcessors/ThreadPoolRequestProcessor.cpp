#include <iostream>

#include "RequestProcessors/ThreadPoolRequestProcessor.h"

ThreadPoolRequestProcessor::ThreadPoolRequestProcessor(int workers, int queueSize) { //default 10
    threadPool = ThreadPool<ThreadPoolRequestProcessor, Connection>::createThreadPool(
        workers, queueSize);
    active = false;
}

ThreadPoolRequestProcessor::~ThreadPoolRequestProcessor(){
    if (active)
        shutdown();
}

void ThreadPoolRequestProcessor::initialise() {
    active = true;
    threadPool->start();
    std::cout<<"[ThreadPoolRequestProcessor] Initialised."<<std::endl;
}

void ThreadPoolRequestProcessor::processRequest(Connection c){
    std::cout<<"[ThreadPoolRequestProcessor] Processing a request."<<std::endl;
    threadPool->execute(this, &ThreadPoolRequestProcessor::onIncomingConnection, c);
}


void ThreadPoolRequestProcessor::shutdown(){
    if (active){
        active = false;
        delete threadPool;
    }
}