#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "datatype/JSONPrimitive.h"
#include "datatype/JSONArray.h"
#include "datatype/JSONObject.h"

#if 1
#define LOG(X) std::cout<<X<<std::endl;
#else
#define LOG(X)
#endif

class JSONParser {
    enum ObjectType {NOTHING=-1, OBJECT=1, ARRAY=2, STRING=3, NUMBER=4, ERROR=5};    
    
    const std::string& jsonStr;
    std::string::const_iterator pos;
    JSONBase* object;
    
    bool noEof() {
        return pos != jsonStr.end();
    }
    bool ignoreWhitespace() {
        if (noEof() && *pos > 32)
            return true;
        while (*(++pos) <= 32 && noEof());
        return noEof();
    }
    
    bool consumeChar(char c) {
        bool result = noEof() && *(pos++) == c;
        LOG("Parsed character: "<<c<<" at position: "<<pos - jsonStr.begin());
        return result;
    }
    
    void markString(std::string::const_iterator start, std::string::const_iterator end, 
                    std::string::const_iterator pos1, std::string::const_iterator pos2) {
        LOG(std::string(start,end));
        std::string::const_iterator cur = start;
        for (; cur<pos1; cur++)
            std::cout<<" ";
        std::cout<<"^";
        if (pos1 != pos2) {
            for (; cur<pos2; cur++)
                std::cout<<" ";
            std::cout<<"^";
        }
        std::cout<<"\n";
    }
    
    void printError(const std::string& msg) {
        std::cerr<<"Error: "<<msg<<"\n\tInvalid Character: "<<*pos<<" ("<<pos - jsonStr.begin()<<")\n";
        std::string::const_iterator start = pos - jsonStr.begin() > 10? pos - 10 : jsonStr.begin();
        std::string::const_iterator end = pos + 10 - jsonStr.end() <=0? pos + 10 : jsonStr.end();
        
        markString(start, end, pos, pos);
    }
    
    ObjectType getNextObjectType() {
        if (!ignoreWhitespace()) {
            printError("Encountered error while ignoring whitespace.");
            return ERROR;
        }
        switch (*pos) {
            case '\"':  return STRING;
            case '{' :  return OBJECT;
            case '[' :  return ARRAY;
            case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '0':
                        return NUMBER;
            default :
                printError("Expected a string, number, object, or an array.");
                return ERROR;
        }
    }

    ObjectType parseNumber(JSONBase** object) {
        if (!noEof() && getNextObjectType() != NUMBER)
            return ERROR;
        std::string::const_iterator start = pos;
        LOG("Start parsing number at: "<<pos - jsonStr.begin());
        while (++pos,noEof() && (*pos >= '0' && *pos <= '9'));
        std::string::const_iterator end = pos;
        std::stringstream ss(std::string(start,end));
        int num;
        ss>>num;
        
        LOG("Parsed Number: "<<std::string(start,end));
        LOG("Parsed number, now at: "<<pos - jsonStr.begin());
        
        *object = new JSONPrimitive<int>(num);
        return NUMBER;
    }
    
    ObjectType parseString(JSONBase** object) {
        if (*pos != '\"') {
            printError("Expected beginning of a string: '\"'");
            return ERROR;
        }
        ++pos;
        std::string::const_iterator start = pos;
        LOG("Start parsing string at: "<<pos - jsonStr.begin());
        while (noEof() && *(++pos) != '\"');
        std::string::const_iterator end = pos;
        ++pos;
        
        LOG("Parsed string: "<<std::string(start,end));
        LOG("Parsed string, now at: "<<pos - jsonStr.begin());
        
        *object = new JSONPrimitive<std::string>(std::string(start,end));
        return STRING;
    }
    
