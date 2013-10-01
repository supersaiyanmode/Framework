#include <iostream>

#include "BaseTCPServer.h"

BaseTCPServer::BaseTCPServer(int p): ServerSkeleton(p){
    
}

BaseTCPServer::~BaseTCPServer(){
    
}

void BaseTCPServer::initialise() {
    ServerSkeleton::initialise();
}

void BaseTCPServer::serve(){
    baseTCPServerActive = true;
    while (baseTCPServerActive){
        std::cout<<"[BaseTCPServer] Waiting for a connection.."<<std::endl;
        Connection c = ServerSkeleton::accept();
        std::cout<<"[BaseTCPServer] Got a connection.."<<std::endl;
        processRequest(c);
    }
}

void BaseTCPServer::shutdown(){
    baseTCPServerActive = false;
    ServerSkeleton::shutdown();
}

