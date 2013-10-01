#ifndef TCP_SERVER_SOCKET_H
#define TCP_SERVER_SOCKET_H

#include <string>

#include "TCPSocket.h"
#include "Connection.h"

class TCPServerSocket:public TCPSocket{
    int port;
public:
    TCPServerSocket(int);
    virtual ~TCPServerSocket();
    
    virtual void initialise();
    virtual int bind();
    virtual void listen(int=10);
    virtual Connection accept();
    virtual int close();
};


#endif
