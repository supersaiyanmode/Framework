#include <algorithm>
#include <iostream>

#include "SocketIO/Socket.h"

#ifdef WIN32
    WSADATA wsaData;
    int dummy = WSAStartup(MAKEWORD(2,2), &wsaData);
    int read_(PLATFORM_SOCKET sock, char* arr, int len){
        return recv(sock, arr,len,0);
    }
    int write_(PLATFORM_SOCKET sock, const char* arr, int len){
        return send(sock,arr, len, 0);
    }
    int close_(PLATFORM_SOCKET sock){
        return closesocket(sock);
    }
    #define socklen_t int
#else
    int read_(PLATFORM_SOCKET sock, char* arr, int len){
        return ::recv(sock, arr,len,0);
    }
    int write_(PLATFORM_SOCKET sock, const char* arr, int len){
        return ::send(sock,arr, len,0);
    }
    int close_(PLATFORM_SOCKET sock){
        return ::close(sock);
    }
#endif 

Socket::Socket(PLATFORM_SOCKET sock, int read, int write):
        writeActive(false), readActive(false),
        socket(sock), 
        state(sock>0? INITIALISED : UNINITIALISED) {
    if (sock < 0)
        throw SocketException("Unable to open a socket");
    
    if (read > 0)
        readActive = !!read;
    if (write > 0)
        writeActive = !!write;
}

Socket::Socket(const Socket& other): writeActive(other.writeActive),
                        readActive(other.readActive),
                        socket(other.socket) {
}

Socket& Socket::operator=(const Socket& other){
    if (this == &other)
        return *this;
    this->socket = other.socket;
    this->writeActive = other.writeActive;
    this->readActive = other.readActive;
    return *this;
}

Socket::operator PLATFORM_SOCKET(){
    return socket;
}

Socket::~Socket(){
    
}

void Socket::setIOStatus(int read, int write){ //-1 to retain state, 0/1 to set
    if (write >= 0)
        writeActive = !!write;
    if (read >= 0)
        readActive = !!read;
    
    if (!writeActive && !readActive){
        state = CLOSED;
        close_(this->socket);
    }else
        state = IO_READY;
}

void Socket::initialise(){
    
}

int Socket::write(const char* buf, int len){
    if (!writeActive)
        throw SocketWriteException("Socket not ready for writing");
    int res = write_(this->socket, buf, len); 
    if (res < 0){
        //EOF or error when <0
        if (res == 0) {
            setIOStatus(0,0);
            return 0;
        } else {
            setIOStatus(-1,0);
            throw SocketWriteException("Error encountered while writing");
        }
    }
    return res;
}

int Socket::write(const std::vector<char>& vec){
    return write(&vec[0], vec.size());
}

int Socket::write(const std::string& str){
    try {
        return write(&str[0], str.length());
    } catch (SocketWriteException ex) {
        std::cout<<"Exception: "<<ex.what()<<std::endl;
        throw;
    }
}


int Socket::read(char* buf, int len){
    if (!readActive)
        throw SocketReadException("Socket not ready for reading");
    int res = read_(this->socket, buf, len);
    if (res <= 0){
        //EOF or error when <0
        if (res == 0){
            setIOStatus(0,0);
            return 0;
        } else {
            setIOStatus(0,-1);
            throw SocketReadException("Error encountered while reading");
        }
    }
    return res;
}

int Socket::read(std::vector<char>& vec, int len){
    char *buf = new char[len];
    int res = read(buf, len);
    if (res > 0)
        vec = std::vector<char>(buf, buf+res);
    delete[] buf;
    return res;
}

int Socket::read(std::string& str, int len){
    std::vector<char> vec;
    vec.reserve(len);
    int res;
    try{
        res = read(vec,len);   
    } catch (SocketException ex){
        std::cout<<"Exception: "<<ex.what()<<std::endl;
        throw;
    }
    str = std::string(vec.begin(), vec.end());
    return res;
}


int Socket::closeReading(){
    setIOStatus(0,-1);
    return 0;
}

int Socket::closeWriting(){
    setIOStatus(-1,0);
    return 0;
}

int Socket::close(){
    setIOStatus(0,0);
    return 0;
}

bool Socket::readable() const {
    return readActive;
}

bool Socket::writable() const {
    return writeActive;
}
