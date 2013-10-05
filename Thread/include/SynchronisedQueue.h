#ifndef SYNCRONISED_QUEUE_H
#define SYNCRONISED_QUEUE_H

#include <ctime>
#include <queue>

#include "Mutex.h"
#include "Condition.h"
#include "TimeUtil.h"

template <typename T>
class SynchronisedQueue {
    std::queue<T> internalQueue;
    unsigned int maxQueueSize;
    Mutex* queueLock;
    Condition *notEmpty, *notFull;
    bool active;
    
    SynchronisedQueue(const SynchronisedQueue&){}
    SynchronisedQueue& operator=(const SynchronisedQueue&){}
    
    SynchronisedQueue(int max): maxQueueSize(max) { 
        active = true;
        queueLock = Mutex::createMutex();
        notEmpty = Condition::createCondition(queueLock);
        notFull = Condition::createCondition(queueLock);
    }
public:
    static SynchronisedQueue* createSynchronisedQueue(int max=0){
        return new SynchronisedQueue(max);
    }
    
    bool resize(unsigned int size) { //only increases size now..
        if (size <= maxQueueSize)
            return false;
        queueLock->acquire();
        maxQueueSize = size;
        queueLock->release();
    }
    
    void push(const T& obj){
        queueLock->acquire();
        if (maxQueueSize != 0)
            while (internalQueue.size() >= maxQueueSize) // > when queue is being shrunk
                notFull->wait();
        
        internalQueue.push(obj);
        notEmpty->signal();
        queueLock->release();
    }
    
    bool timedPush(const T& obj, unsigned int usec){
        if (maxQueueSize == 0){
            push(obj);
            return true;
        }
        PLATFORM_TIMESPAN absTimeout = Time::after(usec);
        int ret = 0;
        
        queueLock->acquire();
        while (internalQueue.size() == maxQueueSize && ret != -1)
            ret = notFull->timedWait(absTimeout);
        
        if (ret == -1){
            queueLock->release();
            return false;
        }
        
        internalQueue.push(obj);
        notEmpty->signal();
        queueLock->release();
        return true;
    }
    
    T pop(){
        queueLock->acquire();
        while (internalQueue.empty())
            notEmpty->wait();
        T obj(internalQueue.front());
        internalQueue.pop();
        notFull->signal();
        queueLock->release();
        
        return obj;
    }
    
    bool timedPop(T& obj, unsigned int usec){
        PLATFORM_TIMESPAN absTimeout = Time::after(usec);
        int ret = 0;
        
        queueLock->acquire();
        while (internalQueue.empty() && ret != -1)
            ret = notEmpty->timedWait(absTimeout);
        
        if (ret == -1){
            queueLock->release();
            return false;
        }
        obj = internalQueue.front();
        internalQueue.pop();
        notFull->signal();
        queueLock->release();
        
        return true;
    }
    
    operator bool() const {
        return isActive();
    }
    
    bool isActive() const{
        return active;
    }
    
    void destroy(){
        active = false;
        queueLock->destroy();
        notEmpty->destroy();
        notFull->destroy();
    }
    
    ~SynchronisedQueue(){
        delete queueLock;
        delete notEmpty;
        delete notFull;
    }
};

#endif
