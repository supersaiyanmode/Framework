#ifndef LINE_READER_H
#define LINE_READER_H

#include <string>

#include "../../InputOutputCapable.h"

class LineReader {
    std::string backBuffer;
    InputOutputCapable& device;
    std::string delim;
public:
    LineReader(InputOutputCapable&, std::string="\n");
    virtual ~LineReader();
    
    virtual std::string readLine();
    virtual int close();
    virtual std::string getBackBuffer() const;
    virtual bool readable() const;
};


#endif
