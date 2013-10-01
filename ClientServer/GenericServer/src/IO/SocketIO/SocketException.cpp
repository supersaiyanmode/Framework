#include "IO/SocketIO/SocketException.h"

SocketException::SocketException(const std::string& str): IOException(str) {
    
}

SocketException::~SocketException() throw(){
    
}

const char* SocketException::what() const throw() {
    return ("SocketException: " + msg).c_str();
}


SocketWriteException::SocketWriteException(const std::string& str):WriteException(str){
    
}
const char* SocketWriteException::what() const throw(){
    return ("SocketWriteException: " + msg).c_str();
}

SocketWriteException::~SocketWriteException() throw(){
    
}


SocketReadException::SocketReadException(const std::string& str):ReadException(str){
    
}
const char* SocketReadException::what() const throw(){
    return ("SocketReadException: " + msg).c_str();
}

SocketReadException::~SocketReadException() throw(){
    
}