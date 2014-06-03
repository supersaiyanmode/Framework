#include <sstream>

#include "datatype/JSONArray.h"


std::string JSONArray::str() const {
	std::stringstream ss;
	ss<<"[";
	for (std::vector<JSONBase*>::const_iterator it=array.begin();
			it != array.end(); it++) {
		ss<<(*it)->str();
		if (std::next(it) != array.end())
			ss<<", ";
	}
	ss<<"]";
	return ss.str();
}

JSONArray::~JSONArray() {
	for (std::vector<JSONBase*>::const_iterator it=array.begin();
			it != array.end(); it++) {
		delete *it;
	}
}
