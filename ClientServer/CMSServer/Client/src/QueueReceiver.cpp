#include "QueueReceiver.h"
#include "ThreadLogger.h"



QueueReceiver::QueueReceiver(CMSServerConnection& c, const CMSDestGroup& d):
                    conn(c), cmsDestGroup(d){
    conn.registerClient(this);
}

QueueReceiver::~QueueReceiver() {
    
}