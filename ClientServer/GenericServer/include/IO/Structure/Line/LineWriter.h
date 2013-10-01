#ifndef LINE_WRITER_H
#define LINE_WRITER_H

#include <string>

#include "../../InputOutputCapable.h"

class LineWriter {
    std::string backBuffer;
    InputOutputCapable& device;
    std::string delim;
public:
    LineWriter(InputOutputCapable&, std::string="\n");
    virtual ~LineWriter();
    
    virtual int writeLine(const std::string&);
    virtual int close();
    virtual bool writable() const;
};

#endif
