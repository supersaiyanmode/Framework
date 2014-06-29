#ifndef LINE_READER_H
#define LINE_READER_H

#include <string>

#include "SocketIO/Connection.h"

class LineReader {
    std::string backBuffer;
    Connection& connection;
    std::string delim;
public:
    LineReader(Connection&, std::string="\n");
    std::string readLine();
    int close();
    std::string getBackBuffer() const;
    bool readable() const;
    bool writable() const;
};

#endif
