#if defined(THREADING_TEST) || defined(ENABLE_ALL_TESTS)
#include <iostream>
#include <vector>

#include "Thread/Thread.h"
#include "Thread/Mutex.h"
#include "Thread/ThreadLogger.h"

class Counter {
    Thread<Counter, int>* thread;
    int id;
    Counter(){
        static int last=0;
        id = ++last;
        
    }
public:
    static Counter* createCounter(){
        return new Counter();
    }
    
    void start(){
        tlog("start(). this="<<this);
        thread = Thread<Counter, int>::createThread(this, &Counter::run);
        thread->start(0);
    }
    
    void run(int){
        tlog("run() invoked. this="<<this);
        ThreadBase::sleep(1000);
        while (true) {
            tlog("["<<id<<"] is alive");
            ThreadBase::sleep(800);
        }
    }
    
    ~Counter() {
        delete thread;
        tlog("Counter destroyed!");
    }
};

int main(){
    const int MAX = 2;
    std::vector<Counter*> vec;
    for (int i=0; i<MAX; i++){
        vec.push_back(Counter::createCounter());
    }
    for (int i=0; i<MAX; i++){
        vec[i]->start();
        tlog("vec["<<i<<"]: "<<vec[i]);
    }
    ThreadBase::sleep(10000);
    
    for (int i=0; i<MAX; i++)
        delete vec[i];
}
#endif
