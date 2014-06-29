#ifndef SOCKET_EXCEPTION_H
#define SOCKET_EXCEPTION_H
#include <exception>
#include <string>

class SocketException {
protected:
    std::string msg;
public:
    SocketException(const std::string&);
    virtual ~SocketException() throw();
    
    virtual const char* what() const throw();
};

class SocketWriteException : public SocketException {
public:
    SocketWriteException(const std::string&);
    virtual const char* what() const throw();
    virtual ~SocketWriteException() throw();
};

class SocketReadException : public SocketException {
public:
    SocketReadException(const std::string&);
    virtual const char* what() const throw();
    virtual ~SocketReadException() throw();
};
#endif
