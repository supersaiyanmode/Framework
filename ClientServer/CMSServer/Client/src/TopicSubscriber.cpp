#include "TopicSubscriber.h"
#include "ThreadLogger.h"



TopicSubscriber::TopicSubscriber(CMSServerConnection& c, const CMSDestGroup& d):
                    conn(c), cmsDestGroup(d){
    conn.registerClient(this);
}

TopicSubscriber::~TopicSubscriber() {
    
}