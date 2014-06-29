#ifndef LINE_WRITER_H
#define LINE_WRITER_H

#include <string>

#include "SocketIO/Connection.h"

class LineWriter {
    std::string backBuffer;
    Connection& connection;
    std::string delim;
public:
    LineWriter(Connection&, std::string="\n");
    int writeLine(const std::string&);
    int close();
    bool writable() const;
};


#endif
