#include <sstream>
#include <iterator>
#include "datatype/JSONObject.h"


std::string JSONObject::str() const {
	std::stringstream ss;
	ss<<"{";
	for (std::map<std::string, JSONBase*>::const_iterator it=dictionary.begin();
			it != dictionary.end(); it++) {
		ss<<'\"'<<it->first<<"\": "<<it->second->str();
		if (&*it != &*dictionary.rbegin())
			ss<<", ";
	}
	ss<<"}";
	return ss.str();
}

const JSONBase& JSONObject::operator[](const std::string& key) const {
	std::map<std::string, JSONBase*>::const_iterator it = dictionary.find(key);
	if (it == dictionary.end())
		throw JSONException("Key does not exist.");
	return *(it->second);
}

JSONBase& JSONObject::operator[](const std::string& key) {
	std::map<std::string, JSONBase*>::const_iterator it = dictionary.find(key);
	if (it == dictionary.end())
		throw JSONException("Key does not exist.");
	return *(it->second);
}

const JSONBase& JSONObject::operator[](unsigned int) const {
	throw JSONException("Not a dictionary.");
}

JSONBase& JSONObject::operator[](unsigned int) {
	throw JSONException("Not a dictionary.");
}

const std::map<std::string, JSONBase*>& JSONObject::get() const{
	return dictionary;
}

JSONObject::~JSONObject() {
	for (std::map<std::string, JSONBase*>::const_iterator it=dictionary.begin();
			it != dictionary.end(); it++) {
		delete it->second;
	}
}
