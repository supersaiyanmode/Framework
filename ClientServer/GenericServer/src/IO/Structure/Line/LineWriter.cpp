#include "IO/Structure/Line/LineWriter.h"

LineWriter::LineWriter(Connection& dv, std::string d):
        connection(dv), delim(d) {
    
}

int LineWriter::writeLine(const std::string& str){
    if (!writable())
        return -1;
    return connection.write(str + delim);
}

int LineWriter::close(){
    return connection.closeWriting();
}

bool LineWriter::writable() const {
    return connection.writable();
}
