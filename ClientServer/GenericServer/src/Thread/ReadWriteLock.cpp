#include "Thread/ReadWriteLock.h"

ReadWriteLock::ReadWriteLock() {
	lock = Mutex::createMutex();
	read = Condition::createCondition(lock);
	write = Condition::createCondition(lock);
	
	readers = writers = readWaiters = writeWaiters = 0;
}

ReadWriteLock::~ReadWriteLock() {
	delete read;
	delete write;
	delete lock;
}

void ReadWriteLock::lockRead() {
	lock->acquire();
	if (writers || writeWaiters) {
        readWaiters++;
        do {
			read->wait();
        } while (writers || writeWaiters);
        readWaiters--;
    }
    readers++;
    lock->release();
}

void ReadWriteLock::unlockRead() {
	lock->acquire();
    readers--;
    if (writeWaiters)
		write->signal();
	lock->release();
}

void ReadWriteLock::lockWrite() {
	lock->acquire();
    if (readers || writers) {
        writeWaiters++;
        do {
			write->wait();
        } while (readers || writers);
        writeWaiters--;
    }
    writers = 1;
    lock->release();
}

void ReadWriteLock::unlockWrite() {
	lock->acquire();
	writers = 0;
    if (writeWaiters)
		write->signal();
    else if (readWaiters)
		read->broadcast();
    lock->release();
}
