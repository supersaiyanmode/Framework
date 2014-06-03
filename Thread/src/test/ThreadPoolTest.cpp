#if defined(THREAD_POOL_TEST) || defined(ENABLE_ALL_TESTS)
#include "Thread/ThreadPool.h"
#include "Thread/ThreadLogger.h"

class Counter {
public:
    void run(int id){
        for (int i=0; i<5; i++){
            ThreadBase::sleep(100);
            tlog("<"<<id<<"> "<<i);
        }
    }
};

int main(){
    ThreadPool<Counter, int>* pool = ThreadPool<Counter, int>::createThreadPool(2,2);
    Counter c;
    pool->start();
    tlog("Pool started!");
    for (int i=0; i<5; i++){
        pool->execute(&c, &Counter::run, i);
        tlog("done executing #"<<i);
    }
    
    ThreadBase::sleep(3000);
    
    tlog("Destroying Pool");
    delete pool;
}

#endif
