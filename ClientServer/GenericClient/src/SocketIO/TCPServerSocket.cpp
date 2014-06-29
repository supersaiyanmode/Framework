#include <cstring>

#include "SocketIO/TCPServerSocket.h"

TCPServerSocket::TCPServerSocket(int p):TCPSocket(0), port(p){
    
}

TCPServerSocket::~TCPServerSocket(){
    
}

void TCPServerSocket::initialise(){
    int optval = 1;
    setsockopt(Socket::socket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof optval);
    bind();
    listen();
}

int TCPServerSocket::bind(){
    sockaddr_in serv_addr;
    std::memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    int res = ::bind(Socket::socket, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
    if (res < 0)
        throw SocketException("Unable to bind server socket.");
    return res;
}

void TCPServerSocket::listen(int queueSize){
    ::listen(Socket::socket,queueSize);
}

Connection TCPServerSocket::accept(){
    sockaddr_in remote;
    socklen_t remoteLen = sizeof(remote);
    PLATFORM_SOCKET sock = ::accept(Socket::socket, (sockaddr*) &remote, &remoteLen);
    if (sock < 0){
        close();
        throw SocketException("Error while accepting connection.");
    }
        
    return Connection(TCPSocket(sock,1,1));
}

int TCPServerSocket::close(){
    return TCPSocket::close();
}
