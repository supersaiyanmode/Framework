#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
#include <map>

class HTTPResponse {
    const static std::string m_version;
    int m_statusCode;
    std::string m_phrase;
    
    std::map<std::string, std::string> m_headers;
    std::string m_body;
    
    bool m_valid;
public:
    HTTPResponse();
    HTTPResponse(int, const std::string& = "");
    void setContentType(const std::string&);
    void write(const std::string&);
    std::string str();
};

#endif
