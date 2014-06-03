#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <map>

#include "JSONBase.h"

class JSONObject : public JSONBase {
    std::map<std::string, JSONBase*> dictionary;
    
public:
    JSONObject(std::map<std::string, JSONBase*> d): dictionary(d) {}
    
	JsonDataType getType() const {
		return JSON_OBJECT;
	}
	
	std::string str() const;
	
	const JSONBase& operator[](const std::string&) const;
	virtual JSONBase& operator[](const std::string&);
	
	virtual const JSONBase& operator[](unsigned int) const;
	virtual JSONBase& operator[](unsigned int);
	
	virtual const std::map<std::string, JSONBase*>& get() const;
		
	~JSONObject();
};

#endif
