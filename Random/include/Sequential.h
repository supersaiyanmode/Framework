#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include <string>

typedef std::string UniqueID;

class Sequential {
public:
    static UniqueID next();
};

#endif