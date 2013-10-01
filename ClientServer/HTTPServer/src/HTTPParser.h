#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include <map>

#include "IO/SocketIO/Connection.h"
#include "HTTPRequest.h"

class HTTPParser {
    HTTPRequest request;
    Connection& connection;
    std::string errorMessage;
public:
    HTTPParser(Connection& c);
    
    bool parse();
    HTTPRequest getRequest();
    
    static std::map<std::string, std::string> parseQueryString(std::string);
    static std::string decodeURIComponent(std::string);
};


inline HTTPRequest HTTPParser::getRequest() {
    return request;
}

#endif