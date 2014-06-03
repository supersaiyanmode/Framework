#ifndef CMS_CLIENT_H
#define CMS_CLIENT_H

#include "Protocol/CMSMessage/GenericCMSMessage.h"
#include "Protocol/CMSDestination/CMSDestGroup.h"
#include "Sequential.h"

class CMSClient {
    UniqueID clientID;
public:
    CMSClient();
    virtual ~CMSClient();
    
    UniqueID id() const;
	virtual const CMSDestGroup& destination() const = 0;
    
    virtual void onAcknowledgement(UniqueID, GenericCMSMessage&) {}
    virtual void onError(UniqueID, GenericCMSMessage&) {}
    virtual void onMessage(GenericCMSMessage&) {}
    
    virtual void onDisconnect(){}
};






//INLINE FUNCTIONS
inline UniqueID CMSClient::id() const{
    return clientID;
}

#endif
