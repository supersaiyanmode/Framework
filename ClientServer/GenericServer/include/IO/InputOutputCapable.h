#ifndef INPUTOUTPUTCAPABLE_H
#define INPUTOUTPUTCAPABLE_H

#include <vector>
#include <string>
#include <exception>

class InputOutputCapable {
public:
    virtual int write(const char*, int)=0;
    virtual int write(const std::vector<char>&)=0;
    virtual int write(const std::string&)=0;

    virtual int read(char*, int)=0;
    virtual int read(std::vector<char>&, int=8192)=0;
    virtual int read(std::string&, int=8192)=0;
    
    virtual int closeReading()=0;
    virtual int closeWriting()=0;
    
    virtual bool writable() const = 0;
    virtual bool readable() const = 0;
};

class IOException : public std::exception {
protected:
    std::string msg;
public:
    IOException(const std::string&);
    virtual ~IOException() throw();
    
    virtual const char* what() throw();
};

class ReadException: public IOException {
public:
    ReadException(const std::string&);
    virtual ~ReadException() throw();
    
    virtual const char* what() throw();
};


class WriteException: public IOException {
public:
    WriteException(const std::string&);
    virtual ~WriteException() throw();
    
    virtual const char* what() throw();
};

#endif
