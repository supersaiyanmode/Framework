#include "IO/SocketIO/TCPClientSocket.h"

TCPClientSocket::TCPClientSocket(const std::string& ip, int p):
                                        TCPSocket(0), remoteIP(ip), port(p){
    
}

TCPClientSocket::~TCPClientSocket(){
    
}

void TCPClientSocket::initialise(){
    ::sockaddr_in serverAddress;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_port=htons(port);
    serverAddress.sin_addr.s_addr=inet_addr(remoteIP.c_str());
    
    if (::connect(Socket::socket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr)) < 0)
        throw SocketException("Unable to reach " + remoteIP);
    setIOStatus(1,1);
}

int TCPClientSocket::close(){
    return TCPSocket::close();
}
