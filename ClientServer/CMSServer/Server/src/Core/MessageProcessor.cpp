#include <algorithm>

#include "Core/MessageProcessor.h"
#include "Core/ClientEndPoint.h"
#include "Sequential.h"
#include "ThreadLogger.h"

//--------- RoundRobin Comparator --------
struct RoundRobinComparator {
    bool operator() (const std::vector<RegistrationData>::iterator& first, 
                        const std::vector<RegistrationData>::iterator& second) const {
        return first->lastServed < second->lastServed;
    }
};



MessageProcessor::MessageProcessor() {
	lock = ReadWriteLock::createReadWriteLock();
}

MessageProcessor::~MessageProcessor() {
    delete lock;
}


//NOTE: Acquire the lock outside!
std::vector<RegistrationData>::iterator MessageProcessor::find(
            ClientEndPoint* cep,
            const std::string& receiverID,
            const std::string& destination,
            int fields){
    std::vector<RegistrationData>::iterator it;
    //lock->lockRead();
    for (it=registrations.begin(); it!=registrations.end(); it++){
        if ((fields & 4) && (it->client != cep))
            continue;
        if ((fields & 2) && (it->receiverID != receiverID))
            continue;
        if ((fields & 1) && (it->destination != destination))
            continue;
        lock->unlockRead();
        return it;
    }
    //lock->unlockRead();
    return it;
}

//NOTE: Acquire the lock outside!
std::vector<std::vector<RegistrationData>::iterator> MessageProcessor::findAll(
            ClientEndPoint* cep,
            const std::string& receiverID,
            const std::string& destination,
            int fields){
    std::vector<std::vector<RegistrationData>::iterator> ret;
    //lock->lockRead();
    for (std::vector<RegistrationData>::iterator it=registrations.begin(); it!=registrations.end(); it++){
        if ((fields & 4) && (it->client != cep))
            continue;
        if ((fields & 2) && (it->receiverID != receiverID))
            continue;
        if ((fields & 1) && (it->destination != destination))
            continue;
        ret.push_back(it);
    }
    //lock->unlockRead();
    return ret;
}


bool MessageProcessor::registerReceiver(
            ClientEndPoint* cep,
            const std::string& receiverID,
            const std::string& dest){
    tlog("[MessageProcessor] Processing Registration Request");
    lock->lockWrite();
    if (find(cep, "", dest, 5) != registrations.end()){
        lock->unlockWrite();
        return false;
    }
    if (!onReceiverRegistrationRequest()) {
        lock->unlockWrite();
        return false;
    }
    RegistrationData rd = {cep, receiverID, dest};
    registrations.push_back(rd);
    lock->unlockWrite();
    return true;
}

bool MessageProcessor::unregisterReceiver(
            ClientEndPoint* cep,
            const std::string& receiverID) {
    tlog("[MessageProcessor] Processing Un-Registration Request");
    lock->lockWrite();
    std::vector<RegistrationData>::iterator it = find(cep, receiverID, "", 6);
    if (it == registrations.end()) {
        lock->unlockWrite();
        return false;
    }
    if (!onReceiverUnregistrationRequest()){
        lock->unlockWrite();
        return false;
    }

    registrations.erase(it);
    lock->unlockWrite();
    return true;
}

void MessageProcessor::removeClient(ClientEndPoint* cep) {
    lock->lockWrite();
    std::vector<std::vector<RegistrationData>::iterator> clients(findAll(cep, "","",4));
    std::vector<std::vector<RegistrationData>::iterator>::iterator it = clients.begin();
    
    for (; it!=clients.end(); it++){
        registrations.erase(*it);
    }
    lock->unlockWrite();
}

bool MessageProcessor::processQueueMessage(GenericCMSMessage& msg, const CMSDestination& override) {
    tlog("[MessageProcessor] Processing Queue Request");
    
    //Acquire a Read lock for the entire Function: What if a regn is erased after finding?!
    
    lock->lockRead();
    CMSDestination dest = msg.getStandardHeader("destination");
    if (override.valid())
        dest = override;
    //TODO: Change findAll parameter
    std::vector<std::vector<RegistrationData>::iterator> clients(findAll(NULL, "", (std::string)dest,1));
    std::vector<RegistrationData>::iterator rdi;
    
    if (!clients.size())
        return false;
    rdi = *std::min_element(clients.begin(), clients.end(), RoundRobinComparator());
    
    rdi->lastServed = Time();
    
    msg.updateStandardHeader("direction", "forward");
    msg.updateStandardHeader("global-message-id", Sequential::next()); //TODO: Acknowledgement mechanism!!
    msg.updateStandardHeader("receiver-id", rdi->receiverID);
    msg.updateStandardHeader("category", GenericCMSMessage::CMSMessageTypeToStr(GenericCMSMessage::Queue));
    
    rdi->client->addOutboundMessage(msg);
    
    lock->unlockRead();
    return true;
}

bool MessageProcessor::processTopicMessage(GenericCMSMessage& msg, const CMSDestination& override) {
    tlog("[MessageProcessor] Processing Topic Request");
    
    //Acquire a Read lock for the entire Function: What if a regn is erased after finding?!
    lock->lockRead();
    CMSDestination dest = msg.getStandardHeader("destination");
    if (override.valid()) 
        dest = override;
    //TODO: change findAll Parameter;
    std::vector<std::vector<RegistrationData>::iterator> clients(findAll(NULL, "", (std::string)dest,1));
    std::vector<std::vector<RegistrationData>::iterator>::iterator it = clients.begin();
    
    
    msg.updateStandardHeader("direction", "forward");
    msg.updateStandardHeader("global-message-id", Sequential::next()); //TODO: Acknowledgement mechanism!!
    msg.updateStandardHeader("category", GenericCMSMessage::CMSMessageTypeToStr(GenericCMSMessage::Topic));    
    
    for (; it != clients.end(); it++){
        msg.updateStandardHeader("receiver-id", (*it)->receiverID);
        (*it)->client->addOutboundMessage(msg);
    }
    
    lock->unlockRead();
    return true;
}
