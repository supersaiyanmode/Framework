#ifndef BASE_TCP_SERVER_H
#define BASE_TCP_SERVER_H

#include "ServerSkeleton.h"
#include "RequestProcessors/RequestProcessor.h"

class BaseTCPServer : public ServerSkeleton, public RequestProcessor {
    bool baseTCPServerActive;
public:
    BaseTCPServer(int);
    virtual ~BaseTCPServer();
    
    virtual void initialise();
    virtual void processRequest(Connection)=0;
    
    virtual void serve();
    virtual void shutdown();
};


#endif
