#ifndef CMS_TOPIC_SUBSCRIBER_H
#define CMS_TOPIC_SUBSCRIBER_H

#include "CMSClient.h"
#include "CMSServerConnection.h"
#include "Protocol/CMSDestination/CMSDestGroup.h"

class TopicSubscriber : public CMSClient {
    CMSServerConnection& conn;
    CMSDestGroup cmsDestGroup;
    
    
    TopicSubscriber(const TopicSubscriber&);
    TopicSubscriber& operator=(const TopicSubscriber&);
protected:
    TopicSubscriber(CMSServerConnection&, const CMSDestGroup&);
    virtual ~TopicSubscriber();

	const CMSDestGroup& destination() const;
    
public:
    virtual void onMessage(GenericCMSMessage&)=0;
    virtual void onDisconnect(){}
};
    

//INLINE FUNCTIONS

inline const CMSDestGroup& TopicSubscriber::destination() const {
	return cmsDestGroup;
}

#endif
