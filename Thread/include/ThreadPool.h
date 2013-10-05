#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>

#include "Thread.h"
#include "ThreadLogger.h"
#include "SynchronisedQueue.h"

#if 0
template <typename T, typename P>
struct ThreadStruct {
    T* object;
    void (T::*function)(P);
    P argument;
};
#endif

template <typename T, typename P>
class ThreadPool {
    SynchronisedQueue<ThreadStruct<T,P> >* queue;
    
    class WorkerThread {
        SynchronisedQueue<ThreadStruct<T,P> >* queue;
        Thread<WorkerThread,int>* thread;
        WorkerThread(SynchronisedQueue<ThreadStruct<T,P> >* q){
            static int last = 0;
            queue = q;
            thread = Thread<WorkerThread, int>::createThread(this, &WorkerThread::run);
            id = ++last;
        }
        
        WorkerThread(const WorkerThread&){}
        void operator=(const WorkerThread&){}
    public:
        bool running, active;
        int id;
        
        static WorkerThread* createWorkerThread(SynchronisedQueue<ThreadStruct<T,P> >* q){
            return new WorkerThread(q);
        }
        
        void start(){
            thread->start(0);
        }
        
        void run(int){
            //tlog("["<<id<<"] WorkerThread started!");
            active = false;
            running = true;
            while (running && queue->isActive()){
                //tlog("Inside while!");
                ThreadStruct<T,P> work;
                if (queue->timedPop(work, 300000)) {
                    active = true;
                    //tlog("["<<id<<"] Work given!");
                    (*(work.object).*(work.function))(work.argument);
                    active = false;
                }
            }
            running = false;
            //tlog("["<<id<<"] WorkerThread exited");
        }
        
        ~WorkerThread(){
            if (running){
                running = false;
                //thread->kill();
                thread->join();
            }
            delete thread;
        }
    };
    
    std::vector<WorkerThread*> threadPool;
    
    ThreadPool(int numWorkers, int queueSize) {
        queue = SynchronisedQueue<ThreadStruct<T,P> >::createSynchronisedQueue(queueSize);
        threadPool.reserve(numWorkers);
        for (int i=0; i<numWorkers; i++){
            WorkerThread* wt = WorkerThread::createWorkerThread(queue);
            threadPool.push_back(wt);
        }
    }
    
public:
    static ThreadPool* createThreadPool(int numWorkers=5, int queueSize=5){
        return new ThreadPool<T,P>(numWorkers, queueSize);
    }
    
    void start(){
        for (typename std::vector<WorkerThread*>::iterator it=threadPool.begin();
                    it!=threadPool.end(); it++){
                        
            (*it)->start();
        }
    }
    
    void execute(T* obj, void (T::*function)(P), P arg){
        ThreadStruct<T,P> ts = {obj, function, arg};
        queue->push(ts);
    }
    
    ~ThreadPool() {
        for (typename std::vector<WorkerThread*>::iterator it=threadPool.begin();
                    it!=threadPool.end(); it++){
            delete *it;
        }
        queue->destroy();
        delete queue;
        //tlog("ThreadPool @ "<<this<<" destroyed!");
    }
};

#endif
