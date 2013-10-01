#include "IO/Structure/Line/LineWriter.h"

LineWriter::LineWriter(InputOutputCapable& dv, std::string d):
        device(dv), delim(d) {
    
}

LineWriter::~LineWriter(){
    
}

int LineWriter::writeLine(const std::string& str){
    if (!writable())
        return -1;
    return device.write(str + delim);
}

int LineWriter::close(){
    return device.closeWriting();
}

bool LineWriter::writable() const {
    return device.writable();
}

