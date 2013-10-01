#include "IO/Structure/Block/BlockWriter.h"

BlockWriter::BlockWriter(InputOutputCapable& d):device(d) {
    
}

BlockWriter::~BlockWriter() {
    
}

int BlockWriter::write(const std::string& s) {
    if (!writable())
        return -1;
    return device.write(s);
}

int BlockWriter::close(){
    return device.closeWriting();
}

bool BlockWriter::writable() const {
    return device.writable();
}

