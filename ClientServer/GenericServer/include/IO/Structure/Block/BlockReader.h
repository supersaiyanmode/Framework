#ifndef BLOCK_READER_H
#define BLOCK_READER_H

#include <string>

#include "../../InputOutputCapable.h"

class BlockReader {
    std::string backBuffer;
    InputOutputCapable& device;
public:
    BlockReader(InputOutputCapable&, const std::string& = "");
    virtual ~BlockReader();
    
    virtual std::string read(size_t);
    virtual std::string getBackBuffer() const;
    virtual int close();
    virtual bool readable() const;
};

#endif
