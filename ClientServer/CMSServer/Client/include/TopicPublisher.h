#ifndef TOPIC_PUBLISHER_H
#define TOPIC_PUBLISHER_H

#include "CMSServerConnection.h"
#include "Protocol/CMSMessage/GenericCMSMessage.h"
#include "Protocol/CMSDestination/CMSDestination.h"

class TopicPublisher {
    CMSServerConnection& conn;
    CMSDestination destination;
    
    TopicPublisher(const TopicPublisher&);
    TopicPublisher& operator=(const TopicPublisher&);
    
protected:
    TopicPublisher(CMSServerConnection&, const CMSDestination&);
    ~TopicPublisher();
    
    void onAcknowledgement(UniqueID, GenericCMSMessage&);
    void onError(UniqueID, GenericCMSMessage&);
    void onMessage(GenericCMSMessage&);

public:
    bool publish(const CMSHeaderSet&, const std::string&);
    bool publish(const std::string&);
    
};

#endif