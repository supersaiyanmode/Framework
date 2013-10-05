#if defined(PRODUCER_CONSUMER_TEST) || defined(ENABLE_ALL_TESTS)
#include <iostream>
#include <vector>

#include "Thread/Thread.h"
#include "Thread/ThreadLogger.h"
#include "Thread/SynchronisedQueue.h"

int nextNum(){
    static Mutex* nextNumLock;
    static int nextNum = 0;
    if (!nextNumLock){
        nextNumLock = Mutex::createMutex();
    }
    int num;
    nextNumLock->acquire();
    num = ++nextNum;
    nextNumLock->release();
    return num;
}

class ProdCons {
    SynchronisedQueue<int>* mainQueue;
    std::vector<Thread<ProdCons, int>*> producers, consumers;
    bool active;
public:
    
    void produce(int sleep){
        tlog("Started to produce");
        int prod = nextNum();
        while (active){
            if (mainQueue->timedPush(prod, 50000)){
                prod++;
                tlog("Produced: "<<prod);
            } else {
                tlog("Full. Can't produce!");
            }
            ThreadBase::sleep(sleep);
        }
    }
    
    void consume(int sleep){
        tlog("Started to consume");
        while (active){
            int obj;
            if (mainQueue->timedPop(obj, 50000)){
                tlog("Consuming: "<<obj);
            }else{
                tlog("Nothing to consume!");
            }
            ThreadBase::sleep(sleep);
        }
    }
    
    ProdCons(int sz, int p, int ps, int c, int cs){
        active = true;
        mainQueue = SynchronisedQueue<int>::createSynchronisedQueue(sz);
        for (int i=0; i<p; i++){
            producers.push_back(
                Thread<ProdCons, int>::createThread(this, &ProdCons::produce)
            );
            producers[i]->start(ps);
        }
        for (int i=0; i<c; i++){
            consumers.push_back(
                Thread<ProdCons, int>::createThread(this, &ProdCons::consume)
            );
            consumers[i]->start(cs);
        }
    }
    
    ~ProdCons(){
        active = false;
        tlog("Destroying ...");
        for (std::vector<Thread<ProdCons, int>*>::iterator it=producers.begin();
                    it != producers.end(); it++){
            delete *it;
            tlog("Kill one producer");
        }
        for (std::vector<Thread<ProdCons, int>*>::iterator it=consumers.begin();
                    it != consumers.end(); it++){
            delete *it;
            tlog("Kill one consumer");
        }
        delete mainQueue;
    }
};

int main(){
    ProdCons p(5, 4, 200, 1, 100);
    ThreadBase::sleep(5000);
}
#endif