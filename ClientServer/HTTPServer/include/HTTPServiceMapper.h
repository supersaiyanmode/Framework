#ifndef HTTP_SERVER_MAPPER_H
#define HTTP_SERVER_MAPPER_H

#include <map>
#include <string>

#include "HTTPEndPointHandler.h"
#include "HTTPServiceMapper.h"

class HTTPRequestProperty {
    HTTPMethod method;
    std::string relativeUrl;
public:
    HTTPRequestProperty(HTTPMethod, const std::string&);
    bool operator<(const HTTPRequestProperty&) const;
    bool operator ==(const HTTPRequestProperty&) const;
};

class HTTPServiceMapper {
    std::map<HTTPRequestProperty, HTTPEndPointHandler*> handlers;
public:
    HTTPServiceMapper();
    virtual ~HTTPServiceMapper();
    
    void registerHandler(const HTTPRequestProperty&, HTTPEndPointHandler*);
    void unregisterHandler(const HTTPRequestProperty&);
    
    
    HTTPEndPointHandler* getHTTPEndPointHandler(HTTPMethod, const std::string&) const;
};

#endif
