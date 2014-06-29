#ifndef SERVER_SKELETON_H
#define SERVER_SKELETON_H

#include "SocketIO/TCPServerSocket.h"

class ServerSkeleton {
protected:
    TCPServerSocket serverSocket;
public:
    ServerSkeleton(int);
    ServerSkeleton(const ServerSkeleton&);
    virtual ~ServerSkeleton();
    
    
    virtual ServerSkeleton& operator=(const ServerSkeleton& other);
    
    virtual void initialise();

    virtual Connection accept();
    virtual void shutdown();
};

#endif