    ObjectType parseObject(JSONBase** object) {
        if (*pos != '{'){
            printError("Expected opening brace: {");
            return ERROR;
        }
        LOG("Start parsing for object from position: " <<pos - jsonStr.begin());
        ++ pos;
        std::map<std::string, JSONBase*> map;
        while (noEof()) {
            JSONBase *key, *value;
            if (!ignoreWhitespace()){
                printError("Encountered error while ignoring whitespace.");
                return ERROR;
            }
            if (*pos == '}') {
                consumeChar('}');
                break;
            }
            ObjectType keyType = getNextObjectType();
            if (keyType == STRING) {
                if (parseString(&key) == ERROR){
                    printError("Encountered error while parsing string.");
                    return ERROR;
                }
                LOG("Key is of type: String");
            } else {
                printError("Expected either a string or a number.");
                return ERROR;
            }
            
            if (!ignoreWhitespace()) {
                printError("Encountered error while ignoring whitespace.");
                return ERROR;
            }
                
            if (!consumeChar(':')) {
                printError("Expected a ':'");
                return ERROR;
            }
            if (consumeJSONValue(&value) == ERROR){ //***
                printError("Encountered error while parsing JSON value.");
                return ERROR;
            }
            if (!ignoreWhitespace()){
                printError("Encountered error while ignoring whitespace.");
                return ERROR;
            }
            
            map[dynamic_cast<JSONPrimitive<std::string>* >(key)->get()] = value;
            
            if (*pos == '}') {
                consumeChar('}');
                break;
            } else if (*pos == ',') {
                consumeChar(',');
            } else {
                printError("Expected either '}' or ','");
                return ERROR;
            }
        }
        *object = new JSONObject(map);
        LOG("Parsed an object ending at position: " <<pos - jsonStr.begin());
        return OBJECT;
    }
    
    ObjectType parseArray(JSONBase** object) {
        if (*pos != '[')
            return ERROR;
        LOG("Start parsing for array from position: " <<pos - jsonStr.begin());
        ++ pos;
        
        std::vector<JSONBase*> array;
        while (noEof()) {
            JSONBase *curObj;
            if (!ignoreWhitespace()) {
                printError("Encountered error while ignoring whitespace.");
                return ERROR;
            }
            if (*pos == ']') {
                consumeChar(']');
                break;
            }
            ObjectType keyType = getNextObjectType();
            switch (keyType) {
                case STRING:
                    if (parseString(&curObj) == ERROR){
                        printError("Encountered error while parsing string.");
                        return ERROR;
                    }
                    break;
                case NUMBER:
                    if (parseNumber(&curObj) == ERROR) {
                        printError("Encountered error while parsing number.");
                        return ERROR;
                    }
                    break;
                case OBJECT:
                    if (parseObject(&curObj) == ERROR) {
                        printError("Encountered error while parsing object.");
                        return ERROR;
                    }
                    break;
                case ARRAY:
                    if (parseArray(&curObj) == ERROR) {
                        printError("Encountered error while parsing array.");
                        return ERROR;
                    }
                    break;
                default:
                    printError("Expected a string, number, object or an array.");
                    return ERROR;
            }
            if (!ignoreWhitespace()){
                printError("Encountered error while ignoring whitespace.");
                return ERROR;
            }
            array.push_back(curObj);
            
            if (*pos == ']') {
                consumeChar(']');
                break;
            } else if (*pos == ',') {
                consumeChar(',');
            } else {
                printError("Expected either ']' or ','");
                return ERROR;
            }
        }
        *object = new JSONArray(array);
        LOG("Parsed an array ending at position: " <<pos - jsonStr.begin());
        return ARRAY;
    }
    
    ObjectType consumeJSONValue(JSONBase** object) {
        ObjectType nextType = getNextObjectType();
        LOG("Next JSONValue type"<<nextType);
        switch(nextType) {
            case OBJECT:    return parseObject(object);
            case ARRAY:     return parseArray(object);
            case STRING:    return parseString(object);
            case NUMBER:    return parseNumber(object);
            default:
                printError("Expected either an object or an array");
                return ERROR;
        }
    }
    
public:
    
    JSONParser(const std::string& s): jsonStr(s), pos(jsonStr.begin()) {
        if (consumeJSONValue(&object) == ERROR) {
            printError("Encountered an error while parsing.");
        }
    }
    
    JSONBase* get() {
        return object;
    }
};

int main() {
    std::cout<<"Hello..\n";
    std::stringstream ssIn;
    ssIn<<std::cin.rdbuf();
    std::cout<<"done\n";
    LOG("Parsing: "<<ssIn.str()<<std::endl<<std::endl);
    JSONParser j(ssIn.str());
    std::cout<<j.get()->str()<<std::endl;
    return 0;
}
