#include "BlockReader.h"
#include <iostream>
BlockReader::BlockReader(Connection& conn, const std::string& bb):
        backBuffer(bb), connection(conn){
    
}

std::string BlockReader::read(size_t length){
    if (!readable())
        return "";
    std::string ret;
    if (backBuffer.length() > 0){ //we already have some string
        std::string ret;
        if (backBuffer.length() >= length){
            ret = backBuffer.substr(0, length);
            if (backBuffer.length() == length)
                backBuffer.clear();
            else
                backBuffer = backBuffer.substr(length);
            return ret;
        } else {
            ret.swap(backBuffer);
            length -= ret.length();
        }
    }
    size_t bytesRead;
    std::string bytes;
    while (length > 0){
         bytesRead = connection.read(bytes);
         if (bytesRead <= 0){
            close();
            ret += bytes;
            break;
         }
         
         if (bytesRead <= length) { //we didn't over-read
             length -= bytesRead;
             ret += bytes;
         } else { //oops, over-read. Insert to backBuffer
             ret += bytes.substr(0, length);
             backBuffer = bytes.substr(length);
             break;
         } 
    }
    return ret;
}


bool BlockReader::readable() const {
    return connection.readable();
}

int BlockReader::close(){
    return connection.closeReading();
}

std::string BlockReader::getBackBuffer() const{
    return backBuffer;
}
