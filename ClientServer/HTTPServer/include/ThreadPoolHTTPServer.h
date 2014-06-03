#ifndef THREAD_POOL_HTTP_SERVER_H
#define THREAD_POOL_HTTP_SERVER_H

#include <string>

#include "HTTPServiceMapper.h"
#include "HTTPEndPointHandler.h"
#include "ThreadPoolTCPServer.h"
#include "ConfigurationFileParser.h"

class ThreadPoolHTTPServer : public ThreadPoolTCPServer,
                            public HTTPServiceMapper, public TCPServerConnectionHandler {
    int port;
    
    ConfigurationFile configuration;
public:
    ThreadPoolHTTPServer(int port, int workers=10, int queueSize=1024);
    virtual ~ThreadPoolHTTPServer();
    
    void registerHandler(const HTTPRequestProperty& prop, HTTPEndPointHandler* handler);
    void unregisterHandler(const HTTPRequestProperty& prop);
    
    virtual void onIncomingConnection(Connection);
    
    void initialise();
};

#endif
