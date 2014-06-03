#ifndef JSONBASE_H
#define JSONBASE_H

#include <iostream>

#include "JSONException.h"

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

	virtual const JSONBase& operator[](const std::string&) const = 0;
	virtual JSONBase& operator[](const std::string&) = 0;

	virtual const JSONBase& operator[](unsigned int) const = 0;
	virtual JSONBase& operator[](unsigned int) = 0;
	
	template <typename T>
	const T& value() const;
};

#include "datatype/JSONPrimitive.h"

template <typename T>
const T& JSONBase::value() const {
	const JSONPrimitive<T>* res = dynamic_cast<const JSONPrimitive<T>*>(this);
	if (!res)
		throw JSONException("There's no value at current node.");
	return res->get();
}

#endif
