#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <vector>
#include "JSONBase.h"

class JSONArray: public JSONBase {
	std::vector<JSONBase*> array;

public:
	JSONArray(std::vector<JSONBase*> arr): array(arr) {}

	JsonDataType getType() const {
		return JSON_ARRAY;
	}
	
	std::string str() const;

	~JSONArray();
};

#endif
