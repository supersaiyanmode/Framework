#ifndef BLOCK_READER_H
#define BLOCK_READER_H

#include <string>

#include "IO/SocketIO/Connection.h"

class BlockReader {
    std::string backBuffer;
    Connection& connection;
public:
    BlockReader(Connection&, const std::string& = "");
    std::string read(size_t);
    std::string getBackBuffer() const;
    int close();
    bool readable() const;
};


#endif