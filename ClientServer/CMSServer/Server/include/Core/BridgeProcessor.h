#ifndef BRIDGE_PROCESSOR_H
#define BRIDGE_PROCESSOR_H
#include <map>
#include <vector>

#include "Sequential.h"
#include "ReadWriteLock.h"
#include "../Protocol/CMSDestination/CMSDestGroup.h"
#include "../Protocol/CMSDestination/CMSDestination.h"
#include "../Protocol/CMSMessage/GenericCMSMessage.h"

#include "MessageProcessor.h"
    
struct Bridge {
    CMSDestGroup from; //Redundant.
    CMSDestination to;
    std::string bridgeID;
};

struct BridgeData {
    CMSDestGroup from;
    std::vector<Bridge> to;
    bool isQueue;
};

class BridgeProcessor {
    ReadWriteLock* lock;
    std::map<CMSDestGroup, BridgeData> bridgeMultimap;
    
    bool bridgeExists(const CMSDestGroup&, const CMSDestination&) const;
public:
    BridgeProcessor();
    UniqueID addBridge(const CMSDestGroup&, const CMSDestination&, bool isQueue);
    bool removeBridge(const UniqueID&);
    
    bool processMessage(GenericCMSMessage& msg, MessageProcessor&);
};

#endif