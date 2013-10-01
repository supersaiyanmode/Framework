#ifndef SOCKET_EXCEPTION_H
#define SOCKET_EXCEPTION_H
#include <exception>
#include <string>
#include "../InputOutputCapable.h"

class SocketException : public IOException {
public:
    SocketException(const std::string&);
    virtual ~SocketException() throw();
    
    virtual const char* what() const throw();
};

class SocketWriteException: public WriteException {
public:
    SocketWriteException(const std::string&);
    virtual const char* what() const throw();
    virtual ~SocketWriteException() throw();
};

class SocketReadException: public ReadException {
public:
    SocketReadException(const std::string&);
    virtual const char* what() const throw();
    virtual ~SocketReadException() throw();
};
#endif
