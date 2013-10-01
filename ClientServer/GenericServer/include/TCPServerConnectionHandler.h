#ifndef TCP_SERVER_CONNECTION_HANDLER_BASE_H
#define TCP_SERVER_CONNECTION_HANDLER_BASE_H

#include "IO/SocketIO/Connection.h"

class TCPServerConnectionHandler {
public:
    virtual void onIncomingConnection(Connection)=0;
    virtual ~TCPServerConnectionHandler() {}
};

#endif
