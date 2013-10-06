#include "Core/BridgeProcessor.h"

BridgeProcessor::BridgeProcessor() {
    lock = ReadWriteLock::createReadWriteLock();
}

//Assumes READ-LOCK 
bool BridgeProcessor::bridgeExists(const CMSDestGroup& src, const CMSDestination& dest) const {
    std::map<CMSDestGroup, BridgeData>::const_iterator it;
    for (it = bridgeMultimap.begin(); it != bridgeMultimap.end(); it++) {
        if (!it->first.matches(src))
            continue;
        std::vector<Bridge> bridges = it->second.to;
        for (std::vector<Bridge>::iterator it1 = bridges.begin(); it1 != bridges.end(); it1++) {
            if (it1->to.matches(dest))
                return true;
        }
    }
    return false;
}

UniqueID BridgeProcessor::addBridge(const CMSDestGroup& from, const CMSDestination& to, bool isQueue) {
    lock->lockWrite();
    
    UniqueID result;
    if (!bridgeExists(from, to)) {
        result = Sequential::next();
        Bridge b = {from, to, result};
        BridgeData bd = {from, std::vector<Bridge>(1, b), isQueue};
        bridgeMultimap[from] = bd;
    }
    
    lock->unlockWrite();
    
    return result;
}

bool BridgeProcessor::removeBridge(const UniqueID& id) {
    lock->lockWrite();
    
    bool result = false;
    std::vector<Bridge>* toRemoveVector;
    std::vector<Bridge>::iterator toRemoveIterator;
    
    std::map<CMSDestGroup, BridgeData>::iterator it;
    for (it = bridgeMultimap.begin(); it != bridgeMultimap.end() && !result; it++) {
        std::vector<Bridge>& bridges = it->second.to;
        for (std::vector<Bridge>::iterator it1 = bridges.begin(); it1 != bridges.end() && !result; it1++) {
            if (it1->bridgeID == id) {
                toRemoveVector = &bridges;
                toRemoveIterator = it1;
                result = true;
            }
        }
    }
    
    if (result) {
        toRemoveVector->erase(toRemoveIterator);
    }
    
    lock->unlockWrite();
    return result;
}
    
bool BridgeProcessor::processMessage(GenericCMSMessage& msg, MessageProcessor& mp) {
    CMSDestination dest;
    
    try {
        dest = CMSDestination((std::string)msg.destination());
    } catch (...) {
        return false;
    }
    
    lock->lockRead();
    
    std::map<CMSDestGroup, BridgeData>::iterator it;
    for (it = bridgeMultimap.begin(); it != bridgeMultimap.end(); it++) {
        if (it->first.matches(dest)) {
            bool isQueue = it->second.isQueue;
            std::vector<Bridge>& bridges = it->second.to;
            for (std::vector<Bridge>::iterator it1 = bridges.begin(); it1 != bridges.end(); it1++) {
                if (isQueue)
                    mp.processQueueMessage(msg, it1->to);
                else
                    mp.processTopicMessage(msg, it1->to);
            }
            break;
        }
    }

    lock->unlockRead();
    return true;
}