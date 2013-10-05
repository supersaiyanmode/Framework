#ifndef READ_WRITE_LOCK_H
#define READ_WRITE_LOCK_H

#include "Mutex.h"
#include "Condition.h"

class ReadWriteLock {
	int readers;
	int writers;
	int readWaiters;
	int writeWaiters;
	
	Mutex* lock;
	Condition *read, *write;
    
	ReadWriteLock();
public:
    static ReadWriteLock* createReadWriteLock();
	~ReadWriteLock();
	
	void lockRead();
	void unlockRead();
	void lockWrite();
	void unlockWrite();
};



//INLINE FUNCTIONS
inline ReadWriteLock* ReadWriteLock::createReadWriteLock(){
    return new ReadWriteLock();
}
#endif