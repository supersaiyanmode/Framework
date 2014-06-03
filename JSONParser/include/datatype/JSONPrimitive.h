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
    const T& get() const {
        return value;
    }
    
    std::string str() const;
    JsonDataType getType() const;
    
	const JSONBase& operator[](const std::string&) const {
	    throw JSONException("Access by key for a primitive.");
	}
	virtual JSONBase& operator[](const std::string&) {
	    throw JSONException("Access by key for a primitive.");
	}
	
	virtual const JSONBase& operator[](unsigned int) const {
	    throw JSONException("Access by key for a primitive.");
	}
	virtual JSONBase& operator[](unsigned int) {
	    throw JSONException("Access by key for a primitive.");
	}
	
    virtual ~JSONPrimitive() {
        
    }
};

template<typename T>
inline std::string JSONPrimitive<T>::str() const {
    std::stringstream ss;
    ss<<value;
    return ss.str();
}

template<>
inline std::string JSONPrimitive<std::string>::str() const {
    std::stringstream ss;
    ss<<'\"';
    ss<<value;
    ss<<'\"';
    return ss.str();
}

template<>
inline JsonDataType JSONPrimitive<int>::getType() const {
    return JSON_INTEGER;
}

template<>
inline JsonDataType JSONPrimitive<std::string>::getType() const {
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
