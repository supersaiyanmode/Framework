#include "ThreadingTCPServer.h"

ThreadingTCPServer::ThreadingTCPServer(int p, TCPServerConnectionHandler* h):
    BaseTCPServer(p), handler(h) {
    
}

ThreadingTCPServer::~ThreadingTCPServer(){
    if (active)
        shutdown();
}

void ThreadingTCPServer::processRequest(Connection c){
    ThreadingRequestProcessor::processRequest(c);
}

void ThreadingTCPServer::onIncomingConnection(Connection c) {
    handler->onIncomingConnection(c);
}


void ThreadingTCPServer::initialise(){
    active = true;
    BaseTCPServer::initialise();
    ThreadingRequestProcessor::initialise();
}

void ThreadingTCPServer::shutdown(){
    if (active) {
        BaseTCPServer::shutdown();
        ThreadingRequestProcessor::shutdown();
        active = false;
    }
}

