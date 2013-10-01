#ifndef THREADING_TCP_SERVER_H
#define THREADING_TCP_SERVER_H

#include "BaseTCPServer.h"
#include "RequestProcessors/ThreadingRequestProcessor.h"
#include "TCPServerConnectionHandler.h"
#include "Plugin.h"

class ThreadingTCPServer : public ThreadingRequestProcessor, public BaseTCPServer {
    bool active;
    TCPServerConnectionHandler* handler;
    
        
    ThreadingTCPServer(const ThreadingTCPServer&);
    ThreadingTCPServer& operator=(const ThreadingTCPServer&);
    
    void processRequest(Connection);
public:
    ThreadingTCPServer(int, TCPServerConnectionHandler*);
    virtual ~ThreadingTCPServer();
    
    virtual void initialise();
    virtual void shutdown();
    
protected:
    virtual void onIncomingConnection(Connection);
};

#endif
