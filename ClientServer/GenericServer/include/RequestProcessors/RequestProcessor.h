#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H

#include "SocketIO/Connection.h"

class RequestProcessor {
protected:
    virtual void initialise() = 0;
    virtual void processRequest(Connection)=0;
};

#endif
