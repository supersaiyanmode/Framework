#ifndef BLOCK_WRITER_H
#define BLOCK_WRITER_H

#include <string>

#include "IO/SocketIO/Connection.h"

class BlockWriter {
    Connection& connection;
public:
    BlockWriter(Connection&);
    int write(const std::string&);
    int close();
    bool writable() const;
};


#endif
