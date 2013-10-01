#include <algorithm>
#include <sstream>

#include "HTTPRequest.h"
#include "StringUtils.h"


HTTPRequest::HTTPRequest(): m_valid(false) {}

HTTPRequest::HTTPRequest(HTTPMethod m, HTTPEndPoint url, std::string version,
        std::map<std::string, std::string> queryMap, 
        std::map<std::string, std::string> headers, std::string body):
        m_method(m), m_url(url), m_version(version), m_queryMap(queryMap), m_body(body), m_valid(true) {
    for (std::map<std::string, std::string>::const_iterator it=headers.begin(); it!=headers.end(); it++) {
        m_headers[StringUtils::toLower(it->first)] = it->second;
    }
}


bool HTTPRequest::bodyPresent() const {
    return length() != 0;
}

int HTTPRequest::length() const {
    std::map<std::string, std::string>::const_iterator it = m_headers.find("content-length");
    if (it == m_headers.end())
        return 0;
    std::stringstream ss(it->second);
    int length;
    ss>>length;
    return length;
}

HTTPMethod HTTPRequest::method() const {
    return m_method;
}

std::string HTTPRequest::version() const {
    return m_version;
}

HTTPEndPoint HTTPRequest::url() const {
    return m_url;
}

std::string HTTPRequest::body() const {
    return m_body;
}

bool HTTPRequest::valid() const {
    return m_valid;
}

std::map<std::string, std::string> HTTPRequest::queryMap() const {
    return m_queryMap;
}
