#ifndef MESSAGE_PROCESSOR_H
#define MESSAGE_PROCESSOR_H

#include <map>
#include <string>

#include "../Protocol/CMSMessage/GenericCMSMessage.h"
#include "ReadWriteLock.h"
#include "TimeUtil.h"

//TODO: Replace CMSDestination instead of std::string when using destinations.

class ClientEndPoint;

struct RegistrationData {
	ClientEndPoint* client;
	std::string receiverID;
	std::string destination;
    std::string destinationType; // "queue" or "topic"
    
    Time lastServed;
};

class MessageProcessor {
public:
	MessageProcessor();
	~MessageProcessor();
    
    bool registerReceiver(ClientEndPoint*, const std::string& id, const std::string& dest);
    bool unregisterReceiver(ClientEndPoint*, const std::string& id);
	
    bool processQueueMessage(GenericCMSMessage&, const CMSDestination& = CMSDestination());
    bool processTopicMessage(GenericCMSMessage&, const CMSDestination& = CMSDestination());
    
    void removeClient(ClientEndPoint*);
    
protected:
    virtual bool onReceiverRegistrationRequest() = 0;
    virtual bool onReceiverUnregistrationRequest() = 0;
    
private:
    std::vector<std::vector<RegistrationData>::iterator> findAll(
        ClientEndPoint*, const std::string&, const std::string&, int fields);
    std::vector<RegistrationData>::iterator find(
        ClientEndPoint*, const std::string&, const std::string&, int fields);
    
	ReadWriteLock* lock;
	std::vector<RegistrationData> registrations;
};

#endif
