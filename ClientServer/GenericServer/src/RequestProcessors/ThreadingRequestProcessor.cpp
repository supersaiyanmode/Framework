#include "RequestProcessors/ThreadingRequestProcessor.h"


typedef Thread<ThreadingRequestProcessor, Connection> TRPThread;

ThreadingRequestProcessor::ThreadingRequestProcessor(): active(false) {
    
}

ThreadingRequestProcessor::~ThreadingRequestProcessor() {
    if (active)
        shutdown();
    for (std::vector<TRPThread*>::iterator it=threads.begin();
                it!=threads.end(); it++)
         delete *it;
}

void ThreadingRequestProcessor::processRequest(Connection c){
    if (!active)
        active = true;
    TRPThread* t = Thread<ThreadingRequestProcessor, Connection>::
                        createThread(this, 
                        &ThreadingRequestProcessor::onIncomingConnection);
    t->start(c);
    threads.push_back(t);
}

void ThreadingRequestProcessor::initialise() {
    active = true;
}

void ThreadingRequestProcessor::shutdown(){
    if (!active)
        return;
    for (std::vector<TRPThread*>::iterator it=threads.begin();
                it!=threads.end(); it++)
         (*it)->kill();
    active = true;
}