#ifndef TCP_CLIENT_SOCKET_H
#define TCP_CLIENT_SOCKET_H

#include <string>
#include "TCPSocket.h"

class TCPClientSocket: public TCPSocket {
    std::string remoteIP;
    int port;
public:
    TCPClientSocket(const std::string&, int);
    virtual ~TCPClientSocket();
    
    virtual void initialise();
    virtual int close();
};

#endif
