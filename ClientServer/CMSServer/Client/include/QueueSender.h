#ifndef QUEUE_SENDER_H
#define QUEUE_SENDER_H

#include "CMSServerConnection.h"
#include "Protocol/CMSMessage/GenericCMSMessage.h"
#include "Protocol/CMSDestination/CMSDestination.h"

class QueueSender {
    CMSServerConnection& conn;
    CMSDestination destination;
    
    QueueSender(const QueueSender&);
    QueueSender& operator=(const QueueSender&);
    
protected:
    QueueSender(CMSServerConnection&, const CMSDestination&);
    ~QueueSender();
    
    void onAcknowledgement(UniqueID, GenericCMSMessage&);
    void onError(UniqueID, GenericCMSMessage&);
    void onMessage(GenericCMSMessage&);

public:
    bool send(const CMSHeaderSet&, const std::string&);
    bool send(const std::string&);
    
};
#endif