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


const JSONBase& JSONArray::operator[](const std::string&) const {
	throw JSONException("Not a dictionary.");
}

JSONBase& JSONArray::operator[](const std::string&) {
	throw JSONException("Not a dictionary.");
}

const JSONBase& JSONArray::operator[](unsigned int index) const {
	if (index >= array.size())
		throw JSONException("Index out of bounds.");
	return *(array.at(index));
}

JSONBase& JSONArray::operator[](unsigned int index) {
	if (index >= array.size())
		throw JSONException("Index out of bounds.");
	return *(array.at(index));
}

const std::vector<JSONBase*>& JSONArray::get() const {
	return array;
}

JSONArray::~JSONArray() {
	for (std::vector<JSONBase*>::const_iterator it=array.begin();
			it != array.end(); it++) {
		delete *it;
	}
}
