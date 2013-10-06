#include "CMSServer.h"
#include "Core/ClientEndPoint.h"

CMSServer::CMSServer(int p): ThreadingTCPServer(p, this) {
    destroyed = false;
}

CMSServer::~CMSServer() {
    if (!destroyed)
        shutdown();
}

void CMSServer::initialise() {
    ThreadingTCPServer::initialise();
}

void CMSServer::shutdown() {
    if (destroyed)
        return;
    ThreadingTCPServer::shutdown();
    destroyed = true;
}
    
void CMSServer::serve() {
    ThreadingTCPServer::serve();
}

void CMSServer::onIncomingConnection(Connection c) {
    ClientEndPoint cep(c, *this, *this);
    cep.processIncoming();
}

bool CMSServer::onReceiverRegistrationRequest() {
    return true;
}

bool CMSServer::onReceiverUnregistrationRequest() {
    return true;
}

std::string CMSServer::addBridge(const CMSDestGroup& from, const CMSDestination& to, bool isQueue) {
    return BridgeProcessor::addBridge(from, to, isQueue);
}
