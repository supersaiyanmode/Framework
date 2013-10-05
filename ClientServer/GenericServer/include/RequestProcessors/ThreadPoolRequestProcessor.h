#ifndef THREAD_POOL_REQUEST_PROCESSOR
#define THREAD_POOL_REQUEST_PROCESSOR

#include <vector>

#include "RequestProcessor.h"
#include "Thread.h"
#include "ThreadPool.h"
#include "../IO/SocketIO/Connection.h"

class ThreadPoolRequestProcessor: public RequestProcessor {
    bool active;
    ThreadPool<ThreadPoolRequestProcessor, Connection>* threadPool;
protected:
    ThreadPoolRequestProcessor(int=10, int=1024);
    virtual ~ThreadPoolRequestProcessor();
    
    virtual void initialise();
    virtual void shutdown();
    
    virtual void processRequest(Connection);
    virtual void onIncomingConnection(Connection)=0;
};

#endif
