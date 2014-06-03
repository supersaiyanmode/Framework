#ifndef PROTOCOL_EXCEPTION_H
#define PROTOCOL_EXCEPTION_H

#include <exception>
#include <string>

class ProtocolException : public std::exception {
protected:
    std::string msg;
public:
    ProtocolException(const std::string&);
    virtual ~ProtocolException() throw();
    
    virtual const char* what() const throw();
};


#endif
