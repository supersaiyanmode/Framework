#include <iostream>

#include "Structure/Line/LineReader.h"

LineReader::LineReader(Connection& dv, std::string d):
        connection(dv), delim(d){
    
}

std::string LineReader::readLine(){
    if (!readable())
        return "";
    
    size_t pos;
    if ((pos=backBuffer.find(delim)) != std::string::npos){ //we already have some string
        std::string ret;
        if (pos == 0)
            ret = "";
        else
            ret = backBuffer.substr(0, pos);
        backBuffer.erase(0, ret.length() + delim.length());
        return ret;
    } else {
        int readRes;
        size_t posDelim;
        std::string ret;
        std::string readStr;
        readStr.reserve(8192);
        while (true){
            readRes = connection.read(readStr, 8192);
            if (readRes > 0) {
                backBuffer += readStr;
            } else {
                close();
                ret = backBuffer;
                backBuffer = "";
                return ret;
            }
            
            if ((posDelim=backBuffer.find(delim)) != std::string::npos)
                break;
        }
        if (posDelim == 0)
            ret = backBuffer;
        else
            ret = backBuffer.substr(0, posDelim);
        backBuffer.erase(0, ret.length() + delim.length());
        return ret;
    }
}

bool LineReader::readable() const {
    return connection.readable();
}

int LineReader::close(){
    return connection.closeReading();
}

std::string LineReader::getBackBuffer() const{
    return backBuffer;
}
