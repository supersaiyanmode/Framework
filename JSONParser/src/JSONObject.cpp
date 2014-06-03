#include <sstream>
#include <iterator>
#include "datatype/JSONObject.h"


std::string JSONObject::str() const {
	std::stringstream ss;
	ss<<"{";
	for (std::map<std::string, JSONBase*>::const_iterator it=dictionary.begin();
			it != dictionary.end(); it++) {
		ss<<'\"'<<it->first<<"\": "<<it->second->str();
		if (std::next(it) != dictionary.end())
			ss<<", ";
	}
	ss<<"}";
	return ss.str();
}


JSONObject::~JSONObject() {
	for (std::map<std::string, JSONBase*>::const_iterator it=dictionary.begin();
			it != dictionary.end(); it++) {
		delete it->second;
	}
}
