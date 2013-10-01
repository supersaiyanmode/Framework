#ifndef CONNECTION_H
#define CONNECTION_H

#include "../InputOutputCapable.h"
#include "SocketException.h" //Not required per se, but allows for "SocketException" to be caught without extra headers
#include "TCPSocket.h"
#include <algorithm>

class Connection : public InputOutputCapable {
    TCPSocket socket;
    std::pair<std::string, int> localEndPoint, remoteEndPoint;
    std::string localAddressStr_, remoteAddressStr_;
public:
    Connection();
    Connection(TCPSocket);
    virtual ~Connection();
    
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
    
    virtual std::pair<std::string, int> getLocalAddress() const;
    virtual std::pair<std::string, int> getRemoteAddress() const;

    virtual std::string localAddressStr() const;
    virtual std::string remoteAddressStr() const;
    
    static Connection open(const std::string&, int);
};

#endif
