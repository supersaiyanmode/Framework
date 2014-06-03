#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "JSONBase.h"

enum JSONObjectType {NOTHING=-1, OBJECT=1, ARRAY=2, STRING=3, NUMBER=4, ERROR=5};    


class JSONParser {
    const std::string& jsonStr;
    std::string::const_iterator pos;
    JSONBase* object;
    
    bool noEof();
    bool ignoreWhitespace();
    
    bool consumeChar(char c);
    
    void markString(std::string::const_iterator start, std::string::const_iterator end, 
                    std::string::const_iterator pos1, std::string::const_iterator pos2);
    
    void printError(const std::string& msg);
    
    JSONObjectType getNextJSONObjectType();

    JSONObjectType parseNumber(JSONBase** object);
    
    JSONObjectType parseString(JSONBase** object);
    
    JSONObjectType parseObject(JSONBase** object);
    
    JSONObjectType parseArray(JSONBase** object);
    
    JSONObjectType consumeJSONValue(JSONBase** object);
    
public:
    
    JSONParser(const std::string& s);
    
    JSONBase* get();
};

#endif
