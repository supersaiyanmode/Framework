#include "IO/InputOutputCapable.h"

IOException::IOException(const std::string& m): msg(m) {
    
}

IOException::~IOException() throw(){
    
}

const char* IOException::what() throw() {
    return ("IOException: " + msg).c_str();
}


ReadException::ReadException(const std::string& m): IOException(m) {
    
}

ReadException::~ReadException() throw(){
    
}
    
const char* ReadException::what() throw() {
    return ("Read Exception: " + msg).c_str();
}


WriteException::WriteException(const std::string& m): IOException(m) {
    
}

WriteException::~WriteException() throw(){
    
}
    
const char* WriteException::what() throw() {
    return ("Write Exception: " + msg).c_str();
}