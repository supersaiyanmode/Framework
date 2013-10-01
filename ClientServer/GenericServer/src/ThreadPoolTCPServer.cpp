#include "ThreadPoolTCPServer.h"

ThreadPoolTCPServer::ThreadPoolTCPServer(int port,
                TCPServerConnectionHandler* h,
                int workers, int queueSize):
                BaseTCPServer(port), ThreadPoolRequestProcessor(workers,queueSize),
                handler(h) {
    
}

ThreadPoolTCPServer::~ThreadPoolTCPServer(){
    if (active)
        shutdown();
}

void ThreadPoolTCPServer::processRequest(Connection c){
    ThreadPoolRequestProcessor::processRequest(c);
}

void ThreadPoolTCPServer::onIncomingConnection(Connection c) {
    //TODO: Check if handler == NULL
    handler->onIncomingConnection(c);
}


void ThreadPoolTCPServer::initialise(){
    BaseTCPServer::initialise();
    ThreadPoolRequestProcessor::initialise();
    active = true;
}

void ThreadPoolTCPServer::shutdown(){
    if (active){
        BaseTCPServer::shutdown();
        ThreadPoolRequestProcessor::shutdown();
        active = false;
    }
}

