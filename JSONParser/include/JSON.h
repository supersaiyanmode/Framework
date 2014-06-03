#ifndef JSON_H
#define JSON_H

#include <vector>
#include <map>

#include "JSONBase.h"
#include "JSONException.h"
#include "datatype/JSONObject.h"
#include "datatype/JSONArray.h"
#include "datatype/JSONPrimitive.h"

class JSON {
public:
    static int getInt(const JSONBase&);
	static double getDouble(const JSONBase&);
	static const std::string& getString(const JSONBase&);

	static const std::vector<JSONBase*>& getArray(const JSONBase&);
	static const std::map<std::string, JSONBase*>& getObject(const JSONBase&);
};

#endif
