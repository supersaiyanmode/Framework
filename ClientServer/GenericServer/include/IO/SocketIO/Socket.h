#ifndef SOCKET_H
#define SOCKET_H

#ifdef WIN32
    #include <windows.h>
    #include <winsock2.h>
    #define PLATFORM_SOCKET SOCKET
#else
    #include <unistd.h>
    #include <sys/types.h> 
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #define PLATFORM_SOCKET int
#endif 
#include <vector>
#include <string>
#include "SocketException.h"
#include "../InputOutputCapable.h"

enum SocketState {
    UNINITIALISED,
    INITIALISED,
    IO_READY,
    CLOSED
};

class Socket : public InputOutputCapable {
    bool writeActive, readActive;
protected:
    void setIOStatus(int=-1, int=-1);
    PLATFORM_SOCKET socket;
    SocketState state;
    Socket(PLATFORM_SOCKET, int=-1, int=-1);
public:
    Socket(const Socket&);
    virtual Socket& operator=(const Socket&);
    virtual operator PLATFORM_SOCKET();
    virtual ~Socket();
    
    virtual void initialise();
    
    virtual int write(const char*, int);
    virtual int write(const std::vector<char>&);
    virtual int write(const std::string&);

    virtual int read(char*, int);
    virtual int read(std::vector<char>&, int=8192);
    virtual int read(std::string&, int=8192);
    
    virtual int closeReading();
    virtual int closeWriting();
    virtual int close();
    
    virtual bool readable() const;
    virtual bool writable() const;
    
};

#endif
