#include "JSON.h"

int JSON::getInt(const JSONBase& obj) {
	const JSONPrimitive<int>& res = dynamic_cast<const JSONPrimitive<int>&>(obj);
	return res.get();
}

double JSON::getDouble(const JSONBase& obj) {
	const JSONPrimitive<double>& res = dynamic_cast<const JSONPrimitive<double>&>(obj);
	return res.get();
}

const std::string& JSON::getString(const JSONBase& obj) {
	const JSONPrimitive<std::string>& res = dynamic_cast<const JSONPrimitive<std::string>&>(obj);
	return res.get();
}

const std::vector<JSONBase*>& JSON::getArray(const JSONBase& obj) {
	const JSONArray& res = dynamic_cast<const JSONArray&>(obj);
	return res.get();
}

const std::map<std::string, JSONBase*>& JSON::getObject(const JSONBase& obj) {
	const JSONObject& res = dynamic_cast<const JSONObject&>(obj);
	return res.get();
}
