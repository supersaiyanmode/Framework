#ifndef THREAD_H
#define THREAD_H

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif
#include <iostream>
#include <ctime>
class ThreadBase {
public:
    static void sleep(int);    
};

template <typename T, typename P>
struct ThreadStruct {
    T* object;
    void (T::*function)(P);
    P argument;
    
    void* thread;
};

template <typename T, typename P>
class Thread : public ThreadBase {
    bool exited;
    
    Thread(const Thread<T,P>& other): object(other.object),
            function(other.function), thread(other.thread) {
        
    }
    
    void operator=(const Thread<T,P>& rhs) {
    }
    
    Thread(T* obj, void (T::*fn)(P)):object(obj), function(fn) {
        
    }
    
public:
    
    static Thread<T,P>* createThread(T* obj, void (T::*fn)(P)) {
        return new Thread<T,P>(obj, fn);
    }
    
    void start(const P& arg){
        exited = false;
        ThreadStruct<T,P> ts = {object, function, arg, (void*)this};
        ThreadStruct<T,P>* threadStruct = new ThreadStruct<T,P>(ts);
        //std::cout<<"About to fork!\n";
    #if WIN32
        thread = CreateThread(0, 0, createThread, (void*)threadStruct, 0, 0);
    #else
        pthread_create(&thread, NULL, createThread, (void*)threadStruct);
    #endif
    }
    
    void join(){
        if (exited)
            return;
    #if WIN32
        ::WaitForSingleObject(thread, INFINITE);
    #else
        pthread_join(thread,NULL);
    #endif
        exited = true;
    }
    
    void kill(){
        if (exited)
            return;
    #if WIN32
        ::TerminateThread(thread, 0);
    #else
        pthread_cancel(thread);
    #endif
        exited = true;
    }

    ~Thread(){
        if (!exited)
            kill();
    }
private:
    T* object;
    void (T::*function)(P);
    
#ifdef WIN32
    HANDLE    thread;
    static DWORD createThread(void* arg){
#else
    pthread_t thread;
    static void* createThread(void* obj){
#endif
        ThreadStruct<T,P>& data = *(ThreadStruct<T,P>*)(obj);
        P param(data.argument);
        T* object = data.object;
        void (T::*function)(P) = data.function;
        Thread<T,P>* thread =  (Thread<T,P>*)data.thread;
        delete &data;
        
        (*object.*function)(param);
        thread->exited = true;
        return 0;
    }
};

#endif // THREAD_H
