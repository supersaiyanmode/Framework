#include "BlockWriter.h"

BlockWriter::BlockWriter(Connection& d):connection(d) {
    
}

int BlockWriter::write(const std::string& s) {
    if (!writable())
        return -1;
    return connection.write(s);
}

int BlockWriter::close(){
    return connection.closeWriting();
}

bool BlockWriter::writable() const {
    return connection.writable();
}