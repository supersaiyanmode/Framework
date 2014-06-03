#ifndef JSONBASE_H
#define JSONBASE_H

#include <iostream>

enum JsonDataType {
    JSON_INTEGER,
    JSON_STRING,
    JSON_FLOAT,
    JSON_ARRAY,
    JSON_OBJECT
};

class JSONBase {
public:
    virtual ~JSONBase() {}
    virtual JsonDataType getType() const = 0;
    virtual std::string str() const = 0;
};

#endif
