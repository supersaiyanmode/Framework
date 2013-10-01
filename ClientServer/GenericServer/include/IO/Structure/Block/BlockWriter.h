#ifndef BLOCK_WRITER_H
#define BLOCK_WRITER_H

#include <string>

#include "../../InputOutputCapable.h"

class BlockWriter {
    InputOutputCapable& device;
public:
    BlockWriter(InputOutputCapable&);
    virtual ~BlockWriter();
    
    virtual int write(const std::string&);
    virtual int close();
    virtual bool writable() const;
};


#endif
