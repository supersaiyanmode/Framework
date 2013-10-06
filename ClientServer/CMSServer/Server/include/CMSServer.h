#ifndef CMS_SERVER_MAIN_H
#define CMS_SERVER_MAIN_H

#include "ThreadingTCPServer.h"
#include "Core/MessageProcessor.h"
#include "Core/BridgeProcessor.h"

class CMSServer : protected ThreadingTCPServer, protected TCPServerConnectionHandler,
                                protected MessageProcessor, protected BridgeProcessor {
    bool destroyed;
    
protected:
    virtual void onIncomingConnection(Connection);

	virtual bool onReceiverRegistrationRequest();
    virtual bool onReceiverUnregistrationRequest();

public:
    CMSServer(int);
    virtual ~CMSServer();

    virtual void initialise();
    virtual void shutdown();
    virtual void serve();
    
    virtual std::string addBridge(const CMSDestGroup&, const CMSDestination&, bool isQueue);
};



#endif
