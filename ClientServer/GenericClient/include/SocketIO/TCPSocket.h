#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include "Socket.h"

class TCPSocket: public Socket {
public:
    TCPSocket(PLATFORM_SOCKET=0, int=-1, int=-1);
    TCPSocket(const TCPSocket&);
    virtual TCPSocket& operator=(const TCPSocket&);
    virtual ~TCPSocket();
    
    virtual void initialise();

};

#endif
