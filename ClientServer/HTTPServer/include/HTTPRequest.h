#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <map>
#include <string>

#include "HTTPDefinitions.h"

class HTTPRequest {
    HTTPMethod m_method;
    HTTPEndPoint m_url;
    std::string m_version;
    std::map<std::string, std::string> m_queryMap;
    std::map<std::string, std::string> m_headers;
    std::string m_body;
    bool m_valid;
public:
    HTTPRequest();
    HTTPRequest(HTTPMethod, HTTPEndPoint, std::string, std::map<std::string, std::string>, 
                        std::map<std::string, std::string>, std::string);
    bool valid() const;
    
    HTTPMethod method() const;
    std::string version() const;
    HTTPEndPoint url() const;
    std::string body() const;
    std::map<std::string, std::string> queryMap() const;
    
    bool bodyPresent() const;
    int length() const;
};

#endif
