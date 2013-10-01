#include "IO/SocketIO/TCPSocket.h"

TCPSocket::TCPSocket(PLATFORM_SOCKET sock, int readState, int writeState):
        Socket(sock == 0? ::socket(AF_INET, SOCK_STREAM, 0):sock, readState, writeState){
}

TCPSocket::TCPSocket(const TCPSocket& other): Socket(other){
    
}

TCPSocket& TCPSocket::operator=(const TCPSocket& other){
    Socket::operator=(other);
    return *this;
}

TCPSocket::~TCPSocket(){
    
}

void TCPSocket::initialise(){
    
}