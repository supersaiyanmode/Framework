#ifndef THREAD_POOL_TCP_SERVER
#define THREAD_POOL_TCP_SERVER

#include <string>

#include "BaseTCPServer.h"
#include "RequestProcessors/ThreadPoolRequestProcessor.h"
#include "../include/TCPServerConnectionHandler.h"
#include "Plugin.h"

class ThreadPoolTCPServer : public BaseTCPServer, public ThreadPoolRequestProcessor {
    bool active;
    TCPServerConnectionHandler* handler;
    
    ThreadPoolTCPServer(const ThreadPoolTCPServer&);
    ThreadPoolTCPServer& operator=(const ThreadPoolTCPServer&);

    void processRequest(Connection);
    void onIncomingConnection(Connection);
    
public:
    ThreadPoolTCPServer(int, TCPServerConnectionHandler*,
                        int workers=10, int queueSize=1024);
    virtual ~ThreadPoolTCPServer();
    
    virtual void initialise();
    virtual void shutdown();    
};

#endif

