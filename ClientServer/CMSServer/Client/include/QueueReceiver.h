#ifndef CMS_QUEUE_RECEIVER_H
#define CMS_QUEUE_RECEIVER_H

#include "CMSClient.h"
#include "CMSServerConnection.h"
#include "Protocol/CMSDestination/CMSDestGroup.h"

class QueueReceiver : public CMSClient {
    CMSServerConnection& conn;
    CMSDestGroup cmsDestGroup;
    
    
    QueueReceiver(const QueueReceiver&);
    QueueReceiver& operator=(const QueueReceiver&);
protected:
    QueueReceiver(CMSServerConnection&, const CMSDestGroup&);
    virtual ~QueueReceiver();

	const CMSDestGroup& destination() const;
    
public:
    virtual void onMessage(GenericCMSMessage&)=0;
    virtual void onDisconnect(){}
};
    

//INLINE FUNCTIONS

inline const CMSDestGroup& QueueReceiver::destination() const {
	return cmsDestGroup;
}

#endif
