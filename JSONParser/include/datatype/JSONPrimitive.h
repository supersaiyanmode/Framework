#ifndef JSON_PRIMITIVE_H
#define JSON_PRIMITIVE_H

#include <string>
#include <sstream>
#include "JSONBase.h"

template<typename T>
class JSONPrimitive: public JSONBase {
    T value;
    
public:
    JSONPrimitive(const T& val) : value(val){
        
    }
    const T& get() {
        return value;
    }
    
    std::string str() const;
    JsonDataType getType() const;
    
    ~JSONPrimitive() {
        
    }
};

template<typename T>
std::string JSONPrimitive<T>::str() const {
    std::stringstream ss;
    ss<<value;
    return ss.str();
}

template<>
std::string JSONPrimitive<std::string>::str() const {
    std::stringstream ss;
    ss<<'\"';
    ss<<value;
    ss<<'\"';
    return ss.str();
}

template<>
JsonDataType JSONPrimitive<int>::getType() const {
    return JSON_INTEGER;
}

template<>
JsonDataType JSONPrimitive<std::string>::getType() const {
    return JSON_STRING;
}
/*
template<class std::string>
const std::string& JSONPrimitive<T>::str() const {
    std::stringstream ss;
    ss<<'\"';
    ss<<value;
    ss<<'\"';
    return ss.str();
}
*/

#endif
